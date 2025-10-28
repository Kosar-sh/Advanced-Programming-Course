#include "Score.hpp"
const string str_goal_keeper = "Goalkeeper";
const string str_forward = "Forward";
const string str_midfielder = "Midfielder";
const string str_defender = "Defender";
const int default_score_goal_keeper = 3;
const int default_score_defender = 1;
const int the_winning_points = 5;
const int losing_points = 1;
const int equal_points = 1;
const int clean_sheets_score = 5;
const int mid_fielder_clean_sheets = 1;
const int forward_goal_point = 3;
const int forward_assist_point = 1;
const int clean_sheets_for_defender = 2;
const int mid_fielder_goal_point = 3;
const int mid_fielder_assist_point = 2;
const int own_goal_loss_point = 3;
const int not_reach_goal_points = 1;
const int defender_assist_in_goal=3;
const int defender_reach_goal=4;

Calculator::Calculator(PlayersInMatch &new_players)
{
    team_one = new_players.get_team_one();
    team_two = new_players.get_team_two();
    goals_informations = new_players.get_goal_reacher();
    team_1_score = new_players.get_score_one();
    team_2_score = new_players.get_score_two();
    assign_any_goal_happen();
    assign_assisting_goals();
    add_clean_sheet_to_players();
}

vector<shared_ptr<InfoOfPlayer>> Calculator::calculating_players_of_team_one_score()
{
    for (int i = 0; i < team_one.size(); i++)
    {
        if (team_one[i]->get_pos() == str_goal_keeper)
            calculating_goal_keeper_of_team_one(i);
        if (team_one[i]->get_pos() == str_defender)
            calculating_defender_of_team_one(i);
        if (team_one[i]->get_pos() == str_midfielder)
            calculating_midfielder_of_team_one(i);
        if (team_one[i]->get_pos() == str_forward)
            calculating_forward_of_team_one(i);
    }
    return team_one;
}

void Calculator::calculating_goal_keeper_of_team_one(int place_to_add)
{
    float calculated_score = 0.0;
    shared_ptr<ScoreOfGoalKeeper> score = make_shared<ScoreOfGoalKeeper>(team_one[place_to_add]->get_name(), "Goalkeeper", team_one[place_to_add]->get_direction(), team_two, goals_informations);
    calculated_score = score->calculate_total_score(stoi(team_1_score), stoi(team_2_score));
    team_one[place_to_add]->add_the_score_to_player(calculated_score);
}

void Calculator::calculating_forward_of_team_one(int place_to_add)
{
    float calculated_score = 0.0;
    shared_ptr<ScoreOfForward> score = make_shared<ScoreOfForward>(team_one[place_to_add]->get_name(), "Forward", team_one[place_to_add]->get_direction(), team_two, goals_informations);
    calculated_score = score->calculate_total_score(stoi(team_1_score), stoi(team_2_score));
    team_one[place_to_add]->add_the_score_to_player(calculated_score);
}

void Calculator::calculating_midfielder_of_team_one(int place_to_add)
{
    float calculated_score = 0.0;
    shared_ptr<ScoreOfMidfielder> score = make_shared<ScoreOfMidfielder>(team_one[place_to_add]->get_name(), "Midfielder", team_one[place_to_add]->get_direction(), team_two, goals_informations);
    calculated_score = score->calculate_total_score(stoi(team_1_score), stoi(team_2_score));
    team_one[place_to_add]->add_the_score_to_player(calculated_score);
}

void Calculator::calculating_defender_of_team_one(int place_to_add)
{
    float calculated_score = 0.0;
    shared_ptr<ScoreOfDefender> score = make_shared<ScoreOfDefender>(team_one[place_to_add]->get_name(), "Defender", team_one[place_to_add]->get_direction(), team_two, goals_informations);
    calculated_score = score->calculate_total_score(stoi(team_1_score), stoi(team_2_score));
    team_one[place_to_add]->add_the_score_to_player(calculated_score);
}

vector<shared_ptr<InfoOfPlayer>> Calculator::calculating_players_of_team_two_score()
{
    for (int i = 0; i < team_two.size(); i++)
    {
        if (team_two[i]->get_pos() == str_goal_keeper)
            calculating_goal_keeper_of_team_two(i);
        if (team_two[i]->get_pos() == str_defender)
            calculating_defender_of_team_two(i);
        if (team_two[i]->get_pos() == str_midfielder)
            calculating_midfielder_of_team_two(i);
        if (team_two[i]->get_pos() == str_forward)
            calculating_forward_of_team_two(i);
    }
    return team_two;
}

