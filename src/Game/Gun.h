#pragma once
#ifndef GUN_H
#define GUN_H

#include "../GameObject.h"

/**
 * @class Gun
 * @brief Class representing a gun object in the game.
 */
class Gun : public GameObject
{
public:
	/**
	 * @brief Constructor for Gun.
	 */
	Gun();	

	/**
	 * @brief Function called on every update to update the Gun object.
	 * @param timestep The time since the last update.
	 */
	virtual void onUpdate(Timestep timestep) override;

	/**
	 * @brief Handles the key input for looking through the camera.
	 * @param seconds The time since the last update.
	 * @return True if the camera view was adjusted, false otherwise.
	 */
	bool lookCameraKey(float seconds);

	/**
	 * @brief Draws the Gun object using the specified shader and camera.
	 * @param shader The shader used for rendering.
	 * @param camera The camera used for rendering.
	 */
	void draw(Shader& shader, Camera& camera) override;

	// TODO: DECIDE IF TO BE DELETED
	/**
	 * @brief Rotates the camera.
	 * @param ts The time since the last update.
	 */
	void rotateCamera(Timestep ts);

private:
	Camera* camerap = nullptr; /**< Pointer to the camera. */

	// TODO: DECIDE IF TO BE DELETED
	glm::vec3 direction = { 1.0, 0.0, 0.0 }; /**< The direction in which the gun is pointing. */
};

#endif // !GUN_H
