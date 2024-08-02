#ifndef MOUSE_EVENT_CLASS_H
#define MOUSE_EVENT_CLASS_H

#include "Event.h"

/**
 * @class MouseMovedEvent
 *
 * @brief Event triggered when the mouse is moved.
 */
class MouseMovedEvent : public Event
{
public:
	/**
	 * @brief Constructs a MouseMovedEvent object with the specified coordinates.
	 *
	 * @param x The x-coordinate of the mouse position.
	 * @param y The y-coordinate of the mouse position.
	 */
	MouseMovedEvent(float x, float y) : mouseX(x), mouseY(y) {};

	/**
	 * @brief Gets the x-coordinate of the mouse position.
	 *
	 * @return The x-coordinate.
	 */
	inline float getX() const { return mouseX; }

	/**
	 * @brief Gets the y-coordinate of the mouse position.
	 *
	 * @return The y-coordinate.
	 */
	inline float getY() const { return mouseY; }

	/**
	 * @brief Converts the MouseMovedEvent to a string representation.
	 *
	 * @return The MouseMovedEvent as a string.
	 */
	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << mouseX << ", " << mouseY;
		return ss.str();
	}

	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse) /**< Creates the methods conected to the category of the event: Mouse and Input. */
	EVENT_CLASS_TYPE(MouseMoved) /**< Creates the methods conected to the type of the event: MouseMoved. */

private:
	float mouseX; /**< The x-coordinate of the mouse position. */
	float mouseY; /**< The y-coordinate of the mouse position. */
};

/**
 * @class MouseScrolledEvent
 *
 * @brief Event triggered when the mouse wheel is scrolled.
 */
class MouseScrolledEvent : public Event
{
public:
	/**
	 * @brief Constructs a MouseScrolledEvent object with the specified scroll offsets.
	 *
	 * @param offsetX The horizontal scroll offset.
	 * @param offsetY The vertical scroll offset.
	 */
	MouseScrolledEvent(float offsetX, float offsetY) : offsetX(offsetX), offsetY(offsetY) {}
	
	/**
	 * @brief Gets the horizontal scroll offset.
	 *
	 * @return The horizontal scroll offset.
	 */
	inline float getXOffset() const { return offsetX; }

	/**
	 * @brief Gets the vertical scroll offset.
	 *
	 * @return The vertical scroll offset.
	 */
	inline float getYOffset() const { return offsetY; }

	/**
	 * @brief Converts the MouseScrolledEvent to a string representation.
	 *
	 * @return The MouseScrolledEvent as a string.
	 */
	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << offsetX << ", " << offsetY;
		return ss.str();
	}

	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse) /**< Creates the methods conected to the category of the event: Mouse and Input. */
	EVENT_CLASS_TYPE(MouseScrolled) /**< Creates the methods conected to the type of the event: MouseScrolled. */

private:
	float offsetX; /**< The horizontal scroll offset. */
	float offsetY; /**< The vertical scroll offset. */
};

/**
 * @class MouseButtonEvent
 *
 * @brief Base class for mouse button events.
 */
class MouseButtonEvent : public Event
{
public:
	/**
	 * @brief Gets the mouse button associated with the event.
	 *
	 * @return The mouse button.
	 */
	inline int getMouseButton() const { return button; }

	EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse) /**< Creates the methods conected to the category of the event: Mouse and Input. */

protected:
	/**
	 * @brief Constructs a MouseButtonEvent object with the specified mouse button.
	 *
	 * @param button The mouse button associated with the event.
	 */
	MouseButtonEvent(int button) : button(button) {}

	int button; /**< The mouse button associated with the event. */
};

/**
 * @class MouseButtonPressedEvent
 *
 * @brief Event triggered when a mouse button is pressed.
 */
class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	/**
	 * @brief Constructs a MouseButtonPressedEvent object with the specified mouse button.
	 *
	 * @param button The mouse button associated with the event.
	 */
	MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

	/**
	 * @brief Converts the MouseButtonPressedEvent to a string representation.
	 *
	 * @return The MouseButtonPressedEvent as a string.
	 */
	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonPresed) /**< Creates the methods conected to the type of the event: MouseButtonPresed. */
};

/**
 * @class MouseButtonReleasedEvent
 *
 * @brief Event triggered when a mouse button is released.
 */
class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	/**
	 * @brief Constructs a MouseButtonReleasedEvent object with the specified mouse button.
	 *
	 * @param button The mouse button associated with the event.
	 */
	MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

	/**
	 * @brief Converts the MouseButtonReleasedEvent to a string representation.
	 *
	 * @return The MouseButtonReleasedEvent as a string.
	 */
	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased) /**< Creates the methods conected to the type of the event: MouseButtonReleased. */
};

#endif // !MOUSE_EVENT_CLASS_H
