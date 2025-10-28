#include "Enemy.hpp"
const string enemy_left_1="enemy-1-left.png";
const string enemy_left_2="enemy-2-left.png";
const string enemy_right_1="enemy-1-right.png";
const string enemy_right_2="enemy-2-right.png";

Enemy::Enemy(int first_pos_x, int first_pos_y, int which_enemy)
{
    if (which_enemy == 1)
    {
        init_first_enemy();
        lives = 2;
        enemy_num = 1;
    }
    else
    {
        init_second_enemy();
        enemy_num = 2;
        counter = 0;
    }
    sprite.setPosition(first_pos_x, first_pos_y);
    speed_x = 0.5f;
    left = true;
}

Enemy::~Enemy()
{
}

void Enemy::init_first_enemy()
{
    tex.loadFromFile(enemy_left_1);
    sprite.setTexture(tex);
}

void Enemy::init_second_enemy()
{
    tex.loadFromFile(enemy_left_2);
    sprite.setTexture(tex);
}

FloatRect Enemy::where_is_enemy()
{
    return sprite.getGlobalBounds();
}

void Enemy::moving()
{
    if (left == true)
        sprite.move(-1.f, 0.f);
    else
        sprite.move(1.f, 0.f);
    if (enemy_num == 2)
        counter++;
}

void Enemy::reach_wall_end_of_line()
{
    bool new_face_dir = !(left);
    left = new_face_dir;
    if (enemy_num == 1)
        change_sprite_pic_enemy1();
    else
        change_sprite_pic_enemy2();
}

void Enemy::change_sprite_pic_enemy1()
{
    if (left == true)
    {
        tex.loadFromFile(enemy_left_1);
        sprite.setTexture(tex);
    }
    else
    {
        tex.loadFromFile(enemy_right_1);
        sprite.setTexture(tex);
    }
}

void Enemy::change_sprite_pic_enemy2()
{
    if (left == true)
    {
        tex.loadFromFile(enemy_left_2);
        sprite.setTexture(tex);
    }
    else
    {
        tex.loadFromFile(enemy_right_2);
        sprite.setTexture(tex);
    }
}

int Enemy::get_enemy_num()
{
    return enemy_num;
}
void Enemy::Render(RenderWindow &window)
{
    window.draw(sprite);
}
void Enemy::killed_ones()
{
    lives--;
}
