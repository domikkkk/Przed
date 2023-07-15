#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Scorched/Leaderboards/Leaderboards.hpp"
#include "Scorched/GameController/GameController.hpp"

constexpr unsigned int SIZE = 1000;


static std::string filename = "leaderboards.txt";

class Gamee {
public:
	Gamee(sf::RenderWindow& targetwindow, unsigned int Size) : map{ SIZE * 4 / 3, SIZE }, window(targetwindow) {
		window.setSize({ Size * 4 / 3, Size });
		window.setTitle("Czougi");
		window.setFramerateLimit(60);
		sf::Font font{};
		auto fs = cmrc::Resources::get_filesystem();
		auto file = fs.open("src/Resources/Bullpen3D.ttf");

	}
	void play() {

		Tank* player1 = new Tank(map, "player1", 100, 100, 200, 0, 0);
		Tank* player2 = new Tank(map, "player2", 100, 100, 900, 0, 0);
		controller = std::make_unique<GameController>( player1, player2 );
		map.add(player1);
		map.add(player2);
		current = controller->getActivePlayer();
		read_file(filename, board);
	}

	void updateStuff()
	{
		std::pair<bool, bool> theres = map.update();
		controller->update(theres);
		current = controller->getActivePlayer();
	}
	Tank* current = nullptr;
	Map map;
	sf::RenderWindow& window;
	std::unique_ptr<GameController> controller;
	Leaderboard board;
};

enum
{
	Game,
	MainMenu,
	Highscores,
	Invalid = -1
};

struct Button : public sf::RectangleShape
{
	Button(sf::Vector2f size) : RectangleShape(size){}
	unsigned nextPage = -1;
};

void MoveTextToRect(sf::RectangleShape& button, sf::Text& text)
{
	sf::Vector2f centerPos = sf::Vector2f(button.getPosition().x + button.getSize().x / 2, button.getPosition().y + button.getSize().y / 2);
	text.setPosition(centerPos.x - text.getGlobalBounds().width / 2, centerPos.y - text.getGlobalBounds().height / 2);
}

class Screen
{
public:

	Screen(sf::RenderWindow& targetWindow) : windowRef(targetWindow)
	{
		auto fs = cmrc::Resources::get_filesystem();
		auto file = fs.open("src/Resources/Bullpen3D.ttf");
		/* if (!font.loadFromFile("Bullpen3D.ttf")) */
		if (!font.loadFromMemory(file.begin(), std::size(file)))
		{
			std::cerr << "Error while loading font Bullpen3D.ttf" << std::endl;
			return;
		}
		changePage(MainMenu);
	};

	void showMainMenu()
	{
		changePage(MainMenu);
	}

