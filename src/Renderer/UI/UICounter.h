#pragma once

#ifndef UI_COUNTER_H
#define UI_COUNTER_H

#include "UIElement.h"
#include "UINumber.h"

/**
 * @class UICounter
 * @brief Class representing a UI counter element.
 */
class UICounter : public UIElement
{
public:
	/**
	 * @brief Constructor for UICounter.
	 * @param width The width of the counter.
	 * @param height The height of the counter.
	 * @param size The size of the counter elements (number of digits).
	 */
	UICounter(float width, float height, int size);

	/**
	 * @brief Sets the value of the counter.
	 * @param tvalue The value to set.
	 */
	void setValue(int tvalue);

	/**
	 * @brief Draws the counter using the specified shader and camera.
	 * @param shader The shader to use for rendering.
	 * @param camera The camera to use for rendering.
	 */
	void draw(Shader& shader, Camera& camera) override;

protected:
	std::vector<UINumber> fields; ///< The individual number fields of the counter.
	float height; ///< The height of the counter.
	float width; ///< The width of the counter.
	int value; ///< The current value of the counter.

	/**
	 * @brief Sets up the individual elements of the counter.
	 */
	void setElements();

};

#endif // !UI_COUNTER_H
