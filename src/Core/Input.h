#pragma once
#ifndef INPUT_CLASS_H
#define INPUT_CLASS_H

/**
 * @class Input
 *
 * @brief A static class that provides input-related functionality.
 */
class Input
{
public:
	/**
	 * @brief Checks if a keyboard key is currently pressed.
	 *
	 * @param keyCode The code of the keyboard key.
	 * @return true if the key is pressed, false otherwise.
	 */
	static bool isKeyPressed(int keyCode);

	/**
	 * @brief Checks if a mouse button is currently pressed.
	 *
	 * @param button The code of the mouse button.
	 * @return true if the button is pressed, false otherwise.
	 */
	static bool isMouseButtonPressed(int button);

	/**
	 * @brief Gets the current X position of the mouse cursor.
	 *
	 * @return The X position of the mouse cursor.
	 */
	static float getMouseX();

	/**
	 * @brief Gets the current Y position of the mouse cursor.
	 *
	 * @return The Y position of the mouse cursor.
	 */
	static float getMouseY();
};

#endif // !INPUT_CLASS_H
