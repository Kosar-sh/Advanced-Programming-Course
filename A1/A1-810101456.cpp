#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;
int BreakCheak(string date_1, string date_2, int num1, int num2);
void start_writing(string enter, vector<string> &date, int counter);
void present_day(string enter, vector<string> date, vector<vector<string>> matn);
int finding_maximom(vector<vector<string>> matn, vector<string> date);
void PresentLongest(string enter, vector<string> date, vector<vector<string>> matn, int counter);
int UsedOfWords(string DiaryWords, int sumation);
void PrintingBests(vector<vector<string>> matn, int match, vector<string> date);
void PresentBests(string enter, vector<string> date, vector<vector<string>> matn, int counter);

int main()
{
    int space = 0, counter = -1;
    string enter, command;
    vector<string> date;
    vector<vector<string>> matn;
    while (getline(cin, enter, '\n'))//until no command enter
    {
        for (int i = 0; i < enter.size(); i++)
        {
            if (enter[i] == ' ')
            {
                space = i;
                break;
            }
        }
        if (space != 0)
        {
            command = enter.substr(0, space);
        }
        if (command == "start_day")
        {
            matn.push_back(vector<string>());
            counter++;
            start_writing(enter, date, counter);
        }
        else if (command == "show_day")
        {
            present_day(enter, date, matn);
        }
        else if (enter == "show_the_longest_day")
        {
            PresentLongest(enter, date, matn, counter);
        }
        else if (enter == "show_the_best_day")
        {
            PresentBests(enter, date, matn, counter);
        }
        else
        {
            matn[counter].push_back(enter);//adding text to pre_enter date
            matn[counter].push_back("\n");
        }
    }
    return 0;
}
int BreakCheak(string date_1, string date_2, int num1, int num2)
{
    //find the oldest date in diary
    string day1 = date_1.substr(0, 2);
    string month1 = date_1.substr(3, 2);
    string year1 = date_1.substr(6, 4);
    string day2 = date_2.substr(0, 2);
    string month2 = date_2.substr(3, 2);
    string year2 = date_2.substr(6, 4);
    if (stoi(year1) > stoi(year2))
    {
        return num2;
    }
    else if (stoi(year1) < stoi(year2))
    {
        return num1;
    }
    else
    {
        if (stoi(month1) < stoi(month2))
        {
            return num1;
        }
        else if (stoi(month1) > stoi(month2))
        {
            return num2;
        }
        else
        {
            if (stoi(day1) > stoi(day2))
            {
                return num2;
            }
            else if (stoi(day1) < stoi(day2))
            {
                return num1;
            }
        }
    }
    return 0;
}
void start_writing(string enter, vector<string> &date, int counter)
{
    string day;
    enter.erase(enter.begin(), enter.begin() + 10);
    date.push_back(enter);//add a new date
}
void present_day(string enter, vector<string> date, vector<vector<string>> matn)
{
    int find = 0;
    enter.erase(enter.begin(), enter.begin() + 9);//separate date from command
    for (int i = 0; i < date.size(); i++)
    {
        if (date[i] == enter)
        {
            find = i;
        }
    }
    for (int i = 0; i < matn[find].size(); i++)
    {
        cout << matn[find][i];
    }
}
int finding_maximom(vector<vector<string>> matn, vector<string> date)
{
    int find = 0, num1 = 0, num2 = 0;
    int sum = 0;
    int maximom = 0;
    for (int i = 0; i < matn.size(); i++)
    {
        for (int j = 0; j < matn[i].size(); j++)
        {
            sum = sum + matn[i][j].size();
        }
        if (maximom < sum)
        {
            maximom = sum;
            find = i;
        }
        else if (maximom == sum)
        {
            num1 = find;
            num2 = i;
            find = BreakCheak(date[num1], date[num2], num1, num2);//similar character<<the oldest choose

            sum = 0;
        }
    }
    return find;
}
void PresentLongest(string enter, vector<string> date, vector<vector<string>> matn, int counter)
{
    int MatchDate = 0;
    MatchDate = finding_maximom(matn, date);//the longest day
    cout << date[MatchDate] << endl;
    int summery = 0;
    for (int i = 0; i < matn[MatchDate].size(); i++)
    {
        for (int j = 0; j < matn[MatchDate][i].size(); j++)
        {
            summery++;
            if (summery <= 20)//20 characters allowed
            {
                cout << matn[MatchDate][i][j];
            }
            else
            {
                cout << "...\n";
                i = matn[MatchDate].size();//break 2 loops
                break;
            }
        }
    }
}
int UsedOfWords(string DiaryWords, int sumation)
{
    string words;
    vector<string> BesrWords;
    int sum = 0;
    ifstream best_words;
    best_words.open("positive_word", ios::in);//opening text file
    while (getline(best_words, words))//put words in vector
    {
        BesrWords.push_back(words);
        sum++;
    }
    for (int i = 0; i < BesrWords.size(); i++)
    {
        if (BesrWords[i] == DiaryWords)//check similarity
        {
            sumation++;
            return sumation;//total match<<increment each time
        }
    }
    best_words.close();
    return sumation;
}
void PrintingBests(vector<vector<string>> matn, int match, vector<string> date)
{
    int summery = 0;
    cout << date[match] << endl;
    for (int i = 0; i < matn[match].size(); i++)
    {
        for (int j = 0; j < matn[match][i].size(); j++)
        {
            summery++;
            if (summery <= 20)//until 20 character print it
            {
                cout << matn[match][i][j];
            }
            else
            {
                cout << "...\n";
                i = matn[match].size();//break two loops
                break;
            }
        }
    }
}
void PresentBests(string enter, vector<string> date, vector<vector<string>> matn, int counter)
{
    int position1 = 0, position2 = 0, total = 0, maximom = 0, T_Count = 0, bestir = 0;
    int num1 = 0, num2 = 0;
    string CutToPiece;
    for (int i = 0; i < matn.size(); i++)
    {
        for (int j = 0; j < matn[i].size(); j++)
        {
            position1 = 0;
            position2 = 0;
            for (int k = 0; k < matn[i][j].size(); k++)
            {
                if (matn[i][j][k] == ' ')//reach space<<pour the string in cut to piece <<check similarity
                {
                    position2 = k;
                    total = position2 - position1;
                    CutToPiece = matn[i][j].substr(position1, total);
                    T_Count = UsedOfWords(CutToPiece, T_Count);
                    position1 = position2 + 1;
                }
                else if (k == (matn[i][j].size() - 1))//reach end of the line<<do the same above
                {
                    position2 = k + 1;
                    total = position2 - position1;
                    CutToPiece = matn[i][j].substr(position1, total);
                    T_Count = UsedOfWords(CutToPiece, T_Count);
                }
            }
            if (j == matn[i].size() - 1)//one day reach end
            {
                if (maximom < T_Count)
                {
                    bestir = i;
                }
                else if (maximom == T_Count)//similar number << choose the oldest
                {
                    num1 = bestir;
                    num2 = i;
                    bestir = BreakCheak(date[num1], date[num2], num1, num2);
                }

                T_Count = 0;
            }
        }
    }
    PrintingBests(matn, bestir, date);
}
