#ifndef SCORE_HPP
#define SCORE_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <memory>
#include "PlayersInMatch.hpp"
using namespace std;
class Score;
class ScoreOfGoalKeeper;

class Calculator
{
private:
    vector<shared_ptr<InfoOfPlayer>> team_one;
    vector<shared_ptr<InfoOfPlayer>> team_two;
    vector<shared_ptr<GoalsInfo>> goals_informations;
    string team_1_score;
    string team_2_score;

public:
    Calculator(PlayersInMatch &new_players);
    vector<shared_ptr<InfoOfPlayer>> calculating_players_of_team_one_score();
    void calculating_goal_keeper_of_team_one(int place_to_add);
    void calculating_forward_of_team_one(int place_to_add);
    void calculating_midfielder_of_team_one(int place_to_add);
    void calculating_defender_of_team_one(int place_to_add);
    vector<shared_ptr<InfoOfPlayer>> calculating_players_of_team_two_score();
    void calculating_goal_keeper_of_team_two(int place_to_add);
    void calculating_defender_of_team_two(int place_to_add);
    void calculating_midfielder_of_team_two(int place_to_add);
    void calculating_forward_of_team_two(int place_to_add);
    void assign_any_goal_happen();
    void assign_assisting_goals();
    void add_clean_sheet_to_players();
    friend class Score;
    friend class ScoreOfGoalKeeper;
};

class Score
{
protected:
    int default_score;
    string name;
    string position;
    string direction;
    vector<shared_ptr<InfoOfPlayer>> opponent_team;
    vector<shared_ptr<GoalsInfo>> goals_info;

public:
    virtual float calculate_total_score(int current_team_score, int opponent_score) = 0;
    virtual float apply_the_formula_of_score(float score);
    void changing_score_based_on_result(int current_team_score, int opponent_score);
    virtual void this_person_assisted_in_goals(int assisting_point);
    virtual void this_person_reached_goals(int reach_point);
};

class ScoreOfGoalKeeper : public Score
{
public:
    ScoreOfGoalKeeper(string _name, string _position, string _direction, const vector<shared_ptr<InfoOfPlayer>> &_opponent_team,
                      const vector<shared_ptr<GoalsInfo>> &_goals_info);
    float calculate_total_score(int current_team_score, int opponent_score);
    virtual void the_game_was_clean_sheets(int opponent_score);
};

class ScoreOfDefender : public Score
{
public:
    ScoreOfDefender(string _name, string _position, string _direction, const vector<shared_ptr<InfoOfPlayer>> &_opponent_team,
                    const vector<shared_ptr<GoalsInfo>> &_goals_info);
    float calculate_total_score(int current_team_score, int opponent_score);
    void effect_of_goals_on_defender();
    virtual void the_game_was_clean_sheets(int opponent_score);
};

class ScoreOfMidfielder : public Score
{
public:
    ScoreOfMidfielder(string _name, string _position, string _direction, const vector<shared_ptr<InfoOfPlayer>> &_opponent_team,
                      const vector<shared_ptr<GoalsInfo>> &_goals_info);
    float calculate_total_score(int current_team_score, int opponent_score);
    void effect_of_goals_on_midfielder();
    virtual void the_game_was_clean_sheets(int opponent_score);
};

class ScoreOfForward : public Score
{
public:
    ScoreOfForward(string _name, string _position, string _direction, const vector<shared_ptr<InfoOfPlayer>> &_opponent_team,
                   const vector<shared_ptr<GoalsInfo>> &_goals_info);
    float calculate_total_score(int current_team_score, int opponent_score);
    void did_the_forward_reach_goal();
};

#endif