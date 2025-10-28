#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct Time
{
   int hour;
   int min;
};
struct Teachers
{
   string name;
   int number_of_free;
   vector<string> name_of_free;
   int number_of_course;
   vector<string> name_course;
};
struct Course
{
   string name;
   Time start;
   Time end;
   string day1;
   string day2;
};

struct Schechule
{
   string course;
   string teacher;
   int class_num;
   Time start;
   string day1;
   string day2;
};
struct founded_ones
{
   string name;
   string teach;
};
struct class_final
{
   string name;
   string teacher;
   Time start;
};
int starting_time[3][2] = {{7, 30}, {9, 30}, {11, 30}};

#define CLASS_NUMBER_1 1
#define CLASS_NUMBER_2 2
#define HOUR_PARAMETER_S 0
#define MIN_PARAMETER_S 3
#define INITIAL_CONDITION 0
#define NO_MATCH_FOUND -1
#define FIRST_RING_PERIOD "07:30 09:00"
#define SECOND_RING_PERIOD "09:30 11:00"
#define THIRD_RING_PERIOD "11:30 13:00"
const int first_ring=7;
const int second_ring=9;
const int third_ring=11;
const int length=2;
const int days_of_week=5;
const int finding_limit=2;

typedef vector<Schechule> schechule;
typedef vector<Course> course;
typedef vector<Teachers> teachers;

void design_the_system(teachers personal, course doros, schechule &barname,
                       int status);
void input(teachers &personal, course &doros);
void add_new_class_timeing(schechule &barname, int status, int current_hour, int min, int where_to_add);
void add_new_lesson(schechule &barname, course doros, int where_to_add, int find_c);
void make_two_class_seperated(schechule barname,vector<class_final> &one_class,vector<class_final> &two_class);
void find_the_final_result(schechule &barname,course doros,teachers personal,int hour,int min
                               ,int status,vector<founded_ones> this_day);
void add_not_found_in_situation(string dars, schechule &barname, vector<int> result, int status);
void where_to_add(string dars, schechule &barname, vector<int> result);
void adding_not_found(course doros, schechule &barname);
void sort_subjects(vector<string> &current_week, course doros);
void printing_out(course doros, vector<class_final> one_class, vector<class_final> two_class, vector<string> current_week);
void make_two_class_seperated(schechule barname,vector<class_final> &one_class,vector<class_final> &two_class);

string the_final_result(int current_hour);
string which_day(int current_day);

bool integer_same(int number1, int number2, int compare_num1, int compare_num2);
bool have_day(Course current, string current_day);
bool have_same_day_present(Teachers current, string day1, string day2);
bool compare_three_string(string one,string compare1,string compare2);
bool these_same_or_not(string day1, string day2, string subject_day1, string subject_day2);
bool teaching_in_another_class(schechule barname, int status, int current_hour, int m,
                                 string day1, string day2, string teach);
bool have_been_set_in(int status, int current_hour, int y, string day1, string day2, schechule barname, string name);
bool used_object(int status, schechule barname, string name);
bool check_each_one(schechule barname, course doros, int status, int find);
bool check_matches_with_day(Teachers personal, string founded_subject);
bool this_day(course doros, string current_day);

int choose_smaller_one(int number1, int number2);
int find_minimom(teachers personal, vector<int> result);
int teachers_organize_alphabetical(teachers personal, vector<int> result);
int subjects_organized_alphabetically(vector<founded_ones> result);
int choose_teacher(teachers personal, course doros, int find, int current_hour, int m, int status, schechule barname);
int add_new_use_time(schechule &barname, vector<Teachers> personal, int find_t);

vector<int> who_has_more_freedays(teachers personal, course doros, int find, vector<int> &result);
vector<int> subject_teacher_same_day(teachers personal, string founded_subject);
vector<int> check_already_used(int status, int current_hour, int y, course doros, schechule barname, vector<int> result);
vector<int> check_any_similar_course_that_day(schechule barname, course doros, int status, vector<int> result);
vector<int> all_the_possible_classes(course doros, int hour, int min, string current_day);
vector<int> having_special_class(course doros, schechule barname, vector<int> result, int status);
vector<int> some_one_at_school_that_day(course doros, teachers personal, vector<int> result);
vector<founded_ones> which_one_choose(course doros, teachers personal, int hour, int min, string current_day,
                     schechule &barname, int status);
