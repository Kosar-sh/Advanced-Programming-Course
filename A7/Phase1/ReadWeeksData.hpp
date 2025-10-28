#ifndef MATCH_HPP
#define MATCH_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <memory>
#include "Match.hpp"
#include "LeagueTeams.hpp"
#include "Player.hpp"
using namespace std;

class ReadWeeksData
{
private:
    string team_1_name;
    string team_2_name;
    string score_1_team;
    string score_2_team;
    vector<shared_ptr<Match>> matches;  
public:
    void read_new_week_data(fstream &file,string input,vector<shared_ptr<LeagueTeams>> &league_teams,shared_ptr<Match> &new_match,int week_number);
    string find_team_name(string input,vector<shared_ptr<LeagueTeams>> &league_teams);
    string find_team_scores(string remain,vector<shared_ptr<LeagueTeams>> &league_teams,int week_number);
    string find_injured_people(string remain,vector<shared_ptr<LeagueTeams>> &league_teams,int week_number);
    void add_injured_sign_to_player(vector<shared_ptr<LeagueTeams>> &league_teams,const vector<string> &injured_ones,int week_number);
    vector<int> find_semi_colon(string remain);
    string find_yellow_cards(string remain,vector<shared_ptr<LeagueTeams>> &league_teams,int week_number);
    void apply_yellow_cards_to_players(string needed_for_this_sec, vector<shared_ptr<LeagueTeams>> &league_teams, int week_number);
    string find_red_cards(string remain,vector<shared_ptr<LeagueTeams>> &league_teams,int week_number);
    void apply_red_cards_to_players(string needed_for_this_sec, vector<shared_ptr<LeagueTeams>> &league_teams, int week_number);
    void find_each_player_score(string remain,vector<shared_ptr<LeagueTeams>> &league_teams,int week_number);
    void apply_the_team_score(string found_person,vector<shared_ptr<LeagueTeams>> &league_teams, int week_number);
    void what_is_the_final_statue_of_this_match(int &status_of_one,int &status_of_two);
    void add_the_given_result_to_teams(vector<shared_ptr<LeagueTeams>> &league_teams,int week_number);
    vector<string> make_vector_of_read_inputs(vector<int> semi_colon_pos,string remain);
    vector<shared_ptr<Match>> read_from_weeks(vector<shared_ptr<LeagueTeams>> &league_teams);

};




























#endif