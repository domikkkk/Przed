// sfml_czougi.cpp : Defines the entry point for the application.
//

#ifndef M_PI
#define M_PI 3.14159
#endif

#include <SFML/Graphics.hpp>
#include "Terrain.hpp"
#include "Scorched/Terrain/TerrainTypes.hpp"
#include "Scorched/Tank/Tank.hpp"

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

constexpr int SIZE = 1000; // window size
constexpr int SIZEY = SIZE * 3 / 4;


bool collision(Bullet& b, Terrain& t){
    float ypos{b.get_position().y};
    float y = t.FloorHeight(b.get_position());
    if(ypos >= y or ypos>=SIZEY){
        b.set_collide_to_true();
        return b.if_hit();
    }
    return false;
}


// this won't be used in final program, generates a sand terrain, displays it,
// shows debug mouse and floor pointers
int main()
{
    srand(time(0));

    // terrain
    SandTerrain visual(SIZE, SIZE / 60);

    // bullets that appear at start
    HugeBullet bullet(100, 200, 1, M_PI/3);
    BounceBullet bounce(150, 100, 1, 0);
    std::vector<Bullet> bullets{bullet, bounce};
    Tank t1(100,100,100,100,0);

    // debug markers
    sf::CircleShape bombCircle{ 50 };
    sf::CircleShape drop{ 10 };
    bombCircle.setFillColor(sf::Color::Red);
    drop.setFillColor(sf::Color::Green);

    // window
    sf::RenderWindow window(sf::VideoMode(SIZE, SIZEY), "Czougi");
    window.setFramerateLimit(60);

	while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                visual.MakeHole(event.mouseButton.x, event.mouseButton.y, 50);
                bullets.push_back(BounceBullet(event.mouseButton.x, event.mouseButton.y, 1, M_PI/6));
            }
//            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
//                bullets.push_back(HugeBullet(300, 50, 1, M_PI/2));
//                break;
//            }
        }
        // Clear screen
        window.clear();

        window.draw(visual);

        // bullet update loop
        auto i = bullets.begin();
        while(i!=bullets.end()) {
            i->update();
            window.draw(*i);
            if (i->if_hit()){
                i = bullets.erase(i);
            }
            if (collision(*i, visual)) {
                visual.MakeHole(i->get_position().x, i->get_position().y, i->get_range());
                i = bullets.erase(i);
            }
            if (i == bullets.end()) break;
            ++i;
        }
        t1.update();
        window.draw(t1);

        // updating debug markers
        sf::Vector2i mPos = sf::Mouse::getPosition(window);
        float mouse_floor = visual.FloorHeight(mPos.x, mPos.y);
        //std::cout<<mouse_floor<<"\n";
        bombCircle.setPosition(mPos.x-50, mPos.y-50);
        drop.setPosition(mPos.x-10, mouse_floor-20);
        window.draw(bombCircle);
        window.draw(drop);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
