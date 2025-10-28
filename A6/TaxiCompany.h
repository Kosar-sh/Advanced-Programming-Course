#ifndef TAXICOMPANY_H
#define TAXICOMPANY_H

#include <iostream>
#include <vector>
#include <string>
#include "Mission.h"
#include "Driver.h"
using namespace std;

class TaxiCompany
{
private:
    vector<Mission *> missions;
    vector<Driver *> drivers;
    vector<int> finished_already;

public:
    void add_new_mission(Mission *new_one);
    void valid_mission_id(string mission_id);
    void valid_mission_time(long start_timestamp, long end_timestamp);
    void show_missions_all_info();
    void assign_mission_with_driver(string mission_id, string driver_id);
    void printing_completed_missions_for_this_driver(vector<Mission *> this_driver_missions,vector<int> finished_ones, string driver_id);
    int has_the_mission(string _id);
    void does_this_mission_add_before(string _id, string mission_id);
    void record_finished_projects(long start_timestamp, long end_timestamp, string driver_id, long distance);
    int already_have_this_driver(string id);
    void print_the_missions(vector<Mission *> missions_of_driver);
    void showing_all_missions_of_driver(string driver_id);
    void add_new_or_use_old_defined_driver(int mission_id, string driver_id, int founded_place);
    bool check_if_any_mission_finish(Mission *founded_mission,long this_mission_start_times, long start_timestamp, long end_timestamp, long distance);
    int find_driver_by_id(string id);
    bool validating_id_and_missions(string id);
    vector<int> sort_all_missions_by_time(vector<int> find_mission_indexes);
    vector<int> sort_missions_by_time(vector<long> time_stamps);
    vector<Mission *> all_of_driver_missions(string driver_id);
    vector<int> find_finished_missions_for_this_driver(vector<Mission *> this_driver_missions,long start_timestamp, long end_timestamp, long distance);
    vector<long> sort_starting_times_of_mission(vector<Mission *> this_driver_missions);
    vector<int> find_indexes_of_the_mission(vector<Mission *> missions_of_driver,vector<long> start_times);

};

#endif