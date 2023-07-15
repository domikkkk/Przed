Project Structure:

```
Scorched
|----CMakeLists.txt (Project build system, links libs like SFML and GTest)
|----cmake (Additional CMake scripts)
|----include (Files, which could be used outside of this project. Separated for better encapsulation)
|    |----Scorched
|         |----Bullet (Bullet types)
|         |----GameController (Game state management)
|         |----Map (Manages all entities and their collisions)
|         |----Shared (Classes shared among objects for better inheritance)
|         |----Tank (Tank class, which is controlled by the player)
|         |----Terrain (Terrain representation and interaction with it)
|
|
|----src (Internal game files)
|    |----Main.cpp (Application entry point)
|    |----Resources (Resources used by the game, linked at compile time)
|    |----Scorched
|         |----Bullet
|         |----GameController
|         |----Map
|         |----Shared
|         |----Tank
|         |----Terrain
|
|----test (Unit tests)
```

Run the game with **Scorched.out** and tests with **tests.out**.


Authors:
1. Dominik Sidorczuk:
- Bullets
- Tank movement
- Math and physics for bullets
- Collisons of bullets and terrain

2. Tomasz Sroka
- Terrain
- Math for Terrain
- Collisions with terrain and tank
- Game logic
- CMake relations
- Textures for objects

3. Krzysztof Stawarski
- Project structure
- Tank
- Linking of resources with the binary
- Unit tests
- Some CMake files
- This README
