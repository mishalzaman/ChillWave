#include "G_EventManager.h"

/*
* Create an EventManager
*/
G_EventManager::G_EventManager()
{
    mouseDown = false;
    mousePressed = false;
    mouseReleased = false;
    mouseX = 0;
    mouseY = 0;

    // Set all key states to "up"
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
    {
        keyDown[i] = false;
        keyPressed[i] = false;
        keyReleased[i] = false;
    }
}

/*
* Handle incoming Input Events
*/
bool G_EventManager::OnEvent(const irr::SEvent& m_event)
{
    // Check if the Input Event is Key related
    if (m_event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        // Get the Key that triggered the Event
        irr::EKEY_CODE key = m_event.KeyInput.Key;
        bool down = m_event.KeyInput.PressedDown;

        // Check if the Key is down
        if (down)
        {
            // Check if the key was just pressed
            if (!keyDown[key])
            {
                keyPressed[key] = true;
            }

            keyDown[key] = true;
        }
        else
        {
            // Check if the key was just released
            if (keyDown[key])
            {
                keyReleased[key] = true;
            }

            keyDown[key] = false;
        }

    }
    // Check if the Input Event is Mouse related
    else if (m_event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        // Check if the left mouse button is pressed
        bool pressed = m_event.MouseInput.isLeftPressed();

        // Set member variables accordingly
        if (pressed)
        {
            // Check if the button was just pressed
            if (!mouseDown)
            {
                mousePressed = true;
            }

            mouseDown = true;
        }
        else
        {
            // Check if the button was just released
            if (mouseDown)
            {
                mouseReleased = true;
            }

            mouseDown = false;
        }

        // Update the Mouse position
        mouseX = m_event.MouseInput.X;
        mouseY = m_event.MouseInput.Y;
    }

    return false;
}

/*
* Check if the Left MB is down
*/
bool G_EventManager::isMouseDown()
{
    return mouseDown;
}

/*
* Check if the Left MB was just pressed
*/
bool G_EventManager::isMousePressed()
{
    return mousePressed;
}

/*
* Check if the Left MB was just released
*/
bool G_EventManager::isMouseReleased()
{
    return mouseReleased;
}

/*
* Get the X location of the Mouse
*/
int G_EventManager::mouse_x()
{
    return mouseX;
}

/*
* Get the Y location of the Mouse
*/
int G_EventManager::mouse_y()
{
    return mouseY;
}

/*
* Check if a Key is Down
*/
bool G_EventManager::isKeyDown(irr::EKEY_CODE keyCode)
{
    return keyDown[keyCode];
}

/*
* Check if a Key was just pressed
*/
bool G_EventManager::isKeyPressed(irr::EKEY_CODE keyCode)
{
    return keyPressed[keyCode];
}

/*
* Check if a Key was just released
*/
bool G_EventManager::isKeyReleased(irr::EKEY_CODE keyCode)
{
    return keyReleased[keyCode];
}

/*
* Reset the EventManager (clear mousePressed and mouseReleased)
*/
void G_EventManager::reset()
{
    mousePressed = false;
    mouseReleased = false;

    // Reset the KeyPressed and KeyReleased states
    for (int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
    {
        keyPressed[i] = false;
        keyReleased[i] = false;
    }
}