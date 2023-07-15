//
// Created by domik on 29.04.2022.
//

#ifndef PROJECT_BULLET_H
#define PROJECT_BULLET_H
#pragma once
#include <SFML/Graphics.hpp>
#include "Scorched/Shared/Entity.hpp"
#include "Scorched/Map/Map.hpp"

class Map;

static const char* bulletTexture = "src/Resources/bullet.png";
static const char* clusterTexture = "src/Resources/cluster.png";
static const char* clusterFragmentTexture = "src/Resources/small_cluster.png"; //unused but available
static const char* hugeBulletTexture = "src/Resources/huge.png";
static const char* bounceBulletTexture = "src/Resources/bounce.png";

class Bullet : public Entity{
public:
    Bullet(Map& mapref, float x, float y, float velocity, float angle);
    ~Bullet() override = default;
    float bottom();
    bool if_hit() const;
    virtual void update();
    void set_color(sf::Color new_color);
    void set_radius(float new_radius);
    void set_gravitation(float new_gravitation);
    void set_damage(float new_damage);
    void set_range(float new_range);
    void set_velocity(float new_x, float new_y);
    virtual void set_collide_to_true();
    sf::Vector2f get_position();
    float get_radius();
    float get_range();
    float get_damage();
    bool canCollide()
    {
        return immuneCounter == 0;
    }

protected:
    sf::CircleShape bullet; // visual shape
    sf::Sprite sprite;
    sf::Texture texture;
    float bullet_radius;
    float gravitation{0.05f};
    bool collide{false};
    bool bounce{false};
    float damage{10.0f};
    float range{10.0f};
    unsigned int immuneCounter = 5; // all bullets spawn with 2 frames of no colision
    virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    void LoadTexture(const char* filename);
};

class NormalBullet : public Bullet
{
public:
    NormalBullet(Map& mapref, float x, float y, float velocity, float angle);
};

class HugeBullet :public Bullet{
public:
    HugeBullet(Map& mapref, float x, float y, float velocity, float angle);

protected:
    sf::CircleShape bullet;
};


class BounceBullet :public Bullet{
public:
    BounceBullet(Map& maprec, float x, float y, float velocity, float angle);
    void set_collide_to_true() override;
protected:
    sf::CircleShape bullet;
};


class ClusterBullet :public Bullet{
public:
    ClusterBullet(Map& mapref, float x, float y, float velocity, float angle);
    void set_collide_to_true() override;

protected:
    sf::CircleShape bullet;
};


class Missile :public Bullet{
public:
    Missile(Map& mapref, float x, float y, float velocity, float angle);
    void update() override;
protected:
    sf::CircleShape bullet;
};


#endif //PROJECT_BULLET_H
