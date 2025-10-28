#include "Player.hpp"
const string str_goal_keeper = "Goalkeeper";
const string str_forward = "Forward";
const string str_midfielder = "Midfielder";
const string str_defender = "Defender";
const string summarized_goal_keeper = "gk";
const string summarized_forward = "fw";
const string summarized_midfielder = "md";
const string summarized_defender = "df";
const string str_score = "score: ";
const string not_available_player = "This player is not available for next week";
const string vertical_bar = " | ";
const string str_role = "role: ";
const string str_name = "name: ";
const string str_empty = "";
const string semi_colon = ": ";
Player::Player(string _name, string _position)
{
    name = _name;
    position = _position;
    able_to_transfer = true;
}

Player::~Player()
{
    delete this;
}

bool Player::has_the_same_name(string _name)
{
    if (this->name == _name)
    {
        return true;
    }
    return false;
}

void Player::make_this_person_injured(string week_num, bool _is_injured)
{
    int flag = 0;
    for (int i = 0; i < weeks_situation.size(); i++)
    {
        if (weeks_situation[i].week_num == week_num)
        {
            flag++;
            weeks_situation[i].make_this_player_injured_this_week(_is_injured);
        }
    }
    if (flag == 0)
        make_new_week(true, 0, 0, 0, week_num);
}

void Player::add_yellow_card_to_this_person(string week_num)
{
    int flag = 0;
    for (int i = 0; i < weeks_situation.size(); i++)
    {
        if (weeks_situation[i].week_num == week_num)
        {
            flag++;
            weeks_situation[i].this_player_got_yellow_card(1);
        }
    }
    if (flag == 0)
        make_new_week(false, 0, 1, 0, week_num);
}

void Player::add_red_card_to_this_player(string week_num)
{
    int flag = 0;
    for (int i = 0; i < weeks_situation.size(); i++)
    {
        if (weeks_situation[i].week_num == week_num)
        {
            flag++;
            weeks_situation[i].this_player_got_red_card(1);
        }
    }
    if (flag == 0)
        make_new_week(false, 1, 0, 0, week_num);
}

void Player::add_the_score_of_this_player(string week_num, float _score)
{
    int flag = 0;
    for (int i = 0; i < weeks_situation.size(); i++)
    {
        if (weeks_situation[i].week_num == week_num)
        {
            flag++;
            weeks_situation[i].change_the_player_score_this_week(_score);
        }
    }
    if (flag == 0)
        make_new_week(false, 0, 0, _score, week_num);
}

bool Player::has_red_card(string week_num)
{
    for (int i = 0; i < weeks_situation.size(); i++)
    {
        if (this->weeks_situation[i].red_card != 0 && weeks_situation[i].week_num == week_num)
            return true;
    }
    return false;
}

void Player::make_new_week(bool injured, int red_card, int yellow_card, float score, string week_num)
{
    Weeks new_one(injured, red_card, yellow_card, score, week_num);
    weeks_situation.push_back(new_one);
}

bool Player::has_the_same_position(string _position)
{
    if (position == _position)
    {
        return true;
    }
    return false;
}

float Player::find_the_score_of_this_week(string week_num)
{
    for (int i = 0; i < weeks_situation.size(); i++)
    {
        if (weeks_situation[i].week_num == week_num)
            return weeks_situation[i].score;
    }
    return 0.0;
}

string Player::get_name()
{
    return this->name;
}

string Player::get_position()
{
    return this->position;
}

void Player::show_the_best_player(string week_num)
{
    cout << semi_colon << this->name << vertical_bar;
    for (int i = 0; i < weeks_situation.size(); i++)
    {
        if (weeks_situation[i].week_num == week_num)
            cout << fixed << setprecision(1) << str_score << weeks_situation[i].score << endl;
    }
}

string reverse_pos_name(string pos)
{
    if (str_forward == pos)
        return summarized_forward;
    else if (str_goal_keeper == pos)
        return summarized_goal_keeper;
    else if (str_midfielder == pos)
        return summarized_midfielder;
    else if (str_defender == pos)
        return summarized_defender;
    return str_empty;
}

void Player::show_the_player_score_this_week(string week_num)
{
    float average_of_score = calculate_average_score_per_weeks(week_num);
    cout << str_name << this->name << vertical_bar << str_role << reverse_pos_name(position) << vertical_bar << str_score;
    cout << fixed << setprecision(1) << average_of_score << endl;
}