	void HandleEvents(sf::Event event)
	{
		if (event.type == sf::Event::Closed) {
			windowRef.close();
			auto board = actualgame->controller->get_board();
			write_to_file(filename, board);
		}

		if (event.type == sf::Event::MouseButtonPressed)
			mouseHandler(event);

		//
		// events that can be executed only if game state is waiting
		//
		if (!actualgame) return;
		if (!actualgame->controller->isWaiting()) return;
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
			actualgame->current->shoot();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			try {
				actualgame->current->mainGun.setAngle(actualgame->current->mainGun.getAngle() + 0.01f);
			}
			catch (const std::invalid_argument& e) {
#ifdef _DEBUG
				std::cout << e.what() << "\n";
#endif
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			try {
				actualgame->current->mainGun.setAngle(actualgame->current->mainGun.getAngle() - 0.01f);
			}
			catch (const std::invalid_argument& e) {
#ifdef _DEBUG
				std::cout << e.what() << "\n";
#endif
			};
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
			actualgame->current->setAmmoSlot(1);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
			actualgame->current->setAmmoSlot(2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
			actualgame->current->setAmmoSlot(3);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
			actualgame->current->setAmmoSlot(4);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
			actualgame->current->setAmmoSlot(5);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			actualgame->current->amovelo += 0.1f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			actualgame->current->amovelo -= 0.1f;
			if (actualgame->current->amovelo < 0) actualgame->current->amovelo = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			actualgame->current->moveLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			actualgame->current->moveRight();
		}
	}

	void draw()
	{
		windowRef.clear(sf::Color(0x10275100));
		if (currentPage == Game)
		{
			actualgame->updateStuff();
			actualgame->map.draw(windowRef);

			std::stringstream converter;

			converter << "Ammo: " << actualgame->current->getAmmoSlot();
			auto& a = dynamic_cast<sf::Text&>(*screenObjects[0]);
			a.setString(converter.str());
			converter.str("");
			converter << "Current player: " << actualgame->current->getName();
			auto& b = dynamic_cast<sf::Text&>(*screenObjects[1]);
			b.setString(converter.str());
			converter.str("");
			converter << "Velocty: " << actualgame->current->getAmoVelo();
			auto& c = dynamic_cast<sf::Text&>(*screenObjects[2]);
			c.setString(converter.str());
			// Clear screen


			windowRef.draw(a);
			windowRef.draw(b);
			windowRef.draw(c);
			activePlayerArrow->setPosition(actualgame->current->position.x - 25, actualgame->current->position.y - 80);
			windowRef.draw(*activePlayerArrow);

			// Update the window
			if (actualgame->controller->isGameOver())
			{
				auto board = actualgame->controller->get_board();

				write_to_file(filename, board);
				auto current = actualgame->controller->getActivePlayer(); //make sure to get the correct tank
				sf::Text over;
				over.setFont(font);
				over.setString(actualgame->current->getName() + " won!");
				over.setCharacterSize(100);
				over.setPosition({ SIZE / 2,SIZE / 2 });
				windowRef.draw(over);
				windowRef.display();
				sf::sleep(sf::seconds(5));
				showMainMenu();
				//            window.close();
			}
		}



		for (auto& object : screenObjects)
		{
			windowRef.draw(*object);
		}

		windowRef.display();
	}

	void update()
	{
		if (currentPage == Game)
		{
			activePlayerArrow->setPosition(actualgame->current->position.x - 25, actualgame->current->position.y - 80);
		}
	}

	/// <summary>
	/// this function is further divided to handle each screen differently
	/// </summary>
	/// <param name="event"></param>
	void mouseHandler(sf::Event event)
	{
		auto pos = sf::Mouse::getPosition(windowRef);
		for (auto& obj : screenObjects)
		{
			try
			{
				auto& casted = dynamic_cast<Button&>(*obj);
				if (casted.getGlobalBounds().contains(windowRef.mapPixelToCoords(sf::Mouse::getPosition(windowRef))))
				{
					changePage(casted.nextPage);
					break;
				}
			}
			catch (...) {} // bad cast exceptions
			
		}
	}

//private:

	void changePage(int pageNumber)
	{
		currentPage = pageNumber;
		screenObjects.clear();
		switch (pageNumber)
		{
		case Game:
		{
			delete actualgame;
			actualgame = new Gamee{windowRef,SIZE };
			actualgame->play();
			// HUD, and then game is also displayed
			auto ammo = std::make_unique<sf::Text>();
			auto plrName = std::make_unique<sf::Text>();
			auto velo = std::make_unique<sf::Text>();
            activePlayerArrow = std::make_unique<sf::ConvexShape>(3);
            activePlayerArrow->setPoint(0, { 5,0 });
            activePlayerArrow->setPoint(1, { 45,0 });
            activePlayerArrow->setPoint(2, { 25,25 });
            activePlayerArrow->setFillColor(sf::Color(0, 0x99, 0));
            activePlayerArrow->setOutlineThickness(-3);
            activePlayerArrow->setOutlineColor(sf::Color::Black);
            std::stringstream converter;
			ammo->setFont(font);
			plrName->setFont(font);
			velo->setFont(font);
			ammo->setPosition(10, 10);
			plrName->setPosition(10, 50);
			velo->setPosition(150, 10);
            converter.str("");
            converter << "Ammo: " << actualgame->current->getAmmoSlot();
            ammo->setString(converter.str());
            converter.str("");
            converter << "Current player: " << actualgame->current->getName();
            plrName->setString(converter.str());
            converter.str("");
            converter << "Velocty: " << actualgame->current->getAmoVelo();
            velo->setString(converter.str());
			screenObjects.push_back(std::move(ammo));
			screenObjects.push_back(std::move(plrName));
			screenObjects.push_back(std::move(velo));
		}
		break;
		case MainMenu:
			// two buttons
		{
			auto startButton = std::make_unique<Button>(sf::Vector2f{ 400,100 });
			auto scoresButton = std::make_unique<Button>(sf::Vector2f{ 400,100 });
			startButton->setPosition(windowRef.getSize().x / 2.f, 100.f);
			scoresButton->setPosition(windowRef.getSize().x / 2.f, 300.f);
			startButton->setFillColor(sf::Color(0x996633));
			scoresButton->setFillColor(sf::Color(0x996633));
			startButton->nextPage = Game;
			scoresButton->nextPage = Highscores;
			auto startText = std::make_unique<sf::Text>();
			auto scoresText = std::make_unique<sf::Text>();
			startText->setString("Start");
			scoresText->setString("Highscores");
			startText->setFont(font);
			scoresText->setFont(font);
			MoveTextToRect(*startButton, *startText);
			MoveTextToRect(*scoresButton, *scoresText);
			screenObjects.push_back(std::move(startButton));
			screenObjects.push_back(std::move(scoresButton));
			screenObjects.push_back(std::move(startText));
			screenObjects.push_back(std::move(scoresText));
		}
		break;
		case Highscores:
		{
			// some text labels that need to be loaded from file
			auto backText = std::make_unique<sf::Text>();
			backText->setFont(font);
			backText->setString("<- Back");
			auto backButton = std::make_unique<Button>(sf::Vector2f{ 100,50 });
			backButton->setPosition(50, 50);
			backButton->nextPage = MainMenu;
			backButton->setFillColor(sf::Color(0x996633));
			MoveTextToRect(*backButton, *backText);
			screenObjects.push_back(std::move(backButton));
			screenObjects.push_back(std::move(backText));
            Leaderboard board;
            read_file(filename, board);
            std::stringstream converter;
			actualgame->controller->set_board(board);
            converter << board;
            auto leaderboard = std::make_unique<sf::Text>();
            leaderboard->setPosition(500, 100);
            leaderboard->setFont(font);
            leaderboard->setString(converter.str());
            screenObjects.push_back(std::move(leaderboard));
		}
		break;

		default:
			((void(*)())0x2137)(); // jeszcze jak
			currentPage = Invalid;
		}
	}


	sf::Font font{};
	unsigned currentPage = -1;
	std::vector<std::unique_ptr<sf::Drawable>> screenObjects;
	sf::RenderWindow& windowRef;
    Gamee* actualgame = nullptr;
	std::unique_ptr<sf::ConvexShape> activePlayerArrow;
};
