//
// Created 9/24/18.
//


#include "../inc/ConditionFactory.hpp"
#include "../inc/HasCondition.hpp"
#include "../inc/StatusCondition.hpp"


Condition* ConditionFactory::CreateCondition(rapidxml::xml_node<> *condition_node) {

    Condition * retVal = nullptr;

    rapidxml::xml_node<> * child_has_node = condition_node -> first_node("has");
    rapidxml::xml_node<> * child_status_node = condition_node -> first_node("status");

    if(child_has_node)
    {
        retVal =  new HasCondition(condition_node);
    }

    else if(child_status_node)
    {
        retVal =  new StatusCondition(condition_node);
    }

    return retVal;
}
