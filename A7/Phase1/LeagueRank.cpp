#include "LeagueRank.hpp"
const string str_goals_for = " | GF: ";
const string str_score = ": score: ";
const string str_goals_against = " | GA: ";
const string dot = ". ";
LeagueRank::LeagueRank(string week_num)
{
    this->week_number = week_num;
}

LeagueRank::LeagueRank(string _name, long int _total_score, long int _difference_of_goals, long int _total_goals_for, long int _total_goals_against)
{
    this->name = _name;
    this->total_score = _total_score;
    this->difference_of_goals = _difference_of_goals;
    this->total_goals_for = _total_goals_for;
    this->total_goals_against = _total_goals_against;
}

void LeagueRank::sort_the_vector_of_teams(vector<LeagueRank> &teams_rank)
{
    sort(teams_rank.begin(), teams_rank.end(), [](LeagueRank const &a, LeagueRank const &b) -> bool
         {
             if (a.total_score != b.total_score)
                 return a.total_score > b.total_score;
             if (a.difference_of_goals != b.difference_of_goals)
                 return a.difference_of_goals > b.difference_of_goals;
             if (a.total_goals_for != b.total_goals_for)
                 return a.total_goals_for > b.total_goals_for;
             if (a.name != b.name)
                 return a.name < b.name;
           return true; });
}

void LeagueRank::find_the_data_of_each_team(string week_num, const vector<shared_ptr<LeagueTeams>> &league_teams)
{
    vector<LeagueRank> teams_rank;
    for (int i = 0; i < league_teams.size(); i++)
    {
        long int difference_of_goals = league_teams[i]->calculate_total_goals_for(week_num) - league_teams[i]->calculate_total_goals_against(week_num);
        teams_rank.push_back(LeagueRank(league_teams[i]->get_team_name(), league_teams[i]->calculate_total_score(week_num),
                                        difference_of_goals, league_teams[i]->calculate_total_goals_for(week_num),
                                        league_teams[i]->calculate_total_goals_against(week_num)));
    }
    sort_the_vector_of_teams(teams_rank);
    printing_the_result(teams_rank);
}

void LeagueRank::printing_the_result(vector<LeagueRank> teams_rank)
{
    int counter = 1;
    for (int i = 0; i < teams_rank.size(); i++)
    {
        cout << counter << dot << teams_rank[i].name << str_score << teams_rank[i].total_score << str_goals_for
             << teams_rank[i].total_goals_for << str_goals_against << teams_rank[i].total_goals_against << endl;
        counter++;
    }
}
