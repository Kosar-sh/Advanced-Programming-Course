#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace sf;

#ifndef BONUS_OBJECT_H
#define BONUS_OBJECT_H

class BonusObj
{
private:
    Texture texture;
    Sprite object;
    int price_value;
    bool have_catch;

public:
    BonusObj(int diamond_or_star, int first_pos_x, int first_pos_y);
    void init_star(int first_pos_x, int first_pos_y);
    void init_diamond(int first_pos_x, int first_pos_y);
    void Render(RenderWindow &window);
    FloatRect where_is_the_object();
    void rotate_object();
    void player_catch_diamond();
    bool not_catch_before();
};

#endif