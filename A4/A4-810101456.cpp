#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

using namespace std;

struct timetable
{
    int start;
    int end;
    int day;
    int time_difference;
};

int initial_condition = 0;
int not_found = -1;
const char csv_delimiter = ',';
const char member_id_delimiter = '$';
const string invalid_arguments = "INVALID_ARGUMENTS";
const string employee_not_found = "EMPLOYEE_NOT_FOUND";
const string invalid_level = "INVALID_LEVEL";
const string level_not_found = "LEVEL";
const string invalid_interval = "INVALID_INTERVAL";
const string team_not_found = "TEAM_NOT_FOUND";
const string address_salary_configs = "salary_configs.csv";
const string address_teams = "teams.csv";
const string address_working_hours = "working_hours.csv";
const string address_employee = "employees.csv";
const string semicolon = ": ";
const string team_id = "Team ID";
const string id = "ID";
const string salary = "Salary";
const string not_exist = "0";
const string bonus = "Bonus";
const string tax = "Tax";
const string total_earning = "Total Earning";
const string member_id = "Member ID";
const string day = "Day ";
const string hashtag = "#";
const string no_bonus_team = "NO_BONUS_TEAMS";
const string ok = "OK";
const string periods_with_min_working_employees = "Period(s) with Min Working Employees";
const string periods_with_max_working_employees = "Period(s) with Max Working Employees";
const string space = " ";
const string name = "Name";
const string total_working_hour = "Total Working Hours";
const string more_to_add = "---";
const string no_team = "N/A";
const string dash = "-";
const string slash = "/";
const string days_with_max_working_hours = "Day(s) with Max Working Hours";
const string days_with_min_working_hours = "Day(s) with Min Working Hours";
vector<string> Set_values_salary = {"Base Salary", "Salary Per Hour", "Salary Per Extra Hour", "Official Working Hours", "Tax"};
vector<string> team_print_val = {"ID", "Head ID", "Head Name", "Team Total Working Hours", "Average Member Working Hours", "Bonus"};
vector<string> special_employee_print = {"Name", "Age", "Level", "Team ID", "Total Working Hours", "Absent Days"};
vector<string> prescribed_orders = {"report_salaries", "update_team_bonus", "add_working_hours",
                                    "show_salary_config", "delete_working_hours", "update_salary_config", "report_total_hours_per_day",
                                    "report_employee_per_hour", "report_team_salary", "report_employee_salary", "find_teams_for_bonus"};

class Employee;
class SoftwareSalary;
class Team;
class SalaryGiven;

class Employee
{
private:
    string id;
    string name;
    int age;
    string level;
    vector<timetable> all_presents;
    string team_id;

public:
    void assign_first_val_of_employee(string _id, string _name, int _age, string _level);
    void add_employee_to_team(string team_id_1);
    bool is_it_same_employee(string id_1);
    void add_timing_hours(int _day, int _start, int _end);
    void delete_timing_hours(int day);
    bool this_day_exist(int day);
    bool no_interference_occurs(int day, int start, int end);
    string get_name() { return name; };
    string get_id() { return id; };
    string get_team_id() { return team_id; };
    string get_level() { return level; };
    int get_age() { return age; };
    int calculate_total_working_hours();
    int special_day_working_hours(int _day);
    int calculate_absent_days();
    vector<timetable> get_working_hours() { return all_presents; };
    bool any_time_interval_happen(timetable current_timing, int start2, int end2);
};

bool Employee::this_day_exist(int day)
{
    for (int i = 0; i < all_presents.size(); i++)
    {
        if (all_presents[i].day == day)
            return true;
    }
    return false;
}

bool Employee::any_time_interval_happen(timetable current_timing, int start2, int end2)
{
    if (current_timing.start == start2 || current_timing.end == end2)
        return false;
    else if (current_timing.start < start2)
    {
        if (start2 < current_timing.end)
        {
            return false;
        }
        else if (current_timing.start > start2)
            if (end2 > current_timing.start)
                return false;
    }
    return true;
}

bool Employee::no_interference_occurs(int day, int start, int end)
{
    vector<int> number_of_days;
    for (int i = 0; i < all_presents.size(); i++)
    {
        if (all_presents[i].day == day)
            number_of_days.push_back(i);
    }
    int flag = initial_condition;
    for (int i = 0; i < number_of_days.size(); i++)
    {
        if (!any_time_interval_happen(all_presents[number_of_days[i]], start, end))
            flag++;
    }
    if (flag == initial_condition)
        return true;
    return false;
}

void Employee::delete_timing_hours(int _day)
{
    vector<timetable> new_timing;
    for (int i = 0; i < all_presents.size(); i++)
    {
        if (all_presents[i].day != _day)
        {
            int counter = new_timing.size();
            new_timing.push_back(timetable());
            new_timing[counter] = all_presents[i];
        }
    }
    all_presents = new_timing;
}

int Employee::special_day_working_hours(int _day)
{
    int work_hours_sum = initial_condition;
    for (int i = 0; i < all_presents.size(); i++)
    {
        if (all_presents[i].day == _day)
            work_hours_sum += all_presents[i].time_difference;
    }
    return work_hours_sum;
}

int Employee::calculate_total_working_hours()
{
    int total_hours_sum = initial_condition;
    for (int i = 0; i < all_presents.size(); i++)
        total_hours_sum += all_presents[i].time_difference;
    return total_hours_sum;
}

int Employee::calculate_absent_days()
{
    vector<int> days;
    for (int i = 0; i < all_presents.size(); i++)
    {
        int flag =initial_condition;
        for (int k = 0; k < days.size(); k++)
        {
            if (all_presents[i].day == days[k])
                flag++;
        }
        if (flag == initial_condition)
            days.push_back(all_presents[i].day);
    }
    int present_days = days.size();
    int absent_days = 30 - present_days;
    return absent_days;
}

void Employee::assign_first_val_of_employee(string _id, string _name, int _age, string _level)
{
    age = _age;
    id = _id;
    name = _name;
    level = _level;
    team_id = not_exist;
}

void Employee::add_employee_to_team(string _team_id)
{
    team_id = _team_id;
}