void Calculator::calculating_goal_keeper_of_team_two(int place_to_add)
{
    float calculated_score = 0.0;
    shared_ptr<ScoreOfGoalKeeper> score = make_shared<ScoreOfGoalKeeper>(team_two[place_to_add]->get_name(), str_goal_keeper, team_two[place_to_add]->get_direction(), team_one, goals_informations);
    calculated_score = score->calculate_total_score(stoi(team_2_score), stoi(team_1_score));
    team_two[place_to_add]->add_the_score_to_player(calculated_score);
}

void Calculator::calculating_defender_of_team_two(int place_to_add)
{
    float calculated_score = 0.0;
    shared_ptr<ScoreOfDefender> score = make_shared<ScoreOfDefender>(team_two[place_to_add]->get_name(), str_defender, team_two[place_to_add]->get_direction(), team_one, goals_informations);
    calculated_score = score->calculate_total_score(stoi(team_2_score), stoi(team_1_score));
    team_two[place_to_add]->add_the_score_to_player(calculated_score);
}

void Calculator::calculating_midfielder_of_team_two(int place_to_add)
{
    float calculated_score = 0.0;
    shared_ptr<ScoreOfMidfielder> score = make_shared<ScoreOfMidfielder>(team_two[place_to_add]->get_name(), str_midfielder, team_two[place_to_add]->get_direction(), team_one, goals_informations);
    calculated_score = score->calculate_total_score(stoi(team_2_score), stoi(team_1_score));
    team_two[place_to_add]->add_the_score_to_player(calculated_score);
}

void Calculator::calculating_forward_of_team_two(int place_to_add)
{
    float calculated_score = 0.0;
    shared_ptr<ScoreOfForward> score = make_shared<ScoreOfForward>(team_two[place_to_add]->get_name(), str_forward, team_two[place_to_add]->get_direction(), team_one, goals_informations);
    calculated_score = score->calculate_total_score(stoi(team_2_score), stoi(team_1_score));
    team_two[place_to_add]->add_the_score_to_player(calculated_score);
}

void Calculator::assign_any_goal_happen()
{
    for (int i = 0; i < team_one.size(); i++)
    {
        for (int h = 0; h < goals_informations.size(); h++)
        {
            if (goals_informations[h]->this_person_passed_goal(team_one[i]->get_name()))
                team_one[i]->add_changes_in_achieving_goals();
            if (goals_informations[h]->this_person_passed_goal(team_two[i]->get_name()))
                team_two[i]->add_changes_in_achieving_goals();
        }
    }
}

void Calculator::assign_assisting_goals()
{
    for (int i = 0; i < team_one.size(); i++)
    {
        for (int h = 0; h < goals_informations.size(); h++)
        {
            if (goals_informations[h]->was_this_person_assisted(team_one[i]->get_name()))
                team_one[i]->add_changes_in_assisting_goals();
            if (goals_informations[h]->was_this_person_assisted(team_two[i]->get_name()))
                team_two[i]->add_changes_in_assisting_goals();
        }
    }
}

void Calculator::add_clean_sheet_to_players()
{
    if (stoi(team_2_score) == 0)
    {
        for (int i = 0; i < team_one.size(); i++)
            team_one[i]->add_clean_sheet();
    }
    if (stoi(team_1_score) == 0)
    {
        for (int i = 0; i < team_two.size(); i++)
            team_two[i]->add_clean_sheet();
    }
}

ScoreOfGoalKeeper::ScoreOfGoalKeeper(string _name, string _position, string _direction,
                                     const vector<shared_ptr<InfoOfPlayer>> &_opponent_team,
                                     const vector<shared_ptr<GoalsInfo>> &_goals_info)
{
    this->name = _name;
    default_score = default_score_goal_keeper;
    position = _position;
    direction = _direction;
    goals_info = _goals_info;
    opponent_team = _opponent_team;
}

float ScoreOfGoalKeeper::calculate_total_score(int current_team_score, int opponent_score)
{
    changing_score_based_on_result(current_team_score, opponent_score);
    the_game_was_clean_sheets(opponent_score);
    float final_score = apply_the_formula_of_score(default_score);
    return final_score;
}

void ScoreOfGoalKeeper::the_game_was_clean_sheets(int opponent_score)
{
    if (opponent_score == 0)
        default_score += clean_sheets_score;
    else
        default_score -= opponent_score;
}

float Score::apply_the_formula_of_score(float score)
{
    float first_vals = (1.0) / (1.0 + exp(-score / 6.0));
    float secund_vals = first_vals * 10;
    return secund_vals;
}

