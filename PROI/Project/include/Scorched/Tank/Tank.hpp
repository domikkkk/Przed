#pragma once
#include "../src/Scorched/Tank/TankConstants.hpp"
#include "Scorched/Shared/Entity.hpp"
#include <string>

class Map;

class Gun{
    /*
     * Class used to describe the gun of a Tank and ways to aim with it.
     */
    public:
        Gun(float angle = defaultAngle);
        void setAngle(float newAngle);
        float getAngle() const;
        void moveUp();
        void moveDown();

    private:
        int length;
        float angle;
};

class Tank : public Entity{
    public:
        Tank(Map& mapref, std::string name, int hp, int armor, float posX, float posY, bool direction,
                float posCoefficient = 1);
        void setHp(int newHp);
        int getHp() const;
        void setArmor(int newArmor);
        int getArmor() const;
        void setPos(float newPosX, float newPosY);
        float getX();
        float getY();

        std::string& getName();

        bool getGrounded() const;
        void setGrounded(bool flag);

        // TODO: these two should have better integration with Map, to reflect
        // hills etc.
        void moveLeft();
        void moveRight();

        // TODO: consider improving the way the dmg is calculated
        // maybe not flat, but % of inteded dmg?
        void hit(int damage);

        void shoot();

        void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

        void update();
        float getHight();

        void setAmmoSlot(unsigned int slot);
        unsigned getAmmoSlot();
        float getAmoVelo();
        float amovelo = 5;
        Gun mainGun;
        int points{0};

    private:
        int hp;
        int armor;
        // false is left, true is right
        bool direction;
        bool grounded = false; // ignore gravity
        unsigned ammoSlot = 1;

        int maxHp; // the value passed to constructor
        int maxArmor;

        std::string name;


        // value by which each position change is to be multiplied
        // TODO: this value could be passed in the constructor and be used as a
        // modifier for different terrains (e.g. higher (= more movement in one
        // iteration) in grasslands, lower in deserts)
        /* static constexpr float posCoefficient = 1; */
        // NOTE: this should be included only in Map, without Tank knowing
        // anything about how it moves

        sf::CircleShape shape;
        sf::Sprite sprite;
        sf::Texture texture;
};
