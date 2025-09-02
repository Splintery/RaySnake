#include "ObjectTracker.h"
#include <ostream>
#include <iostream>

std::map<std::string, int> ObjectTracker::tracker;

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

void ObjectTracker::printStatus()
{
    for (std::map<std::string, int>::iterator itr = tracker.begin(); itr != tracker.end(); itr++)
    {
        std::cout << "[" << itr->first << "]: " << itr->second << std::endl; 
    }
}

