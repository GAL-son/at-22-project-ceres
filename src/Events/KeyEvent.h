#ifndef KEY_EVENT_CLASS_H
#define KEY_EVENT_CLASS_H

#include "Event.h"

/**
 * @class KeyEvent
 *
 * @brief Base class for key events.
 */
class KeyEvent : public Event
{
public:
	/**
	 * @brief Gets the key code associated with the event.
	 *
	 * @return The key code.
	 */
	inline int getKeyCode() const { return keyCode; }

	EVENT_CLASS_CATEGORY( EventCategoryKeyboard | EventCategoryInput ) /**< Creates the methods conected to the category of the event: Keyboard and Input. */

protected:
	/**
	 * @brief Constructs a KeyEvent object with the specified key code.
	 *
	 * @param keyCode The key code associated with the event.
	 */
	KeyEvent(int keyCode) : keyCode(keyCode) {}
	 
	int keyCode; /**< The key code associated with the event. */
};

/**
 * @class KeyPressedEvent
 *
 * @brief Event triggered when a key is pressed.
 */
class KeyPressedEvent : public KeyEvent
{
public:
	/**
	 * @brief Constructs a KeyPressedEvent object with the specified key code and repeat count.
	 *
	 * @param keyCode The key code associated with the event.
	 * @param repeatCount The number of times the key has been repeated.
	 */
	KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), repeatCount(repeatCount) {}
	
	/**
	 * @brief Gets the number of times the key has been repeated.
	 *
	 * @return The repeat count.
	 */
	inline int getRepeatCount() const { return repeatCount; }

	/**
	 * @brief Converts the KeyPressedEvent to a string representation.
	 *
	 * @return The KeyPressedEvent as a string.
	 */
	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << "repeats)";
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyPressed) /**< Creates the methods conected to the type of the event: KeyPressed. */

private:
	int repeatCount; /**< The number of times the key has been repeated. */
};

/**
 * @class KeyReleasedEvent
 *
 * @brief Event triggered when a key is released.
 */
class KeyReleasedEvent : public KeyEvent
{
public:
	/**
	 * @brief Constructs a KeyReleasedEvent object with the specified key code.
	 *
	 * @param keyCode The key code associated with the event.
	 */
	KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

	/**
	 * @brief Converts the KeyReleasedEvent to a string representation.
	 *
	 * @return The KeyReleasedEvent as a string.
	 */
	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyRleasedEvent: " << keyCode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased) /**< Creates the methods conected to the type of the event: KeyReleased. */
};

#endif // !KEY_EVENT_CLASS_H