bool Employee::is_it_same_employee(string _id)
{
    if (_id == id)
        return true;
    return false;
}

void Employee::add_timing_hours(int _day, int _start, int _end)
{
    int where_to_add = this->all_presents.size();
    this->all_presents.push_back(timetable());
    this->all_presents[where_to_add].day = _day;
    this->all_presents[where_to_add].end = _end;
    this->all_presents[where_to_add].start = _start;
    this->all_presents[where_to_add].time_difference = _end - _start;
}

class SalaryGiven
{
private:
    string level;
    double salary_base;
    double hour_per_salary;
    double hour_extra_per_salary;
    double hours_working_official;
    double percentage_tax;

public:
    void assigning_first_val(string _level, double _salary_base, double _hour_per_salary, double _hour_extra_per_salary, double _hours_working_official, double _percentage_tax);
    double get_official_working_hour() { return hours_working_official; };
    double get_salary_base() { return salary_base; };
    double get_salary_per_hour() { return hour_per_salary; };
    double get_tax_percentage() { return percentage_tax; };
    double get_salary_per_extra_hour() { return hour_extra_per_salary; };
    string get_level() { return level; };
    void changing_parameters_of_level(double _salary_base, double _hour_per_salary, double _hour_extra_per_salary, double _hours_working_official, double _percentage_tax);
};

void SalaryGiven::assigning_first_val(string _level, double _salary_base, double _hour_per_salary, double _hour_extra_per_salary, double _hours_working_official, double _percentage_tax)
{
    level = _level;
    salary_base = _salary_base;
    hour_per_salary = _hour_per_salary;
    hour_extra_per_salary = _hour_extra_per_salary;
    hours_working_official = _hours_working_official;
    percentage_tax = _percentage_tax;
}

void SalaryGiven::changing_parameters_of_level(double _salary_base, double _hour_per_salary, double _hour_extra_per_salary, double _hours_working_official, double _percentage_tax)
{
    salary_base = _salary_base;
    hour_per_salary = _hour_per_salary;
    hour_extra_per_salary = _hour_extra_per_salary;
    hours_working_official = _hours_working_official;
    percentage_tax = _percentage_tax;
}

class Team
{
private:
    string id_team;
    int bonus;
    vector<string> member_ids;
    string id_head_team;
    double bonus_min_working_hours;
    double bonus_working_hours_max_variance;

public:
    void assigning_new_team(string team_id, vector<string> members, string head, double min, double max);
    pair<vector<string>, string> find_team_members();
    void set_new_bonus(int new_bonus);
    vector<string> get_members() { return member_ids; };
    string get_team_id() { return id_team; };
    string get_id_head_team() { return id_head_team; };
    double get_bonus_min_working() { return bonus_min_working_hours; };
    double get_bonus_working_hours_max() { return bonus_working_hours_max_variance; };
    int get_bonus() { return bonus; };
    bool has_the_same_id(string _id_team);
    int get_all_members_WH(vector<Employee> Employees);
    string get_head_name(vector<Employee> Employees);
};

string Team::get_head_name(vector<Employee> Employees)
{
    for (int i = 0; i < Employees.size(); i++)
    {
        if (Employees[i].get_id() == id_head_team)
            return Employees[i].get_name();
    }
    return not_exist;
}

int Team::get_all_members_WH(vector<Employee> Employees)
{
    int total_WH = initial_condition;
    for (int i = 0; i < Employees.size(); i++)
    {
        for (int j = 0; j < member_ids.size(); j++)
        {
            if (Employees[i].get_id() == member_ids[j])
                total_WH += Employees[i].calculate_total_working_hours();
        }
    }
    return total_WH;
}

pair<vector<string>, string> Team::find_team_members()
{
    pair<vector<string>, string> result = make_pair(member_ids, id_team);
    return result;
}

bool Team::has_the_same_id(string _id_team)
{
    if (id_team == _id_team)
        return true;
    return false;
}

void Team::set_new_bonus(int _new_bonus)
{
    bonus = _new_bonus;
}

void Team::assigning_new_team(string team_id, vector<string> members, string head, double min, double max)
{
    id_team = team_id;
    member_ids = members;
    id_head_team = head;
    bonus_min_working_hours = min;
    bonus_working_hours_max_variance = max;
    bonus = initial_condition;
}

class ReadingInput
{
private:
    vector<Employee> Employees;
    vector<Team> teams;
    vector<SalaryGiven> salary_parameters;

public:
    void start_processing(string file_name);
    vector<Employee> get_employees() { return Employees; };
    vector<Team> get_team() { return teams; };
    vector<SalaryGiven> get_salary() { return salary_parameters; };
    void read_from_employee(string file_name);
    vector<string> read_line_by_line(string filename);
    void assigning_new_emp(vector<string> read_context, int start);
    void read_from_working_hours(string file_name);
    void assign_times_to_particular_employee(vector<string> read_context, int start);
    void read_from_teams(string file_name);
    void add_new_team(vector<string> read_context, int i);
    void assign_team_to_members(vector<string> members, string team_id);
    void add_new_config_for_salary(vector<string> read_context, int start);
    void which_people_are_in_this_team();
    void read_from_salary_config(string file_name);
    vector<string> find_members(string all_members);
    vector<string> find_members_id(string all_members, vector<int> delimiter_poses);
    pair<int, int> separate_start_end(vector<string> read_context, int start);
    vector<int> find_pos_of_delimiter(string all_founded_members);
};
void ReadingInput::add_new_config_for_salary(vector<string> read_context, int start)
{
    int counter = salary_parameters.size();
    salary_parameters.push_back(SalaryGiven());
    string level = read_context[start];
    double base_salary = stod(read_context[start + 1]), per_hour_salary = stod(read_context[start + 2]), extra_per_hour = stod(read_context[start + 3]);
    double official_working_hour = stod(read_context[start + 4]), tax_percent = stod(read_context[start + 5]);
    salary_parameters[counter].assigning_first_val(level, base_salary, per_hour_salary, extra_per_hour, official_working_hour, tax_percent);
}

void ReadingInput::start_processing(string file_name)
{
    read_from_employee(file_name);
    read_from_working_hours(file_name);
    read_from_teams(file_name);
    which_people_are_in_this_team();
    read_from_salary_config(file_name);
}

