#ifndef PROCESS_HPP
#define PROCESS_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <memory>
#include <exception>
#include "LeagueTeams.hpp"
#include "Player.hpp"
#include "Match.hpp"
#include "LeagueRank.hpp"
#include "FantasyTeam.hpp"
using namespace std;
class AccessRecord;

class Process
{
private:
    vector<shared_ptr<LeagueTeams>> league_teams;
     vector<shared_ptr<Match>> matches;
    vector<AccessRecord> records;
    vector<shared_ptr<FantasyTeam>> fantasy_teams;
    vector<shared_ptr<FantasyTeam>> last_week_fantasy_teams;
    string current_access;
    bool admin_login;
    bool user_login;
    bool transfer_window;

public:
    Process(vector<shared_ptr<LeagueTeams>> _league_teams, vector<shared_ptr<Match>> _matches);
    void handling_commands();
    string find_special_word_in_vector(vector<string> read_words, string needed_one);
    void validate_week_number(string ordered_week, string current_week);
    void finding_team_of_the_week(string remain, string current_week_num);
    void printing_all_the_best_ones(string week_num);
    void finding_the_best_defender(string week_num);
    void sorting_the_vector_of_special_players(vector<shared_ptr<Player>> &best_players_each_team, string week_num);
    vector<shared_ptr<Player>> find_each_team_best_defenders(string week_num);
    void finding_the_best_midfielder(string week_num);
    vector<shared_ptr<Player>> find_each_team_best_midfielder(string week_num);
    void finding_the_best_goalkeeper(string week_num);
    vector<shared_ptr<Player>> find_each_team_best_goalkeeper(string week_num);
    void finding_the_best_forward(string week_num);
    vector<shared_ptr<Player>> find_each_team_best_forward(string week_num);
    void get_command_subset(string remain, string current_week);
    void how_many_parameters_mention(const vector<string> &read_words, string &position, string &team_name, bool &ranks);
    void validate_having_this_team(string &team_name);
    void find_the_league_team_asked(string remain, string current_week);
    void find_the_matches_happen_this_week(string remain, string current_week_num);
    void print_the_matches_in_this_week(string week_number);
    void sort_the_users(vector<shared_ptr<FantasyTeam>> &copy_fantasy_teams);
    void find_the_user_ranking();
    void find_the_league_ranking(string week_num);
    void find_fantasy_team(string remain,string week_number);
    int find_the_index_of_wanted_team(string fantasy_team_name);
    void print_the_found_fantasy_team(string fantasy_team_name,string week_number);
    void post_command_subset(string remain, string week_num, int &week_number_counter);
    void login_the_user(string remain);
    void is_the_user_info_right(string id, string password);
    void add_admin_id();
    void add_new_user(string id, string password);
    void find_the_name_password(string remain, string &id, string &password, string compare);
    void sign_up_new_user(string remain);
    vector<string> split_the_input(string remain);
    void is_it_duplicate_id(string id);
    void logout_from_the_system();
    void register_admin(string remain);
    void is_admin_login_info_right(string id, string password);
    bool is_another_person_login();
    bool is_the_admin_login();
    bool is_the_user_login();
    void opening_the_transfer_window();
    void closing_the_transfer_window();
    string find_the_name_of_player(vector<string> read_words);
    void validating_the_user_permission();
    void sell_player_from_fantasy_team(string remain, string week_num);
    shared_ptr<Player> find_the_input_player_pointer(string player_name);
    void are_we_allowed_to_buy(shared_ptr<Player> found_player,string week_num);
    void are_we_allowed_to_sell(string player);
    void buy_player_for_fantasy_team(string remain, string week_num);
    void passing_the_week(string week_num, int &week_number_counter);
    void update_the_week_in_fantasy_teams(string week_num, int week_number_counter);
    void show_the_budget();
    void setting_captain_for_this_fantasy_team(string remain);
    string finding_the_name_of_captain( vector<string> read_words);
};

class AccessRecord
{
private:
    string name;
    string pass_word;
    string position;

public:
    friend class Process;
    AccessRecord();
    AccessRecord(string _id, string _password, string _position);
};

#endif