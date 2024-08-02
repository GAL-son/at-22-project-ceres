#pragma once

#ifndef BULLET_H
#define BULLET_H

#include "../GameObject.h"
#include "../Renderer/OpenGL/Light.h"

/**
 * @class Bullet
 * @brief Class representing a bullet object in the game.
 */
class Bullet : public GameObject
{
public:
	/**
	 * @brief Constructor for Bullet.
	 * @param light Pointer to the light associated with the bullet.
	 * @param direction The direction in which the bullet is moving.
	 */
	Bullet(Light* light, glm::vec3 direction);

	/**
	 * @brief Function called on every update to update the Bullet object.
	 * @param ts The time since the last update.
	 */
	void onUpdate(Timestep ts) override;

	/**
	 * @brief Disables the Bullet object.
	 */
	void disable();

private:
	Light* light; /**< Pointer to the light associated with the bullet. */
	float speed = 250.0; /**< The speed of the bullet. */
	glm::vec3 direction; /**< The direction in which the bullet is moving. */
};

#endif // !BULLET_H
