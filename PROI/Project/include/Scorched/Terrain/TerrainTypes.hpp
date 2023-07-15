#pragma once

#include "../src/Scorched/Terrain/Terrain.hpp"
#include "Scorched/Shared/Entity.hpp"
#include <cmrc/cmrc.hpp>
#include <SFML/Graphics.hpp>
#include <stdexcept>
/* #define SAND_TEXTURE_NAME "../src/Resources/sand.jpg" */
#define SAND_TEXTURE_NAME "src/Resources/sand.jpg"
/* #define SAND_TEXTURE_NAME "sand.jpg" */

CMRC_DECLARE(Resources);

// uses texture member from super class
class SandTerrain : public Terrain
{

public:
	SandTerrain(unsigned size, unsigned density=10) : Terrain(size, density)
	{
		LoadTexture();
	}

	SandTerrain(Vector2dVector v) : Terrain(v) //pass vectices to super constructor
	{
		LoadTexture();
	}

	void Interact(Entity& obj)
	{
		// when physics calculations decided that a bullet collided, handle interaction here
		// MakeHole()? Bounce away? Gets stuck in sand? rm -rf?
	}

private:
	void LoadTexture()
	{
		/* if (!texture.loadFromFile(SAND_TEXTURE_NAME)) */
        auto fs = cmrc::Resources::get_filesystem();
        auto file = fs.open(SAND_TEXTURE_NAME);
		if (!texture.loadFromMemory(file.begin(), std::size(file)))
			throw std::runtime_error("Texture not found\n"); //@TODO this isn't caught anywhere and segfaults?

		texture.setRepeated(true);
	}
	//here we can place some properties like bounce amount, drag force
};
