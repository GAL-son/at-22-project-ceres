#pragma once

#ifndef MEDPACK_H
#define MEDPACK_H

#include "../GameObject.h"

/**
 * @class Medpack
 * @brief Class representing a medpack object in the game.
 */
class Medpack : public GameObject
{
public:
	/**
	 * @brief Constructor for Medpack.
	 */
	Medpack();

	/**
	 * @brief Function called on every update to update the Medpack object.
	 * @param timestep The time since the last update.
	 */
	void onUpdate(Timestep timestep);

	/**
	 * @brief Get the distance from the Medpack to the camera.
	 * @return The distance from the Medpack to the camera.
	 */
	float getDistanceFromCamera();

	/**
	 * @brief Draw the Medpack object.
	 * @param shader The shader used for rendering.
	 * @param camera The camera used for rendering.
	 */
	void draw(Shader& shader, Camera& camera);

private:
	glm::vec3 campos; /**< The position of the camera. */
};
#endif // !MEDPACK_H

