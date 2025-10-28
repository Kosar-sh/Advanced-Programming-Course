#ifndef MISSION_H
#define MISSION_H
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Mission
{
protected:
    string mission_id;
    string status;
    long start_timestamp;
    long end_time_stamp;
    long reward_amount;

public:
    Mission(string _mission_id, long _s_timestamp, long _e_timestamp, long _reward_amount);
    Mission(const Mission &pre_one);
    virtual void show_the_missions();
    bool has_the_same_id(string _mission_id);
    bool has_the_same_end_time(long _e_time_stamp);
    virtual bool does_the_ride_end_this_mission(long _s_time_stamp, long _e_time_stamp, long distance) = 0;
    bool is_the_mission_over();
    void show_completed_missions();
    long get_mission_start_timestamp();
    bool is_it_the_same_time(long _s_timestamp);
    Mission *return_current_mission();
    virtual Mission* make_copy_of(string mission_id,long _s_time_stamp, long _e_time_stamp,int target,int reward)=0;
    long get_start_timestamp(){return start_timestamp;};
    string get_mission_id(){return mission_id;};
    long get_end_time_stamp(){return end_time_stamp;};
    long get_reward_amount(){return reward_amount;};
    virtual long get_target()=0;

};

class TimeMission : public Mission
{
private:
    long target_in_min;
    long target_in_second;

public:
    TimeMission(string _mission_id, long _s_timestamp, long _e_timestamp, long _target_in_min, int _reward_amount);
    TimeMission(const TimeMission &pre_one);
    bool does_the_ride_end_this_mission(long _s_time_stamp, long _e_time_stamp, long distance);
    Mission* make_copy_of(string mission_id,long _s_time_stamp, long _e_time_stamp,int target,int reward);
    long get_target(){return target_in_min;};

};

class DistanceMission : public Mission
{
private:
    int target_distance_in_meters;

public:
    DistanceMission(string _mission_id, long _s_timestamp, long _e_timestamp, int _target_distance_in_meters, int _reward_amount);
    DistanceMission(const DistanceMission &pre_one);
    //virtual Mission *copy_of_this_mission(DistanceMission &pre_one);
    bool does_the_ride_end_this_mission(long _s_time_stamp, long _e_time_stamp, long distance);
    Mission* make_copy_of(string mission_id,long _s_time_stamp, long _e_time_stamp,int target,int reward);
    long get_target(){return target_distance_in_meters;};

};

class CountMission : public Mission
{
private:
    long target_number;
    int number_of_finished_trips;

public:
    CountMission(string _mission_id, long _s_timestamp, long _e_timestamp, int _target_number, int _reward_amount);
    CountMission(const CountMission &pre_one);
    Mission* make_copy_of(string mission_id,long _s_time_stamp, long _e_time_stamp,int target,int reward);
    long get_target(){return target_number;};

    bool does_the_ride_end_this_mission(long _s_time_stamp, long _e_time_stamp, long distance);
};

#endif