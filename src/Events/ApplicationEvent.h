#ifndef APPLICATION_EVENT_H
#define APPLICATION_EVENT_H

#include "Event.h"

/**
 * @class WindowResizedEvent
 *
 * @brief Event representing a window resize.
 */
class WindowResizedEvent : public Event
{
public:
	/**
	 * @brief Constructs a WindowResizedEvent object.
	 *
	 * @param width The new width of the window.
	 * @param height The new height of the window.
	 */
	WindowResizedEvent(unsigned int width, unsigned int height) : width(width), height(height) {}

	/**
	 * @brief Gets the width of the window.
	 *
	 * @return The width of the window.
	 */
	inline unsigned int getWidth() const { return width; }

	/**
	 * @brief Gets the height of the window.
	 *
	 * @return The height of the window.
	 */
	inline unsigned int getHeight() const { return height; }

	/**
	 * @brief Converts the WindowResizedEvent to a string representation.
	 *
	 * @return The WindowResizedEvent as a string.
	 */
	std::string toString() const override
	{
		std::stringstream ss;
		ss << "WindowResizedEvent: " << width << " ," << height;
		return ss.str();
	}

	EVENT_CLASS_CATEGORY(EventCategoryApplication) /**< Creates the methods conected to the category of the event: Application. */
	EVENT_CLASS_TYPE(WindowResized) /**< Creates the methods conected to the type of the event: WindowResized. */

private:
	unsigned int width; /**< The new width of the window. */
	unsigned int height; /**< The new height of the window. */
};

/**
 * @class WindowCloseEvent
 *
 * @brief Event representing a window close.
 */
class WindowCloseEvent : public Event
{
public:
	/**
	 * @brief Constructs a WindowCloseEvent object.
	 */
	WindowCloseEvent() {}

	EVENT_CLASS_CATEGORY(EventCategoryApplication) /**< Creates the methods conected to the category of the event: Application. */
	EVENT_CLASS_TYPE(WindowClose) /**< Creates the methods conected to the type of the event: WindowClose. */
};

#endif // !APPLIATION_EVENT_H