void ReadingInput::read_from_salary_config(string file_name)
{
    string filename = file_name + slash + address_salary_configs;
    vector<string> read_context = read_line_by_line(filename);
    for (int i = 0; i < read_context.size(); i++)
    {
        if (i % 6 == initial_condition)
            add_new_config_for_salary(read_context, i);
    }
}
void ReadingInput::assign_team_to_members(vector<string> members, string team_id)
{
    for (int j = 0; j < members.size(); j++)
    {
        for (int k = 0; k < Employees.size(); k++)
        {
            if (Employees[k].is_it_same_employee(members[j]))
                Employees[k].add_employee_to_team(team_id);
        }
    }
}
void ReadingInput::which_people_are_in_this_team()
{
    for (int i = 0; i < teams.size(); i++)
    {
        pair<vector<string>, string> found_ones = teams[i].find_team_members();
        string team_id = found_ones.second;
        vector<string> members = found_ones.first;
        assign_team_to_members(members, team_id);
    }
}

void ReadingInput::add_new_team(vector<string> read_context, int i)
{
    int counter = teams.size();
    teams.push_back(Team());
    vector<string> all_members = find_members(read_context[i + 2]);
    teams[counter].assigning_new_team(read_context[i], all_members, read_context[i + 1], stod(read_context[i + 3]), stod(read_context[i + 4]));
}

void ReadingInput::read_from_teams(string file_name)
{
    string filename = file_name + slash + address_teams;
    vector<string> read_context = read_line_by_line(filename);
    for (int i = 0; i < read_context.size(); i++)
    {
        if (i % 5 == initial_condition)
            add_new_team(read_context, i);
    }
}

void ReadingInput::read_from_working_hours(string file_name)
{
    string filename = file_name + slash + address_working_hours;
    vector<string> read_context = read_line_by_line(filename);
    for (int i = 0; i < read_context.size(); i++)
    {
        if (i % 3 == initial_condition)
            assign_times_to_particular_employee(read_context, i);
    }
}

pair<int, int> ReadingInput::separate_start_end(vector<string> read_context, int start)
{
    int pos = read_context[start + 2].find(dash);
    int start_1 = stoi(read_context[start + 2].substr(initial_condition, pos));
    int end = stoi(read_context[start + 2].substr(pos + 1));
    pair<int, int> time_sch = make_pair(start_1, end);
    return time_sch;
}

void ReadingInput::assign_times_to_particular_employee(vector<string> read_context, int start)
{
    for (int j = 0; j < Employees.size(); j++)
    {
        if (Employees[j].is_it_same_employee(read_context[start]))
        {
            pair<int, int> time_sch = separate_start_end(read_context, start);
            int day = stoi(read_context[start + 1]);
            Employees[j].add_timing_hours(day, time_sch.first, time_sch.second);
        }
    }
}

void ReadingInput::read_from_employee(string file_name)
{
    string filename = file_name + slash + address_employee;
    vector<string> read_context = read_line_by_line(filename);
    for (int i = 0; i < read_context.size(); i++)
    {
        if (i % 4 == initial_condition)
            assigning_new_emp(read_context, i);
    }
}

void ReadingInput::assigning_new_emp(vector<string> read_context, int start)
{
    int place_to_add = Employees.size();
    Employees.push_back(Employee());
    string id = read_context[start], name = read_context[start + 1], level = read_context[start + 3];
    int age = stoi(read_context[start + 2]);
    Employees.at(place_to_add).assign_first_val_of_employee(id, name, age, level);
}

vector<string> ReadingInput::read_line_by_line(string filename)
{
    vector<string> result;
    string lines_of_file;
    ifstream input_file(filename);
    getline(input_file, lines_of_file);
    while (getline(input_file, lines_of_file))
    {
        istringstream line(lines_of_file);
        string read_string;
        while (getline(line, read_string, csv_delimiter))
            result.push_back(read_string);
    }
    input_file.close();
    return result;
}

vector<int> ReadingInput::find_pos_of_delimiter(string all_founded_members)
{
    vector<int> delimiter_poses;
    for (int i = 0; i < all_founded_members.size(); i++)
    {
        if (all_founded_members[i] == member_id_delimiter)
            delimiter_poses.push_back(i);
    }
    return delimiter_poses;
}

vector<string> ReadingInput::find_members_id(string all_members, vector<int> delimiter_poses)
{
    vector<string> member_1;
    int pos =initial_condition;
    for (int i = 0; i < delimiter_poses.size(); i++)
    {
        int set_difference = delimiter_poses[i] - pos;
        string member = all_members.substr(pos, set_difference);
        member_1.push_back(member);
        pos = delimiter_poses[i] + 1;
    }
    member_1.push_back(all_members.substr(pos));
    return member_1;
}

vector<string> ReadingInput::find_members(string all_members)
{
    vector<int> delimiter_poses = find_pos_of_delimiter(all_members);
    vector<string> member_1 = find_members_id(all_members, delimiter_poses);
    return member_1;
}

