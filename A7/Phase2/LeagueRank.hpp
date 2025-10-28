#ifndef LEAGUERANK_HPP
#define LEAGUERANK_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <memory>
#include <exception>
#include "LeagueTeams.hpp"
#include "Player.hpp"

class LeagueRank
{
private:
    long int total_score;
    long int total_goals_for;
    long int total_goals_against;
    long int difference_of_goals;
    string name;
    string week_number;

public:
    LeagueRank(string week_num);
    LeagueRank(string _name, long int _total_score, long int difference_of_goals, long int _total_goals_for, long int _total_goals_against);
    void sort_the_vector_of_teams(vector<LeagueRank> &teams_rank);
    void find_the_data_of_each_team(string week_num, const vector<shared_ptr<LeagueTeams>> &league_teams);
    void printing_the_result(vector<LeagueRank> teams_rank);
};

#endif