//
// Created on 9/17/18.
//

#ifndef _TRIGGER_H_
#define _TRIGGER_H_
#include "../lib/rapidxml-1.13/rapidxml.hpp"
#include <string>
#include <vector>
#include "Condition.hpp"
// #include "GameWorld.hpp"

using namespace std;

class Trigger
{

  public:
    Trigger(rapidxml::xml_node<> *);
    Trigger(rapidxml::xml_node<> *, string); //Overloaded constructor
    Trigger(string);
    virtual ~Trigger();
    virtual bool IsActivated(string, GameWorld &);
    virtual bool Fire(GameWorld &);
    virtual bool is_disabled();

    string type_ = "single";
    string command_ = "";
    vector<Condition *> conditions_;
    vector<string> actions_;
    vector<string> messages_;
    friend ostream & operator<< (ostream&, const Trigger&);
  private:
    bool is_disabled_ = false;
};

#endif //_TRIGGER_H_
