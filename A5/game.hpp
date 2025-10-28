
#include "player.hpp"
#include "movable_back.hpp"
#include "BonusObject.hpp"
#include "BabyTurtle.hpp"
#include "Enemy.hpp"
using namespace std;
using namespace sf;

#ifndef GAME_HPP
#define GAME_HPP

class Game
{
private:
    RenderWindow *window;
    Player *player;
    int which_pic_has_set;
    vector<MovableBackground *> grounding;
    vector<MovableBackground *> walls;
    MovableBackground *starting_gate;
    vector<BonusObj *> stars;
    vector<BonusObj *> diamonds;
    pair<float, float> start_gate_pos;
    vector<string> game_map;
    vector<Texture *> right_going_pics;
    vector<Texture *> left_going_pics;
    View game_going_view;
    vector<BabyTurtle *> baby_turtls;
    vector<Enemy *> enemies;
    Text text;
    Font font;
    bool direction;
    int total_diamond;
    int total_stars;

public:
    Game();
    ~Game();

    void run();
    void init_window();
    void update();
    void render();
    void init_player(float starting_point_x, float starting_point_y);
    void init_game_ground();
    void read_from_map();
    bool still_on_ground();
    bool place_it_on_ground();
    bool falling();
    void free_the_babies();
    void walking_turtles();
    void can_move_more(BabyTurtle *free_one);
    void calculate_bonus_amounts();
    void enemies_stay_in_line(Enemy *free_one);
    void losing_life();
    void baby_turtles_cross_enemy();
    void kiling_enemies();
    bool player_cross_walls();
    void player_going_down();
    void player_going_up();
    void player_going_right();
    void player_going_left();
    void handle_crashing_falling(BabyTurtle *free_one, bool crash_wall, bool can_move);
    void rendering_bonus_objects();
    void rendering_enemies_babies();
    void rendering_back_ground();
    void init_background_from_map(char background_read_from_map, int width, int &hight);
    void init_enemies(char enemy_read_from_map, int width, int &hight);
    void init_bonus_objects(char objects_read_from_map, int width, int &hight);
    void init_baby_turtles(char babies_read_from_map, int width, int &hight);
    bool the_player_win_the_game();
    void init_starting_gate(char gate_read_from_map, int width, int &hight);
    void printing_scores();
    void init_texts();
};
#endif