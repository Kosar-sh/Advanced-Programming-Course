#include "Driver.h"

const string duplicate_driver_mission = "DUPLICATE_DRIVER_MISSION\n";

Driver::Driver(string id, Mission *new_mission)
{
    driver_id = id;
    Mission *new_one = new_mission->make_copy_of(new_mission->get_mission_id(), new_mission->get_start_timestamp(), new_mission->get_end_time_stamp(),
                                                 new_mission->get_target(), new_mission->get_reward_amount());
    missions_assign.push_back(new_one);
}

void Driver::already_assign_mission(string mission_id)
{
    for (int i = 0; i < missions_assign.size(); i++)
    {
        if (missions_assign[i]->has_the_same_id(mission_id))
        {
            throw runtime_error(duplicate_driver_mission);
        }
    }
}

bool Driver::the_same_driver(string _id)
{
    if (driver_id == _id)
    {
        return true;
    }
    return false;
}

void Driver::add_new_mission(Mission *new_mission)
{
    Mission *new_one = new_mission->make_copy_of(new_mission->get_mission_id(), new_mission->get_start_timestamp(), new_mission->get_end_time_stamp(), new_mission->get_target(), new_mission->get_reward_amount());
    missions_assign.push_back(new_one);
}
