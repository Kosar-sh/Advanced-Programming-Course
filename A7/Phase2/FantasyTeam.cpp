#include "FantasyTeam.hpp"
const string str_goal_keeper = "Goalkeeper";
const string str_forward = "Forward";
const string str_midfielder = "Midfielder";
const string str_defender = "Defender";
const string permission_denied = "Permission Denied";
const string bad_request = "Bad Request";
const string not_found = "Not Found";
const string str_striker = "Striker: ";
const string defender_one = "Defender1: ";
const string defender_two = "Defender2: ";
const string str_empty = "";
const string str_team_name = "team_name";
const string str_fantasy_name = "fantasy_team: ";
const string vertical_bar = " | ";
const string str_point = "point: ";
const string total_point = "Total Points: ";
const string str_colon = ": ";
const string every_thing_ok = "OK";
const int default_budget = 2500;
const string str_team_cost = "Team Cost: ";
const string str_captain = " (CAPTAIN)";

FantasyTeam::FantasyTeam(string _name)
{
    name = _name;
    score = 0.0;
    has_defender_1 = false;
    has_defender_2 = false;
    has_forward = false;
    has_goal_keeper = false;
    has_midfielder = false;
    able_to_buy_more_players = 0;
    able_to_sell_more_players = 0;
    week_team_is_completed = str_empty;
    current_budget = default_budget;
    team_cost = 0;
    captain = "";
}

bool FantasyTeam::has_the_same_name(string _name)
{
    if (name == _name)
    {
        return true;
    }
    return false;
}

void FantasyTeam::show_the_team()
{
    cout << str_team_name << str_colon << name << vertical_bar << str_point;
    cout << fixed << setprecision(1) << score << endl;
}

long FantasyTeam::get_total_score()
{
    long double_score = score * 10;
    return double_score;
}

string FantasyTeam::get_name()
{
    return name;
}

void FantasyTeam::can_we_get_this_player(shared_ptr<Player> new_player, string week_num)
{
    string current_pos = new_player->get_position();
    can_unlimited_buy_happen(week_num);
    new_player->can_we_buy_this_player(week_num);
    checking_the_price_of_player(new_player);
    already_have_forward(new_player, current_pos, week_num);
    already_have_goal_keeper(new_player, current_pos, week_num);
    already_have_midfielder(new_player, current_pos, week_num);
    already_have_defenders(new_player, current_pos, week_num);
    is_the_team_completed(week_num);
    able_to_buy_more_players++;
}

void FantasyTeam::checking_the_price_of_player(shared_ptr<Player> new_player)
{
    if (new_player->get_price() > current_budget)
    {
        throw runtime_error(bad_request);
    }
}

void FantasyTeam::already_have_defenders(shared_ptr<Player> new_player, string position, string week_num)
{
    if (position == str_defender)
    {
        if (has_defender_1 == true && has_defender_2 == true)
            throw runtime_error(bad_request);
        if (has_defender_2 == false && has_defender_1 == true)
        {
            defender2 = new_player;
            current_budget = current_budget - new_player->get_price();
            has_defender_2 = true;
        }
        if (has_defender_1 == false)
        {
            defender1 = new_player;
            current_budget = current_budget - new_player->get_price();
            has_defender_1 = true;
        }
    }
}

void FantasyTeam::already_have_goal_keeper(shared_ptr<Player> new_player, string position, string week_num)
{
    if (position == str_goal_keeper)
    {
        if (has_goal_keeper == false)
        {
            goal_keeper = new_player;
            current_budget = current_budget - new_player->get_price();
            has_goal_keeper = true;
        }
        else
            throw runtime_error(bad_request);
    }
}

void FantasyTeam::already_have_forward(shared_ptr<Player> new_player, string position, string week_num)
{
    if (position == str_forward)
    {
        if (has_forward == false)
        {
            forward = new_player;
            current_budget = current_budget - new_player->get_price();
            has_forward = true;
        }
        else
            throw runtime_error(bad_request);
    }
}

