#include "ReadLeagueTeamsData.hpp"
const string str_goal_keeper = "Goalkeeper";
const string str_forward = "Forward";
const string str_midfielder = "Midfielder";
const string str_defender = "Defender";
const string str_file_name = "data/premier_league.csv";
const char semi_colon = ';';
const char comma = ',';
const char new_line = '\n';
const char dollar_sign = '$';
const char colon_sign = ':';

void ReadLeagueTeamsData::add_players_one_by_one(string remain, string position, vector<shared_ptr<Player>> &players, vector<int> colon_pos, int &first_pos)
{
    for (int i = 0; i < colon_pos.size(); i++)
    {
        find_the_price_and_name(remain, position, first_pos, colon_pos[i], players);
        first_pos = colon_pos[i] + 1;
    }
}

string ReadLeagueTeamsData::remove_dollar_sign(string price_of_player)
{
    string price;
    for (int i = 0; i < price_of_player.size(); i++)
    {
        if (price_of_player[i] != dollar_sign)
            price.push_back(price_of_player[i]);
    }
    return price;
}

void ReadLeagueTeamsData::find_the_price_and_name(string remain, string position, int start, int end, vector<shared_ptr<Player>> &players)
{
    int differ = end - start;
    int pos_of_colon = (remain.substr(start, differ)).find(colon_sign);
    name = (remain.substr(start, differ)).substr(0, pos_of_colon);
    string price_of_player = (remain.substr(start, differ)).substr(pos_of_colon + 1);
    string price = remove_dollar_sign(price_of_player);
    shared_ptr<Player> new_one = make_shared<Player>(name, position, stoi(price));
    players.push_back(new_one);
}

void ReadLeagueTeamsData::make_teams_one_by_one(vector<shared_ptr<LeagueTeams>> &league_teams)
{
    vector<shared_ptr<Player>> players;
    string remain = find_the_team_name();
    remain = make_Goalkeepers(remain, players);
    remain = make_Defenders(remain, players);
    remain = make_Midfielder(remain, players);
    make_Forwards(remain, players);
    shared_ptr<LeagueTeams> new_one = make_shared<LeagueTeams>(team_name, players);
    league_teams.push_back(new_one);
}

vector<shared_ptr<LeagueTeams>> ReadLeagueTeamsData::making_all_the_teams()
{
    fstream file;
    vector<shared_ptr<LeagueTeams>> league_teams;
    file.open(str_file_name, ios::in);
    getline(file, input, new_line);
    while (getline(file, input, new_line))
    {
        make_teams_one_by_one(league_teams);
    }
    file.close();
    return league_teams;
}

string ReadLeagueTeamsData::find_the_team_name()
{
    int name_of_team_pos = input.find(comma);
    team_name = input.substr(0, name_of_team_pos);
    string remain = input.substr(name_of_team_pos + 1);
    return remain;
}

vector<int> ReadLeagueTeamsData::find_semi_colon(string remain)
{
    vector<int> semi_colon_pos;
    for (int i = 0; i < remain.size(); i++)
    {
        if (remain[i] == semi_colon)
            semi_colon_pos.push_back(i);
    }
    return semi_colon_pos;
}

void ReadLeagueTeamsData::making_new_player(string remain, string position, vector<shared_ptr<Player>> &players)
{
    vector<int> colon_pos = find_semi_colon(remain);
    int first_pos = 0;
    add_players_one_by_one(remain, position, players, colon_pos, first_pos);
    int pos_of_colon = (remain.substr(first_pos)).find(colon_sign);
    name = (remain.substr(first_pos)).substr(0, pos_of_colon);
    string price_of_player = (remain.substr(first_pos)).substr(pos_of_colon + 1);
    string price = remove_dollar_sign(price_of_player);
    shared_ptr<Player> new_one = make_shared<Player>(name, position, stoi(price));
    players.push_back(new_one);
}

string ReadLeagueTeamsData::make_Goalkeepers(string remain, vector<shared_ptr<Player>> &players)
{
    int Goalkeepers_pos = (remain).find(comma);
    making_new_player(remain.substr(0, Goalkeepers_pos), str_goal_keeper, players);
    remain = remain.substr(Goalkeepers_pos + 1);
    return remain;
}

string ReadLeagueTeamsData::make_Defenders(string remain, vector<shared_ptr<Player>> &players)
{
    int Defenders_pos = (remain).find(comma);
    making_new_player(remain.substr(0, Defenders_pos), str_defender, players);
    remain = remain.substr(Defenders_pos + 1);
    return remain;
}

string ReadLeagueTeamsData::make_Midfielder(string remain, vector<shared_ptr<Player>> &players)
{
    int Midfielder_pos = (remain).find(comma);
    making_new_player(remain.substr(0, Midfielder_pos), str_midfielder, players);
    remain = remain.substr(Midfielder_pos + 1);
    return remain;
}

void ReadLeagueTeamsData::make_Forwards(string remain, vector<shared_ptr<Player>> &players)
{
    int Forwards_pos = (remain).find(comma);
    making_new_player(remain.substr(0, Forwards_pos), str_forward, players);
}
