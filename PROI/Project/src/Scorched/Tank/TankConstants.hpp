#ifndef TANK_CONSTANTS_HPP
#define TANK_CONSTANTS_HPP
// value by which each angle change is to be multiplied
static constexpr double angleCoefficient = 1.5;

// default angle of the tank's gun
static constexpr double defaultAngle = 0.0;
// default length of the tank's gun
static constexpr int defaultGunLength = 25;

static constexpr float radius = 25; //@Todo: place this somewhere;

static const char* tankTexture = "src/Resources/tank2.png";
#endif
