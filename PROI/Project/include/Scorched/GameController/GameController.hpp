#pragma once
#include <vector>
#include "Scorched/Leaderboards/Leaderboards.hpp"

enum State { shooting, waiting, game_over};

class GameController
{
public:

	template <class... T> explicit GameController(T... tanks) : players{ tanks... }, current(players.begin()) {}

	void update(std::pair<bool, bool> theres)
	{
		if (state == waiting && theres.first)
		{
            (*current)->points++;
			state = shooting;
		}
		else if (state == shooting && !theres.first)
		{
            (*current)->points = 0;
			state = waiting;
			if (++current == players.end()) current = players.begin();
		}
        if (state == waiting)
        {
            (*current)->points++;
        }
        if(theres.second) {
            (*current)->points *= 0.25;
            board.update(*current);
        }
		// always check for game over

		if ((*current)->getKillStatus())
		{
			current = players.erase(current);
			if (current == players.end()) current = players.begin(); // the player was last, erase doesn't point to next valid
		}

		if (players.size() == 1)
		{
			state = game_over;
		}
	}

	Tank* getActivePlayer()
	{
		return *current;
	}
    Leaderboard get_board()
    {
        return board;
    }
    void set_board(Leaderboard& new_board)
    {
        this->board = new_board;
    }
	bool isGameOver()
	{
		return state == game_over;
	}

	bool isWaiting()
	{
		return state == waiting;
	}
    void add_player(Tank* tank)
    {
        players.push_back(tank);
    }
    Leaderboard board;
	State state = waiting;
	std::vector<Tank*> players;
	std::vector<Tank*>::iterator current;
};
