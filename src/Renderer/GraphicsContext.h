#pragma once
#ifndef GRAPHICS_CONTEXT_H
#define GRAPHICS_CONTEXT_H

/**
 * @class GraphicsContext
 * @brief Abstract class representing a graphics context.
 */
class GraphicsContext 
{
public:
	/**
	 * @brief Initializes the graphics context.
	 */
	virtual void init() = 0;

	/**
	 * @brief Swaps the front and back buffers.
	 */
	virtual void swapBuffers() = 0;
};

#endif // !GRAPHICS_CONTEXT_H

