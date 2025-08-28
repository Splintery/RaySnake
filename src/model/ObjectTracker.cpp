#include "ObjectTracker.h"
#include <ostream>
#include <iostream>

void ObjectTracker::addTo(std::string key)
{
    if (!tracker[key])
    {
        tracker[key] = 1;
    }
    else
    {
        tracker[key]++;
    }
}

void ObjectTracker::removeFrom(std::string key)
{
    if (!tracker[key])
    {
        std::cout << "ERROR: key[" << key << "] doesn't have an entry in tracker" << std::endl;
    }
    else
    {
        tracker[key]--;
    }
}

std::ostream &operator<<(std::ostream &out, const ObjectTracker &objt)
{
    for (std::map<std::string, int>::iterator itr = objt.tracker.begin(); itr != objt.tracker.end(); itr++)
    {
        out << "[" << itr->first << "]: " << itr->second << std::endl; 
    }
    return out;
}