vector<string> process(teachers personal, course doros, schechule &barname);

int main()
{
   vector<string> current_week;
   teachers personal;
   course doros;
   schechule barname;
   input(personal, doros);
   current_week = process(personal, doros, barname);
   vector<class_final> one_class;
   vector<class_final> two_class;
   make_two_class_seperated(barname,one_class,two_class);
   printing_out(doros, one_class, two_class, current_week);
}
vector<string> process(teachers personal, course doros, schechule &barname)
{
   vector<string> current_week;
   design_the_system(personal, doros, barname, CLASS_NUMBER_1);
   design_the_system(personal, doros, barname, CLASS_NUMBER_2);
   sort_subjects(current_week, doros);
   adding_not_found(doros, barname);
   return current_week;
}
void printing_out(course doros, vector<class_final> one_class, vector<class_final> two_class, vector<string> current_week)
{
   vector<string> already_printed;
   for (int i = 0; i < current_week.size(); i++)
   {
      cout << current_week[i] << endl;
      for (int j = 0; j < one_class.size(); j++)
      {
         if (one_class[j].name == current_week[i])
         {
            if (one_class[j].teacher != "Not Found")
            {
               cout << one_class[j].teacher << ": ";
               string time = the_final_result(one_class[j].start.hour);
               cout << time << endl;
            }
            else
               cout << one_class[j].teacher << endl;
         }
      }
      for (int j = 0; j < two_class.size(); j++)
      {
         if (two_class[j].name == current_week[i])
         {
            if (two_class[j].teacher != "Not Found")
            {
               cout << two_class[j].teacher << ": ";
               string time = the_final_result(two_class[j].start.hour);
               cout << time << endl;
            }
            else
               cout << two_class[j].teacher << endl;
         }
      }
   }
}
void make_two_class_seperated(schechule barname,vector<class_final> &one_class,vector<class_final> &two_class)
{
for (int i = 0; i < barname.size(); i++)
   {
      if (barname[i].class_num == CLASS_NUMBER_1)
      {
         int counter1 = one_class.size();
         one_class.push_back(class_final());
         one_class[counter1].name = barname[i].course;
         one_class[counter1].teacher = barname[i].teacher;
         one_class[counter1].start.hour = barname[i].start.hour;
         one_class[counter1].start.min = barname[i].start.min;
      }
      else if (barname[i].class_num == CLASS_NUMBER_2)
      {
         int counter2 = two_class.size();
         two_class.push_back(class_final());
         two_class[counter2].name = barname[i].course;
         two_class[counter2].teacher = barname[i].teacher;
         two_class[counter2].start.hour = barname[i].start.hour;
         two_class[counter2].start.min = barname[i].start.min;
      }
   }
}
int the_input_number()
{
   int number;
   cin >> number;
   return number;
}
string the_input_string()
{
   string entered;
   cin >> entered;
   return entered;
}
void how_many_free(teachers &personal, int current_person)
{
   int number2 = the_input_number();
   personal[current_person].number_of_free = number2;
   for (int j = 0; j < number2; j++)
      personal[current_person].name_of_free.push_back(the_input_string());
}
void how_many_course(teachers &personal, int current_person)
{
   int number3 = the_input_number();
   personal[current_person].number_of_course = number3;
   for (int j = 0; j < number3; j++)
      personal[current_person].name_course.push_back(the_input_string());
}
void teachers_input(teachers &personal)
{
   string full_name;
   int number_teacher = the_input_number();
   for (int i = 0; i < number_teacher; i++)
   {
      personal.push_back(Teachers());
      personal[i].name = the_input_string();
      how_many_free(personal, i);
      how_many_course(personal, i);
   }
}

