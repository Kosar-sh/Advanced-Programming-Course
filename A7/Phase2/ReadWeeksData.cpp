#include "ReadWeeksData.hpp"
const string name_of_the_file = "data/weeks_stats/week_";
const string type_of_the_file = ".csv";
const int win = 3;
const int lose = 0;
const char comma = ',';
const char colon = ':';
const char new_line = '\n';
const char semi_colon = ';';
vector<shared_ptr<Match>> ReadWeeksData::read_from_weeks(vector<shared_ptr<LeagueTeams>> &league_teams)
{
    fstream file;
    string input;
    int week_number = 1;
    while (week_number != 20)
    {
        file.open(name_of_the_file + to_string(week_number) + type_of_the_file, ios::in);
        shared_ptr<Match> new_match = make_shared<Match>(to_string(week_number));
        read_new_week_data(file, input, league_teams, new_match, week_number);
        matches.push_back(new_match);
        week_number++;
        file.close();
    }
    return matches;
}

void ReadWeeksData::read_new_week_data(fstream &file, string input, vector<shared_ptr<LeagueTeams>> &league_teams, shared_ptr<Match> &new_match, int week_number)
{
    getline(file, input, new_line);
    while (getline(file, input, new_line))
    {
        string remain = find_team_name(input, league_teams);
        remain = find_team_scores(remain, league_teams, week_number);
        remain = find_injured_people(remain, league_teams, week_number);
        remain = find_yellow_cards(remain, league_teams, week_number);
        remain = find_red_cards(remain, league_teams, week_number);
        calculating_the_data_of_scores(remain, new_match, league_teams, week_number);
    }
}

void ReadWeeksData::calculating_the_data_of_scores(string remain, shared_ptr<Match> &new_match, vector<shared_ptr<LeagueTeams>> &league_teams, int week_number)
{
    PlayersInMatch new_players(score_1_team, score_2_team);
    remain = read_from_goals_information(remain, new_players);
    remain = read_from_team_one_players(remain, new_players);
    remain = read_from_team_two_players(remain, new_players);
    new_match->add_new_match(team_1_name, team_2_name, score_1_team, score_2_team);
    calculate_team_score(new_players, league_teams, week_number);
}

string ReadWeeksData::find_team_name(string input, vector<shared_ptr<LeagueTeams>> &league_teams)
{
    int teams_in_match_pos = input.find(comma);
    string remain = input.substr(0, teams_in_match_pos);
    int pos_of_semi_colon = remain.find(colon);
    team_1_name = remain.substr(0, pos_of_semi_colon);
    team_2_name = remain.substr(pos_of_semi_colon + 1);
    remain = input.substr(teams_in_match_pos + 1);
    return remain;
}

string ReadWeeksData::find_team_scores(string remain, vector<shared_ptr<LeagueTeams>> &league_teams, int week_number)
{
    int result_pos = remain.find(comma);
    string else_str = remain.substr(0, result_pos);
    int pos_colon = else_str.find(colon);
    score_1_team = else_str.substr(0, pos_colon);
    score_2_team = else_str.substr(pos_colon + 1);
    add_the_given_result_to_teams(league_teams, week_number);
    remain = remain.substr(result_pos + 1);
    return remain;
}

void ReadWeeksData::what_is_the_final_statue_of_this_match(int &status_of_one, int &status_of_two)
{
    if (stoi(score_1_team) > stoi(score_2_team))
    {
        status_of_one = win;
        status_of_two = lose;
    }
    else if (stoi(score_2_team) > stoi(score_1_team))
    {
        status_of_one = lose;
        status_of_two = win;
    }
}

void ReadWeeksData::add_the_given_result_to_teams(vector<shared_ptr<LeagueTeams>> &league_teams, int week_number)
{
    int status_of_1 = 1, status_of_2 = 1;
    what_is_the_final_statue_of_this_match(status_of_1, status_of_2);
    for (int i = 0; i < league_teams.size(); i++)
    {
        if (league_teams[i]->has_the_same_name(team_2_name))
            league_teams[i]->add_team_score(to_string(week_number), stoll(score_2_team), stoll(score_1_team), status_of_2);
        if (league_teams[i]->has_the_same_name(team_1_name))
            league_teams[i]->add_team_score(to_string(week_number), stoll(score_1_team), stoll(score_2_team), status_of_1);
    }
}

string ReadWeeksData::find_injured_people(string remain, vector<shared_ptr<LeagueTeams>> &league_teams, int week_number)
{
    int injured_pos = remain.find(comma);
    string needed_for_this_sec = remain.substr(0, injured_pos);
    vector<int> semi_colon_pos = find_semi_colon(needed_for_this_sec);
    vector<string> injured_ones = make_vector_of_read_inputs(semi_colon_pos, needed_for_this_sec);
    add_injured_sign_to_player(league_teams, injured_ones, week_number);
    remain = remain.substr(injured_pos + 1);
    return remain;
}

void ReadWeeksData::add_injured_sign_to_player(vector<shared_ptr<LeagueTeams>> &league_teams, const vector<string> &injured_ones, int week_number)
{
    for (int i = 0; i < injured_ones.size(); i++)
    {
        for (int k = 0; k < league_teams.size(); k++)
        {
            league_teams[k]->make_special_player_injured(injured_ones[i], to_string(week_number));
        }
    }
}

