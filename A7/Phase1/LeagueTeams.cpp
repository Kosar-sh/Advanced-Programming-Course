#include "LeagueTeams.hpp"
const string str_goal_keeper = "Goalkeeper";
const string str_forward = "Forward";
const string str_midfielder = "Midfielder";
const string str_defender = "Defender";
const string summarized_goal_keeper = "gk";
const string summarized_forward = "fw";
const string summarized_midfielder = "md";
const string summarized_defender = "df";
const string dot= ". ";
const string str_empty = "";

LeagueTeams::LeagueTeams(string _team_name, vector<shared_ptr<Player>> _players)
{
    team_name = _team_name;
    players = _players;
}

void LeagueTeams::add_team_score(string week_number, long int _goals_for, long int goals_against, int the_score_of_this_match)
{
    TeamWeek new_week(week_number, _goals_for, goals_against, the_score_of_this_match);
    team_weeks.push_back(new_week);
}

LeagueTeams::~LeagueTeams()
{
    delete this;
}

bool LeagueTeams::has_the_same_name(string _name)
{
    if (team_name == _name)
    {
        return true;
    }
    return false;
}

void LeagueTeams::make_special_player_injured(string name, string week_num)
{
    for (int i = 0; i < this->players.size(); i++)
    {
        if (this->players[i]->has_the_same_name(name))
        {
            this->players[i]->make_this_person_injured(week_num, true);
        }
    }
}

void LeagueTeams::give_player_yellow_card(string name, string week_num)
{
    for (int i = 0; i < this->players.size(); i++)
    {
        if (this->players[i]->has_the_same_name(name))
        {
            this->players[i]->add_yellow_card_to_this_person(week_num);
        }
    }
}

void LeagueTeams::give_player_red_card(string name, string week_num)
{
    for (int i = 0; i < this->players.size(); i++)
    {
        if (this->players[i]->has_the_same_name(name))
        {
            this->players[i]->add_red_card_to_this_player(week_num);
        }
    }
}

void LeagueTeams::give_the_player_his_score(string name, string week_num, float score)
{
    for (int i = 0; i < this->players.size(); i++)
    {
        if (this->players[i]->has_the_same_name(name))
        {
            this->players[i]->add_the_score_of_this_player(week_num, score);
        }
    }
}

void LeagueTeams::find_the_best_defender(string week_num, shared_ptr<Player> &best_defender1, shared_ptr<Player> &best_defender2)
{
    vector<shared_ptr<Player>> all_defenders;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->has_the_same_position(str_defender))
            all_defenders.push_back(players[i]);
    }
    sorting_the_vector_of_special_players(all_defenders, week_num);
    best_defender1 = all_defenders[0];
    best_defender2 = all_defenders[1];
}

void LeagueTeams::sorting_the_vector_of_special_players(vector<shared_ptr<Player>> &best_of_type, string week_num)
{
    sort(best_of_type.begin(), best_of_type.end(), [&week_num](shared_ptr<Player> const &a, shared_ptr<Player> const &b) -> bool
         {if (a->find_the_score_of_this_week(week_num) != b->find_the_score_of_this_week(week_num))
                 return a->find_the_score_of_this_week(week_num) >b->find_the_score_of_this_week(week_num);
             if (a->get_name() != b->get_name())
                 return a->get_name() < b->get_name();
            return true; });
}

shared_ptr<Player> LeagueTeams::find_the_best_midfielder(string week_num)
{
    vector<shared_ptr<Player>> all_midfielders;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->has_the_same_position(str_midfielder))
            all_midfielders.push_back(players[i]);
    }
    sorting_the_vector_of_special_players(all_midfielders, week_num);
    return all_midfielders[0];
}

shared_ptr<Player> LeagueTeams::find_the_best_goalkeeper(string week_num)
{
    vector<shared_ptr<Player>> all_goalkeeper;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->has_the_same_position(str_goal_keeper))
            all_goalkeeper.push_back(players[i]);
    }
    sorting_the_vector_of_special_players(all_goalkeeper, week_num);    
    return all_goalkeeper[0];
}

shared_ptr<Player> LeagueTeams::find_the_best_forward(string week_num)
{
    vector<shared_ptr<Player>> all_forward;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->has_the_same_position(str_forward))
            all_forward.push_back(players[i]);
    }
    sorting_the_vector_of_special_players(all_forward, week_num);
    return all_forward[0];
}

long int LeagueTeams::calculate_total_score(string _week_num)
{
    long int total_score = 0;
    int counter = stoi(_week_num);
    for (int i = 0; i < team_weeks.size(); i++)
    {
        for (int j = counter; j > 0; j--)
        {
            if (team_weeks[i].week_num == to_string(j))
                total_score += team_weeks[i].the_score_of_this_match;
        }
    }
    return total_score;
}

