#include "BabyTurtle.hpp"

const string baby_turtle_0="baby_turtle.png";
const string baby_turtle_1="baby_walk_1.png";
const string baby_turtle_2="baby_walk_2.png";
const string baby_turtle_3="baby_walk_3.png";
const string baby_turtle_4="baby_walk_4.png";

BabyTurtle::BabyTurtle(float pos_x, float pos_y)
{
    first_pos_x = pos_x;
    first_pos_y = pos_y;
    speed_x = 5.f;
    speed_y = 5.f;
    _tex.loadFromFile(baby_turtle_0);
    turtle_pic.setTexture(_tex);
    turtle_pic.scale(0.6, 0.6);
    turtle_pic.setPosition(first_pos_x, first_pos_y);
    unprisoned = false;
    reach_gate = false;
    counter = 0;
    left = true;
}

void BabyTurtle::moving()
{
    if (left == true)
        going_left();
    else
        going_right();
}

void BabyTurtle::Render(RenderWindow &window)
{
    window.draw(turtle_pic);
}

bool BabyTurtle::still_keptive()
{
    if (unprisoned == false)
        return true;
    return false;
}

FloatRect BabyTurtle::where_is_kept()
{
    return turtle_pic.getGlobalBounds();
}

bool BabyTurtle::free_the_turtle()
{
    unprisoned = true;
    return false;
}
void BabyTurtle::going_left()
{
    if (counter % 2 == 0)
        _tex.loadFromFile(baby_turtle_1);
    else
        _tex.loadFromFile(baby_turtle_2);
    turtle_pic.setTexture(_tex);
    turtle_pic.move(speed_x * -2, speed_y * 0);
    counter++;
}

void BabyTurtle::going_right()
{
    if (counter % 2 == 0)
        _tex.loadFromFile(baby_turtle_3);
    else
        _tex.loadFromFile(baby_turtle_4);
    turtle_pic.setTexture(_tex);
    turtle_pic.move(speed_x * +2, speed_y * 0);
    counter++;
}

void BabyTurtle::change_face_dir()
{
    bool pre_direction = left;
    left = !(pre_direction);
}

void BabyTurtle::falling()
{
    if (left == true)
        turtle_pic.move(speed_x * -5, speed_y * +30);
    else
        turtle_pic.move(speed_x * +5, speed_y * +30);
}

void BabyTurtle::setting_keptive_again()
{
    _tex.loadFromFile(baby_turtle_0);
    turtle_pic.setTexture(_tex);
    turtle_pic.setPosition(first_pos_x, first_pos_y);
    unprisoned = false;
    counter = 0;
    left = true;
}

void BabyTurtle::reaching_gate()
{
    reach_gate = true;
}

bool BabyTurtle::does_it_reach()
{
    if (reach_gate == true)
    {
        return true;
    }
    return false;
}
