#include "player.hpp"
const string left_stay = "1-left.png";
const string left_run = "2-left.png";
const string right_stay = "1-right.png";
const string right_run = "2-right.png";

Player::Player(int starting_point_x, int starting_point_y)
{
    movement_speed = 5.f;
    jump_y_speed = 5.f;
    jump_x_speed = 5.f;
    this->init_texture();
    this->init_sprite(starting_point_x, starting_point_y);
    start_point_x = starting_point_x;
    start_point_y = starting_point_y;
    left = true;
}
void Player::render(sf::RenderWindow &window)
{
    window.draw(spirit);
}
void Player::init_texture()
{
    texrie.loadFromFile(left_stay);
}
void Player::init_sprite(int starting_point_x, int starting_point_y)
{
    spirit.setTexture(texrie);
    spirit.scale(0.6f, 0.6f);
    spirit.setPosition(starting_point_x, starting_point_y);
}

void Player::moving(const float dirx, const float diry, int &which_locki, int which_direction)
{
    if (which_direction == 0)
    {
        going_left(dirx, diry, which_locki);
        left = true;
    }
    else
    {
        going_right(dirx, diry, which_locki);
        left = false;
    }
    spirit.setTexture(texrie);
    spirit.move(movement_speed * dirx, movement_speed * diry);
    which_locki++;
}

FloatRect Player::where_is_player()
{
    return this->spirit.getGlobalBounds();
}

void Player::going_left(const float dirx, const float diry, int &which_locki)
{
    if (which_locki % 2 == 0)
        texrie.loadFromFile(left_run);
    else
        texrie.loadFromFile(left_stay);
}

void Player::going_right(const float dirx, const float diry, int &which_locki)
{

    if (which_locki % 2 == 0)
        texrie.loadFromFile(right_stay);
    else
        texrie.loadFromFile(right_stay);
}

void Player::losing_life_turtle()
{
    spirit.setPosition(start_point_x, start_point_y);
}

Vector2f Player::posing()
{
    return spirit.getPosition();
}

void Player::set(float x, float y)
{
    spirit.setPosition(x, y);
}

void Player::falling_from_jump()
{
    spirit.move(0.f, 150.f);
}

const Texture *Player::get_text()
{
    return spirit.getTexture();
}

void Player::change_face_direction()
{
    bool current_dir = left;
    left = !(current_dir);
}
