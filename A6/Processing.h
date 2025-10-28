#ifndef PROCESSING_H
#define PROCESSING_H
#include <iostream>
#include <string>
#include <algorithm>

#include <vector>
#include "Mission.h"
#include "TaxiCompany.h"
using namespace std;

class Processing
{
private:
    TaxiCompany taxi_company;
    string mission_id,driver_id;
    long int start_time_stamp, end_time_stamp, target, reward,distance;
public:
    void add_time_mission(string input_information);
    void add_distance_mission(string input_information);
    void add_count_mission(string input_information);
    void assign_mission_with_chosen_driver(string input_information);
    void recording_finished_ride(string input_information);
    void show_missions_status(string input_information);
    void read_adding_mission_info(string input_information);
    void read_record_ride_info(string input_information);
    void read_assigning_info(string input_information);
    void adding_missions_assign_first_vals(string rest_remain, vector<int> space_pos);
    void adding_record_ride_first_vals(string rest_remain,vector<int> space_pos);
    void validating_inputs(string input_information);
    vector<int> find_space_positions(string rest_remain);
};
#endif