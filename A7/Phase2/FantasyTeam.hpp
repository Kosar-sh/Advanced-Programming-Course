#ifndef FANTASYTEAM_HPP
#define FANTASYTEAM_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <memory>

#include "LeagueTeams.hpp"
#include "Player.hpp"
using namespace std;
class PostOfTeam;
class PreviousWeek;

class FantasyTeam
{
private:
    string name;
    float score;
    shared_ptr<Player> defender1;
    shared_ptr<Player> defender2;
    shared_ptr<Player> goal_keeper;
    shared_ptr<Player> midfielder;
    shared_ptr<Player> forward;
    string captain;
    vector<shared_ptr<PreviousWeek>> previous_players;
    bool has_defender_1;
    bool has_defender_2;
    bool has_forward;
    bool has_midfielder;
    bool has_goal_keeper;
    int able_to_buy_more_players;
    int able_to_sell_more_players;
    string week_team_is_completed;
    long int current_budget;
    long int team_cost;
public:
    FantasyTeam(string _name);
    bool has_the_same_name(string _name);
    void show_the_team();
    long get_total_score();
    string get_name();
    void checking_the_ability_to_buy(shared_ptr<Player> new_player);
    void can_we_get_this_player(shared_ptr<Player> new_player, string week_num);
    void checking_the_price_of_player(shared_ptr<Player> new_player);
    void already_have_defenders(shared_ptr<Player> new_player, string position, string week_num);
    void already_have_goal_keeper(shared_ptr<Player> new_player, string position, string week_num);
    void already_have_forward(shared_ptr<Player> new_player, string position, string week_num);
    void already_have_midfielder(shared_ptr<Player> new_player, string position, string week_num);
    void buy_this_player(shared_ptr<Player> new_player, string position, string week_num);
    void print_details_of_the_team(string week_number);
    bool can_unlimited_buy_happen(string week_num);
    void is_the_team_completed(string week_num);
    bool every_post_is_taken();
    void calculate_without_captain(string week_num);
    void calculate_with_captain(string week_num);
    void calculate_attack_line(string week_num);
    void calculate_defend_line(string week_num);
    void calculate_the_whole_week_score(string week_num);
    void restart_the_ability_to_buy_sell();
    void can_unlimited_sell_happen();
    void can_we_sell_this_player(string name_of_player);
    void can_we_sell_defender(string name, int &flag);
    void check_defender_one(string name, int &flag);
    void check_defender_two(string name, int &flag);
    void can_we_sell_midfielder(string name, int &flag);
    void can_we_sell_goalkeeper(string name, int &flag);
    void can_we_sell_forward(string name, int &flag);
    bool is_the_team_full();
    void make_vector_of_previous_week_players(string week_num);
    bool was_the_team_completed_previous_week(string week_number);
    void show_the_budget();
    bool check_having_the_player(string captain_name);
    void checking_the_defender(int &flag,string captain_name);
    void checking_the_forward(int &flag,string captain_name);
    void checking_the_midfielder(int &flag,string captain_name);
    void checking_the_goal_keeper(int &flag,string captain_name);
    void setting_the_captain(string captain_name);
    ~FantasyTeam();
};

class PreviousWeek
{
private:
    string week_number;
    vector<shared_ptr<Player>> last_week_players;
    string captain_of_team;
public:
    PreviousWeek(shared_ptr<Player> defender1,shared_ptr<Player> defender2,
                 shared_ptr<Player> goal_keeper,shared_ptr<Player> midfielder,
                 shared_ptr<Player> forward,string week_num,string captain_of_team);
    friend class FantasyTeam;
    ~PreviousWeek();
    void printing_the_parameters();
    bool check_having_captain(string name);
    void printing_goal_keeper();
    void sort_the_defenders_for_print();
    void printing_defenders(vector<string> defenders);
    void printing_striker();
    void printing_midfielder();
    void calculate_team_cost();
};


#endif