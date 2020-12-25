#ifndef EVENT_MANAGER_H_
#define EVENT_MANAGER_H_

#include <irrlicht.h>

class G_EventManager : public irr::IEventReceiver
{
public:
    // Constructor
    G_EventManager();

    // The overriden virtual method
    bool OnEvent(const irr::SEvent& m_event);

    // Methods for checking mouse states and position
    bool isMouseDown();
    bool isMousePressed();
    bool isMouseReleased();
    int mouse_x();
    int mouse_y();

    // Methods for checking key states
    bool isKeyDown(irr::EKEY_CODE keyCode);
    bool isKeyPressed(irr::EKEY_CODE keyCode);
    bool isKeyReleased(irr::EKEY_CODE keyCode);

    // Reset the EventManager
    // Do it at the end of the Game loop
    void reset();

private:
    bool keyDown[irr::KEY_KEY_CODES_COUNT];
    bool keyPressed[irr::KEY_KEY_CODES_COUNT];
    bool keyReleased[irr::KEY_KEY_CODES_COUNT];

    bool mouseDown;
    bool mousePressed;
    bool mouseReleased;

    int mouseX;
    int mouseY;
};

#endif