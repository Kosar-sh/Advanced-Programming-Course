#include "TaxiCompany.h"
#include "Mission.h"
#include <algorithm>
const string duplicate_mission_id = "DUPLICATE_MISSION_ID\n";
const string invalid_arguments = "INVALID_ARGUMENTS\n";
const string mission_not_found = "MISSION_NOT_FOUND\n";
const string driver_mission_not_found = "DRIVER_MISSION_NOT_FOUND\n";
const string complete_mission_for_this_driver = "completed missions for driver";
const string mission_status = "missions status for driver";
const string ok = "OK\n";
const string space = " ";
const string semicolon = ":";
void TaxiCompany::add_new_mission(Mission *new_one)
{
    missions.push_back(new_one);
}

void TaxiCompany::valid_mission_id(string mission_id)
{
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i]->has_the_same_id(mission_id))
            throw runtime_error(duplicate_mission_id);
    }
}

void TaxiCompany::valid_mission_time(long start_timestamp, long end_timestamp)
{
    if (end_timestamp < start_timestamp)
        throw runtime_error(invalid_arguments);
}

void TaxiCompany::show_missions_all_info()
{
    for (int i = 0; i < missions.size(); i++)
    {
        missions[i]->show_the_missions();
    }
}

void TaxiCompany::assign_mission_with_driver(string mission_id, string driver_id)
{
    try
    {
        int mission = has_the_mission(mission_id);
        does_this_mission_add_before(driver_id, mission_id);
        int founded_place = already_have_this_driver(driver_id);
        add_new_or_use_old_defined_driver(mission, driver_id, founded_place);
        cout << ok;
    }
    catch (const std::exception &e)
    {
        cout << e.what();
    }
}

void TaxiCompany::printing_completed_missions_for_this_driver(vector<Mission *> this_driver_missions, vector<int> finished_ones, string driver_id)
{
    cout << complete_mission_for_this_driver << space << driver_id << semicolon << endl;
    for (int i = 0; i < finished_ones.size(); i++)
    {
        this_driver_missions[finished_ones[i]]->show_completed_missions();
        if (i != finished_ones.size() - 1)
            cout << endl;
    }
}

int TaxiCompany::has_the_mission(string _id)
{
    int mission = 0;
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i]->has_the_same_id(_id))
            return i;
    }
    if (mission == 0)
        throw runtime_error(mission_not_found);
    return mission;
}

void TaxiCompany::does_this_mission_add_before(string _id, string mission_id)
{
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i]->the_same_driver(_id))
            drivers[i]->already_assign_mission(mission_id);
    }
}

void TaxiCompany::record_finished_projects(long start_timestamp, long end_timestamp, string driver_id, long distance)
{
    if (validating_id_and_missions(driver_id))
    {
        vector<Mission *> this_driver_missions = all_of_driver_missions(driver_id);
        vector<int> finished_ones = find_finished_missions_for_this_driver(this_driver_missions, start_timestamp, end_timestamp, distance);
        printing_completed_missions_for_this_driver(this_driver_missions,finished_ones,driver_id);
    }
    else
        return;
}

vector<int> TaxiCompany::find_finished_missions_for_this_driver(vector<Mission *> this_driver_missions, long start_timestamp, long end_timestamp, long distance)
{
    vector<long> start_times = sort_starting_times_of_mission(this_driver_missions);
    vector<int> finished_ones;
    for (int i = 0; i < start_times.size(); i++)
    {
        for (int j = 0; j < this_driver_missions.size(); j++)
        {
            if (check_if_any_mission_finish(this_driver_missions[j], start_times[i], start_timestamp, end_timestamp, distance))
                finished_ones.push_back(j);
        }
    }
    return finished_ones;
}

vector<long> TaxiCompany::sort_starting_times_of_mission(vector<Mission *> this_driver_missions)
{
    vector<long> start_times;
    for (int i = 0; i < this_driver_missions.size(); i++)
    {
        start_times.push_back(this_driver_missions[i]->get_mission_start_timestamp());
    }
    sort(start_times.begin(), start_times.end());
    return start_times;
}

