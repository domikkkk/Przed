#include "Scorched/Leaderboards/Leaderboards.hpp"


std::istream &operator>>(std::istream &is, Leaderboard &lb){
    std::string name;
    int score;
    is >> name >> score;
    lb.tab.emplace_back(name, score);
    return is;
}

std::ostream &operator<<(std::ostream &os, Leaderboard &lb) {
    auto it=lb.tab.begin();
    if (it == lb.tab.end()){
        os << '\n';
        return os;
    }
    for(it; it<lb.tab.end();++it){
        os << it->first << ' ' << it->second << '\n';
    }
    return os;
}

void Leaderboard::update(Tank *tank) {
    for(auto player = tab.begin(); player<tab.end(); ++player){
        if(player->first == tank->getName()){
            player->second += tank->points;
            player->second = std::max(0, player->second);
            tank->points = 0;
            return;
        }
    }
    tab.emplace_back(tank->getName(), tank->points);
    tank->points = 0;
}

void read_file(std::string file, Leaderboard& lb){
    std::fstream handle;
    handle.open(file);
    std::string is;
    do {
        std::stringstream iss;
        std::getline(handle, is);
        if(is.empty()){
            break;
        }
        iss << is;
        iss >> lb;
    }
    while(!is.empty());
    handle.close();
}

void write_to_file(std::string file, Leaderboard& lb){
    std::fstream handle;
    handle.open(file, std::ios::out);
    std::stringstream os;
    os<<lb;
    handle << os.str();
    handle.close();
}
