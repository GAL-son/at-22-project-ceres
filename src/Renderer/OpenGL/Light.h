#pragma once
#ifndef LIGHT_CLASS_H
#define LIGHT_CLASS_H

#include <glm/glm.hpp>
#include <string>

#include "Shader.h"
#include "../Camera.h"

/**
 * @enum LightType
 *
 * @brief Enumeration representing different types of lights
 */
enum LightType
{
	NONE	= 0, ///< empty light
	DIRECT	= 1, ///< direct light
	POINT	= 2  ///< point light
};

/**
 * @class Light
 *
 * @brief Class representing a light object
 */
class Light
{
public:

	/**
	* @brief Constructs a Light object.
	* 
	* @param type what type of light is constructed (default = NONE)
	* @param position light position (default = [0.0, 0.0, 0.0] // Scene origin)
	* @param color light color - values of RGB from 0.0 to 1.0 (default = [0.0, 0.0, 0.0] // white)
	* @param intensity light intensity (default = 1)
	* @param direction specifies the light direction (only used with DIRECT - no effect on POINT or NONE)
	*/
	Light
	(
		LightType type = NONE,
		glm::vec3 position = glm::vec3(0.0, 0.0, 0.0),
		glm::vec3 color = glm::vec3(1.0, 1.0, 1.0),
		float intensity = 1.0f,
		glm::vec3 direction = glm::vec3(0.0, 1.0, 0.0)
	) : type(type), position(position), color(color), direction(direction), intensity(intensity) {}

	/**
	* @brief sets type of light
	* 
	* @param type specifies type of light to be set
	*/
	inline void setType(LightType type) { this->type = type; }

	/**
	* @brief sets position of the light
	* 
	* @param type specifies position of light to be set
	*/
	inline void setPosition(glm::vec3 position) { this->position = position; }

	/**
	* @brief sets directiom of the light - only affects DIRECT lights
	*
	* @param type specifies direction of light to be set
	*/
	inline void setDirection(glm::vec3 direction) { this->direction = direction; }

	/**
	* @brief sets color of the light
	*
	* @param type specifies color of light to be set
	*/
	inline void setColor(glm::vec3 color) { this->color = color; }

	/**
	* @brief sets intensity of the light
	*
	* @param type intensity color of light to be set
	*/
	inline void setIntensity(float intensity) { this->intensity = intensity; }

	/**
	* @brief gets the position of the light
	*
	* @return position of the light in glm::vec3
	*/
	inline glm::vec3 getPosition() { return position; }

	/**
	* @brief passes light to shader
	* 
	* @param shader specifies a shader that will receive light uniform
	* @param camera specifies a camera that will be used to calcuate reflections
	* @param index specifies index of light in array of lights in shader
	*/
	void passToShader(Shader& shader, Camera& camera, GLuint index);

	/**
	* @brief discards the light
	*/
	inline void discard() { bdiscard = true; intensity = 0.0; };

	/**
	* @brief method for checking if light is discarded
	* 
	* @return value of bdiscarded flag. If light is discarded - true, otherwise false.
	*/
	inline bool isDiscarded() { return bdiscard; }

private:
	LightType type; ///< Light type
	glm::vec3 position; ///< Light position
	glm::vec3 direction; ///< Light direction - Only used with DIRECT light
	glm::vec3 color; ///< Light color 
	float intensity; ///< Light intensity
	bool bdiscard = false; ///< Light discarded flag
};

#endif // !LIGHT_CLASS_H
