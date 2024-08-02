#pragma once

#ifndef AMMO_H
#define AMMO_H

#include "../GameObject.h"

/**
 * @class Ammo
 * @brief Class representing an ammunition object in the game.
 */
class Ammo : public GameObject
{
public:
	/**
	 * @brief Default constructor for Ammo.
	 */
	Ammo();	

	/**
	 * @brief Function called on every update to update the Ammo object.
	 * @param timestep The time since the last update.
	 */
	void onUpdate(Timestep timestep) override;

	/**
	 * @brief Gets the distance of the Ammo object from the camera.
	 * @return The distance from the camera.
	 */
	float getDistanceFromCamera();

	/**
	 * @brief Function called to draw the Ammo object using a shader and camera.
	 * @param shader The shader used for rendering.
	 * @param camera The camera used for rendering.
	 */
	void draw(Shader& shader, Camera& camera) override;

private:
	glm::vec3 campos; /**< The camera position. */
};

#endif // !AMMO_H

