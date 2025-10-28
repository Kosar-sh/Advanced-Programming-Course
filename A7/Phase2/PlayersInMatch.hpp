#ifndef PLAYERSINMATCH_HPP
#define PLAYERSINMATCH_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <memory>
using namespace std;

class InfoOfPlayer;
class GoalsInfo;

class PlayersInMatch
{
private:
    vector<shared_ptr<InfoOfPlayer>> team_one;
    vector<shared_ptr<InfoOfPlayer>> team_two;
    vector<shared_ptr<GoalsInfo>> assist_goal;
    string team_1_score;
    string team_2_score;

public:
    PlayersInMatch(string _score_1, string _score_2);
    void made_vector_of_goals(string remain);
    vector<string> add_names_to_vector(string remain);
    vector<int> make_vector_of_semi_colon(string remain);
    vector<string> make_vector_of_names(string remain,vector<int> pos_of_semi_colon);
    void find_players_of_team_one(string remain);
    void find_players_of_team_two(string remain);
    void make_player_info(string name, string position, string direction, int current_team);
    string finding_left_or_right(int i);
    vector<shared_ptr<InfoOfPlayer>> get_team_one() { return team_one; };
    vector<shared_ptr<InfoOfPlayer>> get_team_two() { return team_two; };
    vector<shared_ptr<GoalsInfo>> get_goal_reacher() { return assist_goal; };
    string get_score_one() { return team_1_score; };
    string get_score_two() { return team_2_score; };
};

class InfoOfPlayer
{
private:
    string name;
    string position;
    string direction;
    float score;
    int scored_goal;
    int assisting_goal;
    bool clean_sheet;

public:
    InfoOfPlayer(string _name, string _position, string _direction);
    void print_info();
    string get_pos();
    string get_direction();
    string get_name();
    float get_score();
    bool get_clean_sheet();
    int get_assisting_goals();
    int get_reaching_goals();
    void add_the_score_to_player(float _score);
    void add_changes_in_achieving_goals();
    void add_changes_in_assisting_goals();
    bool can_minus_defender_score_for_goals( string _position, string _direction);
    bool can_minus_midfielder_score_for_goals();
    void add_clean_sheet();
    friend class PlayersInMatch;
};
class GoalsInfo
{
private:
    string assist_goal;
    string goal_reacher;
    int counter;
public:
    GoalsInfo(string _name, string _name_reacher);
    bool this_person_assisted(string checking_name);
    bool this_person_scored(string checking_name,bool &own_goal);
    bool this_person_passed_goal(string person);
    bool was_this_person_assisted(string checking_name);
    friend class PlayersInMatch;
};

#endif
