#ifndef DRIVER_H
#define DRUVER_H
#include <iostream>
#include <vector>
#include <string>
#include "Mission.h"
using namespace std;
class Driver
{
private:
    vector<string> completed_missions;
    string driver_id;
    vector<string> missions;
    vector<Mission *> missions_assign;

public:
    Driver(string id, Mission *new_mission);
    void already_assign_mission(string mission_id);
    bool the_same_driver(string _id);
    void add_new_mission( Mission *new_mission);
    vector<Mission*> get_missions() { return missions_assign; }
};

#endif