void FantasyTeam::already_have_midfielder(shared_ptr<Player> new_player, string position, string week_num)
{
    if (position == str_midfielder)
    {
        if (has_midfielder == false)
        {
            midfielder = new_player;
            current_budget = current_budget - new_player->get_price();
            has_midfielder = true;
        }
        else
            throw runtime_error(bad_request);
    }
}

void FantasyTeam::print_details_of_the_team(string week_number)
{
    int week_num = stoi(week_number) - 1;
    for (int k = 0; k < previous_players.size(); k++)
    {
        if (previous_players[k]->week_number == to_string(week_num))
        {
            cout << str_fantasy_name << this->name << endl;
            previous_players[k]->printing_the_parameters();
            cout << fixed << setprecision(1) << total_point << this->score << endl;
            previous_players[k]->calculate_team_cost();
            break;
        }
    }
}

bool FantasyTeam::can_unlimited_buy_happen(string week_num)
{
    if (week_team_is_completed != str_empty)
    {
        if (able_to_buy_more_players == 2)
            throw runtime_error(permission_denied);
    }
    return true;
}

void FantasyTeam::is_the_team_completed(string week_num)
{
    if (week_team_is_completed == str_empty)
    {
        if (every_post_is_taken())
        {
            week_team_is_completed = week_num;
            able_to_buy_more_players = 0;
        }
    }
}

bool FantasyTeam::every_post_is_taken()
{
    return has_defender_1 && has_defender_2 && has_forward && has_goal_keeper && has_midfielder;
}

void FantasyTeam::calculate_without_captain(string week_num)
{
    score = score + defender1->find_the_score_of_this_week(week_num);
    score = score + defender2->find_the_score_of_this_week(week_num);
    score = score + forward->find_the_score_of_this_week(week_num);
    score = score + goal_keeper->find_the_score_of_this_week(week_num);
    score = score + midfielder->find_the_score_of_this_week(week_num);
}

void FantasyTeam::calculate_with_captain(string week_num)
{
    if (captain != goal_keeper->get_name())
        score = score + goal_keeper->find_the_score_of_this_week(week_num);
    else
        score = score + (goal_keeper->find_the_score_of_this_week(week_num)) * 2;
    calculate_attack_line(week_num);
    calculate_defend_line(week_num);
}

void FantasyTeam::calculate_attack_line(string week_num)
{
    if (captain != forward->get_name())
        score = score + forward->find_the_score_of_this_week(week_num);
    else
        score = score + (forward->find_the_score_of_this_week(week_num)) * 2;
    if (captain != midfielder->get_name())
        score = score + midfielder->find_the_score_of_this_week(week_num);
    else
        score = score + (midfielder->find_the_score_of_this_week(week_num)) * 2;
}

void FantasyTeam::calculate_defend_line(string week_num)
{
    if (captain != defender1->get_name())
        score = score + defender1->find_the_score_of_this_week(week_num);
    else
        score = score + (defender1->find_the_score_of_this_week(week_num)) * 2;
    if (captain != defender2->get_name())
        score = score + defender2->find_the_score_of_this_week(week_num);
    else
        score = score + (defender2->find_the_score_of_this_week(week_num)) * 2;
}

void FantasyTeam::calculate_the_whole_week_score(string week_num)
{
    if (!is_the_team_full())
        return;
    if (captain != "")
        calculate_with_captain(week_num);
    else
        calculate_without_captain(week_num);
}

void FantasyTeam::restart_the_ability_to_buy_sell()
{
    able_to_buy_more_players = 0;
    able_to_sell_more_players = 0;
}

void FantasyTeam::can_unlimited_sell_happen()
{
    if (week_team_is_completed != str_empty)
    {
        if (able_to_sell_more_players == 2)
            throw runtime_error(permission_denied);
    }
}

void FantasyTeam::can_we_sell_this_player(string name_of_player)
{
    int flag = 0;
    can_unlimited_sell_happen();
    can_we_sell_defender(name_of_player, flag);
    can_we_sell_forward(name_of_player, flag);
    can_we_sell_goalkeeper(name_of_player, flag);
    can_we_sell_midfielder(name_of_player, flag);
    if (flag == 0)
        throw runtime_error(not_found);
    cout << every_thing_ok << endl;
}

