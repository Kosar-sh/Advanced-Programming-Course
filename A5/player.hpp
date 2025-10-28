#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;
using namespace sf;
#ifndef PLAYER_H
#define PLAYER_H

class Player
{
private:
    Texture texrie;
    Sprite spirit;
    float movement_speed;
    float jump_x_speed;
    float jump_y_speed;
    int start_point_x;
    int start_point_y;
    bool left;

public:
    Player(int starting_point_x, int starting_point_y);
    ~Player();
    void update();
    void render(sf::RenderWindow &window); //(RenderTarget &target);
    void init_texture();
    void init_sprite(int starting_point_x, int starting_point_y);
    void moving(const float dirx, const float diry, int &which_locki, int which_direction);
    float situation_y() { return spirit.getPosition().y; }
    float situation_x() { return spirit.getPosition().x; }
    FloatRect where_is_player();
    void going_left(const float dirx, const float diry, int &which_locki);
    void going_right(const float dirx, const float diry, int &which_locki);
    void losing_life_turtle();
    Vector2f posing();
    void set(float x, float y);
    void falling_from_jump();
    const Texture *get_text();
    void change_face_direction();
};

#endif