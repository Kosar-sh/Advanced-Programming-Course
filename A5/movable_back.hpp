#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>

#ifndef GUIMOVABLEBACKGROUNDS_H
#define GUIMOVABLEBACKGROUNDS_H

using namespace std;
using namespace sf;
class MovableBackground
{
public:
        void creating_gate_start(int first_pos_x, int first_pos_y);
        void Update(sf::RenderWindow &window, int move_y, int move_x);
        void Render(sf::RenderWindow &window);
        MovableBackground(int first_pos_x, int first_pos_y, int choosen_object);
        FloatRect where_it_is();
        sf::Vector2f getPosition();
        float getHalfSize_x();
        float getHalfSize_y();
        void creating_walls(int first_pos_x, int first_pos_y);
        void creating_tiles(int first_pos_x, int first_pos_y);

private:
        Texture _tex;
        RectangleShape bgShape;
        Vector2f size_of_sprite;
        Sprite sprite;
        float sprite_speed;
        float pos_x;
        float pos_y;
};
#endif