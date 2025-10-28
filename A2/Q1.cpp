#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;
vector<int> input_list(int counter);
int find_max(int last_place, vector<int> numbers, int position);
int find_min(int last_place, vector<int> numbers, int position);
void changing_direction(int first_val, int &last_place, int &place, int &second_val, vector<int> numbers);
int search_the_list(vector<int> numbers, int counter, int place, int max, int min, int last_place);
int main()
{
    string entered_count;
    vector<int> numbers;
    int counter, min = 1, max = 0, place = 0, last_place = 0;
    getline(cin, entered_count);
    counter = stoi(entered_count); // convert string to int
    numbers = input_list(counter);
    search_the_list(numbers, counter, place, max, min, last_place);
}
vector<int> input_list(int counter)
{
    vector<int> numbers;
    string nums;
    getline(cin, nums);
    istringstream is(nums);
    int converted_num;
    while (is >> converted_num)
    {
        numbers.push_back(converted_num); // add nums seperated by space to vector
    }
    return numbers;
}
int find_max(int last_place, vector<int> numbers, int position)
{
    if (numbers[last_place] < numbers[position])
    {
        return numbers[position];
    }
    return numbers[last_place];
}
int find_min(int last_place, vector<int> numbers, int position)
{
    if (numbers[last_place] > numbers[position])
    {
        return numbers[position];
    }
    return numbers[last_place];
}
void changing_direction(int first_val, int &last_place, int &place, int &second_val, vector<int> numbers)
{
    int find = 0;
    last_place = place;
    place = first_val + place; // go to next element
    second_val = 0;
    find = last_place;
    cout << numbers[find] << " "; // print the element
}
int search_the_list(vector<int> numbers, int counter, int place, int max, int min, int last_place)
{
    int find = 0;
    if (place >= counter)
        exit(0); // end the program
    if (max == 0)
    {
        max = find_max(last_place, numbers, place);
        if (max == 0)
        {
            min = find_min(last_place, numbers, place);
            if (min == 0)
            {
                cout << max << " " << endl; // reach many 0's print one of them
                exit(0);
            }
        }
        changing_direction(max, last_place, place, min, numbers);
        search_the_list(numbers, counter, place, max, min, last_place);
    }
    else if (min == 0 && place != 0)
    {
        min = find_min(last_place, numbers, place);
        changing_direction(min, last_place, place, max, numbers);
        search_the_list(numbers, counter, place, max, min, last_place);
    }
    return 0;
}