class SoftwareSalary
{
private:
    vector<Employee> Employees;
    vector<Team> teams;
    vector<SalaryGiven> salary_parameters;

public:
    void receive_input_information(ReadingInput informations);
    void report_employee_salary(string input_command, int pos);
    void report_employee_per_hour(string input_command, int pos);
    void input_handling();
    bool separate_day1_day2(string input_command, int &start, int &end);
    void report_total_hours_per_day(string input_command, int pos);
    void update_salary_parameters(string input_command, int pos);
    vector<string> reporting_salaries();
    int calculate_earning(Employee found_one, int bonus);
    string update_team_bonus(string other_parts);
    int calculate_salary_without_bonus(SalaryGiven for_found_one, int working_hour);
    int add_bonus_to_salary(int bonus, double salary);
    int calculate_tax_of_salary(double salary_before_tax, int tax_percentage);
    string add_working_hours(string rest_remain);
    void validating_working_hours_args(string &output, vector<string> info, int id);
    void show_parameter_of_salary(string otherwise);
    int which_level_is_requested(string otherwise);
    string delete_working_hours(string rest_remain);
    string change_salary_parameters(int found, vector<string> info);
    void printing_team_members_salary(Team current_team);
    void reporting_team(string id);
    vector<pair<string, float>> find_employee_in_the_period(int start, int end);
    int how_many_work_in_this_hour(int start, int end);
    vector<pair<int, int>> working_hours_in_day(int start, int end, vector<int> &days_number);
    void show_one_employee_salary(Employee employee);
    void print_reported_salaries(vector<string> output_parameters);
    int the_employee_exist(string id);
    vector<string> transfer_string_to_vector(vector<int> pos_of_space, string rest_remain);
    vector<string> separate_sentence_by_space(string rest_remain);
    void show_special_employee(Employee employee);
    int salary_level_for_employee(Employee found_one);
    int which_team_index(Employee employee);
    void show_bonus_salary(Employee employee, int team_id, int &total, int level);
    void show_total_earning_salary(Employee employee, int team_id, int total, int level);
    double can_base_salary_update(SalaryGiven found_level, string new_base);
    double can_tax_update(SalaryGiven found_level, string new_tax);
    double can_work_hour_update(SalaryGiven found_level, string new_work_hour);
    double can_salary_per_extra_hour_update(SalaryGiven found_level, string new_salary_per_extra);
    double can_salary_per_hour_update(SalaryGiven found_level, string new_salary_per_hour);
    int find_id(string id);
    bool separate_start_end_time(string rest_remain, int &start_1, int &end_1);
    void printing_max_min_output_hours(vector<pair<string, float>> periods);
    void finding_second_output(vector<pair<int, int>> output, vector<int> number_of_days);
    void find_min_max_in_outputs(vector<pair<int, int>> output, int &max, int &min);
    int the_level_exist(string level_entered);
    vector<int> sort_employee();
    vector<int> sort_team_members(Team current_team);
    vector<string> find_bonus_team();
    bool check_working_hours(Team current_team);
    bool check_variance(Team current_team);
    float calculate_variance_team(vector<int> hours);
    vector<string> sorting_base_work_hour(vector<int> result);
    void printing_bonus_teams(vector<string> result);
    bool check_correctness_of_day(int day);
    int add_bonus_amount(string id_team_found);
    int the_team_exist(string team_id);
    bool checking_correctness_of_time(int start, int end);
    void find_min_max_averages(vector<pair<string, float>> periods, float &min, float &max);
    string merge_max_min_average_hours(float limit, vector<pair<string, float>> periods);
    void printing_team_first_vals(int found_team);
    float average_working_hour(int all_working_hours, int number_of_members);
    string merge_days_numbers_for_print(vector<pair<int, int>> output, int limit);
    void make_pair_for_days_hours(vector<pair<int, int>> &output, int curr_day, int sum_h);
    string finding_team_id_of_employee(Employee employee);
};

void SoftwareSalary::receive_input_information(ReadingInput informations)
{
    Employees = informations.get_employees();
    teams = informations.get_team();
    salary_parameters = informations.get_salary();
};

void SoftwareSalary::report_employee_salary(string input_command, int pos)
{
    int status = the_employee_exist(input_command.substr(pos + 1));
    if (status != -1)
        show_one_employee_salary(Employees[status]);
    else
        cout << employee_not_found << endl;
}

void SoftwareSalary::report_employee_per_hour(string input_command, int pos)
{
    int start = initial_condition, end = initial_condition;
    if (separate_start_end_time(input_command.substr(pos + 1), start, end))
    {
        vector<pair<string, float>> periods = find_employee_in_the_period(start, end);
        for (int i = 0; i < periods.size(); i++)
            cout << periods[i].first << semicolon << fixed << setprecision(1) << periods[i].second << endl;
        cout << more_to_add << endl;
        printing_max_min_output_hours(periods);
    }
    else
        cout << invalid_arguments << endl;
}

bool SoftwareSalary::separate_day1_day2(string input_command, int &start, int &end)
{
    int pos = input_command.find(space);
    int start_day = stoi(input_command.substr(initial_condition, pos));
    int end_day = stoi(input_command.substr(pos + 1));
    if (check_correctness_of_day(start_day) && check_correctness_of_day(end_day) && start_day < end_day)
    {
        start = start_day;
        end = end_day;
        return true;
    }
    return false;
}

void SoftwareSalary::report_total_hours_per_day(string input_command, int pos)
{
    int start = initial_condition, end = initial_condition;
    if (separate_day1_day2(input_command.substr(pos + 1), start, end))
    {
        vector<int> number_of_days;
        vector<pair<int, int>> output = working_hours_in_day(start, end, number_of_days);
        for (int i = 0; i < output.size(); i++)
            cout << day << hashtag << output[i].first << semicolon << output[i].second << endl;
        cout << more_to_add << endl;
        finding_second_output(output, number_of_days);
    }
    else
        cout << invalid_arguments << endl;
}

void SoftwareSalary::update_salary_parameters(string input_command, int pos)
{
    string status;
    vector<string> info = separate_sentence_by_space(input_command.substr(pos + 1));
    int return_val = the_level_exist(info[0]);
    if (return_val != not_found)
        cout << change_salary_parameters(return_val, info) << endl;
    else
        cout << invalid_level << endl;
}

int SoftwareSalary::calculate_tax_of_salary(double salary_before_tax, int tax_percentage)
{
    float tax = (float)(salary_before_tax * tax_percentage) / 100.0;
    return int(round(tax));
}

int SoftwareSalary::add_bonus_to_salary(int bonus, double salary)
{
    float the_amount_of_increase = initial_condition;
    if (bonus != 0)
        the_amount_of_increase = (float)(salary * bonus) / 100.0;
    return round(the_amount_of_increase);
}

int SoftwareSalary::calculate_salary_without_bonus(SalaryGiven for_found_one, int working_hour)
{
    double salary_per_hour = for_found_one.get_salary_per_hour();
    double salary_extra_per_hour = for_found_one.get_salary_per_extra_hour();
    double official_working_hour = for_found_one.get_official_working_hour();
    double total =initial_condition;
    if (working_hour <= official_working_hour)
    {
        salary_per_hour = salary_per_hour * working_hour;
        total = salary_per_hour + for_found_one.get_salary_base();
    }
    else
    {
        salary_per_hour = salary_per_hour * official_working_hour;
        salary_extra_per_hour = (working_hour - official_working_hour) * salary_extra_per_hour;
        total = salary_extra_per_hour + salary_per_hour + for_found_one.get_salary_base();
    }
    return int(round(total));
}

