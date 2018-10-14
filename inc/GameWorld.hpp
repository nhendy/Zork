//
// Created on 9/17/18.
//

#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include <vector>
#include "Creature.hpp"
#include "Container.hpp"
#include "Item.hpp"
#include "Room.hpp"
#include "InputHandler.hpp"


class GameWorld {

public:

    GameWorld();
    virtual ~GameWorld();

    std::map<string, Room*> rooms_;
    std::map<string, Item*> items_;
    std::map<string, Creature*> creatures_;
    std::map<string, Container*> containers_;
    std::map<string, Item*> inventor_;




//    void InitGameWorld();
//    void InitGameWorld();
    void GameLoop();

private:
    bool execute(string);
    bool is_overridden(string);
    InputHandler handler_;
    string current_room_;



};
#endif //_GAMEWORLD_H_
