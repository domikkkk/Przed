#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include "Scorched/Map/Map.hpp"
#include "Scorched/Tank/Tank.hpp"
#include "Scorched/GameController/GameController.hpp"
#include <cmrc/cmrc.hpp>
#include <Scorched/Leaderboards/Leaderboards.hpp>
#include "Screen.hpp"

CMRC_DECLARE(Resources);


int main()
{
    sf::RenderWindow window(sf::VideoMode(SIZE*4/3, SIZE), "Czougi");
    Screen screen{ window};
    bool k{0};
    while (window.isOpen())
    {

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            screen.HandleEvents(event);
        }
        screen.update();
        screen.draw();
//        if(!k){
//            read_file(filename,screen.actualgame->board);
//            k = true;
//        }
    }
    return EXIT_SUCCESS;
}
