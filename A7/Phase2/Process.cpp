#include "Process.hpp"
const string str_goal_keeper = "Goalkeeper";
const string str_defender_one = "Defender 1";
const string str_defender_two = "Defender 2";
const string str_forward = "Forward";
const string str_midfielder = "Midfielder";
const string str_defender = "Defender";
const string str_week_number = "week_num";
const string str_empty = "";
const string str_list_of_player = "list of players:";
const string str_league_standing = "league standings:";
const string permission_denied = "Permission Denied";
const string bad_request = "Bad Request";
const string not_found = "Not Found";
const string empty = "Empty";
const string every_thing_ok = "OK";
const string str_team_name = "team_name";
const string str_name = "name";
const string str_admin = "admin";
const string str_password = "password";
const string str_user = "user";
const string str_username = "username";
const char new_line = '\n';
const string admin_password = "123456";
const string str_fantast_team = "fantasy_team";
const string dot = ". ";
const string str_space = " ";
const string str_ranks = "ranks";
const string summarized_goal_keeper = "gk";
const string summarized_forward = "fw";
const string summarized_midfielder = "md";
const string summarized_defender = "df";
const string team_of_week="team of the week:";
const vector<string> general_commands = {"GET", "PUT", "DELETE", "POST"};
const vector<string> get_commands = {"matches_result_league", "users_ranking", "team_of_the_week",
                                     "players", "league_standings", "squad", "show_budget"};
const vector<string> post_commands = {"signup", "login", "logout", "register_admin", "buy_player",
                                      "open_transfer_window", "close_transfer_window", "pass_week",
                                      "sell_player", "set_captain"};

Process::Process(vector<shared_ptr<LeagueTeams>> _league_teams, vector<shared_ptr<Match>> _matches)
{
    matches = _matches;
    league_teams = _league_teams;
    admin_login = false;
    user_login = false;
    transfer_window = true;
    add_admin_id();
}

void Process::handling_commands()
{
    string input;
    int current_week = 0;
    while (getline(cin, input, new_line))
    {
        int pos_of_space = input.find(str_space);
        string command = input.substr(0, pos_of_space);
        if (command == general_commands[0])
            get_command_subset(input.substr(pos_of_space + 1), to_string(current_week));
        else if (command == general_commands[1])
            continue;
        else if (command == general_commands[2])
            continue;
        else if (command == general_commands[3])
            post_command_subset(input.substr(pos_of_space + 1), to_string(current_week), current_week);
        else
            cout << bad_request << endl;
    }
}

string Process::find_special_word_in_vector(vector<string> read_words, string needed_one)
{
    string found_one = str_empty;
    for (int i = 0; i < read_words.size(); i++)
    {
        if (read_words[i] == needed_one)
            found_one = read_words[i + 1];
    }
    return found_one;
}

void Process::validate_week_number(string ordered_week, string current_week)
{
    if (ordered_week != str_empty)
    {
        if (stoi(ordered_week) > stoi(current_week))
            throw runtime_error(bad_request);
    }
    else if (stoi(current_week) == 0)
        throw runtime_error(bad_request);
}

void Process::finding_team_of_the_week(string remain, string current_week_num)
{
    vector<string> read_words = split_the_input(remain);
    string input_week = find_special_word_in_vector(read_words, str_week_number);
    validate_week_number(input_week, current_week_num);
    if (input_week != str_empty)
    {
        current_week_num = input_week;
    }
    printing_all_the_best_ones(current_week_num);
}

void Process::printing_all_the_best_ones(string week_num)
{
    cout<<team_of_week<<endl;
    finding_the_best_goalkeeper(week_num);
    finding_the_best_defender(week_num);
    finding_the_best_midfielder(week_num);
    finding_the_best_forward(week_num);
}

void Process::finding_the_best_defender(string week_num)
{
    vector<shared_ptr<Player>> defenders = find_each_team_best_defenders(week_num);
    sorting_the_vector_of_special_players(defenders, week_num);
    cout << str_defender_one;
    defenders[0]->show_the_best_player(week_num);
    cout << str_defender_two;
    defenders[1]->show_the_best_player(week_num);
}

void Process::sorting_the_vector_of_special_players(vector<shared_ptr<Player>> &best_players_each_team, string week_num)
{
    sort(best_players_each_team.begin(), best_players_each_team.end(), [&week_num](shared_ptr<Player> const &first, shared_ptr<Player> const &second) -> bool
         {
             if (first->find_the_score_of_this_week(week_num) != second->find_the_score_of_this_week(week_num))
                 return first->find_the_score_of_this_week(week_num) >second->find_the_score_of_this_week(week_num);
             if (first->get_name() != second->get_name())
                 return first->get_name() < second->get_name();
          return true; });
}

