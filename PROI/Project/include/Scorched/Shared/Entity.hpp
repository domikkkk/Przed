#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class Map; // forward declaration of map solves dependency issue

// defines general object that has a position and circle collision
class Entity : public sf::Drawable
{
public:
	/// <summary>
	/// Creates an entity with position, velocity and velocity angle
	/// </summary>
	/// <param name="pos">vec2f pos</param>
	/// <param name="vel">velocity magnitude</param>
	/// <param name="angle">direction of velocity</param>
	Entity(Map& mapref, sf::Vector2f pos, float vel, float angle) : position(pos), map(mapref)
	{
		this->velocity.x = vel * std::cos(angle);
		this->velocity.y = -vel * std::sin(angle);
		this->position.x = pos.x;
		this->position.y = pos.y;
	};
	Entity(Map& mapref, sf::Vector2f pos, sf::Vector2f vel) : position(pos), velocity(vel), map(mapref) {};

	virtual void update() //by default, simply moves the entity by velocity
	{
		position += velocity;
	}
	virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const = 0; // only final object knows how to do this

	sf::Vector2f position;
	sf::Vector2f velocity;
	float get_collision_radius() const
	{
		return colRadius;
	}

	/// <summary>
	/// returns whether the object is supposed to be deleted as soon as possible
	/// </summary>
	/// <returns></returns>
	bool getKillStatus() const
	{
		return kill;
	}

	// only allowed to set the flag, but not clear
	void setKillStatus()
	{
		kill = true;
	}

protected:
	float colRadius = 20;
	bool kill=false; // status flag, object delegated to be destroyed
	Map& map;
};