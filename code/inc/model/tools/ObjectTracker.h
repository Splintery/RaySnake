#ifndef OBJECTTRACKER_H
#define OBJECTTRACKER_H

#include <map>
#include <string>

class ObjectTracker {
private:
    static std::map<std::string, int> tracker;

public:
    static void addTo(std::string); // TODO call this method from every constructor
    static void removeFrom(std::string); // TODO call this method from every destructor
    static void printStatus();
};

#endif