void days_present(course &doros, int current)
{
   doros[current].day1 = the_input_string();
   doros[current].day2 = the_input_string();
}
void time_present(course &doros, int current)
{
   string start = the_input_string();
   doros[current].start.hour = stoi(start.substr(HOUR_PARAMETER_S, length));
   doros[current].start.min = stoi(start.substr(MIN_PARAMETER_S, length));
   string end = the_input_string();
   doros[current].end.hour = stoi(end.substr(HOUR_PARAMETER_S, length));
   doros[current].end.min = stoi(end.substr(MIN_PARAMETER_S, length));
}
void courses_input(course &doros)
{
   int number = the_input_number();
   for (int i = 0; i < number; i++)
   {
      doros.push_back(Course());
      doros[i].name = the_input_string();
      days_present(doros, i);
      time_present(doros, i);
   }
}
void input(teachers &personal, course &doros)
{
   teachers_input(personal);
   courses_input(doros);
}
string the_final_result(int current_hour)
{
   switch (current_hour)
   {
   case first_ring:
      return FIRST_RING_PERIOD;
      break;
   case second_ring:
      return SECOND_RING_PERIOD;
   case third_ring:
      return THIRD_RING_PERIOD;
   default:
      break;
   }
   return "invalid time";
}

bool have_day(Course current, string current_day)
{
   if (current.day1 == current_day || current.day2 == current_day)
      return true;
   return false;
}
int choose_smaller_one(int number1, int number2)
{
   if (number1 > number2)
      return number2;
   else if (number1 < number2)
      return number1;
   else
      return NO_MATCH_FOUND;
}
int find_minimom(teachers personal, vector<int> result)
{
   int min = days_of_week;
   for (int i = 0; i < result.size(); i++)
   {
      if (min > personal[result[i]].number_of_free)
      {
         min = personal[result[i]].number_of_free;
      }
   }
   return min;
}
vector<int> who_has_more_freedays(teachers personal, course doros, int find, vector<int> &result)
{
   vector<int> new_result;
   int min = find_minimom(personal, result);
   for (int i = 0; i < result.size(); i++)
   {
      if (personal[result[i]].number_of_free <= min)
      {
         new_result.push_back(result[i]);
      }
   }
   return new_result;
}
vector<int> subject_teacher_same_day(teachers personal, string founded_subject)
{
   vector<int> result;
   for (int i = 0; i < personal.size(); i++)
   {
      for (int j = 0; j < personal[i].number_of_course; j++)
      {
         if (personal[i].name_course[j] == founded_subject)
            result.push_back(i);
      }
   }
   return result;
}
bool have_same_day_present(Teachers current, string day1, string day2)
{
   int flag = INITIAL_CONDITION;
   for (int i = 0; i < current.number_of_free; i++)
   {
      if (current.name_of_free[i] == day1 || current.name_of_free[i] == day2)
         flag++;
   }
   if (flag == finding_limit)
      return true;
   return false;
}
bool compare_three_string(string one,string compare1,string compare2)
{
   if (one==compare1 ||one==compare2)
   {
      return true;
   }
   return false;
}
vector<int> day_the_same(teachers personal, vector<int> &result, string day_1, string day_2)
{
   int count = result.size();
   vector<int> new_result;
   for (int k = 0; k < count; k++)
   {
      int flag = INITIAL_CONDITION;
      for (int j = 0; j < personal[result[k]].number_of_free; j++)
      {
         if(compare_three_string(personal[result[k]].name_of_free[j],day_1,day_2))
            flag = flag + 1;
      }
      if (flag == finding_limit)
         new_result.push_back(result[k]);
   }
   return new_result;
}
bool these_same_or_not(string day1, string day2, string subject_day1, string subject_day2)
{
   if ((day1 == subject_day1 || day1 == subject_day2) ||
       (day2 == subject_day2 || day2 == subject_day1))
      return true;
   return false;
}