long int LeagueTeams::calculate_total_goals_for(string _week_num)
{
    long int total_goals_for = 0;
    int counter = stoi(_week_num);
    for (int i = 0; i < team_weeks.size(); i++)
    {
        for (int j = counter; j > 0; j--)
        {
            if (team_weeks[i].week_num == to_string(j))
                total_goals_for += team_weeks[i].goals_for;
        }
    }
    return total_goals_for;
}

long int LeagueTeams::calculate_total_goals_against(string _week_num)
{
    long int total_goals_against = 0;
    int counter = stoi(_week_num);
    for (int i = 0; i < team_weeks.size(); i++)
    {
        for (int j = counter; j > 0; j--)
        {
            if (team_weeks[i].week_num == to_string(j))
                total_goals_against += team_weeks[i].goals_against;
        }
    }
    return total_goals_against;
}

string change_pos_name(string pos)
{
    if (pos == summarized_forward)
        return str_forward;
    else if (pos == summarized_goal_keeper)
        return str_goal_keeper;
    else if (pos == summarized_midfielder)
        return str_midfielder;
    else if (pos == summarized_defender)
        return str_defender;
    return str_empty;
}

string LeagueTeams::get_team_name()
{
    return team_name;
}
void LeagueTeams::sorting_players_by_alphabet()
{
    sort(players.begin(), players.end(), [](shared_ptr<Player> const &a, shared_ptr<Player> const &b) -> bool
         {if (a->get_name() != b->get_name())
                 return a->get_name() < b->get_name();
                 return true; });
}
void LeagueTeams::find_the_result_with_out_ranks(string week_num, string position)
{
    if (position != str_empty)
        the_result_position_given(week_num, position);
    else
    {
        for (int i = 0; i < players.size(); i++)
        {
            cout << to_string(i + 1) << dot;
            players[i]->show_the_player_score_this_week(week_num);
        }
    }
}

void LeagueTeams::the_result_position_given(string week_num, string position)
{
    string pos = change_pos_name(position);
    int counter = 1;
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->has_the_same_position(pos))
        {
            cout << to_string(counter) << dot;
            players[i]->show_the_player_score_this_week(week_num);
            counter++;
        }
    }
}

void LeagueTeams::sorting_players_by_score(string week_num, vector<shared_ptr<Player>> &copy_players)
{
    sort(copy_players.begin(), copy_players.end(), [&week_num](shared_ptr<Player> const &a, shared_ptr<Player> const &b) -> bool
         {if (a->calculate_average_score_per_weeks(week_num)!=b->calculate_average_score_per_weeks(week_num))
            return a->calculate_average_score_per_weeks(week_num)>b->calculate_average_score_per_weeks(week_num);
            if (a->get_name() != b->get_name())
                 return a->get_name() < b->get_name();
                 return true; });
}

void LeagueTeams::printing_the_players_as_they_add(string week_num, string position, bool ranks)
{
    if (ranks == false)
    {
        sorting_players_by_alphabet();
        find_the_result_with_out_ranks(week_num, position);
    }
    else
    {
        vector<shared_ptr<Player>> copy_players = players;
        sorting_players_by_score(week_num, copy_players);
        find_result_with_ranking(week_num, position, copy_players);
    }
}

void LeagueTeams::has_this_player(string name, shared_ptr<Player> &found_player)
{
    for (int i = 0; i < players.size(); i++)
    {
        if (players[i]->has_the_same_name(name))
            found_player = players[i];
    }
}

void LeagueTeams::show_the_size()
{
    cout << players.size() << endl;
}

void LeagueTeams::deleting_previous_yellow_cards_of_team(const int week_number)
{
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->delete_previous_yellow_cards(week_number);
    }
}

void LeagueTeams::printing_with_pos_and_ranks(string week_num, string position, const vector<shared_ptr<Player>> &copy_players)
{
    string pos = change_pos_name(position);
    int counter = 1;
    for (int i = 0; i < copy_players.size(); i++)
    {
        if (copy_players[i]->has_the_same_position(pos))
        {
            cout << to_string(counter) << dot;
            copy_players[i]->show_the_player_score_this_week(week_num);
            counter++;
        }
    }
}

void LeagueTeams::Deprivation_done_for_yellow_cards(int week_number)
{
    for (int i = 0; i < players.size(); i++)
    {
        players[i]->adding_Deprivation_of_yellow_cards(week_number);
    }
    
}

void LeagueTeams::find_result_with_ranking(string week_num, string position, const vector<shared_ptr<Player>> &copy_players)
{
    if (position != str_empty)
        printing_with_pos_and_ranks(week_num, position, copy_players);
    else
    {
        for (int i = 0; i < copy_players.size(); i++)
        {
            cout << to_string(i + 1) << dot;
            copy_players[i]->show_the_player_score_this_week(week_num);
        }
    }
}

TeamWeek::TeamWeek(string _week_num, long int _goals_for, long int _goals_against, int _the_score_of_this_match)
{
    this->the_score_of_this_match = _the_score_of_this_match;
    this->week_num = _week_num;
    this->goals_for = _goals_for;
    this->goals_against = _goals_against;
}
