#pragma once

#ifndef UI_NUMBER_H
#define UI_NUMBER_H

#include "UIElement.h"

/**
 * @class UINumber
 * @brief Represents a numerical UI element.
 */
class UINumber : public UIElement {
public:
	/**
	 * @brief Constructor for UINumber.
	 * @param width The width of the UINumber element.
	 * @param height The height of the UINumber element.
	 */
	UINumber(float width, float height);

	/**
	 * @brief Draws the UINumber element using the specified shader and camera.
	 * @param shader The shader to use for rendering.
	 * @param camera The camera to use for rendering.
	 */
	void draw(Shader& shader, Camera& camera) override;

	/**
	 * @brief Sets the value of the UINumber.
	 * @param value The numerical value to set.
	 */
	void setValue(int value);

protected:
	glm::vec2 textureOffset; ///< The texture offset of the UINumber element.
	int value; ///< The numerical value of the UINumber element.
	float offsetStep = 0.195; ///< The offset step for changing the texture.
};

#endif // !UI_NUMBER_H

