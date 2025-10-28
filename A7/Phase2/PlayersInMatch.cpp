#include "PlayersInMatch.hpp"
const string str_goal_keeper = "Goalkeeper";
const string str_forward = "Forward";
const string str_midfielder = "Midfielder";
const string str_defender = "Defender";
const string str_own_goal = "OWN_GOAL";
const string str_left = "left";
const string str_right = "right";
const string middle = "middle";
const char colon = ':';
const char new_line = '\n';
const char semi_colon = ';';

GoalsInfo::GoalsInfo(string _name, string _name_reacher)
{
    assist_goal = _name;
    goal_reacher = _name_reacher;
}

bool GoalsInfo::this_person_assisted(string checking_name)
{
    if (assist_goal == checking_name)
    {
        return true;
    }
    return false;
}

bool GoalsInfo::this_person_scored(string checking_name, bool &own_goal)
{
    if (goal_reacher == checking_name)
    {
        if (assist_goal == str_own_goal)
        {
            own_goal = true;
        }
        return true;
    }
    return false;
}

bool GoalsInfo::this_person_passed_goal(string person)
{
    if (goal_reacher == person)
    {
        if (assist_goal != str_own_goal)
        {
            return true;
        }
    }
    return false;
}

bool GoalsInfo::was_this_person_assisted(string checking_name)
{
    if (this->assist_goal == checking_name)
    {
        return true;
    }
    return false;
}

PlayersInMatch::PlayersInMatch(string _score_1, string _score_2)
{
    team_1_score = _score_1;
    team_2_score = _score_2;
}

void PlayersInMatch::made_vector_of_goals(string remain)
{
    vector<string> both_people = add_names_to_vector(remain);
    for (int i = 0; i < both_people.size(); i++)
    {
        int pos = both_people[i].find(colon);
        string name = (both_people[i].substr(0, pos));
        string name_2 = (both_people[i].substr(pos + 1));
        shared_ptr<GoalsInfo> goal_info = make_shared<GoalsInfo>(name_2, name);
        assist_goal.push_back(goal_info);
    }
}

vector<string> PlayersInMatch::add_names_to_vector(string remain)
{
    vector<int> pos_of_semi_colon = make_vector_of_semi_colon(remain);
    vector<string> names_of_players = make_vector_of_names(remain, pos_of_semi_colon);
    return names_of_players;
}

vector<int> PlayersInMatch::make_vector_of_semi_colon(string remain)
{
    vector<int> pos_of_semi_colon;
    for (int i = 0; i < remain.size(); i++)
    {
        if (remain[i] ==semi_colon)
        {
            pos_of_semi_colon.push_back(i);
        }
    }
    return pos_of_semi_colon;
}

vector<string> PlayersInMatch::make_vector_of_names(string remain, vector<int> pos_of_semi_colon)
{
    vector<string> names_of_players;
    int first_pos = 0;
    for (int i = 0; i < pos_of_semi_colon.size(); i++)
    {
        int deffer = pos_of_semi_colon[i] - first_pos;
        names_of_players.push_back(remain.substr(first_pos, deffer));
        first_pos = pos_of_semi_colon[i] + 1;
    }
    names_of_players.push_back(remain.substr(first_pos));
    return names_of_players;
}

void PlayersInMatch::find_players_of_team_one(string remain)
{
    vector<string> names_of_players = add_names_to_vector(remain);
    for (int i = 0; i < names_of_players.size(); i++)
    {
        if (i == 0)
            make_player_info(names_of_players[i], str_goal_keeper, finding_left_or_right(i), 1);
        if (i <= 4 && i >= 1)
            make_player_info(names_of_players[i], str_defender, finding_left_or_right(i), 1);
        if (i >= 5 && i <= 7)
            make_player_info(names_of_players[i], str_midfielder, finding_left_or_right(i), 1);
        if (i >= 8 && i <= 10)
            make_player_info(names_of_players[i], str_forward, finding_left_or_right(i), 1);
    }
}

void PlayersInMatch::make_player_info(string name, string position, string direction, int current_team)
{
    shared_ptr<InfoOfPlayer> new_player = make_shared<InfoOfPlayer>(name, position, direction);
    if (current_team == 1)
    {
        team_one.push_back(new_player);
    }
    else
    {
        team_two.push_back(new_player);
    }
}

string PlayersInMatch::finding_left_or_right(int i)
{
    if (i == 1 || i == 5 || i == 8)
        return str_left;
    else if (i == 2 || i == 3 || i == 6 || i == 9)
        return middle;
    else if (i == 4 || i == 7 || i == 10)
        return str_right;
    return "";
}

InfoOfPlayer::InfoOfPlayer(string _name, string _position, string _direction)
{
    name = _name;
    position = _position;
    direction = _direction;
    scored_goal = 0;
    assisting_goal = 0;
    clean_sheet = false;
}

string InfoOfPlayer::get_pos()
{
    return this->position;
}

string InfoOfPlayer::get_direction()
{
    return this->direction;
}

string InfoOfPlayer::get_name()
{
    return this->name;
}

float InfoOfPlayer::get_score()
{
    return this->score;
}

bool InfoOfPlayer::get_clean_sheet()
{
    return this->clean_sheet;
}

int InfoOfPlayer::get_assisting_goals()
{
    return this->assisting_goal;
}

int InfoOfPlayer::get_reaching_goals()
{
    return this->scored_goal;
}

void InfoOfPlayer::add_the_score_to_player(float _score)
{
    score = _score;
}

void InfoOfPlayer::add_changes_in_achieving_goals()
{
    scored_goal++;
}

void InfoOfPlayer::add_changes_in_assisting_goals()
{
    assisting_goal++;
}

bool InfoOfPlayer::can_minus_defender_score_for_goals(string _position, string _direction)
{
    if ((scored_goal != 0) && (this->position == str_defender || this->position == str_forward))
    {
        if (this->direction == str_left && _direction == str_right)
            return true;
        else if (this->direction == str_right && _direction == str_left)
            return true;
        else if (this->direction == middle && _direction == middle)
            return true;
    }
    return false;
}

bool InfoOfPlayer::can_minus_midfielder_score_for_goals()
{
    if (scored_goal != 0 && this->position == str_midfielder)
        return true;
    return false;
}

void InfoOfPlayer::add_clean_sheet()
{
    clean_sheet = true;
}

void PlayersInMatch::find_players_of_team_two(string remain)
{
    vector<string> names_of_players = add_names_to_vector(remain);
    for (int i = 0; i < names_of_players.size(); i++)
    {
        if (i == 0)
            make_player_info(names_of_players[i], str_goal_keeper, finding_left_or_right(i), 2);
        if (i <= 4 && i >= 1)
            make_player_info(names_of_players[i], str_defender, finding_left_or_right(i), 2);
        if (i >= 5 && i <= 7)
            make_player_info(names_of_players[i], str_midfielder, finding_left_or_right(i), 2);
        if (i >= 8 && i <= 10)
            make_player_info(names_of_players[i], str_forward, finding_left_or_right(i), 2);
    }
}
