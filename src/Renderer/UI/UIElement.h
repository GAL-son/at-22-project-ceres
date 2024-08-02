#pragma once
#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include "../OpenGL/Mesh.h"

/**
 * @class UIElement
 * @brief Base class for UI elements.
 */
class UIElement
{
public:
	/**
	 * @brief Default constructor for UIElement.
	 */
	UIElement() {};

	/**
	 * @brief Constructor for UIElement.
	 * @param width The width of the UI element.
	 * @param height The height of the UI element.
	 */
	UIElement(float width, float height);

	/**
	 * @brief Draws the UI element using the specified shader and camera.
	 * @param shader The shader to use for rendering.
	 * @param camera The camera to use for rendering.
	 */
	virtual void draw(Shader& shader, Camera& camera);

	/**
	 * @brief Updates the UI element.
	 * @param ts The timestep since the last update.
	 */
	virtual void onUpdate(Timestep ts) {};

	/**
	 * @brief Sets the position of the UI element.
	 * @param x The x-coordinate of the position.
	 * @param y The y-coordinate of the position.
	 */
	inline void setPosition(float x, float y) { this->position = { x,y }; }

	/**
	 * @brief Sets the texture of the UI element.
	 * @param path The file path of the texture.
	 */
	void setTexture(const char* path);

	/**
	 * @brief Sets the visibility of the UI element.
	 * @param value The visibility value (true or false).
	 */
	void inline setVisible(bool value) { this->visible = value; }

protected:
	Mesh* surface; ///< The mesh of the UI element.
	glm::vec2 position; ///< The position of the UI element.
	bool visible = true; ///< The visibility of the UI element.
};

#endif // !UI_ELEMENT_H
