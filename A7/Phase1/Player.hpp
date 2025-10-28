#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;
class Weeks;

class Player
{
private:
    string name;
    string position;
    bool able_to_transfer;
    vector<Weeks> weeks_situation;

public:
    Player(string _name, string _position);
    ~Player();
    bool has_the_same_name(string _name);
    void make_this_person_injured(string week_num, bool _is_injured);
    void add_yellow_card_to_this_person(string week_num);
    void add_red_card_to_this_player(string week_num);
    void add_the_score_of_this_player(string week_num, float _score);
    bool has_red_card(string week_num);
    void make_new_week(bool injured, int red_card, int yellow_card, float score, string week_num);
    bool has_the_same_position(string _position);
    float find_the_score_of_this_week(string week_num);
    string get_name();
    string get_position();
    void show_the_best_player(string week_num);
    void show_the_player_score_this_week(string week_num);
    vector<string> make_vector_of_weeks(string week_num);
    void what_happened_to_player_this_week(vector<string> weeks, Weeks current_week, int &yellow_cards, int &red_card, int &injured);
    void can_we_buy_this_player(string week_num);
    void calculating_total_yellow_cards(string week_num, int &yellow_cards);
    void delete_previous_yellow_cards(int week_number);
    void summation_of_scores(float &sum_of_score, int week_number, int &week);
    float calculate_average_score_per_weeks(string week_num);
    void adding_Deprivation_of_yellow_cards(int week_number);
    void removing_more_than_3_yellow_cards(int week_number, int yellow_card);
};

class Weeks
{
private:
    string week_num;
    int yellow_card;
    int red_card;
    bool is_injured;
    float score;

public:
    Weeks(bool _injured, int _red_card, int _yellow_card, float _score, string _week_num);
    friend class Player;
    void change_the_player_score_this_week(float _score);
    void make_this_player_injured_this_week(bool _is_injured);
    void this_player_got_red_card(int _red_card);
    void this_player_got_yellow_card(int _yellow_card);
};

#endif