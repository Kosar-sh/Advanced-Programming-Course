#ifndef MATCH1_HPP
#define MATCH1_HPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;
class Match
{
private:
    vector<string> opponents_1;
    vector<string> opponents_2;
    string week_num;
    vector<string> scores_1;
    vector<int> scores_2;

public:
    Match(string _week_num);
    void add_new_match(string opponent_1, string opponent_2, string score1, string score2);
    bool has_the_same_week_num(string week_number);
    void print_all_the_matches_in_this_week();
    ~Match();
};

#endif