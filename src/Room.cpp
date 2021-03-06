//
// Created on 9/20/18.
//

#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include "../inc/Room.hpp"
#include <string>
#include <iostream>


Room::Room(rapidxml::xml_node<> *  room_node) {

    for(rapidxml::xml_node <> * node = room_node -> first_node(); node; node = node -> next_sibling())
    {
        std::string node_name = node -> name();

        if(node_name == "name") { this -> name_ = node -> value() ;}
        else if (node_name == "type") {this -> type_ = node -> value() ;}
        else if (node_name == "status") {this -> status_ = node -> value() ;}
        else if (node_name == "description") {this -> description_ = node -> value();}
        else if (node_name == "border"){
            std::string direction_name = node -> first_node("direction") -> value();
            std::string border_name = node -> first_node("name") -> value();

            this -> direction_to_room_[direction_name] = border_name;
        }
        else if (node_name == "trigger"){this -> triggers_.push_back(new Trigger(node));}
        else if (node_name == "item") {
            this -> items_names_.push_back(node -> value());
        }
        else if (node_name == "creature") {
            this -> creatures_names_.push_back(node -> value());
        }
        else if (node_name == "container") {
            this -> containers_names_.push_back(node -> value());
        }
    }

}


Room::~Room() {

}

ostream & operator<< (ostream& os, const Room& room)
{
    os << "Room: " << room.name_ << "\n";
    // os << "status: " << room.status_ << "\n";    
    // os << "description: " << room.description_ << "\n";  
    os << "Triggers: " ;
    for(Trigger * trigger: room.triggers_)
    {
        os << *trigger << "\n";
    }
    os << "Items: " ;
    for(auto item: room.items_names_)
    {
        os << item << "\n";
    }  
    os << "Containers: " ;
    for(auto container: room.containers_names_)
    {
        os << container << "\n";
    }  
    os << endl;
    return os;
}