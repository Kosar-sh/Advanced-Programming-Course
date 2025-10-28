#include "Match.hpp"
const string str_space = " ";
const string vertical_bar = " | ";
Match::Match(string _week_num)
{
    this->week_num = _week_num;
}

void Match::add_new_match(string opponent_1, string opponent_2, string score1, string score2)
{
    opponents_1.push_back(opponent_1);
    opponents_2.push_back(opponent_2);
    scores_1.push_back(score1);
    scores_2.push_back(stoi(score2));
}

bool Match::has_the_same_week_num(string week_number)
{
    if (this->week_num == week_number)
    {
        return true;
    }
    return false;
}

void Match::print_all_the_matches_in_this_week()
{
    for (int i = 0; i < opponents_1.size(); i++)
    {
        cout << opponents_1[i] << str_space << scores_1[i] << vertical_bar << opponents_2[i] << str_space << scores_2[i] << endl;
    }
}

Match::~Match()
{
    delete this;
}