int SoftwareSalary::calculate_earning(Employee found_one, int bonus)
{
    for (int k = 0; k < salary_parameters.size(); k++)
    {
        if (found_one.get_level() == salary_parameters[k].get_level())
        {
            float total = calculate_salary_without_bonus(salary_parameters[k], found_one.calculate_total_working_hours());
            total = total + add_bonus_to_salary(bonus, total);
            total = total - calculate_tax_of_salary(total, salary_parameters[k].get_tax_percentage());
            return int(round(total));
        }
    }
    return -1;
}

int SoftwareSalary::add_bonus_amount(string id_team_found)
{
    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i].has_the_same_id(id_team_found))
            return teams[i].get_bonus();
    }
    return 0;
}

vector<int> SoftwareSalary::sort_employee()
{
    vector<int> sort_ids;
    for (int i = 0; i < Employees.size(); i++)
        sort_ids.push_back(stoi(Employees[i].get_id()));
    sort(sort_ids.begin(), sort_ids.end());
    vector<int> sort_emp;
    for (int i = 0; i < sort_ids.size(); i++)
    {
        for (int k = 0; k < Employees.size(); k++)
        {
            if (stoi(Employees[k].get_id()) == sort_ids[i])
                sort_emp.push_back(k);
        }
    }
    return sort_emp;
}

vector<string> SoftwareSalary::reporting_salaries()
{
    vector<string> result;
    vector<int> sort_ids = sort_employee();
    for (int i = 0; i < sort_ids.size(); i++)
    {
        result.push_back(Employees[sort_ids[i]].get_id());
        result.push_back(Employees[sort_ids[i]].get_name());
        result.push_back(to_string(Employees[sort_ids[i]].calculate_total_working_hours()));
        result.push_back(to_string(calculate_earning(Employees[sort_ids[i]], add_bonus_amount(Employees[sort_ids[i]].get_team_id()))));
    }
    return result;
}

void SoftwareSalary::print_reported_salaries(vector<string> output_parameters)
{
    for (int i = 0; i < output_parameters.size(); i++)
    {
        if (i % 4 == initial_condition)
        {
            cout << id << semicolon << output_parameters.at(i) << endl;
            cout << name << semicolon << output_parameters.at(i + 1) << endl;
            cout << total_working_hour << semicolon << output_parameters.at(i + 2) << endl;
            cout << total_earning << semicolon << output_parameters.at(i + 3) << endl;
            cout << more_to_add << endl;
        }
    }
}

int SoftwareSalary::the_team_exist(string team_id)
{
    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i].get_team_id() == team_id)
            return i;
    }
    return -1;
}

bool check_correctness_of_bonus(int new_bonus)
{
    if (new_bonus >= 0 && new_bonus <= 100)
        return true;
    return false;
}
string SoftwareSalary::update_team_bonus(string other_parts) //(vector<Team> &teams, string other_parts)
{
    string output;
    int pos = other_parts.find(" ");
    int sth = the_team_exist(other_parts.substr(initial_condition, pos));
    if (sth != -1)
    {
        int new_bonus = stoi(other_parts.substr(pos + 1));
        if (check_correctness_of_bonus(new_bonus))
        {
            teams[sth].set_new_bonus(new_bonus);
            output = ok;
        }
        else
            output = invalid_arguments;
    }
    else
        output = team_not_found;
    return output;
}

bool SoftwareSalary::checking_correctness_of_time(int start, int end)
{
    if (end > start)
    {
        if (end > 0 && end < 25 && start > -1 && start < 24)
            return true;
        return false;
    }
    else
        return false;
}

bool SoftwareSalary::check_correctness_of_day(int day)
{
    if (day > 0 && day < 31)
        return true;
    return false;
}

int SoftwareSalary::the_employee_exist(string id)
{
    for (int i = 0; i < Employees.size(); i++)
    {
        if (Employees[i].is_it_same_employee(id))
            return i;
    }
    return -1;
}

vector<int> find_place_of_space(string rest_remain)
{
    vector<int> pos_of_space;
    for (int i = 0; i < rest_remain.size(); i++)
    {
        if (rest_remain[i] == ' ')
            pos_of_space.push_back(i);
    }
    return pos_of_space;
}

vector<string> SoftwareSalary::transfer_string_to_vector(vector<int> pos_of_space, string rest_remain)
{
    vector<string> info_in_command_line;
    int pos = initial_condition;
    for (int i = 0; i < pos_of_space.size(); i++)
    {
        int set_difference = pos_of_space[i] - pos;
        string member = rest_remain.substr(pos, set_difference);
        info_in_command_line.push_back(member);
        pos = pos_of_space[i] + 1;
    }
    info_in_command_line.push_back(rest_remain.substr(pos));
    return info_in_command_line;
}

vector<string> SoftwareSalary::separate_sentence_by_space(string rest_remain)
{
    vector<int> pos_of_space = find_place_of_space(rest_remain);
    vector<string> info_in_command_line = transfer_string_to_vector(pos_of_space, rest_remain);
    return info_in_command_line;
}

void SoftwareSalary::validating_working_hours_args(string &output, vector<string> info, int id)
{
    if (checking_correctness_of_time(stoi(info[2]), stoi(info[3])) && check_correctness_of_day(stoi(info[1])))
    {
        if (Employees[id].no_interference_occurs(stoi(info[1]), stoi(info[2]), stoi(info[3])))
        {
            Employees[id].add_timing_hours(stoi(info[1]), stoi(info[2]), stoi(info[3]));
            output = ok;
        }
        else
            output = invalid_interval;
    }
    else
        output = invalid_arguments;
}

string SoftwareSalary::add_working_hours(string rest_remain)
{
    string output;
    vector<string> info = separate_sentence_by_space(rest_remain);
    int id = the_employee_exist(info[0]);
    if (id != not_found)
        validating_working_hours_args(output, info, id);
    else
        output = employee_not_found;
    return output;
}

