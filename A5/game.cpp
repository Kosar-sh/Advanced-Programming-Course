#include "game.hpp"

const string map_address = "map.txt";
const char tiles_sym = '.';
const char walls_sym = '|';
const char enemy_1_sym = 'E';
const char enemy_2_sym = 'M';
const char start_gate_sym = '$';
const char baby_turtle_sym = 'O';
const char diamonds_sym = '^';
const char stars_sym = '*';

Game::Game()
{
    this->init_window();
    this->read_from_map();
    this->init_game_ground();
    this->init_player(start_gate_pos.first, start_gate_pos.second);
    game_going_view.setCenter(Vector2f(start_gate_pos.first, start_gate_pos.second));
    window->setView(game_going_view);
    this->init_texts();
}

Game::~Game()
{
    delete this->window;
}

void Game::init_game_ground()
{
    int hight = 0;
    for (int i = 0; i < game_map.size(); i++)
    {
        for (int k = 0; k < game_map[i].size(); k++)
        {
            init_background_from_map(game_map[i][k], k, hight);
            init_bonus_objects(game_map[i][k], k, hight);
            init_baby_turtles(game_map[i][k], k, hight);
            init_starting_gate(game_map[i][k], k, hight);
            init_enemies(game_map[i][k], k, hight);
            if (game_map[i][k] == '\n')
                hight += 150;
        }
    }
}
void Game::read_from_map()
{
    string one_line;
    ifstream myfile(map_address);
    while (getline(myfile, one_line))
        game_map.push_back(one_line + "\n");
    myfile.close();
}
bool Game::still_on_ground()
{
    int flag = 0;
    for (int i = 0; i < grounding.size(); i++)
    {
        if (grounding[i]->where_it_is().intersects(player->where_is_player()))
            flag++;
    }
    if (flag != 0)
        return true;
    return false;
}
bool Game::place_it_on_ground()
{
    int finded = 0;
    for (int i = 0; i < grounding.size(); i++)
    {
        if (grounding[i]->where_it_is().intersects(player->where_is_player()))
        {
            finded = i;
            break;
        }
    }
    player->set(grounding[finded]->getPosition().x, grounding[finded]->getPosition().y);
    return true;
}
bool Game::falling()
{
    int finded = -1;
    player->falling_from_jump();
    for (int i = 0; i < grounding.size(); i++)
    {
        if (grounding[i]->where_it_is().intersects(player->where_is_player()))
        {
            finded = i;
            break;
        }
    }
    if (finded == -1)
        return false;
    return true;
}
void Game::run()
{
    while (window->isOpen())
    {

        this->update();
        if (the_player_win_the_game())
        {
            Game game;
            game.run();
        }
        for (int i = 0; i < stars.size(); i++)
            stars[i]->rotate_object();
        for (int i = 0; i < diamonds.size(); i++)
            diamonds[i]->rotate_object();
        this->render();
    }
}

void Game::init_window()
{
    window = new RenderWindow(VideoMode(850, 650), "turtix");
    window->setFramerateLimit(144);
    window->setPosition(Vector2i(1, 10));
    which_pic_has_set = 0;
}

void Game::init_player(float starting_point_x, float starting_point_y)
{
    player = new Player(starting_point_x, starting_point_y);
    direction = true;
}

void Game::render()
{
    // printing_scores();
    this->window->clear();
    window->setView(game_going_view);
    baby_turtles_cross_enemy();
    losing_life();
    window->draw(text);
    rendering_back_ground();
    starting_gate->Render(*window);
    rendering_bonus_objects();
    rendering_enemies_babies();
    walking_turtles();
    this->player->render(*window);
    this->window->display();
}

void Game::update()
{
    Event ev;
    while (window->pollEvent(ev))
    {
        if (ev.type == Event::KeyPressed)
        {
            if (ev.key.code == Keyboard::Escape)
                window->close();
            else if (ev.key.code == Keyboard::Left)
                player_going_left();
            else if (ev.key.code == Keyboard::Right)
                player_going_right();
            else if (ev.key.code == Keyboard::Up)
                player_going_up();
            else if (ev.key.code == Keyboard::Down)
                player_going_down();
        }
        else if (ev.type == Event::Closed)
            window->close();
        free_the_babies();
    }
}

void Game::free_the_babies()
{
    for (int i = 0; i < baby_turtls.size(); i++)
    {
        if (baby_turtls[i]->where_is_kept().intersects(player->where_is_player()) && baby_turtls[i]->still_keptive())
            baby_turtls[i]->free_the_turtle();
    }
}
void Game::walking_turtles()
{
    for (int i = 0; i < baby_turtls.size(); i++)
    {
        if (!baby_turtls[i]->still_keptive() && (!baby_turtls[i]->does_it_reach()))
            can_move_more(baby_turtls[i]);
    }
}

