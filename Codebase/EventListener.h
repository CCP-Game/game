#pragma once

#include <windows.h>
#include <iostream>
#include <functional>

/**
 * @brief The EventListener class handles event listening and provides functionality to capture
 * keyboard events.
 */
class EventListener
{
public:
    /**
     * @brief Starts the main event loop. This function handles dispatching windows messages
     * and breaks the loop when a key press is detected.
     */
    static void MainLoop();

    /**
    * @brief Hook procedure to capture windows key presses. It stores the pressed key 
    * and stops further processing if needed.
    */
    static LRESULT CALLBACK CaptureKeyboardEvent(int nCode, WPARAM wParam, LPARAM lParam);

    /**
     * @brief Returns the last key that was pressed and resets the key value after retrieval.
     * 
     * @return The virtual-key code of the pressed key.
     */
    static int getPressedKey();

private:
    /**
     * @brief Stores the virtual-key code of the last key that was pressed.
     */
    static int pressedKey;

    /**
     * @brief A callback function that will be called when an event is detected, if needed.
     * The integer parameter typically represents the event type or code.
     */
    static std::function<void(int)> callback;
};