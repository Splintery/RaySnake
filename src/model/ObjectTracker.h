#ifndef OBJECTTRACKER_H
#define OBJECTTRACKER_H

#include <map>
#include <string>

class ObjectTracker {
public:
    static std::map<std::string, int> tracker;

    void addTo(std::string); // TODO call this method from every constructor
    void removeFrom(std::string); // TODO call this method from every destructor
    
    friend std::ostream &operator<<(std::ostream &, const ObjectTracker &);
};

#endif