vector<string> Player::make_vector_of_weeks(string week_num)
{
    string first_week = to_string(stoi(week_num));
    string second_week = to_string(stoi(week_num) - 1);
    string third_week = to_string(stoi(week_num) - 2);
    vector<string> weeks;
    weeks.push_back(first_week);
    weeks.push_back(second_week);
    weeks.push_back(third_week);
    return weeks;
}

void Player::what_happened_to_player_this_week(vector<string> weeks, Weeks current_week, int &yellow_cards, int &red_card, int &injured)
{
    for (int j = 0; j < weeks.size(); j++)
    {
        if (current_week.week_num == weeks[j] && current_week.is_injured == true)
            injured++;
    }
    if (current_week.week_num == weeks[0])
    {
        if (current_week.red_card != 0)
            red_card++;
    }
}

void Player::can_we_buy_this_player(string week_num)
{
    int yellow_cards = 0, red_card = 0, injured = 0;
    vector<string> weeks = make_vector_of_weeks(week_num);
    for (int i = 0; i < weeks_situation.size(); i++)
    {
        what_happened_to_player_this_week(weeks, weeks_situation[i], yellow_cards, red_card, injured);
    }
    calculating_total_yellow_cards(week_num, yellow_cards);
    if (injured != 0 || red_card != 0 || yellow_cards >= 3)
        throw runtime_error(not_available_player);
}

void Player::calculating_total_yellow_cards(string week_num, int &yellow_cards)
{
    for (int i = 1; i <= stoi(week_num); i++)
    {
        for (int h = 0; h < weeks_situation.size(); h++)
        {
            if (weeks_situation[h].week_num == to_string(i) && weeks_situation[h].yellow_card != 0)
                yellow_cards++;
        }
    }
}

void Player::delete_previous_yellow_cards(int week_number)
{
    if (this->has_red_card(to_string(week_number)))
    {
        for (int i = week_number - 1; i > 0; i--)
        {
            for (int h = 0; h < weeks_situation.size(); h++)
            {
                if (weeks_situation[h].week_num == to_string(i))
                    weeks_situation[h].yellow_card = 0;
            }
        }
    }
}

void Player::summation_of_scores(float &sum_of_score, int week_number, int &week)
{
    for (int i = 0; i < weeks_situation.size(); i++)
    {
        for (int h = week_number; h > 0; h--)
        {
            if (weeks_situation[i].week_num == to_string(h))
            {
                sum_of_score += weeks_situation[i].score;
                week++;
            }
        }
    }
}

float Player::calculate_average_score_per_weeks(string week_num)
{
    float sum_of_score = 0.0;
    int week_number = stoi(week_num);
    int week = 0;
    summation_of_scores(sum_of_score, week_number, week);
    if (weeks_situation.size() == 0 || week == 0)
        return sum_of_score;
    return (sum_of_score) / (float)week;
}

void Player::adding_Deprivation_of_yellow_cards(int week_number)
{
    int yellow_card = 0;
    for (int i = 0; i < weeks_situation.size(); i++)
    {
        for (int h = 1; h <= week_number; h++)
        {
            if (weeks_situation[i].week_num == to_string(h) && weeks_situation[i].yellow_card != 0)
                yellow_card++;
        }
    }
    removing_more_than_3_yellow_cards(week_number, yellow_card);
}

void Player::removing_more_than_3_yellow_cards(int week_number, int yellow_card)
{
    if (yellow_card >= 3)
    {
        for (int i = 0; i < weeks_situation.size(); i++)
        {
            for (int h = 1; h <= week_number; h++)
            {
                if (weeks_situation[i].week_num == to_string(h))
                    weeks_situation[i].yellow_card = 0;
            }
        }
    }
}

Weeks::Weeks(bool _injured, int _red_card, int _yellow_card, float _score, string _week_num)
{
    is_injured = _injured;
    red_card = _red_card;
    yellow_card = _yellow_card;
    score = _score;
    week_num = _week_num;
}

void Weeks::change_the_player_score_this_week(float _score)
{
    this->score = _score;
}

void Weeks::make_this_player_injured_this_week(bool _is_injured)
{
    this->is_injured = _is_injured;
}

void Weeks::this_player_got_red_card(int _red_card)
{
    this->red_card = _red_card;
}

void Weeks::this_player_got_yellow_card(int _yellow_card)
{
    this->yellow_card = _yellow_card;
}