void FantasyTeam::can_we_sell_defender(string name, int &flag)
{
    check_defender_one(name, flag);
    check_defender_two(name, flag);
}

void FantasyTeam::check_defender_one(string name, int &flag)
{
    if (has_defender_1 == true)
    {
        if (defender1->get_name() == name)
        {
            current_budget = current_budget + defender1->get_price();
            if (defender1->get_name() == captain)
                captain = "";
            defender1 = nullptr;
            has_defender_1 = false;
            able_to_sell_more_players++;
            flag++;
        }
    }
}

void FantasyTeam::check_defender_two(string name, int &flag)
{
    if (has_defender_2 == true)
    {
        if (defender2->get_name() == name)
        {
            if (defender2->get_name() == captain)
                captain = "";
            current_budget = current_budget + defender2->get_price();
            defender2 = nullptr;
            has_defender_2 = false;
            able_to_sell_more_players++;
            flag++;
        }
    }
}

void FantasyTeam::can_we_sell_midfielder(string name, int &flag)
{
    if (has_midfielder == true)
    {
        if (midfielder->get_name() == name)
        {
            if (midfielder->get_name() == captain)
                captain = "";
            current_budget = current_budget + midfielder->get_price();
            midfielder = nullptr;
            has_midfielder = false;
            able_to_sell_more_players++;
            flag++;
        }
    }
}

void FantasyTeam::can_we_sell_goalkeeper(string name, int &flag)
{
    if (has_goal_keeper == true)
    {
        if (goal_keeper->get_name() == name)
        {
            if (goal_keeper->get_name() == captain)
                captain = "";
            current_budget = current_budget + goal_keeper->get_price();
            has_goal_keeper = false;
            goal_keeper = nullptr;
            able_to_sell_more_players++;
            flag++;
        }
    }
}

void FantasyTeam::can_we_sell_forward(string name, int &flag)
{
    if (has_forward == true)
    {
        if (forward->get_name() == name)
        {
            if (forward->get_name() == captain)
                captain = "";
            current_budget = current_budget + forward->get_price();
            forward = nullptr;
            has_forward = false;
            able_to_sell_more_players++;
            flag++;
        }
    }
}

bool FantasyTeam::is_the_team_full()
{
    return has_defender_1 && has_defender_2 && has_forward && has_goal_keeper && has_midfielder;
}

void FantasyTeam::make_vector_of_previous_week_players(string week_num)
{
    if (is_the_team_full())
    {
        shared_ptr<PreviousWeek> new_one = make_shared<PreviousWeek>(defender1, defender2, goal_keeper, midfielder, forward, week_num, captain);
        previous_players.push_back(new_one);
    }
}

bool FantasyTeam::was_the_team_completed_previous_week(string week_number)
{
    int week_num = stoi(week_number) - 1;
    for (int k = 0; k < previous_players.size(); k++)
    {
        if (previous_players[k]->week_number == to_string(week_num))
            return true;
    }
    return false;
}

void FantasyTeam::show_the_budget()
{
    cout << this->current_budget << endl;
}

bool FantasyTeam::check_having_the_player(string captain_name)
{
    int flag = 0;
    checking_the_defender(flag,captain_name);
    checking_the_midfielder(flag,captain_name);
    checking_the_forward(flag,captain_name);
    checking_the_goal_keeper(flag,captain_name);
    if (flag != 0)
        return true;
    return false;
}

void FantasyTeam::checking_the_defender(int &flag,string captain_name)
{
    if (has_defender_1 == true)
    {
        if (defender1->get_name() == captain_name)
        {
            captain = defender1->get_name();
            flag++;
        }
    }
    if (has_defender_2 == true)
    {
        if (defender2->get_name() == captain_name)
        {
            captain = defender2->get_name();
            flag++;
        }
    }
}