int SoftwareSalary::which_level_is_requested(string otherwise)
{
    for (int i = 0; i < salary_parameters.size(); i++)
    {
        if (salary_parameters[i].get_level() == otherwise)
            return i;
    }
    return not_found;
}

void SoftwareSalary::show_parameter_of_salary(string otherwise)
{
    int level_index = which_level_is_requested(otherwise);
    if (level_index != not_found)
    {
        cout << Set_values_salary[0] << semicolon << fixed << setprecision(0) << salary_parameters[level_index].get_salary_base() << endl;
        cout << Set_values_salary[1] << semicolon << fixed << setprecision(0) << salary_parameters[level_index].get_salary_per_hour() << endl;
        cout << Set_values_salary[2] << semicolon << fixed << setprecision(0) << salary_parameters[level_index].get_salary_per_extra_hour() << endl;
        cout << Set_values_salary[3] << semicolon << fixed << setprecision(0) << salary_parameters[level_index].get_official_working_hour() << endl;
        cout << Set_values_salary[4] << semicolon << fixed << setprecision(0) << salary_parameters[level_index].get_tax_percentage() << "%" << endl;
    }
    else
        cout << invalid_level << endl;
}

int SoftwareSalary::find_id(string id)
{
    for (int i = 0; i < Employees.size(); i++)
    {
        if (Employees[i].is_it_same_employee(id))
            return i;
    }
    return -1;
}

string SoftwareSalary::delete_working_hours(string rest_remain)
{
    string out_put;
    int pos = rest_remain.find(space);
    int id = find_id(rest_remain.substr(initial_condition, pos));
    if (id != not_found)
    {
        int day = stoi(rest_remain.substr(pos + 1));
        if (check_correctness_of_day(day) && Employees[id].this_day_exist(day))
        {
            Employees[id].delete_timing_hours(day);
            out_put = ok;
        }
        else
            out_put = invalid_arguments;
    }
    else
        out_put = employee_not_found;
    return out_put;
}

double SoftwareSalary::can_base_salary_update(SalaryGiven found_level, string new_base)
{
    double base;
    if (new_base == dash)
        base = found_level.get_salary_base();
    else
        base = stod(new_base);
    return base;
}

double SoftwareSalary::can_tax_update(SalaryGiven found_level, string new_tax)
{
    double tax;
    if (new_tax == dash)
        tax = found_level.get_tax_percentage();
    else
        tax = stod(new_tax);
    return tax;
}

double SoftwareSalary::can_work_hour_update(SalaryGiven found_level, string new_work_hour)
{
    double working_h;
    if (new_work_hour == dash)
        working_h = found_level.get_official_working_hour();
    else
        working_h = stod(new_work_hour);
    return working_h;
}

double SoftwareSalary::can_salary_per_extra_hour_update(SalaryGiven found_level, string new_salary_per_extra)
{
    double salary_per_extra;
    if (new_salary_per_extra == dash)
        salary_per_extra = found_level.get_salary_per_extra_hour();
    else
        salary_per_extra = stod(new_salary_per_extra);
    return salary_per_extra;
}

double SoftwareSalary::can_salary_per_hour_update(SalaryGiven found_level, string new_salary_per_hour)
{
    double salary_per_h;
    if (new_salary_per_hour == dash)
        salary_per_h = found_level.get_salary_per_hour();
    else
        salary_per_h = stod(new_salary_per_hour);
    return salary_per_h;
}

string SoftwareSalary::change_salary_parameters(int found, vector<string> info)
{
    double base_salary = can_base_salary_update(salary_parameters[found], info[1]);
    double salary_per_hour = can_salary_per_hour_update(salary_parameters[found], info[2]);
    double salary_per_extra = can_salary_per_extra_hour_update(salary_parameters[found], info[3]);
    double official_work_hour = can_work_hour_update(salary_parameters[found], info[4]);
    double tax_percentage = can_tax_update(salary_parameters[found], info[5]);
    salary_parameters[found].changing_parameters_of_level(base_salary, salary_per_hour, salary_per_extra, official_work_hour, tax_percentage);
    return ok;
}

int SoftwareSalary::the_level_exist(string level_entered)
{
    for (int i = 0; i < salary_parameters.size(); i++)
    {
        if (salary_parameters[i].get_level() == level_entered)
            return i;
    }
    return not_found;
}

float SoftwareSalary::average_working_hour(int all_working_hours, int number_of_members)
{
    float average = (float)all_working_hours / (float)number_of_members;
    average = (round(average * 10)) / 10;
    return average;
}

void SoftwareSalary::printing_team_first_vals(int found_team)
{
    cout << team_print_val[0] << semicolon << teams[found_team].get_team_id() << endl;
    cout << team_print_val[1] << semicolon << teams[found_team].get_id_head_team() << endl;
    cout << team_print_val[2] << semicolon << teams[found_team].get_head_name(Employees) << endl;
    cout << team_print_val[3] << semicolon << teams[found_team].get_all_members_WH(Employees) << endl;
    cout << team_print_val[4] << semicolon << fixed << setprecision(1) << average_working_hour(teams[found_team].get_all_members_WH(Employees), teams[found_team].get_members().size()) << endl;
    cout << team_print_val[5] << semicolon << teams[found_team].get_bonus() << endl;
    cout << more_to_add << endl;
}

vector<int> SoftwareSalary::sort_team_members(Team current_team)
{
    vector<int> sort_id, sort_members;
    for (int i = 0; i < current_team.get_members().size(); i++)
        sort_id.push_back(stoi(current_team.get_members()[i]));
    sort(sort_id.begin(), sort_id.end());
    for (int i = 0; i < sort_id.size(); i++)
    {
        for (int k = 0; k < current_team.get_members().size(); k++)
        {
            if (stoi(current_team.get_members()[k]) == sort_id[i])
                sort_members.push_back(k);
        }
    }
    return sort_members;
}

