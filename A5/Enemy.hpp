#include "player.hpp"
#include "movable_back.hpp"
#include "BonusObject.hpp"
#include "BabyTurtle.hpp"
using namespace std;
using namespace sf;

#ifndef ENEMY_HPP
#define ENEMY_HPP

class Enemy
{
private:
    Texture tex;
    Sprite sprite;
    float speed_x;
    int lives;
    bool left;
    int enemy_num;
    int counter;

public:
    Enemy( int first_pos_x, int first_pos_y,int which_enemy);
    ~Enemy();
    void init_first_enemy();
    void init_second_enemy();
    FloatRect where_is_enemy();
    void moving();
    void reach_wall_end_of_line();
    void change_sprite_pic_enemy1();
    void change_sprite_pic_enemy2();
    int get_enemy_num();
    void Render(RenderWindow &window);
    void killed_ones();
    
};
















#endif