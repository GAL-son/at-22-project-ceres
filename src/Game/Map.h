#pragma once

#ifndef MAP_H
#define MAP_H

#include "../GameObject.h"

/**
 * @class Map
 * @brief Class representing a map object in the game.
 */
class Map : public GameObject
{
public:
	/**
	 * @brief Constructor for Map.
	 * @param path The path to the map file.
	 */
	Map(const char* path);

	/**
	 * @brief Function called on every update to update the Map object.
	 * @param timestep The time since the last update.
	 */
	inline void onUpdate(Timestep timestep) override {}
};

#endif // !MAP_H