void Game::can_move_more(BabyTurtle *free_one)
{
    bool crash_wall = false, can_move = false;
    free_one->moving();
    if (starting_gate->where_it_is().intersects(free_one->where_is_kept()))
        free_one->reaching_gate();
    for (int i = 0; i < grounding.size(); i++)
    {
        if (grounding[i]->where_it_is().intersects(free_one->where_is_kept()))
            can_move = true;
    }
    for (int i = 0; i < walls.size(); i++)
    {
        if (free_one->where_is_kept().intersects(walls[i]->where_it_is()))
            crash_wall = true;
    }
    handle_crashing_falling(free_one, crash_wall, can_move);
}

void Game::calculate_bonus_amounts()
{
    for (int i = 0; i < diamonds.size(); i++)
    {
        if (diamonds[i]->where_is_the_object().intersects(player->where_is_player()))
        {
            total_diamond += 10;
            diamonds[i]->player_catch_diamond();
        }
    }
    for (int i = 0; i < stars.size(); i++)
    {
        if (stars[i]->where_is_the_object().intersects(player->where_is_player()))
        {
            total_stars += 5;
            stars[i]->player_catch_diamond();
        }
    }
}

void Game::enemies_stay_in_line(Enemy *free_one)
{
    bool crash_wall = false;
    bool can_move = false;
    for (int i = 0; i < grounding.size(); i++)
    {
        if (grounding[i]->where_it_is().intersects(free_one->where_is_enemy()))
            can_move = true;
    }
    for (int i = 0; i < walls.size(); i++)
    {
        if (free_one->where_is_enemy().intersects(walls[i]->where_it_is()))
            crash_wall = true;
    }
    if (crash_wall == true || can_move == false)
    {
        free_one->reach_wall_end_of_line();
        free_one->moving();
    }
}

void Game::losing_life()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i]->where_is_enemy().intersects(player->where_is_player()))
        {
            player->losing_life_turtle();
            game_going_view.setCenter(Vector2f(start_gate_pos.first, start_gate_pos.second));
        }
    }
}

void Game::baby_turtles_cross_enemy()
{
    for (int i = 0; i < baby_turtls.size(); i++)
    {
        for (int k = 0; k < enemies.size(); k++)
        {
            if (enemies[k]->where_is_enemy().intersects(baby_turtls[i]->where_is_kept()))
                baby_turtls[i]->setting_keptive_again();
        }
    }
}

void Game::kiling_enemies()
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i]->where_is_enemy().top == player->posing().y)
        {
            enemies[i]->killed_ones();
        }
    }
}

bool Game::player_cross_walls()
{
    for (int i = 0; i < walls.size(); i++)
    {
        if (walls[i]->where_it_is().intersects(player->where_is_player()))
        {
            player->change_face_direction();
            return true;
        }
    }
    return false;
}

void Game::player_going_down()
{
    if (direction == false)
    {
        player->moving(5.f, +30.f, which_pic_has_set, 1);
    }
    else
    {
        player->moving(-5.f, +30.f, which_pic_has_set, 0);
    }
    if (!still_on_ground())
        falling();
    else
    {
        game_going_view.move(0.f, +150.f);
        text.move(0.f, +150.f);
    }
}

void Game::player_going_up()
{
    if (direction == false)
        player->moving(5.f, -30.f, which_pic_has_set, 1);
    else
        player->moving(-5.0f, -30.f, which_pic_has_set, 0);
    kiling_enemies();
    calculate_bonus_amounts();
    if (!still_on_ground())
        falling();
    else
    {
        game_going_view.move(0.f, -150.f);
        text.move(0.f, -150.f);
    }
}

void Game::player_going_right()
{
    player->moving(2.f, 0.f, which_pic_has_set, 1);
    if (!still_on_ground())
    {
        which_pic_has_set--;
        if (!player_cross_walls())
        {
            if (!falling())
            {
                game_going_view.setCenter(Vector2f(start_gate_pos.first, start_gate_pos.second));
                player->losing_life_turtle();
            }
            else
                game_going_view.move(+5.f, 150.f);
        }
        else
            player->moving(-2.f, 0.f, which_pic_has_set, 0);
    }
    else
    {
        direction = false;
        game_going_view.move(+10.f, 0.f);
        text.move(10.f,0.f);
    }
}

