#include "game.hpp"
Game::Game()
{
    this->init_window();
    this->read_from_map();
    this->init_game_ground();
    this->init_player(start_gate_pos.first, start_gate_pos.second);
    game_going_view.setCenter(Vector2f(start_gate_pos.first, start_gate_pos.second));
    window->setView(game_going_view);
}

Game::~Game()
{
    delete this->window;
    delete this->player;
}

// functions
void Game::init_game_ground()
{
    int first = 0;

    for (int i = 0; i < game_map.size(); i++)
    {
        for (int k = 0; k < game_map[i].size(); k++)
        {
            if (game_map[i][k] == '.')
            {
                MovableBackground *kosa = new MovableBackground((k * 85), first, 21);
                grounding.push_back(kosa);
            }
            else if (game_map[i][k] == '$')
            {
                // MovableBackground *kosa = new MovableBackground((k * 87), first + 45, 20);
                // grounding.push_back(kosa);
                start_gate_pos.first = k * 85;
                start_gate_pos.second = first + 85;
            }

            if (game_map[i][k] == '\n')
            {
                first += 150;
            }
        }
    }
}
void Game::read_from_map()
{
    string one_line;
    ifstream myfile("map.txt");
    while (getline(myfile, one_line))
    {
        game_map.push_back(one_line + "\n");
    }
    myfile.close();
    for (int i = 0; i < game_map.size(); i++)
    {
        cout << game_map[i];
    }
}
bool Game::still_on_ground(float x, float y)
{
    int flag = 0;
    for (int i = 0; i < grounding.size(); i++)
    {
        if (grounding[i]->where_it_is().intersects(player->where_is_player()))
        {
            flag++;
        }
    }
    if (flag != 0)
    {
        // cout << flag << endl;
        return true;
    }
    return false;
}
bool Game::place_it_on_ground()
{
    int finded = 0;
    for (int i = 0; i < grounding.size(); i++)
    {
        if (grounding[i]->where_it_is().intersects(player->where_is_player()))
        {
            finded = i;
            break;
        }
    }
    player->set(grounding[finded]->getPosition().x, grounding[finded]->getPosition().y);
    return true;
}
bool Game::falling()
{
    int counter = grounding.size() - 1;
    int finded = -1;

    for (int j = 0; j < grounding[counter]->getHalfSize_y(); j++)
    {
        // cout << "\t" << grounding[counter]->getHalfSize_y() << endl;
        player->falling_from_jump();
        for (int i = 0; i < grounding.size(); i++)
        {
            if (grounding[i]->where_it_is().intersects(player->where_is_player()))
            {
                finded = i;
                break;
            }
        }
        if (finded != -1)
        {
            cout << "----" << grounding[finded]->getPosition().x << grounding[finded]->getPosition().y << endl;
            // player->set(grounding[finded]->getPosition().x, grounding[finded]->getPosition().y);
            break;
        }
    }

    return true;
}
void Game::run()
{
    while (window->isOpen())
    {

        this->update();
        this->render();
    }
}

void Game::init_window()
{
    window = new RenderWindow(VideoMode(850, 650), "turtix");
    window->setFramerateLimit(144);
    // window->setVerticalSyncEnabled(false);
    window->setPosition(Vector2i(1, 10));
    which_pic_has_set = 0;
}

void Game::init_player(float starting_point_x, float starting_point_y)
{
    player = new Player(starting_point_x, starting_point_y);
    direction = true;
}

void Game::render()
{
    this->window->clear();
    window->setView(game_going_view);
    for (int i = 0; i < grounding.size(); i++)
    {
        grounding[i]->Render(*window);
    }
    this->player->render(*window);
    this->window->display();
}

void Game::update()
{
    Event ev;
    while (window->pollEvent(ev))
    {
        if (ev.type == Event::KeyPressed)
        {
            if (ev.key.code == Keyboard::Space)
            {
                window->close();
            }
            else if (ev.key.code == Keyboard::Left)
            {
                player->moving(-2.f, 0.f, which_pic_has_set, 0);
                if (!still_on_ground(1.f, 1.f))
                {
                    cout << "game_over" << endl;
                    // window->close();
                    which_pic_has_set--;
                    player->moving(10.f, 0.f, which_pic_has_set, 0);
                }
                else
                {
                    direction = true;
                    /*for (int k = 0; k < grounding.size(); k++)
                    {
                        grounding[k]->Update(*window, 0, +1.f);
                    }*/
                    game_going_view.move(-10.f, 0.f);
                }

                // still_on_ground(1.f, 2.f);
                /*player->moving(-1.f, 0.f, which_pic_locki);
                for (int k = 0; k < grounding.size(); k++)
                {
                    grounding[k]->Update(*window, 0, +1.f);
                }*/
            }
            else if (ev.key.code == Keyboard::Right)
            {
                player->moving(2.f, 0.f, which_pic_has_set, 1);

                if (!still_on_ground(1.f, 0.f))
                {
                    cout << "game_over" << endl;
                    // window->close();
                    which_pic_has_set--;
                    player->moving(-10.f, 0.f, which_pic_has_set, 1);
                }
                else
                {
                    direction = false;
                    /*for (int i = 0; i < grounding.size(); i++)
                    {
                        grounding[i]->Update(*window, 0, -1.f);
                    }*/
                    game_going_view.move(+10.f, 0.f);
                }
            }
            else if (ev.key.code == Keyboard::Up)
            {
                if (direction == false)
                {
                    // player->jumping(25.f, 6.f);
                    player->moving(5.f, -30.f, which_pic_has_set, 1);
                    cout << "right\n";
                    if (!still_on_ground(1.f, 0.f))
                    {
                        player->moving(5.f, 30.f, which_pic_has_set, 1);
                        cout << "game_over" << endl;
                        falling();
                    }
                    else
                    {
                        //place_it_on_ground();
                        cout<<"pop"<<endl;
                        /*for (int i = 0; i < grounding.size(); i++)
                        {
                            grounding[i]->Update(*window, +5.f, 5.f);
                        }*/
                        game_going_view.move(+0.f, -200.f);
                    }
                }
                else
                {
                    // player->jumping(-25.f, -6.f);
                    player->moving(-5.f, -30.f, which_pic_has_set, 0);
                    if (!still_on_ground(1.f, 0.f))
                    {
                        player->moving(+5.f, +30.f, which_pic_has_set, 0);
                        cout << "game_over" << endl;
                        falling();
                    }
                    else
                    {
                        //place_it_on_ground();
                        /*for (int i = 0; i < grounding.size(); i++)
                        {
                            grounding[i]->Update(*window, -5.f, -5.f);
                        }*/
                        game_going_view.move(0.f, -200.f);
                    }
                }
            }
            else if (ev.key.code == Keyboard::Down)
            {
                player->moving(0.f, +1.f, which_pic_has_set, 0);
                /*for (int i = 0; i < grounding.size(); i++)
                {
                    grounding[i]->Update(*window, -1.f, 1.f);
                }*/
                game_going_view.move(0.f, 5.f);
            }
        }
        else if (ev.type == Event::Closed)
        {
            window->close();
        }
    }
}
