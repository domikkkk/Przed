#include <SFML/Graphics.hpp>
#include <utility>
#include "Triangulate.hpp"
#pragma once

// @TODO make more terrain types with different behaviours (slippery? bombs bounce off a bit?)
class Terrain : public sf::Drawable
{
public:

	explicit Terrain(unsigned terrain_size, unsigned density=10)
	{
        this->size=terrain_size;
		raw_vertices = GenerateRandom(terrain_size, density);
		update_geo();
	}
    unsigned size;
	//initialise raw_vertices (copy them)
	explicit Terrain(Vector2dVector input) : raw_vertices(std::move(input))
	{
		update_geo(); //construct the whole thing at init
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override; //SFML draw function
	void MakeHole(float x, float y, float r);
	void MakeHole(sf::Vector2f pos, float r); // overload

	
	std::pair<float, float> FloorHeight(sf::Vector2f pos, bool allowCeiling = false); // returns floor height at given x coordinate, so tank can sit there
	std::pair<float, float> FloorHeight(float x, float y, bool allowCeiling = false)
	{
		return FloorHeight(sf::Vector2f(x, y), allowCeiling);
	}
	
	static Vector2dVector GenerateRandom(unsigned terrain_size,unsigned density);

	//Vector2dVector GenerateDebug();

	sf::Texture texture;

private:
	float textureScale = 3; //@TODO think about how to make this useful

	Vector2dVector raw_vertices; // vector describing terrain as one giant plygon, used for physics and stuff
	std::vector<sf::ConvexShape> tris; // vector of triangles, only for rendering
	void update_geo();
};
