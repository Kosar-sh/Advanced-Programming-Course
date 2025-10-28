#ifndef LEAGUETEAMS_HPP
#define LEAGUETEAMS_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include "Player.hpp"
using namespace std;
class TeamWeek;
class LeagueTeams
{
private:
    string team_name;
    vector<shared_ptr<Player>> players;
    vector<TeamWeek> team_weeks;
    shared_ptr<Player> best_goalkeeper;
    shared_ptr<Player> best_forward;

public:
    LeagueTeams(string _team_name, vector<shared_ptr<Player>> _players);
    void add_team_score(string week_number, long int _goals_for, long int goals_against, int the_score_of_this_match);
    ~LeagueTeams();
    bool has_the_same_name(string _name);
    void make_special_player_injured(string name, string week_num);
    void give_player_yellow_card(string name, string week_num);
    void give_player_red_card(string name, string week_num);
    void give_the_player_his_score(string name, string week_num, float score);
    void find_the_best_defender(string week_num, shared_ptr<Player> &best_defender1, shared_ptr<Player> &best_defender2);
    void sorting_the_vector_of_special_players(vector<shared_ptr<Player>> &best_of_type,string week_num);
    shared_ptr<Player> find_the_best_midfielder(string week_num);
    shared_ptr<Player> find_the_best_goalkeeper(string week_num);
    shared_ptr<Player> find_the_best_forward(string week_num);
    long int calculate_total_score(string _week_num);
    long int calculate_total_goals_for(string _week_num);
    long int calculate_total_goals_against(string _week_num);
    string get_team_name();
    void sorting_players_by_alphabet();
    void find_the_result_with_out_ranks(string week_num,string position);
    void the_result_position_given(string week_num,string position);
    void find_result_with_ranking(string week_num,string position,const vector<shared_ptr<Player>> &copy_players);
    void sorting_players_by_score(string week_num,vector<shared_ptr<Player>> &copy_players);
    void printing_the_players_as_they_add(string week_num,string position,bool ranks);
    void printing_the_players_sorted_ascending(string pos,string week_num);
    void has_this_player(string name,shared_ptr<Player> &found_player);
    void show_the_size();
    void deleting_previous_yellow_cards_of_team(const int week_number);
    void printing_with_pos_and_ranks(string week_num,string position,const vector<shared_ptr<Player>> &copy_players);
    void Deprivation_done_for_yellow_cards(int week_number);
};

class TeamWeek
{
private:
    string week_num;
    long int goals_for;
    long int goals_against;
    int the_score_of_this_match;

public:
    TeamWeek(string _week_num, long int _goals_for, long int _goals_against, int _the_score_of_this_match);
    friend class LeagueTeams;
    friend class FantasyTeam;
};
#endif