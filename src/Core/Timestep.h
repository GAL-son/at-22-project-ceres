#pragma once

#ifndef TIMESTEP_H
#define TIMESTEP_H

/**
 * @class Timestep
 *
 * @brief Represents a timestep or duration of time.
 */
class Timestep {
public:
	/**
	 * @brief Constructs a Timestep object.
	 *
	 * @param timeSeconds The duration of time in seconds.
	 */
	Timestep(float timeSeconds = 0.0f) : timeSeconds(timeSeconds) {}

	/**
	 * @brief Gets the duration of time in seconds.
	 *
	 * @return The duration of time in seconds.
	 */
	float getSeconds() const { return timeSeconds; }

	/**
	 * @brief Gets the duration of time in milliseconds.
	 *
	 * @return The duration of time in milliseconds.
	 */
	float getMiliseconds() const { return timeSeconds * 1000.0f; }

	/**
	 * @brief Converts the Timestep to a float value.
	 *
	 * @return The Timestep as a float value.
	 */
	operator float() const { return timeSeconds; }


private:
	float timeSeconds; /**< The duration of time in seconds. */
};

#endif // !TIMESTEP_H
