#ifndef READ_DATA_HPP
#define READ_DATA_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <memory>
#include "LeagueTeams.hpp"
#include "Player.hpp"
using namespace std;

class ReadLeagueTeamsData
{
private:
    string input;
    string team_name;

public:
    void making_new_player(string remain, string position, vector<shared_ptr<Player>> &players);
    void add_players_one_by_one(string remain, string position, vector<shared_ptr<Player>> &players, vector<int> colon_pos, int &first_pos);
    void make_teams_one_by_one(vector<shared_ptr<LeagueTeams>> &league_teams);
    vector<shared_ptr<LeagueTeams>> making_all_the_teams();
    string make_Goalkeepers(string remain, vector<shared_ptr<Player>> &players);
    string make_Defenders(string remain, vector<shared_ptr<Player>> &players);
    string make_Midfielder(string remain, vector<shared_ptr<Player>> &players);
    void make_Forwards(string remain, vector<shared_ptr<Player>> &players);
    string find_the_team_name();
    vector<int> find_semi_colon(string remain);
};

#endif