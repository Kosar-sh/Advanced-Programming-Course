#include "BonusObject.hpp"
const string diamonds_add="diamond_1.png";
const string stars_add="star_1.png";

BonusObj::BonusObj(int diamond_or_star, int first_pos_x, int first_pos_y)
{
    have_catch = false;
    if (diamond_or_star == 0)
        init_diamond(first_pos_x, first_pos_y);
    else
        init_star(first_pos_x, first_pos_y);
    object.setTexture(texture);
    object.setScale(0.7f, 0.7f);
    object.setPosition(first_pos_x, first_pos_y);
}

void BonusObj::Render(RenderWindow &window)
{
    window.draw(object);
}

FloatRect BonusObj::where_is_the_object()
{
    return object.getGlobalBounds();
}

void BonusObj::rotate_object()
{
    object.setOrigin(Vector2f(object.getGlobalBounds().width, object.getGlobalBounds().height) / 2.f);
    object.rotate(22.f);
}

void BonusObj::player_catch_diamond()
{
    have_catch = true;
}

bool BonusObj::not_catch_before()
{
    if (have_catch == true)
        return true;
    return false;
}
void BonusObj::init_star(int first_pos_x, int first_pos_y)
{
    texture.loadFromFile(stars_add);
    price_value = 5;
}

void BonusObj::init_diamond(int first_pos_x, int first_pos_y)
{
    texture.loadFromFile(diamonds_add);
    price_value = 10;
}
