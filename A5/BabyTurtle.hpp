#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>

#ifndef BABY_TURTLE_H
#define BABY_TURTLE_H

using namespace std;
using namespace sf;
class BabyTurtle
{
private:
    float first_pos_x;
    float first_pos_y;
    float free_pos_x;
    float free_pos_y;
    float speed_x;
    float speed_y;
    Texture _tex;
    Sprite turtle_pic;
    bool left;
    bool unprisoned;
    bool reach_gate;
    int counter;

public:
    BabyTurtle(float pos_x, float pos_y);
    void moving();
    void Render(RenderWindow &window);
    bool still_keptive();
    FloatRect where_is_kept();
    bool free_the_turtle();
    void going_left();
    void going_right();
    void change_face_dir();
    void falling();
    void setting_keptive_again();
    void reaching_gate();
    bool does_it_reach();
};

#endif