void Game::player_going_left()
{
    player->moving(-2.f, 0.f, which_pic_has_set, 0);
    if (!still_on_ground())
    {
        which_pic_has_set--;
        if (!player_cross_walls())
        {
            if (!falling())
            {
                game_going_view.setCenter(Vector2f(start_gate_pos.first, start_gate_pos.second));
                player->losing_life_turtle();
            }
            else
                game_going_view.move(-5.f, 150.f);
        }
        else
            player->moving(+2.f, 0.f, which_pic_has_set, 1);
    }
    else
    {
        direction = true;
        game_going_view.move(-10.f, 0.f);
        text.move(-10.f,0.f);
    }
}

void Game::handle_crashing_falling(BabyTurtle *free_one, bool crash_wall, bool can_move)
{
    if (crash_wall == true)
    {
        free_one->change_face_dir();
        free_one->moving();
    }
    else if (crash_wall == false && can_move == false)
    {
        free_one->falling();
        bool not_die = false;
        for (int i = 0; i < grounding.size(); i++)
        {
            if (grounding[i]->where_it_is().intersects(free_one->where_is_kept()))
                not_die = true;
        }
        if (not_die == false)
            free_one->setting_keptive_again();
    }
}

void Game::rendering_bonus_objects()
{
    for (int i = 0; i < stars.size(); i++)
    {
        if (!stars[i]->not_catch_before())
            stars[i]->Render(*window);
    }
    for (int i = 0; i < diamonds.size(); i++)
    {
        if (!diamonds[i]->not_catch_before())
            diamonds[i]->Render(*window);
    }
}

void Game::rendering_enemies_babies()
{
    for (int i = 0; i < baby_turtls.size(); i++)
    {
        if (!baby_turtls[i]->does_it_reach())
            baby_turtls[i]->Render(*window);
    }
    for (int i = 0; i < enemies.size(); i++)
    {
        enemies[i]->Render(*window);
        enemies[i]->moving();
        enemies_stay_in_line(enemies[i]);
    }
}

void Game::rendering_back_ground()
{
    for (int i = 0; i < grounding.size(); i++)
    {
        grounding[i]->Render(*window);
    }
    for (int i = 0; i < walls.size(); i++)
    {
        walls[i]->Render(*window);
    }
}

void Game::init_background_from_map(char background_read_from_map, int width, int &hight)
{
    if (background_read_from_map == tiles_sym)
    {
        MovableBackground *kosa = new MovableBackground((width * 85), hight, 21);
        grounding.push_back(kosa);
    }
    else if (background_read_from_map == walls_sym)
    {

        MovableBackground *kosa = new MovableBackground((width * 85), hight, 22);
        walls.push_back(kosa);
    }
}

void Game::init_enemies(char enemy_read_from_map, int width, int &hight)
{
    if (enemy_read_from_map == enemy_1_sym)
    {
        Enemy *new_one = new Enemy((width * 85), hight + 75, 1);
        enemies.push_back(new_one);
    }
    else if (enemy_read_from_map == enemy_2_sym)
    {
        Enemy *new_one = new Enemy((width * 85), hight + 75, 2);
        enemies.push_back(new_one);
    }
}

void Game::init_bonus_objects(char objects_read_from_map, int width, int &hight)
{
    if (objects_read_from_map == stars_sym)
    {
        BonusObj *new_one = new BonusObj(1, (width * 85), hight + 15);
        stars.push_back(new_one);
    }

    else if (objects_read_from_map == diamonds_sym)
    {
        BonusObj *new_one = new BonusObj(0, (width * 85), hight + 15);
        diamonds.push_back(new_one);
    }
}

void Game::init_baby_turtles(char babies_read_from_map, int width, int &hight)
{
    if (babies_read_from_map == baby_turtle_sym)
    {
        BabyTurtle *new_one = new BabyTurtle((width * 85), hight + 75);
        baby_turtls.push_back(new_one);
    }
}
bool Game::the_player_win_the_game()
{
    for (int i = 0; i < baby_turtls.size(); i++)
    {
        if (baby_turtls[i]->still_keptive())
        {
            return false;
        }
    }
    return true;
}
void Game::init_starting_gate(char gate_read_from_map, int width, int &hight)
{
    if (gate_read_from_map == start_gate_sym)
    {
        starting_gate = new MovableBackground((width * 85), hight + 85, 20);
        start_gate_pos.first = width * 85;
        start_gate_pos.second = hight + 85;
    }
}

/*void Game::printing_scores()
{
    text.setString("Diamonds:" + to_string(total_diamond));
    text.setFillColor(Color::Blue);
}*/

void Game::init_texts()
{
    font.loadFromFile("Arial.ttf");
    text.setFont(font);
    text.setString("Diamonds:" + to_string(total_diamond) + "\n" + "Stars:" + to_string(total_stars));
    text.setFillColor(Color::Blue);
    text.setPosition(game_going_view.getSize().x, game_going_view.getSize().y);
}
