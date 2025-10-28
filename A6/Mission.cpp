#include "Mission.h"
using namespace std;
const string ongoing = "ongoing";
const string completed = "completed";
const string mission = "mission";
const string semicolon = ":";
const string invalid_arguments = "INVALID_ARGUMENTS\n";
const string str_end_timestamp = "end timestamp: ";
const string str_start_timestamp = "start timestamp: ";
const string str_status = "status: ";
const string str_reward = "reward: ";
const string not_finished = "-1";
const string space = " ";
Mission::Mission(string _mission_id, long _s_timestamp, long _e_timestamp, long _reward_amount)
{
    mission_id = _mission_id;
    start_timestamp = _s_timestamp;
    end_time_stamp = _e_timestamp;
    if (_reward_amount < 0)
    {
        throw runtime_error(invalid_arguments);
    }
    reward_amount = _reward_amount;
    status = ongoing;
}

Mission::Mission(const Mission &pre_one)
{
    mission_id = pre_one.mission_id;
    start_timestamp = pre_one.start_timestamp;
    end_time_stamp = pre_one.end_time_stamp;
    reward_amount = pre_one.reward_amount;
    status = pre_one.status;
}

void Mission::show_the_missions()
{
    cout << mission << space << mission_id << semicolon << endl;
    cout << str_start_timestamp << start_timestamp << endl;
    if (status == ongoing)
        cout << str_end_timestamp << not_finished << endl;
    else
        cout << str_end_timestamp << end_time_stamp << endl;
    cout << str_reward << reward_amount << endl;
    cout << str_status << status << endl;
}

bool Mission::has_the_same_id(string _mission_id)
{
    if (this->mission_id == _mission_id)
    {
        return true;
    }
    return false;
}

bool Mission::has_the_same_end_time(long _e_time_stamp)
{
    if (end_time_stamp == _e_time_stamp)
    {
        return true;
    }
    return false;
}

bool Mission::is_the_mission_over()
{
    if (status == completed)
    {
        return true;
    }
    return false;
}

void Mission::show_completed_missions()
{
    cout << mission << semicolon << space << mission_id << endl;
    cout << str_start_timestamp << start_timestamp << endl;
    cout << str_end_timestamp << end_time_stamp << endl;
    cout << str_reward << reward_amount << endl;
}

long Mission::get_mission_start_timestamp()
{
    return start_timestamp;
}

bool Mission::is_it_the_same_time(long _s_timestamp)
{
    if (_s_timestamp == this->start_timestamp)
    {
        return true;
    }
    return false;
}

Mission *Mission::return_current_mission()
{
    return this;
}

TimeMission::TimeMission(string _mission_id, long _s_timestamp, long _e_timestamp, long _target_in_min, int _reward_amount)
    : Mission(_mission_id, _s_timestamp, _e_timestamp, _reward_amount)
{
    if (_target_in_min < 0)
    {
        throw runtime_error(invalid_arguments);
    }
    target_in_min = _target_in_min;
    target_in_second = target_in_min * 60;
}

TimeMission::TimeMission(const TimeMission &pre_one)
    : Mission(pre_one)
{

    target_in_min = pre_one.target_in_min;
    target_in_second = target_in_min * 60;
}

bool TimeMission::does_the_ride_end_this_mission(long _s_time_stamp, long _e_time_stamp, long distance)
{
    if (end_time_stamp >= _e_time_stamp && start_timestamp <= _s_time_stamp)
    {
        long dt = _e_time_stamp - _s_time_stamp;
        target_in_second = target_in_second - dt;
        if (target_in_second <= 0)
        {
            end_time_stamp = _e_time_stamp;
            status = completed;
            return true;
        }
    }
    return false;
}

Mission *TimeMission::make_copy_of(string mission_id, long _s_time_stamp, long _e_time_stamp, int target, int reward)
{
    TimeMission *new_one = new TimeMission(mission_id, _s_time_stamp, _e_time_stamp, target, reward);
    return new_one;
}

DistanceMission::DistanceMission(string _mission_id, long _s_timestamp, long _e_timestamp, int _target_distance_in_meters, int _reward_amount)
    : Mission(_mission_id, _s_timestamp, _e_timestamp, _reward_amount)
{
    if (_target_distance_in_meters < 0)
    {
        throw runtime_error(invalid_arguments);
    }
    target_distance_in_meters = _target_distance_in_meters;
}

DistanceMission::DistanceMission(const DistanceMission &pre_one)
    : Mission(pre_one)
{
    target_distance_in_meters = pre_one.target_distance_in_meters;
}

bool DistanceMission::does_the_ride_end_this_mission(long _s_time_stamp, long _e_time_stamp, long distance)
{
    if (end_time_stamp >= _e_time_stamp && start_timestamp <= _s_time_stamp)
    {
        target_distance_in_meters = target_distance_in_meters - distance;
        if (target_distance_in_meters <= 0)
        {
            end_time_stamp = _e_time_stamp;
            status = completed;
            return true;
        }
    }
    return false;
}

Mission *DistanceMission::make_copy_of(string mission_id, long _s_time_stamp, long _e_time_stamp, int target, int reward)
{
    DistanceMission *new_one = new DistanceMission(mission_id, _s_time_stamp, _e_time_stamp, target, reward);
    return new_one;
}

CountMission::CountMission(string _mission_id, long _s_timestamp, long _e_timestamp, int _target_number, int _reward_amount)
    : Mission(_mission_id, _s_timestamp, _e_timestamp, _reward_amount)
{
    if (_target_number < 0)
    {
        throw runtime_error(invalid_arguments);
    }
    target_number = _target_number;
    number_of_finished_trips = 0;
}

CountMission::CountMission(const CountMission &pre_one)
    : Mission(pre_one)
{
    target_number = pre_one.target_number;
}

Mission *CountMission::make_copy_of(string mission_id, long _s_time_stamp, long _e_time_stamp, int target, int reward)
{
    CountMission *new_one = new CountMission(mission_id, _s_time_stamp, _e_time_stamp, target, reward);
    return new_one;
}

bool CountMission::does_the_ride_end_this_mission(long _s_time_stamp, long _e_time_stamp, long distance)
{
    if (_s_time_stamp >= start_timestamp && end_time_stamp >= _e_time_stamp)
    {
        number_of_finished_trips++;
        if (number_of_finished_trips >= target_number)
        {
            end_time_stamp = _e_time_stamp;
            status = completed;
            return true;
        }
    }
    return false;
}