bool teaching_in_another_class(schechule barname, int status, int current_hour, int m, string day1, string day2, string teach)
{
   for (int i = 0; i < barname.size(); i++)
   {
      if (barname[i].teacher == teach)
      {
         if (these_same_or_not(barname[i].day1,barname[i].day2,day1,day2))
         {
            if (barname[i].start.hour == current_hour)
               return true;
         }
      }
   }
   return false;
}
vector<int> checking_the_teachers(teachers personal, course doros, int find,
                                  int current_hour, int m, int status, schechule barname, vector<int> result)
{
   vector<int> new_result;
   for (int i = 0; i < result.size(); i++)
   {
      if (!teaching_in_another_class(barname, status, current_hour, m, doros[find].day1, doros[find].day2, personal[result[i]].name))
         new_result.push_back(result[i]);
   }
   return new_result;
}
int choose_teacher(teachers personal, course doros, int find, int current_hour, int m, int status, schechule barname)
{
   int find_t = NO_MATCH_FOUND;
   vector<int> result = subject_teacher_same_day(personal, doros[find].name);
   result = checking_the_teachers(personal, doros, find, current_hour, m, status, barname, result);
   result = day_the_same(personal, result, doros[find].day1, doros[find].day2);
   result = who_has_more_freedays(personal, doros, find, result);
   if (result.size() != 1)
      find_t = teachers_organize_alphabetical(personal, result);
   if (result.size() == 1)
      return result[0];
   else if (result.size() == INITIAL_CONDITION)
      return NO_MATCH_FOUND;
   return find_t;
}
bool integer_same(int number1, int number2, int compare_num1, int compare_num2)
{
   if (number1 == compare_num1 && number2 == compare_num2)
      return true;
   return false;
}

bool have_been_set_in(int status, int current_hour, int y, string day1, string day2, schechule barname, string name)
{
   for (int i = 0; i < barname.size(); i++)
   {
      if (barname[i].class_num == status)
      {
         if (integer_same(barname[i].start.hour, barname[i].start.min, current_hour, y))
         {
            if (these_same_or_not(barname[i].day1, barname[i].day2, day1, day2))
               return false;
         }
      }
   }
   return true;
}
vector<int> check_already_used(int status, int current_hour, int y, course doros, schechule barname, vector<int> result)
{
   vector<int> new_result;
   for (int i = 0; i < result.size(); i++)
   {
      if (have_been_set_in(status, current_hour, y, doros[result[i]].day1, doros[result[i]].day2, barname, doros[result[i]].name))
         new_result.push_back(result[i]);
   }
   return new_result;
}

