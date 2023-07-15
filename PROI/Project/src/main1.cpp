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

constexpr unsigned int SIZE = 1000;


int main()
{
    sf::RenderWindow window(sf::VideoMode(SIZE*4/3, SIZE), "Czougi");
    Map mainMap{SIZE*4/3, SIZE};
    Gamee game{mainMap, window, SIZE};
    Screen screen{ window, game };
    Leaderboard board;
    read_file(filename, board);
    Tank* player1 = new Tank(mainMap, "player1", 100, 100, 200, 0, 0);
    Tank* player2 = new Tank(mainMap, "player2", 100, 100, 900, 0, 0);
    Tank* current;
    GameController controller{player1, player2};
    controller.set_board(board);
    sf::ConvexShape activePlayerArrow(3);
    activePlayerArrow.setPoint(0, { 5,0 });
    activePlayerArrow.setPoint(1, { 45,0 });
    activePlayerArrow.setPoint(2, { 25,25 });
    activePlayerArrow.setFillColor(sf::Color(0, 0x99, 0));
    activePlayerArrow.setOutlineThickness(-3);
    activePlayerArrow.setOutlineColor(sf::Color::Black);


    //player1->mainGun.setAngle(1);
    mainMap.add(player1);
    mainMap.add(player2);

    window.setFramerateLimit(60);
    //window.setKeyRepeatEnabled(false);

    sf::Font font{};
    auto fs = cmrc::Resources::get_filesystem();
    auto file = fs.open("src/Resources/Bullpen3D.ttf");
    /* if (!font.loadFromFile("Bullpen3D.ttf")) */
    if (!font.loadFromMemory(file.begin(), std::size(file)))
    {
        std::cerr << "Error while loading font Bullpen3D.ttf" << std::endl;
        return -1;
    }
    // set up HUD
    sf::Text ammo, plrName, velo;
    ammo.setFont(font);
    plrName.setFont(font);
    velo.setFont(font);
    ammo.setPosition(10, 10);
    plrName.setPosition(10, 50);
    velo.setPosition(150, 10);
    std::stringstream converter;
    while (window.isOpen())
    {
        current = controller.getActivePlayer();

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
                board = controller.get_board();
                write_to_file(filename, board);
            }
            if (event.type == sf::Event::MouseButtonPressed)
                screen.mouseHandler(event);


            //
            // events that can be executed only if game state is waiting
            //
            if (!controller.isWaiting()) continue;
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                current->shoot();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                try
                {
                    current->mainGun.setAngle(current->mainGun.getAngle() + 0.01f);
                }
                catch (const std::invalid_argument& e)
                {
#ifdef _DEBUG
                    std::cout << e.what() << "\n";
#endif
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                try
                {
                    current->mainGun.setAngle(current->mainGun.getAngle() - 0.01f);
                }
                catch (const std::invalid_argument& e)
                {
#ifdef _DEBUG
                    std::cout << e.what() << "\n";
#endif
                };
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
            {
                current->setAmmoSlot(1);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
            {
                current->setAmmoSlot(2);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
            {
                current->setAmmoSlot(3);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
            {
                current->setAmmoSlot(4);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
            {
                current->setAmmoSlot(5);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                current->amovelo += 0.1f;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                current->amovelo -= 0.1f;
                if (current->amovelo<0) current->amovelo = 0;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                current->moveLeft();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                current->moveRight();
            }
        }
        converter.str("");
        converter << "Ammo: " << current->getAmmoSlot();
        ammo.setString(converter.str());
        converter.str("");
        converter << "Current player: " << current->getName();
        plrName.setString(converter.str());
        converter.str("");
        converter << "Velocty: " << current->getAmoVelo();
        velo.setString(converter.str());
        // Clear screen
        window.clear(sf::Color(0x10275100));


        std::pair<bool, bool> theres = mainMap.update();
        controller.update(theres);
        mainMap.draw(window); // pass target window
        window.draw(ammo);
        window.draw(plrName);
        window.draw(velo);
        screen.draw();
        activePlayerArrow.setPosition(current->position.x - 25, current->position.y-80);
        window.draw(activePlayerArrow);

        // Update the window
        if (controller.isGameOver())
        {;
            board = controller.get_board();
            write_to_file(filename, board);
            current = controller.getActivePlayer(); //make sure to get the correct tank
            sf::Text over;
            over.setFont(font);
            over.setString(current->getName() + " won!");
            over.setCharacterSize(100);
            over.setPosition({SIZE/2,SIZE/2});
            window.draw(over);
            window.display();
            sf::sleep(sf::seconds(5));
            screen.showMainMenu();
//            window.close();
        }
        window.display();
    }
    return EXIT_SUCCESS;
}