void SoftwareSalary::printing_team_members_salary(Team current_team)
{
    vector<int> sort_members = sort_team_members(current_team);
    for (int j = 0; j < sort_members.size(); j++)
    {
        for (int i = 0; i < Employees.size(); i++)
        {
            if (Employees[i].get_id() == current_team.get_members()[sort_members[j]])
            {
                cout << member_id << semicolon << current_team.get_members()[sort_members[j]] << endl;
                cout << total_earning << semicolon << calculate_earning(Employees[i], current_team.get_bonus()) << endl;
                cout << more_to_add << endl;
            }
        }
    }
}

void SoftwareSalary::reporting_team(string id)
{
    int found_team_id = the_team_exist(id);
    if (found_team_id != -1)
    {
        printing_team_first_vals(found_team_id);
        printing_team_members_salary(teams[found_team_id]);
    }
    else
        cout << team_not_found << endl;
}

string SoftwareSalary::merge_max_min_average_hours(float limit, vector<pair<string, float>> periods)
{
    vector<string> result;
    string final_result = "";
    for (int i = 0; i < periods.size(); i++)
    {
        if (limit == periods[i].second)
            result.push_back(periods[i].first);
    }
    for (int i = 0; i < result.size(); i++)
    {
        final_result += result[i];
        if (i != result.size() - 1)
            final_result += space;
    }
    return final_result;
}

void SoftwareSalary::find_min_max_averages(vector<pair<string, float>> periods, float &min, float &max)
{
    vector<float> result;
    for (int i = 0; i < periods.size(); i++)
        result.push_back(periods[i].second);
    max = *max_element(result.begin(), result.end());
    min = *min_element(result.begin(), result.end());
}

void SoftwareSalary::printing_max_min_output_hours(vector<pair<string, float>> periods)
{
    float min, max;
    find_min_max_averages(periods, min, max);
    string min_hours = merge_max_min_average_hours(min, periods);
    string max_hours = merge_max_min_average_hours(max, periods);
    cout << periods_with_max_working_employees << semicolon << max_hours << endl;
    cout << periods_with_min_working_employees << semicolon << min_hours << endl;
}

bool SoftwareSalary::separate_start_end_time(string rest_remain, int &start_1, int &end_1)
{
    int pos = rest_remain.find(" ");
    int start = stoi(rest_remain.substr(0, pos));
    int end = stoi(rest_remain.substr(pos + 1));
    if (checking_correctness_of_time(start, end))
    {
        start_1 = start;
        end_1 = end;
        return true;
    }
    return false;
}

int SoftwareSalary::how_many_work_in_this_hour(int start, int end)
{
    int sum_in_this_time = 0;
    for (int j = 0; j < Employees.size(); j++)
    {
        vector<timetable> curr_person_working = Employees[j].get_working_hours();
        for (int k = 0; k < curr_person_working.size(); k++)
        {
            if (curr_person_working[k].start <= start && curr_person_working[k].end >= end)
            {
                sum_in_this_time++;
            }
        }
    }
    return sum_in_this_time;
}

vector<pair<string, float>> SoftwareSalary::find_employee_in_the_period(int start, int end)
{
    vector<pair<string, float>> periods;
    for (int i = start; i + 1 <= end; i++)
    {
        int sum_in_this_hour = how_many_work_in_this_hour(i, i + 1);
        float average = float(sum_in_this_hour) / float(30);
        average = (float)(round(average * 10)) / 10.0;
        string now = to_string(i) + "-" + to_string(i + 1);
        int counter = periods.size();
        periods.push_back(pair<string, float>());
        periods[counter].first = now;
        periods[counter].second = average;
    }
    return periods;
}

string SoftwareSalary::merge_days_numbers_for_print(vector<pair<int, int>> output, int limit)
{
    vector<string> result;
    string final_result = "";
    for (int i = 0; i < output.size(); i++)
    {
        if (limit == output[i].second)
            result.push_back(to_string(output[i].first));
    }
    for (int i = 0; i < result.size(); i++)
    {
        final_result += result[i];
        if (i != result.size() - 1)
            final_result += space;
    }
    return final_result;
}

void SoftwareSalary::find_min_max_in_outputs(vector<pair<int, int>> output, int &max, int &min)
{
    vector<int> result;
    for (int i = 0; i < output.size(); i++)
        result.push_back(output[i].second);
    max = *max_element(result.begin(), result.end());
    min = *min_element(result.begin(), result.end());
}

void SoftwareSalary::finding_second_output(vector<pair<int, int>> output, vector<int> number_of_days)
{
    int min, max;
    find_min_max_in_outputs(output, max, min);
    string max_days = merge_days_numbers_for_print(output, max);
    string min_days = merge_days_numbers_for_print(output, min);
    cout << days_with_max_working_hours << semicolon << max_days << endl;
    cout << days_with_min_working_hours << semicolon << min_days << endl;
}

void SoftwareSalary::make_pair_for_days_hours(vector<pair<int, int>> &output, int curr_day, int sum_h)
{
    int counter = output.size();
    output.push_back(pair<int, int>());
    output[counter].first = curr_day;
    output[counter].second = sum_h;
}

vector<pair<int, int>> SoftwareSalary::working_hours_in_day(int start, int end, vector<int> &days_number)
{
    vector<pair<int, int>> output;
    for (int i = start; i <= end; i++)
    {
        int sum = 0;
        for (int k = 0; k < Employees.size(); k++)
            sum += Employees[k].special_day_working_hours(i);
        days_number.push_back(i);
        make_pair_for_days_hours(output, i, sum);
    }
    return output;
}

string SoftwareSalary::finding_team_id_of_employee(Employee employee)
{
    if (employee.get_team_id() == not_exist)
        return no_team;
    else
        return employee.get_team_id();
}

void SoftwareSalary::show_special_employee(Employee employee)
{
    cout << id << semicolon << employee.get_id() << endl;
    cout << special_employee_print[0] << semicolon << employee.get_name() << endl;
    cout << special_employee_print[1] << semicolon << employee.get_age() << endl;
    cout << special_employee_print[2] << semicolon << employee.get_level() << endl;
    cout << special_employee_print[3] << semicolon << finding_team_id_of_employee(employee) << endl;
    cout << special_employee_print[4] << semicolon << employee.calculate_total_working_hours() << endl;
    cout << special_employee_print[5] << semicolon << employee.calculate_absent_days() << endl;
}