vector<int> ReadWeeksData::find_semi_colon(string remain)
{
    vector<int> semi_colon_pos;
    for (int i = 0; i < remain.size(); i++)
    {
        if (remain[i] == semi_colon)
            semi_colon_pos.push_back(i);
        if (i == remain.size() - 1)
            semi_colon_pos.push_back(remain.size());
    }
    return semi_colon_pos;
}

string ReadWeeksData::find_yellow_cards(string remain, vector<shared_ptr<LeagueTeams>> &league_teams, int week_number)
{
    int yellow_card_pos = remain.find(comma);
    string needed_for_this_sec = remain.substr(0, yellow_card_pos);
    apply_yellow_cards_to_players(needed_for_this_sec, league_teams, week_number);
    remain = remain.substr(yellow_card_pos + 1);
    return remain;
}

void ReadWeeksData::apply_yellow_cards_to_players(string needed_for_this_sec, vector<shared_ptr<LeagueTeams>> &league_teams, int week_number)
{
    vector<int> semi_colon_pos = find_semi_colon(needed_for_this_sec);
    vector<string> yellow_cards = make_vector_of_read_inputs(semi_colon_pos, needed_for_this_sec);
    for (int i = 0; i < yellow_cards.size(); i++)
    {
        for (int k = 0; k < league_teams.size(); k++)
        {
            league_teams[k]->give_player_yellow_card(yellow_cards[i], to_string(week_number));
        }
    }
}

string ReadWeeksData::find_red_cards(string remain, vector<shared_ptr<LeagueTeams>> &league_teams, int week_number)
{
    int red_cards_pos = remain.find(comma);
    string needed_for_this_sec = remain.substr(0, red_cards_pos);
    apply_red_cards_to_players(needed_for_this_sec, league_teams, week_number);
    remain = remain.substr(red_cards_pos + 1);
    return remain;
}

void ReadWeeksData::apply_red_cards_to_players(string needed_for_this_sec, vector<shared_ptr<LeagueTeams>> &league_teams, int week_number)
{
    vector<int> semi_colon_pos = find_semi_colon(needed_for_this_sec);
    vector<string> red_cards = make_vector_of_read_inputs(semi_colon_pos, needed_for_this_sec);
    for (int i = 0; i < red_cards.size(); i++)
    {
        for (int k = 0; k < league_teams.size(); k++)
        {
            league_teams[k]->give_player_red_card(red_cards[i], to_string(week_number));
        }
    }
}

vector<string> ReadWeeksData::make_vector_of_read_inputs(vector<int> semi_colon_pos, string remain)
{
    vector<string> read_inputs;
    int pos_1 = 0;
    for (int i = 0; i < semi_colon_pos.size(); i++)
    {
        int differ = semi_colon_pos[i] - pos_1;
        read_inputs.push_back(remain.substr(pos_1, differ));
        pos_1 = semi_colon_pos[i] + 1;
    }
    return read_inputs;
}

string ReadWeeksData::read_from_goals_information(string remain, PlayersInMatch &new_players)
{
    int goals_pos = remain.find(comma);
    string found_string = remain.substr(0, goals_pos);
    new_players.made_vector_of_goals(found_string);
    return remain.substr(goals_pos + 1);
}

string ReadWeeksData::read_from_team_one_players(string remain, PlayersInMatch &new_players)
{
    int team_one_pos = remain.find(comma);
    string found_string = remain.substr(0, team_one_pos);
    new_players.find_players_of_team_one(found_string);
    return remain.substr(team_one_pos + 1);
}

string ReadWeeksData::read_from_team_two_players(string remain, PlayersInMatch &new_players)
{
    int team_two_pos = remain.find(comma);
    string found_string = remain.substr(0, team_two_pos);
    new_players.find_players_of_team_two(found_string);
    return remain.substr(team_two_pos + 1);
}

void ReadWeeksData::calculate_team_score(PlayersInMatch &new_players, vector<shared_ptr<LeagueTeams>> &league_teams, int week_number)
{
    Calculator new_o(new_players);
    vector<shared_ptr<InfoOfPlayer>> team_one = new_o.calculating_players_of_team_one_score();
    vector<shared_ptr<InfoOfPlayer>> team_two = new_o.calculating_players_of_team_two_score();
    applying_players_of_team_score(team_one, team_two, league_teams, week_number);
}

void ReadWeeksData::applying_players_of_team_score(vector<shared_ptr<InfoOfPlayer>> team_one, vector<shared_ptr<InfoOfPlayer>> team_two,
                                                   vector<shared_ptr<LeagueTeams>> &league_teams, int week_number)
{
    for (int i = 0; i < league_teams.size(); i++)
    {
        if (league_teams[i]->has_the_same_name(team_1_name))
            league_teams[i]->adding_this_week_info(team_one, to_string(week_number));
        if (league_teams[i]->has_the_same_name(team_2_name))
            league_teams[i]->adding_this_week_info(team_two, to_string(week_number));
    }
}