void FantasyTeam::checking_the_forward(int &flag,string captain_name)
{
    if (has_forward == true)
    {
        if (forward->get_name() == captain_name)
        {
            captain = forward->get_name();
            flag++;
        }
    }
}

void FantasyTeam::checking_the_midfielder(int &flag,string captain_name)
{
    if (has_midfielder == true)
    {
        if (midfielder->get_name() == captain_name)
        {
            captain = midfielder->get_name();
            flag++;
        }
    }
}

void FantasyTeam::checking_the_goal_keeper(int &flag,string captain_name)
{
    if (has_goal_keeper == true)
    {
        if (goal_keeper->get_name() == captain_name)
        {
            captain = goal_keeper->get_name();
            flag++;
        }
    }
}

void FantasyTeam::setting_the_captain(string captain_name)
{
    if (!check_having_the_player(captain_name))
    {
        throw runtime_error(not_found);
    }
    cout << every_thing_ok << endl;
}

FantasyTeam::~FantasyTeam()
{
    delete this;
}

PreviousWeek::PreviousWeek(shared_ptr<Player> defender1, shared_ptr<Player> defender2, shared_ptr<Player> goal_keeper,
                           shared_ptr<Player> midfielder, shared_ptr<Player> forward, string week_num, string captain)
{
    week_number = week_num;
    last_week_players.push_back(defender1);
    last_week_players.push_back(defender2);
    last_week_players.push_back(goal_keeper);
    last_week_players.push_back(midfielder);
    last_week_players.push_back(forward);
    captain_of_team = captain;
}

PreviousWeek::~PreviousWeek()
{
    delete this;
}

void PreviousWeek::printing_the_parameters()
{
    printing_goal_keeper();
    sort_the_defenders_for_print();
    printing_midfielder();
    printing_striker();
}

bool PreviousWeek::check_having_captain(string name)
{
    if (captain_of_team == name)
    {
        return true;
    }
    return false;
}

void PreviousWeek::printing_goal_keeper()
{
    for (int i = 0; i < last_week_players.size(); i++)
    {
        if (last_week_players[i]->get_position() == str_goal_keeper)
        {
            cout << str_goal_keeper << str_colon << last_week_players[i]->get_name();
            if (check_having_captain(last_week_players[i]->get_name()))
                cout << str_captain;
            cout << endl;
        }
    }
}

void PreviousWeek::sort_the_defenders_for_print()
{
    vector<string> defenders;
    for (int i = 0; i < last_week_players.size(); i++)
    {
        if (last_week_players[i]->get_position() == str_defender)
            defenders.push_back(last_week_players[i]->get_name());
    }
    printing_defenders(defenders);
}

void PreviousWeek::printing_defenders(vector<string> defenders)
{
    sort(defenders.begin(), defenders.end());
    cout << defender_one << defenders[0];
    if (check_having_captain(defenders[0]))
        cout << str_captain;
    cout << endl;
    cout << defender_two << defenders[1];
    if (check_having_captain(defenders[1]))
        cout << str_captain;
    cout << endl;
}

void PreviousWeek::printing_striker()
{
    for (int i = 0; i < last_week_players.size(); i++)
    {
        if (last_week_players[i]->get_position() == str_forward)
        {
            cout << str_striker << last_week_players[i]->get_name();
            if (check_having_captain(last_week_players[i]->get_name()))
                cout << str_captain;
            cout << endl;
        }
    }
}

void PreviousWeek::printing_midfielder()
{
    for (int i = 0; i < last_week_players.size(); i++)
    {
        if (last_week_players[i]->get_position() == str_midfielder)
        {
            cout << str_midfielder << str_colon << last_week_players[i]->get_name();
            if (check_having_captain(last_week_players[i]->get_name()))
                cout << str_captain;
            cout << endl;
        }
    }
}

void PreviousWeek::calculate_team_cost()
{
    long int team_cost = 0;
    for (int i = 0; i < last_week_players.size(); i++)
    {
        team_cost += last_week_players[i]->get_price();
    }
    cout << str_team_cost << team_cost << endl;
}