void Score::changing_score_based_on_result(int current_team_score, int opponent_score)
{
    if (current_team_score > opponent_score)
        default_score += the_winning_points;
    else if (current_team_score < opponent_score)
        default_score -= losing_points;
    else if (current_team_score == opponent_score)
        default_score += equal_points;
}

void Score::this_person_assisted_in_goals(int assisting_point)
{
    for (int i = 0; i < goals_info.size(); i++)
    {
        if (goals_info[i]->this_person_assisted(name))
        {
            default_score += assisting_point;
        }
    }
}

void Score::this_person_reached_goals(int reach_point)
{
    for (int i = 0; i < goals_info.size(); i++)
    {
        bool own_goal = false;
        if (goals_info[i]->this_person_scored(this->name, own_goal))
        {
            if (own_goal == true)
                default_score -= own_goal_loss_point;
            else
                default_score += reach_point;
        }
    }
}

ScoreOfDefender::ScoreOfDefender(string _name, string _position, string _direction,
                                 const vector<shared_ptr<InfoOfPlayer>> &_opponent_team,
                                 const vector<shared_ptr<GoalsInfo>> &_goals_info)
{
    this->name = _name;
    default_score = default_score_defender;
    position = _position;
    direction = _direction;
    goals_info = _goals_info;
    opponent_team = _opponent_team;
}

float ScoreOfDefender::calculate_total_score(int current_team_score, int opponent_score)
{
    changing_score_based_on_result(current_team_score, opponent_score);
    the_game_was_clean_sheets(opponent_score);
    this_person_assisted_in_goals(defender_assist_in_goal);
    this_person_reached_goals(defender_reach_goal);
    effect_of_goals_on_defender();
    float final_score = apply_the_formula_of_score(default_score);
    return final_score;
}

void ScoreOfDefender::effect_of_goals_on_defender()
{
    for (int i = 0; i < opponent_team.size(); i++)
    {
        if (opponent_team[i]->can_minus_defender_score_for_goals(position, direction))
        {
            default_score = default_score - 1;
        }
    }
}

void ScoreOfDefender::the_game_was_clean_sheets(int opponent_score)
{
    if (opponent_score == 0)
    {
        default_score += clean_sheets_for_defender;
    }
}

ScoreOfMidfielder::ScoreOfMidfielder(string _name, string _position, string _direction,
                                     const vector<shared_ptr<InfoOfPlayer>> &_opponent_team,
                                     const vector<shared_ptr<GoalsInfo>> &_goals_info)
{
    this->name = _name;
    default_score = 0;
    position = _position;
    direction = _direction;
    goals_info = _goals_info;
    opponent_team = _opponent_team;
}

float ScoreOfMidfielder::calculate_total_score(int current_team_score, int opponent_score)
{
    changing_score_based_on_result(current_team_score, opponent_score);
    the_game_was_clean_sheets(opponent_score);
    this_person_assisted_in_goals(mid_fielder_assist_point);
    this_person_reached_goals(mid_fielder_goal_point);
    effect_of_goals_on_midfielder();
    float final_score = apply_the_formula_of_score(default_score);
    return final_score;
}

void ScoreOfMidfielder::effect_of_goals_on_midfielder()
{
    for (int i = 0; i < opponent_team.size(); i++)
    {
        if (opponent_team[i]->can_minus_midfielder_score_for_goals())
            default_score -= 1;
    }
}

void ScoreOfMidfielder::the_game_was_clean_sheets(int opponent_score)
{
    if (opponent_score == 0)
    {
        default_score += mid_fielder_clean_sheets;
    }
}

ScoreOfForward::ScoreOfForward(string _name, string _position, string _direction,
                               const vector<shared_ptr<InfoOfPlayer>> &_opponent_team,
                               const vector<shared_ptr<GoalsInfo>> &_goals_info)
{
    this->name = _name;
    default_score = 0;
    position = _position;
    direction = _direction;
    goals_info = _goals_info;
    opponent_team = _opponent_team;
}

float ScoreOfForward::calculate_total_score(int current_team_score, int opponent_score)
{
    changing_score_based_on_result(current_team_score, opponent_score);
    this_person_assisted_in_goals(forward_assist_point);
    this_person_reached_goals(forward_goal_point);
    did_the_forward_reach_goal();
    float final_score = apply_the_formula_of_score(default_score);
    return final_score;
}

void ScoreOfForward::did_the_forward_reach_goal()
{
    int flag = 0;
    for (int i = 0; i < goals_info.size(); i++)
    {
        if (goals_info[i]->this_person_passed_goal(this->name))
            flag++;
    }
    if (flag == 0)
        default_score -= not_reach_goal_points;
}