vector<int> TaxiCompany::find_indexes_of_the_mission(vector<Mission *> missions_of_driver, vector<long> start_times)
{
    vector<int> sorted_missions;
    for (int i = 0; i < start_times.size(); i++)
    {
        for (int j = 0; j < missions_of_driver.size(); j++)
        {
            if (missions_of_driver[j]->is_it_the_same_time(start_times[i]))
                sorted_missions.push_back(j);
        }
    }
    return sorted_missions;
}

int TaxiCompany::already_have_this_driver(string id)
{
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i]->the_same_driver(id))
            return i;
    }
    return -1;
}

void TaxiCompany::print_the_missions(vector<Mission *> missions_of_driver)
{
    vector<long> start_times = sort_starting_times_of_mission(missions_of_driver);
    vector<int> sorted_missions = find_indexes_of_the_mission(missions_of_driver, start_times);
    for (int i = 0; i < sorted_missions.size(); i++)
    {
        missions_of_driver[sorted_missions[i]]->show_the_missions();
        if (i != sorted_missions.size() - 1)
            cout << endl;
    }
}

void TaxiCompany::showing_all_missions_of_driver(string driver_id)
{
    int driver_pos = find_driver_by_id(driver_id);
    if (driver_pos == -1)
        throw runtime_error(driver_mission_not_found);
    vector<Mission *> missions_of_driver = drivers[driver_pos]->get_missions();
    if (missions_of_driver.size() == 0)
        throw runtime_error(driver_mission_not_found);
    cout << mission_status << space << driver_id << semicolon << endl;
    print_the_missions(missions_of_driver);
}

void TaxiCompany::add_new_or_use_old_defined_driver(int mission_id, string driver_id, int founded_place)
{
    if (founded_place == -1)
    {
        Driver *new_one = new Driver(driver_id, missions[mission_id]);
        drivers.push_back(new_one);
    }
    else
        drivers[founded_place]->add_new_mission(missions[mission_id]);
}

bool TaxiCompany::check_if_any_mission_finish(Mission *founded_mission, long this_mission_start_times, long start_timestamp, long end_timestamp, long distance)
{
    if (founded_mission->is_it_the_same_time(this_mission_start_times))
    {
        if (founded_mission->does_the_ride_end_this_mission(start_timestamp, end_timestamp, distance))
            return true;
    }
    return false;
}

int TaxiCompany::find_driver_by_id(string id)
{
    int driver_pos = -1;
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i]->the_same_driver(id))
            driver_pos = i;
    }
    return driver_pos;
}

vector<Mission *> TaxiCompany::all_of_driver_missions(string driver_id)
{
    vector<Mission *> missions_of_this_driver;
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i]->the_same_driver(driver_id))
        {
            missions_of_this_driver = drivers[i]->get_missions();
            break;
        }
    }
    return missions_of_this_driver;
}

bool TaxiCompany::validating_id_and_missions(string id)
{
    int flag = -1;
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i]->the_same_driver(id))
            flag = i;
    }
    if (flag == -1)
        return false;
    else
    {
        if (drivers[flag]->get_missions().size() == 0)
            return false;
    }
    return true;
}

vector<int> TaxiCompany::sort_all_missions_by_time(vector<int> find_mission_indexes)
{
    vector<long> start_times;
    for (int i = 0; i < find_mission_indexes.size(); i++)
        start_times.push_back(missions[find_mission_indexes[i]]->get_mission_start_timestamp());
    vector<int> ordered_by_time_missions = sort_missions_by_time(start_times);
    return ordered_by_time_missions;
}

vector<int> TaxiCompany::sort_missions_by_time(vector<long> start_times)
{
    sort(start_times.begin(), start_times.end());
    vector<int> time_order_mission;
    for (int l = 0; l < start_times.size(); l++)
    {
        for (int i = 0; i < missions.size(); i++)
        {
            if (missions[i]->is_it_the_same_time(start_times[l]))
                time_order_mission.push_back(i);
        }
    }
    return time_order_mission;
}
