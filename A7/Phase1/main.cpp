#include <iostream>
#include <string>
#include <vector>
#include "LeagueTeams.hpp"
#include "ReadLeagueTeamsData.hpp"
#include "Player.hpp"
#include "ReadWeeksData.hpp"
#include "Match.hpp"
#include <fstream>
#include "Match.hpp"
#include "Process.hpp"
using namespace std;

int main()
{
    ReadLeagueTeamsData input_teams;
    vector<shared_ptr<LeagueTeams>> league_teams = input_teams.making_all_the_teams();
    ReadWeeksData week_data_input;
    vector<shared_ptr<Match>> matches = week_data_input.read_from_weeks(league_teams);
    Process processing(league_teams, matches);
    processing.handling_commands();
}