vector<shared_ptr<Player>> Process::find_each_team_best_defenders(string week_num)
{
    vector<shared_ptr<Player>> defenders;
    for (int i = 0; i < league_teams.size(); i++)
    {
        shared_ptr<Player> best_defender1, best_defender2;
        league_teams[i]->find_the_best_defender(week_num, best_defender1, best_defender2);
        defenders.push_back(best_defender1);
        defenders.push_back(best_defender2);
    }
    return defenders;
}

void Process::finding_the_best_midfielder(string week_num)
{
    vector<shared_ptr<Player>> midfielders = find_each_team_best_midfielder(week_num);
    sorting_the_vector_of_special_players(midfielders, week_num);
    cout << str_midfielder;
    midfielders[0]->show_the_best_player(week_num);
}

vector<shared_ptr<Player>> Process::find_each_team_best_midfielder(string week_num)
{
    vector<shared_ptr<Player>> midfielders;
    for (int i = 0; i < league_teams.size(); i++)
    {
        shared_ptr<Player> found_ones = league_teams[i]->find_the_best_midfielder(week_num);
        midfielders.push_back(found_ones);
    }
    return midfielders;
}

void Process::finding_the_best_goalkeeper(string week_num)
{
    vector<shared_ptr<Player>> goalkeepers = find_each_team_best_goalkeeper(week_num);
    sorting_the_vector_of_special_players(goalkeepers, week_num);
    cout << str_goal_keeper;
    goalkeepers[0]->show_the_best_player(week_num);
}

vector<shared_ptr<Player>> Process::find_each_team_best_goalkeeper(string week_num)
{
    vector<shared_ptr<Player>> goalkeepers;
    for (int i = 0; i < league_teams.size(); i++)
    {
        shared_ptr<Player> found_ones = league_teams[i]->find_the_best_goalkeeper(week_num);
        goalkeepers.push_back(found_ones);
    }
    return goalkeepers;
}

void Process::finding_the_best_forward(string week_num)
{
    vector<shared_ptr<Player>> forwards = find_each_team_best_forward(week_num);
    sorting_the_vector_of_special_players(forwards, week_num);
    cout << str_forward;
    forwards[0]->show_the_best_player(week_num);
}

vector<shared_ptr<Player>> Process::find_each_team_best_forward(string week_num)
{
    vector<shared_ptr<Player>> forwards;
    for (int i = 0; i < league_teams.size(); i++)
    {
        shared_ptr<Player> found_ones = league_teams[i]->find_the_best_forward(week_num);
        forwards.push_back(found_ones);
    }
    return forwards;
}