bool used_object(int status, schechule barname, string name)
{
   for (int i = 0; i < barname.size(); i++)
   {
      if (barname[i].class_num == status)
      {
         if (barname[i].course == name)
            return false;
      }
   }
   return true;
}
vector<int> check_any_similar_course_that_day(schechule barname, course doros, int status, vector<int> result)
{
   vector<int> new_result;
   for (int i = 0; i < result.size(); i++)
   {
      if (used_object(status, barname, doros[result[i]].name))
         new_result.push_back(result[i]);
   }
   return new_result;
}
vector<int> all_the_possible_classes(course doros, int hour, int min, string current_day)
{
   vector<int> result;
   for (int i = 0; i < doros.size(); i++)
   {
      if (!have_day(doros[i], current_day))
         continue;
      if (doros[i].start.hour > hour)
         continue;
      else if (doros[i].start.hour == hour && doros[i].start.min > min)
         continue;
      else if (doros[i].end.hour < hour)
         continue;
      else if (doros[i].end.hour < hour + 2)
         continue;
      else
         result.push_back(i);
   }
   return result;
}
int teachers_organize_alphabetical(teachers personal, vector<int> result)
{
   vector<string> teach;
   int finded = NO_MATCH_FOUND;
   for (int i = 0; i < result.size(); i++)
      teach.push_back(personal[result[i]].name);
   sort(teach.begin(), teach.end());
   if (teach.size() != 0)
   {
      for (int i = 0; i < result.size(); i++)
      {
         if (personal[result[i]].name == teach[0])
            finded = result[i];
      }
   }
   return finded;
}
bool check_each_one(schechule barname, course doros, int status, int find)
{
   for (int i = 0; i < barname.size(); i++)
   {
      if (barname[i].course == doros[find].name)
      {
         if (barname[i].class_num == status)
            return true;
      }
   }
   return false;
}
vector<int> having_special_class(course doros, schechule barname, vector<int> result, int status)
{
   vector<int> new_result;
   for (int i = 0; i < result.size(); i++)
   {
      if (!check_each_one(barname, doros, status, result[i]))
         new_result.push_back(result[i]);
   }
   return new_result;
}
bool check_matches_with_day(Teachers personal, string founded_subject)
{
   for (int i = 0; i < personal.number_of_course; i++)
   {
      if (personal.name_course[i] == founded_subject)
         return true;
   }
   return false;
}
vector<int> some_one_at_school_that_day(course doros, teachers personal, vector<int> result)
{
   vector<int> new_result;
   for (int i = 0; i < result.size(); i++)
   {
      for (int j = 0; j < personal.size(); j++)
      {
         int flag = INITIAL_CONDITION;
         for (int k = 0; k < personal[j].number_of_free; k++)
         {
            if(compare_three_string(personal[j].name_of_free[k] ,doros[result[i]].day1,doros[result[i]].day2))
            {
               if (check_matches_with_day(personal[j], doros[result[i]].name))
                  flag = flag + 1;
            }
         }
         if (flag == finding_limit)
         {
            new_result.push_back(result[i]);
            j = personal.size();
         }
      }
   }
   return new_result;
}
int add_new_use_time(schechule &barname, vector<Teachers> personal, int find_t)
{
   int where_to_add = barname.size();
   barname.push_back(Schechule());
   barname[where_to_add].teacher = personal[find_t].name;
   return where_to_add;
}
void add_new_class_timeing(schechule &barname, int status, int current_hour, int min, int where_to_add)
{
   barname[where_to_add].class_num = status;
   barname[where_to_add].start.hour = current_hour;
   barname[where_to_add].start.min = min;
}
void add_new_lesson(schechule &barname, course doros, int where_to_add, int find_c)
{
   barname[where_to_add].course = doros[find_c].name;
   barname[where_to_add].day1 = doros[find_c].day1;
   barname[where_to_add].day2 = doros[find_c].day2;
}
vector<founded_ones> which_one_choose(course doros, teachers personal, int hour, int min, string current_day,
                     schechule &barname, int status)
{
   int finded = NO_MATCH_FOUND;
   vector<founded_ones> this_day;
   vector<int> result = all_the_possible_classes(doros, hour, min, current_day);
   result = having_special_class(doros, barname, result, status);
   result = check_already_used(status, hour, min, doros, barname, result);
   result = check_any_similar_course_that_day(barname, doros, status, result);
   for (int i = 0; i < result.size(); i++)
   {
      int find_c = result[i];
      int find_t = choose_teacher(personal, doros, find_c, hour, min, status, barname);
      if (find_t == NO_MATCH_FOUND)
         continue;
      else
      {
         int count = this_day.size();
         this_day.push_back(founded_ones());
         this_day[count].name = doros[find_c].name;
         this_day[count].teach = personal[find_t].name;
      }
   }
   return this_day;
  
}
void find_the_final_result(schechule &barname,course doros,teachers personal,int hour,int min
                               ,int status,vector<founded_ones> this_day)
{
 if (this_day.size() > 1)
   {
      int check_each_one = subjects_organized_alphabetically(this_day);
      int teach_num = 0, dars_num = 0;
      for (int i = 0; i < doros.size(); i++)
      {
         if (this_day[check_each_one].name == doros[i].name)
            dars_num = i;
      }
      for (int i = 0; i < personal.size(); i++)
      {
         if (this_day[check_each_one].teach == personal[i].name)
            teach_num = i;
      }
      int where_to_add = add_new_use_time(barname, personal, teach_num);
      add_new_class_timeing(barname, status, hour, min, where_to_add);
      add_new_lesson(barname, doros, where_to_add, dars_num);
   }
   else if (this_day.size() == 1)
   {
      int teach_num = 0, dars_num = 0;
      for (int i = 0; i < doros.size(); i++)
      {
         if (this_day[0].name == doros[i].name)
            dars_num = i;
      }
      for (int i = 0; i < personal.size(); i++)
      {
         if (this_day[0].teach == personal[i].name)
                     teach_num = i;
      }
      int where_to_add = add_new_use_time(barname, personal, teach_num);
      add_new_class_timeing(barname, status, hour, min, where_to_add);
      add_new_lesson(barname, doros, where_to_add, dars_num);
   }
}
string which_day(int current_day)
{
   switch (current_day)
   {
   case 0:
      return "Saturday";
      break;
   case 1:
      return "Sunday";
      break;
   case 2:
      return "Monday";
      break;
   case 3:
      return "Tuesday";
      break;
   case 4:
      return "Wednesday";
      break;
   default:
      break;
   }
   return "invalid day";
}
bool this_day(course doros, string current_day)
{
   for (int i = 0; i < doros.size(); i++)
   {
      if (doros[i].day1 == current_day || doros[i].day2 == current_day)
         return true;
   }
   return false;
}

