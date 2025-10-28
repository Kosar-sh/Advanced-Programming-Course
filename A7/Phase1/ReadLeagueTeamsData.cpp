#include "ReadLeagueTeamsData.hpp"
const string str_goal_keeper = "Goalkeeper";
const string str_forward = "Forward";
const string str_midfielder = "Midfielder";
const string str_defender = "Defender";
const string str_file_name = "data/premier_league.csv";
const char semi_colon = ';';
const char comma = ',';
const char new_line='\n';
void ReadLeagueTeamsData::making_new_player(string remain, string position, vector<shared_ptr<Player>> &players)
{
    vector<int> colon_pos = find_semi_colon(remain);
    int first_pos = 0;
    add_players_one_by_one(remain, position, players, colon_pos, first_pos);
    shared_ptr<Player> new_one = make_shared<Player>(remain.substr(first_pos), position);
    players.push_back(new_one);
}

void ReadLeagueTeamsData::add_players_one_by_one(string remain, string position, vector<shared_ptr<Player>> &players, vector<int> colon_pos, int &first_pos)
{
    for (int i = 0; i < colon_pos.size(); i++)
    {
        int differ = colon_pos[i] - first_pos;
        shared_ptr<Player> new_one = make_shared<Player>(remain.substr(first_pos, differ), position);
        players.push_back(new_one);
        first_pos = colon_pos[i] + 1;
    }
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
