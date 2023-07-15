//
// Created by domik on 29.04.2022.
//
#include <cmrc/cmrc.hpp>
#include "Scorched/Bullet/Bullet.hpp"
#include "Scorched/Shared/Entity.hpp"
#include "Scorched/Map/Map.hpp"
#include <cmath>
#include <string>
#include <iostream>

CMRC_DECLARE(Resources);

#ifndef M_PI
#define M_PI 3.14159
#endif

constexpr int framesOfImmunity = 2;


// logical base class, not supposed to be used in a map, has no texture
Bullet::Bullet(Map& mapref, float x, float y, float velocity, float angle) : Entity(mapref, { x,y }, velocity, angle) {
    this->bullet_radius = 3.0f;
    bullet.setRadius(this->bullet_radius);
    bullet.setOrigin(this->bullet_radius, this->bullet_radius);
    bullet.setFillColor(sf::Color::Yellow);
    set_gravitation(0.05f);
    //LoadTexture(bulletTexture); // do this in derived class
    //sprite.setScale(3, 3);
}

/// <summary>
/// Loads texture from filename, assigns it to this->sprite, then sets oriting to center
/// </summary>
/// <param name="filename">path or relative path from executable to texture</param>
void Bullet::LoadTexture(const char* filename)
{
    auto fs = cmrc::Resources::get_filesystem();
    auto file = fs.open(filename);
    if (!texture.loadFromMemory(file.begin(), std::size(file)))
    {
        throw std::runtime_error(std::string("Bullet texture not found: ")+filename+"\n");
    }
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    //target.draw(this->bullet, state);
    target.draw(sprite, state);
}

void Bullet::update() {
    if (immuneCounter != 0) --immuneCounter;
    this->velocity.y += map.gravity;
    this->position += velocity;
    //bullet.setPosition(this->position); //updates the visual circle
    sprite.setPosition(this->position);
    auto angleRads = std::atan2(-velocity.y, -velocity.x);
    auto angleDegs = angleRads * 180.0 / M_PI;
    sprite.setRotation(angleDegs);
}

void Bullet::set_collide_to_true() {
    this->collide = true;
}

float Bullet::bottom() {
    return this->bullet.getPosition().y + bullet.getRadius();
}

bool Bullet::if_hit() const {
    return collide;
}

void Bullet::set_color(sf::Color new_color) {
    bullet.setFillColor(new_color);
}

void Bullet::set_radius(float new_radius) {
    this->bullet_radius = new_radius;
    this->bullet.setRadius(new_radius); //update the visual radius
}

float Bullet::get_radius() {
    return this->bullet_radius;
}

void Bullet::set_gravitation(float new_gravitation) {
    this->gravitation = new_gravitation;
}

void Bullet::set_damage(float new_damage) {
    this->damage = new_damage;
}

void Bullet::set_range(float new_range) {
    this->range = new_range;
}

void Bullet::set_velocity(float new_x, float new_y) {
    this->velocity.x = new_x;
    this->velocity.y = new_y;
}

sf::Vector2f Bullet::get_position() {
    return bullet.getPosition();
}

float Bullet::get_range() {
    return this->range;
}

float Bullet::get_damage()
{
    return this->damage;
}

NormalBullet::NormalBullet(Map& mapref, float x, float y, float velocity, float angle) :
    Bullet(mapref, x, y, velocity, angle)
{
    this->set_range(20.0f);
    this->set_damage(20.0f);
    LoadTexture(bulletTexture);
    sprite.setScale(3,3);
}


HugeBullet::HugeBullet(Map& mapref, float x, float y, float velocity, float angle) :
Bullet(mapref, x, y, velocity, angle) {
    this->set_color(sf::Color::Red);
    this->set_radius(8.0f);
    this->set_gravitation(0.02f);
    this->set_damage(50.0f);
    this->set_range(40.0f);
    LoadTexture(hugeBulletTexture);
    sprite.setScale(4, 4);
}




BounceBullet::BounceBullet(Map& mapref, float x, float y, float velocity, float angle) :
Bullet(mapref, x, y, velocity, angle){
    this->set_radius(5.0f);
    this->set_color(sf::Color::Blue);
    this->set_damage(10.0f);
    this->set_range(20.0f);
    this->bounce = true;
    LoadTexture(bounceBulletTexture);
    sprite.setScale(4, 4);
}

void BounceBullet::set_collide_to_true() {
    if (immuneCounter == 0) {
        this->collide = true;
        if (bounce) {
            auto floorInfo = map.terrain->FloorHeight(position - velocity);
            float alpha = floorInfo.second;
            if (floorInfo.first-position.y>10)
            {
                //std::cout << "ceiling\n";
                floorInfo = map.terrain->FloorHeight(position, true);
                alpha = floorInfo.second;
            }
            //else std::cout << "floor" << alpha << '\n';
            alpha = M_PI + 2 * (std::atan(velocity.x / velocity.y) - alpha);
            immuneCounter = framesOfImmunity;
            bounce = false;
            this->collide = false;
            position.y -= velocity.y * 0.2; // prevent
            float x{ velocity.x * std::cos(alpha) - velocity.y * std::sin(alpha) };
            float y{ velocity.x * std::sin(alpha) + velocity.y * std::cos(alpha) };
            velocity = { x, 0.9f * y };
        }
        else {
            this->velocity.x = 0;
            this->velocity.y = 0;
        }
    }
}



ClusterBullet::ClusterBullet(Map& mapref, float x, float y, float velocity, float angle) :
Bullet(mapref, x, y, velocity, angle) {
    this->set_radius(5.0f);
    this->set_color(sf::Color::Green);
    this->set_damage(50.0f);
    this->set_range(20.0f);

    LoadTexture(clusterTexture);
    sprite.setScale(4, 4);
}

void ClusterBullet::set_collide_to_true() {
    this->collide = true;
    if(this->collide){
        float angle = map.terrain->FloorHeight(position-velocity).second;
        map.add(new NormalBullet(map, this->position.x, this->position.y, 3.0f, M_PI / 2 + angle));
        map.add(new NormalBullet(map, this->position.x, this->position.y, 3.0f, 2 * M_PI / 3 + angle));
        map.add(new NormalBullet(map, this->position.x, this->position.y, 3.0f, 1 * M_PI / 3 + angle));
        this->velocity.x = 0;
        this->velocity.y = 0;
    }
}

Missile::Missile(Map &mapref, float x, float y, float velocity, float angle) :
Bullet(mapref, x, y, velocity, angle)
{
    this->set_radius(5.0f);
    this->set_color(sf::Color::Cyan);
    this->set_damage(15.0f);
    this->set_range(20.0f);

    LoadTexture(clusterTexture);
    sprite.setScale(4, 4);
}

void Missile::update() {
    if(std::abs(this->velocity.y) < this->gravitation){
        float angle{0.f};
        float v{1.0f};
        float vx{this->velocity.x};
        if(this->velocity.x < 0) {
            angle = M_PI;
            v = -v;
            vx = -vx;
        }
        map.add(new NormalBullet(map, this->position.x, this->position.y, vx, angle));
        map.add(new NormalBullet(map, this->position.x, this->position.y, vx + v, angle + M_PI / 12));
        map.add(new NormalBullet(map, this->position.x, this->position.y, vx - v,  angle - M_PI / 12));
        this->set_collide_to_true();
    }
    Bullet::update();
}
