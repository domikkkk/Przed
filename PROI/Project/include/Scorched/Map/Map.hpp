#pragma once 
#include <vector>

#include "Scorched/Shared/Entity.hpp"
#include "Scorched/Terrain/TerrainTypes.hpp"

extern float Vectof2f_mag(sf::Vector2f v); // stolen from terrain

class Map
{
public:
    Map(unsigned int sizeX, unsigned int sizeY)
    {
        terrain = new SandTerrain{ sizeX, sizeX / 60 };
        this->sizeX = sizeX;
        this->sizeY = sizeY;
    };
    Map(){};
    ~Map()
    {
        for (Entity* ent : entities)
        {
            delete ent;
        }
        delete terrain;
    };
    void add(Entity* newEntity);
    void set(int x, int y){
        this->sizeX = x;
        this->sizeY = y;
        terrain = new SandTerrain{sizeX, sizeX / 60};
    };

    bool TestCollision(sf::Vector2f target) const;
    std::pair<bool, bool> update();
    void draw(sf::RenderWindow& window);

    void UpdateLock(bool status)
    {
        locked = status;
        if (!locked)
        {
            entities.insert(entities.end(), std::make_move_iterator(tempEntities.begin()),
                std::make_move_iterator(tempEntities.end()));
            tempEntities.clear();
        }

    }

    float gravity = 0.05f;

    Terrain* terrain;

    private:
        std::vector<Entity*> entities; // active entities
        std::vector<Entity*> tempEntities; // entities are extended with those after update is finished
        unsigned sizeX, sizeY; //game dimensions
        bool locked = false; // it is necessary to lock operations on real entities array while map::update() is running
};
