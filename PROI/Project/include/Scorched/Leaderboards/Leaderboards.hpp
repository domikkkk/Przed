#ifndef SCORCHED_LEADERBOARDS_HPP
#define SCORCHED_LEADERBOARDS_HPP
#pragma once
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Scorched/Tank/Tank.hpp"


class Leaderboard{
public:
    std::vector<std::pair<std::string, int>> tab;
    friend std::istream &operator>>(std::istream &is, Leaderboard& lb);
    friend std::ostream &operator<<(std::ostream &os, Leaderboard& lb);
    void update(Tank *tank);
};
void read_file(std::string file, Leaderboard& lb);
void write_to_file(std::string file, Leaderboard& lb);

#endif //SCORCHED_LEADERBOARDS_HPP