void Process::get_command_subset(string remain, string current_week)
{
    try
    {
        int pos_of_space = remain.find(str_space);
        if (remain.substr(0, pos_of_space) == get_commands[0])
            find_the_matches_happen_this_week(remain.substr(pos_of_space + 1), current_week);
        else if (remain == get_commands[1])
            find_the_user_ranking();
        else if (remain.substr(0, pos_of_space) == get_commands[2])
            finding_team_of_the_week(remain.substr(pos_of_space + 1), current_week);
        else if (remain.substr(0, pos_of_space) == get_commands[3])
            find_the_league_team_asked(remain.substr(pos_of_space + 1), current_week);
        else if (remain == get_commands[4])
            find_the_league_ranking(current_week);
        else if (remain.substr(0, pos_of_space) == get_commands[5])
            find_fantasy_team(remain.substr(pos_of_space + 1), current_week);
        else if (remain == get_commands[6])
            show_the_budget();
        else
            throw runtime_error(not_found);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
}

void Process::how_many_parameters_mention(const vector<string> &read_words, string &position, string &team_name, bool &ranks)
{
    for (int i = 0; i < read_words.size(); i++)
    {
        if (read_words[i] == str_team_name)
            team_name = read_words[i + 1];
        if (read_words[i] == str_ranks)
            ranks = true;
        if (read_words[i] != str_ranks && i == 3)
            position = read_words[i];
    }
    if (!(position == summarized_goal_keeper || position == summarized_defender || position == summarized_midfielder || position == summarized_forward) && position != "")
        throw runtime_error(bad_request);
}

void Process::validate_having_this_team(string &team_name)
{
    int flag = 0;
    string new_nn;
    for (int i = 0; i < team_name.size(); i++)
    {
        if (team_name[i] == '_')
            new_nn += str_space;
        else
            new_nn += team_name[i];
    }
    for (int i = 0; i < league_teams.size(); i++)
    {
        if (league_teams[i]->has_the_same_name(new_nn))
            flag++;
    }
    if (flag == 0)
        throw runtime_error(not_found);
    team_name = new_nn;
}

void Process::find_the_league_team_asked(string remain, string current_week)
{
    string position = str_empty, team_name;
    bool ranks = false;
    vector<string> read_words = split_the_input(remain);
    how_many_parameters_mention(read_words, position, team_name, ranks);
    validate_having_this_team(team_name);
    for (int i = 0; i < league_teams.size(); i++)
    {
        if (league_teams[i]->has_the_same_name(team_name))
        {
            cout << str_list_of_player << endl;
            league_teams[i]->printing_the_players_as_they_add(current_week, position, ranks);
        }
    }
}

void Process::find_the_matches_happen_this_week(string remain, string current_week_num)
{
    vector<string> read_words = split_the_input(remain);
    string week_num = find_special_word_in_vector(read_words, str_week_number);
    validate_week_number(week_num, current_week_num);
    if (week_num != str_empty)
        print_the_matches_in_this_week(week_num);
    else
        print_the_matches_in_this_week(current_week_num);
}

void Process::print_the_matches_in_this_week(string week_number)
{
    for (int i = 0; i < matches.size(); i++)
    {
        if (matches[i]->has_the_same_week_num(week_number))
        {
            matches[i]->print_all_the_matches_in_this_week();
        }
    }
}

void Process::sort_the_users(vector<shared_ptr<FantasyTeam>> &copy_fantasy_teams)
{
    sort(copy_fantasy_teams.begin(), copy_fantasy_teams.end(), [](shared_ptr<FantasyTeam> const &a, shared_ptr<FantasyTeam> const &b) -> bool
         {if (a->get_total_score()!=b->get_total_score())
            return a->get_total_score()>b->get_total_score();
            if (a->get_name() != b->get_name())
                 return a->get_name() < b->get_name();
            return true; });
}

void Process::find_the_user_ranking()
{
    if (last_week_fantasy_teams.size() == 0)
        throw runtime_error(empty);
    sort_the_users(last_week_fantasy_teams);
    for (int h = 0; h < last_week_fantasy_teams.size(); h++)
    {
        cout << to_string(h + 1) << dot;
        last_week_fantasy_teams[h]->show_the_team();
    }
}

void Process::find_the_league_ranking(string week_num)
{
    cout << str_league_standing << endl;
    LeagueRank this_week_league_teams_rank(week_num);
    this_week_league_teams_rank.find_the_data_of_each_team(week_num, league_teams);
}

void Process::find_fantasy_team(string remain, string week_number)
{
    if (!is_the_user_login())
        throw runtime_error(permission_denied);
    vector<string> read_words = split_the_input(remain);
    string requested_team = find_special_word_in_vector(read_words, str_fantast_team);
    if (requested_team != str_empty)
        print_the_found_fantasy_team(requested_team, week_number);
    else
        print_the_found_fantasy_team(current_access, week_number);
}

int Process::find_the_index_of_wanted_team(string fantasy_team_name)
{
    int found = -1;
    for (int i = 0; i < fantasy_teams.size(); i++)
    {
        if (fantasy_teams[i]->has_the_same_name(fantasy_team_name))
            found = i;
    }
    if (found == -1)
        throw runtime_error(not_found);
    return found;
}

void Process::print_the_found_fantasy_team(string fantasy_team_name, string week_number)
{
    int index_needed = find_the_index_of_wanted_team(fantasy_team_name);
    if (!fantasy_teams[index_needed]->was_the_team_completed_previous_week(week_number))
    {
        throw runtime_error(empty);
    }
    fantasy_teams[index_needed]->print_details_of_the_team(week_number);
}

void Process::post_command_subset(string remain, string week_num, int &week_number_counter)
{
    try
    {
        int pos_of_space = remain.find(str_space);
        if (remain.substr(0, pos_of_space) == post_commands[0])
            sign_up_new_user(remain.substr(pos_of_space + 1));
        else if (remain.substr(0, pos_of_space) == post_commands[1])
            login_the_user(remain.substr(pos_of_space + 1));
        else if (remain == post_commands[2])
            logout_from_the_system();
        else if (remain.substr(0, pos_of_space) == post_commands[3])
            register_admin(remain.substr(pos_of_space + 1));
        else if (remain.substr(0, pos_of_space) == post_commands[4])
            buy_player_for_fantasy_team(remain.substr(pos_of_space + 1), week_num);
        else if (remain == post_commands[5])
            opening_the_transfer_window();
        else if (remain == post_commands[6])
            closing_the_transfer_window();
        else if (remain == post_commands[7])
            passing_the_week(week_num, week_number_counter);
        else if (remain.substr(0, pos_of_space) == post_commands[8])
            sell_player_from_fantasy_team(remain.substr(pos_of_space + 1), week_num);
        else if (remain.substr(0, pos_of_space) == post_commands[9])
            setting_captain_for_this_fantasy_team(remain.substr(pos_of_space + 1));
        else
            throw runtime_error(not_found);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
}

void Process::login_the_user(string remain)
{
    string id, password;
    find_the_name_password(remain, id, password, str_team_name);
    is_another_person_login();
    is_the_user_info_right(id, password);
    user_login = true;
    current_access = id;
    cout << every_thing_ok << endl;
}

void Process::is_the_user_info_right(string id, string password)
{
    int flag = 0;
    for (int i = 0; i < records.size(); i++)
    {
        if (records[i].name == id)
        {
            if (records[i].pass_word != password)
                throw runtime_error(permission_denied);
            flag++;
        }
    }
    if (flag == 0)
        throw runtime_error(not_found);
}

void Process::add_admin_id()
{
    AccessRecord admin(str_admin, admin_password, str_admin);
    records.push_back(admin);
}

void Process::sign_up_new_user(string remain)
{
    string id, password;
    find_the_name_password(remain, id, password, str_team_name);
    is_another_person_login();
    is_it_duplicate_id(id);
    add_new_user(id, password);
    user_login = true;
    current_access = id;
    cout << every_thing_ok << endl;
}

void Process::add_new_user(string id, string password)
{
    AccessRecord new_user(id, password, str_user);
    records.push_back(new_user);
    shared_ptr<FantasyTeam> new_one = make_shared<FantasyTeam>(id);
    fantasy_teams.push_back(new_one);
}

void Process::find_the_name_password(string remain, string &id, string &password, string compare)
{
    vector<string> read_words = split_the_input(remain);
    for (int i = 0; i < read_words.size(); i++)
    {
        if (read_words[i] == compare)
            id = read_words[i + 1];
        if (read_words[i] == str_password)
            password = read_words[i + 1];
    }
}

vector<string> Process::split_the_input(string remain)
{
    istringstream ss(remain);
    string word;
    vector<string> read_words;
    while (ss >> word)
    {
        read_words.push_back(word);
    }
    return read_words;
}

void Process::is_it_duplicate_id(string id)
{
    for (int i = 0; i < records.size(); i++)
    {
        if (records[i].name == id)
            throw runtime_error(bad_request);
    }
}

void Process::logout_from_the_system()
{
    current_access = str_empty;
    admin_login = false;
    user_login = false;
    cout << every_thing_ok << endl;
}

void Process::register_admin(string remain)
{
    string id, password;
    find_the_name_password(remain, id, password, str_username);
    is_another_person_login();
    is_admin_login_info_right(id, password);
    admin_login = true;
    current_access = id;
    cout << every_thing_ok << endl;
}

void Process::is_admin_login_info_right(string id, string password)
{
    for (int i = 0; i < records.size(); i++)
    {
        if (records[i].position == str_admin)
        {
            if (records[i].name != id || records[i].pass_word != password)
                throw runtime_error(bad_request);
        }
    }
}

bool Process::is_another_person_login()
{
    if (user_login == true || admin_login == true)
    {
        throw runtime_error(bad_request);
    }
    return false;
}

bool Process::is_the_admin_login()
{
    if (admin_login == true)
    {
        return true;
    }
    return false;
}

bool Process::is_the_user_login()
{
    if (user_login == true)
    {
        return true;
    }

    return false;
}

void Process::opening_the_transfer_window()
{
    if (is_the_admin_login())
    {
        transfer_window = true;
        cout << every_thing_ok << endl;
    }
    else
        throw runtime_error(permission_denied);
}

void Process::closing_the_transfer_window()
{
    if (is_the_admin_login())
    {
        transfer_window = false;
        cout << every_thing_ok << endl;
    }
    else
        throw runtime_error(permission_denied);
}

string Process::find_the_name_of_player(vector<string> read_words)
{
    string player;
    int found = -1;
    for (int i = 0; i < read_words.size(); i++)
    {
        if (found == 0)
        {
            player = player + read_words[i];
            if (i != read_words.size() - 1)
                player += str_space;
        }
        if (read_words[i] == str_name)
            found = 0;
    }
    return player;
}

void Process::validating_the_user_permission()
{
    if (is_the_admin_login())
        throw runtime_error(permission_denied);
    if (transfer_window == false)
        throw runtime_error(permission_denied);
}

shared_ptr<Player> Process::find_the_input_player_pointer(string player_name)
{
    shared_ptr<Player> found_player;
    for (int i = 0; i < league_teams.size(); i++)
    {
        league_teams[i]->has_this_player(player_name, found_player);
    }
    if (found_player == nullptr)
        throw runtime_error(not_found);
    return found_player;
}

void Process::are_we_allowed_to_buy(shared_ptr<Player> found_player, string week_num)
{
    validating_the_user_permission();
    for (int i = 0; i < fantasy_teams.size(); i++)
    {
        if (fantasy_teams[i]->has_the_same_name(current_access))
            fantasy_teams[i]->can_we_get_this_player(found_player, week_num);
    }
}

void Process::are_we_allowed_to_sell(string player)
{
    validating_the_user_permission();
    for (int i = 0; i < fantasy_teams.size(); i++)
    {
        if (fantasy_teams[i]->has_the_same_name(current_access))
            fantasy_teams[i]->can_we_sell_this_player(player);
    }
}

void Process::sell_player_from_fantasy_team(string remain, string week_num)
{
    if (!is_the_user_login())
    {
        throw runtime_error(permission_denied);
    }
    vector<string> read_words = split_the_input(remain);
    string player = find_the_name_of_player(read_words);
    are_we_allowed_to_sell(player);
}

void Process::buy_player_for_fantasy_team(string remain, string week_num)
{
    if (!is_the_user_login())
        throw runtime_error(permission_denied);
    vector<string> read_words = split_the_input(remain);
    shared_ptr<Player> found_player = find_the_input_player_pointer(find_the_name_of_player(read_words));
    are_we_allowed_to_buy(found_player, week_num);
    cout << every_thing_ok << endl;
}

void Process::passing_the_week(string week_num, int &week_number_counter)
{
    if (!is_the_admin_login())
        throw runtime_error(permission_denied);
    for (int i = 0; i < league_teams.size(); i++)
        league_teams[i]->Deprivation_done_for_yellow_cards(week_number_counter);
    week_number_counter++;
    update_the_week_in_fantasy_teams(week_num, week_number_counter);
    for (int i = 0; i < league_teams.size(); i++)
        league_teams[i]->deleting_previous_yellow_cards_of_team(week_number_counter);
    cout << every_thing_ok << endl;
}

void Process::update_the_week_in_fantasy_teams(string week_num, int week_number_counter)
{
    for (int i = 0; i < fantasy_teams.size(); i++)
    {
        fantasy_teams[i]->make_vector_of_previous_week_players(week_num);
        fantasy_teams[i]->restart_the_ability_to_buy_sell();
        fantasy_teams[i]->calculate_the_whole_week_score(to_string(week_number_counter));
    }
    last_week_fantasy_teams = fantasy_teams;
}

void Process::show_the_budget()
{
    if (!is_the_user_login())
        throw runtime_error(permission_denied);
    for (int i = 0; i < fantasy_teams.size(); i++)
    {
        if (fantasy_teams[i]->has_the_same_name(current_access))
        {
            fantasy_teams[i]->show_the_budget();
        }
    }
}

void Process::setting_captain_for_this_fantasy_team(string remain)
{
    int found = -1;
    vector<string> read_words = split_the_input(remain);
    string name=finding_the_name_of_captain(read_words);
    if (!is_the_user_login())
        throw runtime_error(permission_denied);
    for (int i = 0; i < fantasy_teams.size(); i++)
    {
        if (fantasy_teams[i]->has_the_same_name(current_access))
        {
            fantasy_teams[i]->setting_the_captain(name);
        }
    }
}

string Process::finding_the_name_of_captain(vector<string> read_words)
{
    int found = -1;
    string name;
    for (int i = 0; i < read_words.size(); i++)
    {
        if (found == 0)
        {
            name = name + read_words[i];
            if (i != read_words.size() - 1)
                name += str_space;
        }
        if (read_words[i] == str_name)
            found = 0;
    }
    return name;
}

AccessRecord::AccessRecord(string _id, string _password, string _position)
{
    name = _id;
    pass_word = _password;
    position = _position;
}