int SoftwareSalary::salary_level_for_employee(Employee found_one)
{
    for (int i = 0; i < salary_parameters.size(); i++)
    {
        if (salary_parameters[i].get_level() == found_one.get_level())
            return i;
    }
    return 1;
}

int SoftwareSalary::which_team_index(Employee employee)
{
    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i].get_team_id() == employee.get_team_id())
            return i;
    }
    return -1;
}

void SoftwareSalary::show_bonus_salary(Employee employee, int index_team, int &total, int level)
{
    if (-1 != index_team)
    {
        cout << bonus << semicolon << add_bonus_to_salary(teams[index_team].get_bonus(), total) << endl;
        total = total + add_bonus_to_salary(teams[index_team].get_bonus(), total);
    }
    else
        cout << bonus << semicolon << not_exist << endl;
}

void SoftwareSalary::show_total_earning_salary(Employee employee, int index_team, int total, int level)
{
    if (-1 != index_team)
        cout << total_earning << semicolon << calculate_earning(employee, teams[index_team].get_bonus()) << endl;
    else
        cout << total_earning << semicolon << calculate_earning(employee, initial_condition) << endl;
}

void SoftwareSalary::show_one_employee_salary(Employee employee)
{
    int index_team = which_team_index(employee);
    show_special_employee(employee);
    int level = salary_level_for_employee(employee);
    int total = calculate_salary_without_bonus(salary_parameters[level], employee.calculate_total_working_hours());
    cout << salary << semicolon << total << endl;
    show_bonus_salary(employee, index_team, total, level);
    cout << tax << semicolon << calculate_tax_of_salary(total, salary_parameters[level].get_tax_percentage()) << endl;
    show_total_earning_salary(employee, index_team, total, level);
}

bool SoftwareSalary::check_working_hours(Team current_team)
{
    int total_wh = current_team.get_all_members_WH(Employees);
    if (total_wh > current_team.get_bonus_min_working())
        return true;
    return false;
}

float SoftwareSalary::calculate_variance_team(vector<int> hours)
{
    float sum = 0.0, variance = 0.0;
    for (int i = 0; i < hours.size(); i++)
        sum = sum + hours[i];
    sum = sum / hours.size();
    for (int i = 0; i < hours.size(); i++)
        variance += pow(hours[i] - sum, 2);
    variance = variance / hours.size();
    float sth = round(variance * 1000);
    sth = sth / 1000;
    return sth;
}

bool SoftwareSalary::check_variance(Team current_team)
{
    vector<int> hours;
    vector<string> member_ids = current_team.get_members();
    for (int i = 0; i < member_ids.size(); i++)
    {
        for (int k = 0; k < Employees.size(); k++)
        {
            if (member_ids[i] == Employees[k].get_id())
                hours.push_back(Employees[k].calculate_total_working_hours());
        }
    }
    if (calculate_variance_team(hours) < current_team.get_bonus_working_hours_max())
        return true;
    return false;
}

vector<string> SoftwareSalary::sorting_base_work_hour(vector<int> result)
{
    vector<int> hours;
    for (int i = 0; i < result.size(); i++)
        hours.push_back(teams[result[i]].get_all_members_WH(Employees));
    sort(hours.begin(), hours.end());
    vector<string> final_order;
    for (int i = 0; i < hours.size(); i++)
    {
        for (int k = 0; k < result.size(); k++)
        {
            if (teams[result[k]].get_all_members_WH(Employees) == hours[i])
                final_order.push_back(teams[result[k]].get_team_id());
        }
    }
    return final_order;
}

vector<string> SoftwareSalary::find_bonus_team()
{
    vector<int> result;
    int flag = initial_condition;
    vector<string> order;
    for (int i = 0; i < teams.size(); i++)
    {
        if (check_variance(teams[i]) && check_working_hours(teams[i]))
            result.push_back(i);
    }
    if (result.size() != 0)
        order = sorting_base_work_hour(result);
    return order;
}

void SoftwareSalary::printing_bonus_teams(vector<string> result)
{
    if (result.size() != 0)
    {
        for (int i = 0; i < result.size(); i++)
            cout << team_id << semicolon << result[i] << endl;
    }
    else
        cout << no_bonus_team << endl;
}

void SoftwareSalary::input_handling()
{
    string input_command;
    while (getline(cin, input_command))
    {
        int pos_space = input_command.find(space);
        if (input_command == prescribed_orders[0])
            print_reported_salaries(reporting_salaries());
        else if (input_command.substr(0, pos_space) == prescribed_orders[1])
            cout << update_team_bonus(input_command.substr(pos_space + 1)) << endl;
        else if (input_command.substr(0, pos_space) == prescribed_orders[2])
            cout << add_working_hours(input_command.substr(pos_space + 1)) << endl;
        else if (input_command.substr(0, pos_space) == prescribed_orders[3])
            show_parameter_of_salary(input_command.substr(pos_space + 1));
        else if (input_command.substr(0, pos_space) == prescribed_orders[4])
            cout << delete_working_hours(input_command.substr(pos_space + 1)) << endl;
        else if (input_command.substr(0, pos_space) == prescribed_orders[5])
            update_salary_parameters(input_command, pos_space);
        else if (input_command.substr(0, pos_space) == prescribed_orders[6])
            report_total_hours_per_day(input_command, pos_space);
        else if (input_command.substr(0, pos_space) == prescribed_orders[7])
            report_employee_per_hour(input_command, pos_space);
        else if (input_command.substr(0, pos_space) == prescribed_orders[8])
            reporting_team(input_command.substr(pos_space + 1));
        else if (input_command.substr(0, pos_space) == prescribed_orders[9])
            report_employee_salary(input_command, pos_space);
        else if (input_command.substr(0, pos_space) == prescribed_orders[10])
            printing_bonus_teams(find_bonus_team());
    }
}

int main(int argc, char *argv[])
{
    ReadingInput read_from_input;
    read_from_input.start_processing(argv[1]);
    SoftwareSalary software_calculating_salary;
    software_calculating_salary.receive_input_information(read_from_input);
    software_calculating_salary.input_handling();
}

