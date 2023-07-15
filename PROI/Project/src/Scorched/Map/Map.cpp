#include "Scorched/Map/Map.hpp"
#include "Scorched/Bullet/Bullet.hpp"
#include "Scorched/Tank/Tank.hpp"
#include <iostream>

#ifdef _DEBUG
#include <iostream>
#endif

void Map::add(Entity* newEntity)
{
    if (locked)
        tempEntities.push_back(newEntity);
    else
        entities.push_back(newEntity);
}

bool Map::TestCollision(sf::Vector2f target) const
{
    //@TODO: take out the -10000, its hidden in FloorHeight atm...
    return terrain->FloorHeight(target).first == -10000;
}

// update every object
// return whether there are still some bullets active flying around
std::pair<bool, bool> Map::update()
{
    // tanks and bullets are no more!!
    //for(auto &it: bullets)
    //{
    //    it.update();
    //};

    //// does this even make sense?
    //// what does it have to update?
    //for(auto &it: tanks)
    //{
    //    //(*it).update();
    //};

    //
    UpdateLock(true);

    bool thereIsBullet = false;
    bool thereIshit = false;

    for (Entity* ent : entities)
    {
        ent->update();
    }

    // check collisions with terrain on every object after they have moved
    for (Entity* ent : entities)
    {
        if (ent->getKillStatus()) continue;
        auto* b = dynamic_cast<Bullet*>(ent);
        if (b == nullptr) continue;
        thereIsBullet = true;

        // only bullets interact with terrain at the moment
        float ypos{ b->position.y };
        if (ypos > sizeY || b->position.x<0 || b->position.x>sizeX || b->if_hit())
        {
            ent->setKillStatus();
            continue;
        }

        float y = terrain->FloorHeight(b->position).first;
        if ((ypos >= y or ypos >= sizeY) && b->canCollide()) {
            b->set_collide_to_true(); // THIS CAN INVALIDATE ITERATORS
            if (b->if_hit())
            {
                for (Entity* ent : entities)
                {

                    auto tank = dynamic_cast<Tank*>(ent);
                    if (tank != nullptr)
                    {
                        // remove grounded flag from every tank, because
                        // there is no way to tell when a bullet causes
                        // tank to become airbone
                        tank->setGrounded(false);

                        // damage nearby tank (bullet hits floor near tank, but doesn't land on tank)
                        // reduce hp based linerarly on distance
                        float dist = Vectof2f_mag(tank->position - b->position);
                        float bullet_range = b->get_range()*2; // damage area will be 2 times larger
                        if (dist < bullet_range)
                        {
                            thereIshit = true;
                            float proportion = dist / bullet_range;
                            try
                            {
                                tank->setHp(tank->getHp() - b->get_damage() * proportion);
                            }
                            catch (...)
                            {
                                // tank ded
                                tank->setKillStatus();
                            }
                        }
                    }
                        
                }
                terrain->MakeHole(b->position, b->get_range());
                b->setKillStatus();
            }
        }
        else // did not hit terrain, but maybe hit tank?
        {
            for (Entity* tank_search : entities) {

                auto tank = dynamic_cast<Tank *>(tank_search);
                if (tank != nullptr) {
                    float dist = Vectof2f_mag(tank->position - b->position) - b->get_collision_radius() -
                                 tank->get_collision_radius();
                    if (dist < 0 && b->canCollide()) {
                        // tank got hit directly
#ifdef _DEBUG
                        std::cout << "direct hit\n";
#endif
                        thereIshit = true;
                        try {
                            tank->setHp(tank->getHp() - b->get_damage());
                        }
                        catch (...) {
                            // tank ded
                            tank->setKillStatus();
                        }
                        terrain->MakeHole(b->position, b->get_range());
                        b->setKillStatus();
                        break; // notice how bullet can't damage multiple tanks directly
                    }
                }
            }
        }

    }
    UpdateLock(false); // causes objects to get moved over from tempEntities to entities
    std::erase_if(entities, [](Entity* obj) {
        return obj->getKillStatus();
    });
    return {thereIsBullet, thereIshit};

};

void Map::draw(sf::RenderWindow& window)
{
    // draw everything (terrain first)
    window.draw(*terrain);
    for (Entity* ent : entities)
    {
        window.draw(*ent);
    }
}
