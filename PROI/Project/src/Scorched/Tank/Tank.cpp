#include "Scorched/Tank/Tank.hpp"
#include "Scorched/Map/Map.hpp"
#include "Scorched/Bullet/Bullet.hpp"
#include "TankConstants.hpp"
#include <cmrc/cmrc.hpp>
#include <cmath>
#include <stdexcept>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif

#ifndef M_PI
#define M_PI 3.14159
#endif

CMRC_DECLARE(Resources);

Gun::Gun(float angle){
    this->setAngle(angle);
    this->length = defaultGunLength;
};

void Gun::setAngle(float newAngle){
    if (newAngle < 0)
        throw std::invalid_argument("Angle must be >= 0");
    if (newAngle > M_PI)
        throw std::invalid_argument("Angle must be <= PI");

    this->angle = newAngle;
};

float Gun::getAngle() const{
    return this->angle;
}



Tank::Tank(Map& mapref, std::string name, int hp, int armor, float posX, float posY, bool direction,
    float posCoefficient) : Entity(mapref, {posX, posY},{0,0}), shape(radius), maxHp(hp), maxArmor(armor), name(name) {
    this->setHp(hp);
    this->setArmor(armor);
    this->setPos(posX, posY);
    this->direction = direction;
    this->mainGun = Gun(defaultAngle);

    // temporary circle
    this->shape.setPosition({posX, posY});
    this->shape.setFillColor(sf::Color::Magenta);
    this->shape.setOrigin(shape.getRadius(), shape.getRadius()*2);
    auto fs = cmrc::Resources::get_filesystem();
    auto file = fs.open(tankTexture);
    /* if (!texture.loadFromFile(tankTexture)) */
    if (!texture.loadFromMemory(file.begin(), std::size(file)))
    {
        throw std::runtime_error("Tank texture not found\n");
    }
    sprite.setTexture(texture);
    sprite.setScale(2, 2);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y);
};

void Tank::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    sf::RectangleShape gun{ {defaultGunLength,5} };
    gun.setFillColor(sf::Color::White);
    gun.setPosition(position);
    gun.move(0, -radius);
    gun.setRotation(mainGun.getAngle() * -180 / M_PI);
    target.draw(gun);
    //target.draw(this->shape);

    // draw health bar - two rectangles, one red one green
    sf::RectangleShape redBar{ {(maxHp / 2.f), 5} };
    sf::RectangleShape greenBar{ {(hp / 2.f), 5} };
    redBar.setFillColor(sf::Color::Red);
    greenBar.setFillColor(sf::Color::Green);
    redBar.setPosition(position.x-texture.getSize().x, position.y - 40);
    greenBar.setPosition(position.x - texture.getSize().x, position.y - 40);
    target.draw(redBar);
    target.draw(greenBar);
    target.draw(sprite);
}

void Tank::update()
{
    if (!grounded)
        velocity.y += map.gravity;
    // check if next position would be inside floor
    float height = this->getHight();
    if (!grounded && height == -10000)
    {
        // we can't move here, drop to ground (+ gravity) and set grounded to true
        position.x += velocity.x;
        position.y-=velocity.y+5;
        position.y =  getHight() - map.gravity;
        grounded = true;
        velocity = { 0,0 };
    }
    else
    {
        position += velocity;
    }
    //shape.setPosition(position);
    sprite.setPosition(position);

}

float Tank::getHight() {
    sf::Vector2f offset = { this->texture.getSize().x/2.f,0 }; // check 3 points on both ends of texture and in the middle
    auto p1 = position + offset;
    auto p2 = position - offset;
    auto p3 = position;
    return std::min({map.terrain->FloorHeight(p3).first, map.terrain->FloorHeight(p1).first, map.terrain->FloorHeight(p2).first});
}

void Tank::setHp(int newHP){
    if (newHP <= 0)
        throw std::invalid_argument("Health must be > 0");

    this->hp = newHP;
};

int Tank::getHp() const {
    return this->hp;
};

void Tank::setArmor(int newArmor){
    if (newArmor < 0)
        throw std::invalid_argument("Armor must be >= 0");

    this->armor = newArmor;
};

int Tank::getArmor() const{
    return this->armor;
};

void Tank::setPos(float newPosX, float newPosY){
    if (newPosX < 0)
        throw std::invalid_argument("Position in X axis must be >= 0");
    if (newPosY < 0)
        throw std::invalid_argument("Position in Y axis must be >= 0");

    position = { newPosX, newPosY };
};

float Tank::getX(){
    return position.x;
};

float Tank::getY(){
    return position.y;
};

std::string& Tank::getName()
{
    return name;
}

void Tank::moveLeft(){
    sf::Vector2f prev{this->position};
    this->position.x -= 0.25f;
    this->position.y -= 5;
    float height = this->getHight();
    if(height == -10000)
        this->position = prev;
    else
        this->position.y = height;
};

void Tank::moveRight(){
    sf::Vector2f prev{this->position};
    this->position.x += 0.25f;
    this->position.y -= 5;
    float height = this->getHight();
    if(height == -10000)
        this->position = prev;
    else
        this->position.y = height;
};

void Tank::hit(int damage){
    this->hp -= std::max(0, damage - this->armor);
};

void Tank::setAmmoSlot(unsigned int slot)
{
    this->ammoSlot = slot;
}

unsigned Tank::getAmmoSlot()
{
    return this->ammoSlot;
}

float Tank::getAmoVelo() {
    return this->amovelo;
}

bool Tank::getGrounded() const
{
    return grounded;
}

void Tank::setGrounded(bool flag)
{
    grounded = flag;
}


void Tank::shoot() {
    float angle = this->mainGun.getAngle();
    bool direction = this->direction;
    // tank's posiion + gun's
    // direction should be taken into account
    // TODO: check how Bullet treats angle (where is 0? are there negative
    // angles?)
    float bulletX = this->getX() +
                    defaultGunLength * std::cos(angle);
    float bulletY = this->getY() - radius -
                    defaultGunLength * std::sin(angle);
    // at this point bullet should be spawned on the map with values taken from
    // this method
    // TODO: set this value in a different header or via user interface

    //@TODO: enumify
    switch (ammoSlot) {
        case 1:
            map.add(new NormalBullet(map, bulletX, bulletY, this->amovelo, angle));
            break;
        case 2:
            map.add(new HugeBullet(map, bulletX, bulletY, this->amovelo, angle));
            break;
        case 3:
            map.add(new BounceBullet(map, bulletX, bulletY, this->amovelo, angle));
            break;
        case 4:
            map.add(new ClusterBullet(map, bulletX, bulletY, this->amovelo, angle));
            break;
        case 5:
            map.add(new Missile(map, bulletX, bulletY, this->amovelo, angle));
            break;
    }
}
