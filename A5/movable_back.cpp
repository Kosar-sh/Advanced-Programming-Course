#include "movable_back.hpp"
using namespace sf;
const string walls_pic="walls.png";
const string start_gate_pic="start_gate.png";
const string ground_pic="ground.png";
void MovableBackground::Update(sf::RenderWindow &window, int move_y, int move_x)
{
        sprite.move(sprite_speed * move_x, sprite_speed * move_y);
}
void MovableBackground::Render(sf::RenderWindow &window)
{
        window.draw(sprite);
}

MovableBackground::MovableBackground(int first_pos_x, int first_pos_y, int choosen_object)
{
        if (choosen_object == 20)
                creating_gate_start(first_pos_x, first_pos_y);
        else if (choosen_object == 22)
                creating_walls(first_pos_x, first_pos_y);
        else
                creating_tiles(first_pos_x, first_pos_y);
}
FloatRect MovableBackground::where_it_is()
{
        return this->sprite.getGlobalBounds();
}
sf::Vector2f MovableBackground::getPosition()
{
        return sprite.getPosition();
}
float MovableBackground::getHalfSize_x()
{
        return sprite.getPosition().x;
}
float MovableBackground::getHalfSize_y()
{
        return sprite.getPosition().y;
}
void MovableBackground::creating_walls(int first_pos_x, int first_pos_y)
{
        pos_x = first_pos_x;
        pos_y = first_pos_y;
        _tex.loadFromFile(walls_pic);
        sprite.setTexture(_tex);
        sprite.setPosition(first_pos_x, first_pos_y);
        sprite.scale(0.4f, 0.6f);
}
void MovableBackground::creating_tiles(int first_pos_x, int first_pos_y)
{
        sprite_speed = 10;
        _tex.loadFromFile(ground_pic);
        sprite.setTexture(_tex);
        sprite.setPosition(first_pos_x, first_pos_y);
        sprite.scale(0.4f, 0.4f);
        pos_x = first_pos_x;
        pos_y = first_pos_y;
}
void MovableBackground::creating_gate_start(int first_pos_x, int first_pos_y)
{
        pos_x = first_pos_x;
        pos_y = first_pos_y;
        _tex.loadFromFile(start_gate_pic);
        sprite.setTexture(_tex);
        sprite.setPosition(first_pos_x, first_pos_y);
        sprite.scale(0.7f, 0.7f);
}
