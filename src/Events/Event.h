#ifndef EVENT_CLASS_H
#define EVENT_CLASS_H

#include <string>
#include <functional>
#include <sstream>

/**
 * @enum EventType
 *
 * @brief Enumeration representing different types of events.
 */
enum class EventType
{
	None = 0,
	WindowClose, /**< Window close event. */
	WindowResized, /**< Window resize event. */
	WindowFocus, /**< Window focus event. */
	WindowLostFocus, /**< Window lost focus event. */
	WindowMoved, /**< Window move event. */
	KeyPressed, /**< Key press event. */
	KeyReleased, /**< Key release event. */	
	MouseButtonPresed, /**< Mouse button press event. */
	MouseButtonReleased, /**< Mouse button release event. */
	MouseMoved, /**< Mouse move event. */
	MouseScrolled /**< Mouse scroll event. */
};

/**
 * @def BIT(x)
 *
 * @brief Macro creating a bitfield.
 *
 * @param x bit offset
 */
#define BIT(x) (1 << x)

/**
 * @enum EventCategory
 *
 * @brief Enumeration representing different categories of events.
 */
enum EventCategory
{
	None = 0,
	EventCategoryApplication	= BIT(0), /**< Application-related event category. */
	EventCategoryInput			= BIT(1), /**< Input-related event category. */
	EventCategoryKeyboard		= BIT(2), /**< Keyboard-related event category. */
	EventCategoryMouse			= BIT(3), /**< Mouse-related event category. */
	EventCategoryMouseButton	= BIT(4) /**< Mouse button-related event category. */
};

/**
 * @def EVENT_CLASS_TYPE(type)
 *
 * @brief Macro to streamline the implementation of basic methods for event classes.
 *
 * @param type The type of the event.
 */
#define EVENT_CLASS_TYPE(type)  static EventType getStaticType() { return EventType::##type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

/**
* @def EVENT_CLASS_CATEGORY(category)
*
* @brief Macro to specify the category of an event class.
*
* @param category The category of the event.
*/
#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

/**
 * @class Event
 *
 * @brief Base class for events.
 */
class Event
{
	friend class EventDispatcher;

public:
	/**
	 * @brief Gets the type of the event.
	 *
	 * @return The type of the event.
	 */
	virtual EventType getEventType() const = 0;

	/**
	 * @brief Gets the name of the event.
	 *
	 * @return The name of the event.
	 */
	virtual const char* getName() const = 0;

	/**
	 * @brief Gets the category flags of the event.
	 *
	 * @return The category flags of the event.
	 */
	virtual int getCategoryFlags() const = 0;

	/**
	 * @brief Converts the Event to a string representation.
	 *
	 * @return The Event as a string.
	 */
	virtual std::string toString() const { return getName(); }

	/**
	 * @brief Checks if the event belongs to a specific category.
	 *
	 * @param category The category to check against.
	 * @return True if the event belongs to the specified category, false otherwise.
	 */
	inline bool isInCategory(EventCategory& category)
	{
		return getCategoryFlags() & category;
	}

	/**
	 * @brief Checks if the event has been handled.
	 *
	 * @return True if the event has been handled, false otherwise.
	 */
	inline bool isEventHandeled() const { return isHandled; }

protected:
	bool isHandled = false; /**< Flag indicating if the event has been handled. */
};

/**
*@class EventDispatcher
*
* @brief Dispatches events to their corresponding event functions.
*/
class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;

public:	
	/**
	 * @brief Constructs an EventDispatcher object.
	 *
	 * @param event The event to dispatch.
	 */
	EventDispatcher(Event& event) : event(event) {}

	/**
	 * @brief Dispatches the event to the corresponding event function.
	 *
	 * @tparam T The type of event to dispatch.
	 * @param func The event function to dispatch the event to.
	 * @return True if the event was dispatched successfully, false otherwise.
	 */
	template<typename T>
	bool dispatch(EventFn<T> func)
	{
		if (event.getEventType() == T::getStaticType())
		{
			event.isHandled = func(*(T*) &event);
			return true;
		}
		return false;
	}

private:
	Event& event; /**< The event to dispatch. */
};

#endif // !EVENT_CLASS_H
