#pragma once

#ifndef ENEMY_H
#define ENEMY_H

#include "../GameObject.h"
#include "../Renderer/OpenGL/Light.h"

/**
 * @class Enemy
 * @brief Class representing an enemy object in the game.
 */
class Enemy : public GameObject
{
public:
	/**
	 * @brief Constructor for Enemy.
	 */
	Enemy();

	/**
	 * @brief Function called on every update to update the Enemy object.
	 * @param ts The time since the last update.
	 */
	void onUpdate(Timestep ts) override;

	/**
	 * @brief Applies damage to the Enemy object.
	 * @param damagept The amount of damage to apply.
	 */
	void damage(float damagept);

	/**
	 * @brief Draws the Enemy object using the specified shader and camera.
	 * @param shader The shader used for rendering.
	 * @param camera The camera used for rendering.
	 */
	void draw(Shader& shader, Camera& camera);

	/**
	 * @brief Calculates the distance from the Enemy object to a given point.
	 * @param point The point to calculate the distance to.
	 * @return The distance between the Enemy object and the point.
	 */
	float distanceTo(glm::vec3 point);

	/**
	 * @brief Moves the Enemy object.
	 * @param ts The time since the last update.
	 */
	void moveEnemy(Timestep ts);

	/**
	* @brief Adds a light to the Enemy object.
	* @param light Pointer to the light to add.
	* @param yPos The y-coordinate position of the light.
	*/
	void addLight(Light* light, float yPos);

	/**
	 * @brief Checks if the Enemy object is killed.
	 * @return value of killed variable which represents whether enemy was killed or not.
	 */
	inline bool isKilled() { return killed; }

private:
	int hp; /**< The health points of the Enemy object. */
	bool killed; /**< Flag indicating if the Enemy object is killed. */
	float speed = 2; /**< The speed of the Enemy object. */
	std::vector<Light*> enemyLights; /**< Vector containing lights associated with the Enemy object. */
	glm::vec3 campos; /**< The position of the camera.*/
	glm::vec3 direction = { 1.0, 0.0, 0.0 }; /**< The direction in which the Enemy object is moving. */
	float hitTimer = 0.0; /**< Timer for hit effects. */

	/**
	 * @brief Rotates the Enemy object.
	 * @param yAngle The angle (in degrees) to rotate the Enemy object around the y-axis.
	 */
	void rotateEnemy(float yAngle);

	/**
	 * @brief Updates the lights associated with the Enemy object.
	 */
	void updateLights();
};

#endif // !ENEMY_H