void design_the_system(teachers personal, course doros, schechule &barname,
                       int status)
{
   int number_day = INITIAL_CONDITION;
   bool still_in_week = true;
   while (still_in_week)
   {
      for (int i = 0; i < 3; i++)
      {
         int current_hour = starting_time[i][0];
         int current_min = starting_time[i][1];
         if (number_day == 5)
            still_in_week = false;
         string current_day = which_day(number_day);
         if (!this_day(doros, current_day))
            continue;
         vector<founded_ones> current=which_one_choose(doros, personal, current_hour, current_min, current_day,
                                                          barname, status);
         find_the_final_result(barname,doros,personal,current_hour,current_min,status,current);
      }
      number_day++;
   }
}


void add_not_found_in_situation(string dars, schechule &barname, vector<int> result, int status)
{
   int counter = barname.size();
   barname.push_back(Schechule());
   barname[counter].course = dars;
   barname[counter].teacher = "Not Found";
   barname[counter].class_num = status;
   barname[counter].start.hour = 0;
   barname[counter].start.min = 0;
}
void where_to_add(string dars, schechule &barname, vector<int> result)
{
   if (result.size() == 0)
   {
      add_not_found_in_situation(dars, barname, result, CLASS_NUMBER_1);
      add_not_found_in_situation(dars, barname, result, CLASS_NUMBER_2);
   }
   else
   {
      if (result[0] == CLASS_NUMBER_1)
         add_not_found_in_situation(dars, barname, result, CLASS_NUMBER_2);
      else if (result[0] == CLASS_NUMBER_2)
         add_not_found_in_situation(dars, barname, result, CLASS_NUMBER_1);
   }
   return;
}
void adding_not_found(course doros, schechule &barname)
{
   vector<int> result;
   for (int i = 0; i < doros.size(); i++)
   {
      for (int j = 0; j < barname.size(); j++)
      {
         if (barname[j].course == doros[i].name)
            result.push_back(barname[j].class_num);
      }
      if (result.size() != 2)
         where_to_add(doros[i].name, barname, result);
      result.clear();
   }
   return;
}
int subjects_organized_alphabetically(vector<founded_ones> result)
{
   vector<string> new_result;
   int finded = NO_MATCH_FOUND;
   for (int i = 0; i < result.size(); i++)
      new_result.push_back(result[i].name);
   sort(new_result.begin(), new_result.end());
   if (new_result.size() != INITIAL_CONDITION)
   {
      for (int i = 0; i < result.size(); i++)
      {
         if (result[i].name == new_result[0])
            finded = i;
      }
   }
   return finded;
}
void sort_subjects(vector<string> &current_week, course doros)
{
   for (int i = 0; i < doros.size(); i++)
   {
      current_week.push_back(doros[i].name);
   }
   sort(current_week.begin(), current_week.end());
}