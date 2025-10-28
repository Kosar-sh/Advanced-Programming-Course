#include "Processing.h"
#include <stdlib.h>
const string invalid_arguments = "INVALID_ARGUMENTS\n";
const string ok = "OK\n";
const char new_line = '\n';
const char space = ' ';
void Processing::add_time_mission(string input_information)
{
    try
    {
        validating_inputs(input_information);
        TimeMission *new_one = new TimeMission(mission_id, start_time_stamp, end_time_stamp, target, reward);
        taxi_company.add_new_mission(new_one);
        cout << ok;
    }
    catch (const exception &e)
    {
        cout << e.what();
    }
}

void Processing::add_distance_mission(string input_information)
{
    try
    {
        validating_inputs(input_information);
        DistanceMission *new_one = new DistanceMission(mission_id, start_time_stamp, end_time_stamp, target, reward);
        taxi_company.add_new_mission(new_one);
        cout << ok;
    }
    catch (const exception &e)
    {
        cout << e.what();
    }
}

void Processing::show_missions_status(string input_information)
{
    driver_id = input_information;
    try
    {
        taxi_company.showing_all_missions_of_driver(driver_id);
    }
    catch (const exception &e)
    {
        cout << e.what();
    }
}

vector<int> Processing::find_space_positions(string rest_remain)
{
    vector<int> space_pos;
    for (int i = 0; i < rest_remain.size(); i++)
    {
        if (rest_remain[i] == space)
            space_pos.push_back(i);
    }
    return space_pos;
}

void Processing::adding_missions_assign_first_vals(string rest_remain, vector<int> space_pos)
{
    mission_id = rest_remain.substr(0, space_pos[0]);
    start_time_stamp = stol(rest_remain.substr(space_pos[0] + 1, space_pos[1] - space_pos[0] - 1));
    end_time_stamp = stol(rest_remain.substr(space_pos[1] + 1, space_pos[2] - space_pos[1] - 1));
    target = stol(rest_remain.substr(space_pos[2] + 1, space_pos[3] - space_pos[2] - 1));
    reward = stol(rest_remain.substr(space_pos[3] + 1));
}

void Processing::read_adding_mission_info(string input_information)
{
    vector<int> space_pos = find_space_positions(input_information);
    if (space_pos.size() < 4)
        throw runtime_error(invalid_arguments);
    adding_missions_assign_first_vals(input_information, space_pos);
}

void Processing::add_count_mission(string input_information)
{
    try
    {
        validating_inputs(input_information);
        CountMission *new_one = new CountMission(mission_id, start_time_stamp, end_time_stamp, target, reward);
        taxi_company.add_new_mission(new_one);
        cout << ok;
    }
    catch (const std::exception &e)
    {
        cout << e.what();
    }
}

void Processing::assign_mission_with_chosen_driver(string input_information)
{
    try
    {
        read_assigning_info(input_information);
        taxi_company.assign_mission_with_driver(mission_id, driver_id);
    }
    catch (const exception &e)
    {
        cout << e.what();
    }
}

void Processing::recording_finished_ride(string input_information)
{
    try
    {
        read_record_ride_info(input_information);
        taxi_company.valid_mission_time(start_time_stamp, end_time_stamp);
        taxi_company.record_finished_projects(start_time_stamp, end_time_stamp, driver_id, distance);
    }
    catch (const exception &e)
    {
        cout << e.what();
    }
}

void Processing::read_record_ride_info(string input_information)
{
    vector<int> space_pos = find_space_positions(input_information);
    if (space_pos.size() < 3)
    {
        throw runtime_error(invalid_arguments);
    }
    adding_record_ride_first_vals(input_information, space_pos);
}

void Processing::read_assigning_info(string input_information)
{
    vector<int> space_pos = find_space_positions(input_information);
    if (space_pos.size() < 1)
        throw runtime_error(invalid_arguments);
    mission_id = (input_information.substr(0, space_pos[0]));
    driver_id = (input_information.substr(space_pos[0] + 1, space_pos[1] - space_pos[0] - 1));
}

void Processing::validating_inputs(string input_information)
{
    read_adding_mission_info(input_information);
    taxi_company.valid_mission_id(mission_id);
    taxi_company.valid_mission_time(start_time_stamp, end_time_stamp);
}

void Processing::adding_record_ride_first_vals(string rest_remain, vector<int> space_pos)
{
    start_time_stamp = stol(rest_remain.substr(0, space_pos[0]));
    end_time_stamp = stol(rest_remain.substr(space_pos[0] + 1, space_pos[1] - space_pos[0] - 1));
    driver_id = (rest_remain.substr(space_pos[1] + 1, space_pos[2] - space_pos[1] - 1));
    distance = stol(rest_remain.substr(space_pos[2] + 1));
}