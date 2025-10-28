#include <iostream>
#include <string>
#include <vector>
#include "Mission.h"
#include "TaxiCompany.h"
#include "Processing.h"
using namespace std;
const string space = " ";
const char new_line = '\n';
const string invalid_arguments = "INVALID_ARGUMENTS\n";
const vector<string> Predefined_commands = {"add_time_mission", "add_distance_mission", "add_count_mission",
                                            "assign_mission", "record_ride", "show_missions_status"};
int main()
{
    Processing process;
    int space_pos = -1;
    string entered_input;
    while (getline(cin, entered_input, new_line))
    {
        space_pos = entered_input.find(space);
        if (space_pos == -1)
        {
            cout << invalid_arguments;
            continue;
        }
        string entered_command = entered_input.substr(0, space_pos);
        if (entered_command == Predefined_commands[0])
            process.add_time_mission(entered_input.substr(space_pos + 1));
        else if (entered_command == Predefined_commands[1])
            process.add_distance_mission(entered_input.substr(space_pos + 1));
        else if (entered_command == Predefined_commands[2])
            process.add_count_mission(entered_input.substr(space_pos + 1));
        else if (entered_command == Predefined_commands[3])
            process.assign_mission_with_chosen_driver(entered_input.substr(space_pos + 1));
        else if (entered_command == Predefined_commands[4])
            process.recording_finished_ride(entered_input.substr(space_pos + 1));
        else if (entered_command == Predefined_commands[5])
            process.show_missions_status(entered_input.substr(space_pos + 1));
        space_pos = -1;
    }
    return 0;
}