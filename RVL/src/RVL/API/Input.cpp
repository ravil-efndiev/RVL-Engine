#include "Input.hpp"
#include <Events/EventListener.hpp>

#include <Rendering/Renderer/Renderer.hpp>

namespace rvl
{
    bool Input::IsKeyPressed(keycode_e keycode)
    {
        keycode_t realKeycode = static_cast<keycode_t>(keycode);

        if (realKeycode >= MOUSE_BUTTONS_OFFSET)
            throw Error("passed mouse button code in KeyPressed function", RVL_RUNTIME_ERROR);
        return EventListener::GetKey(realKeycode);
    }

    bool Input::IsKeyPressedOnce(keycode_e keycode)
    {
        keycode_t realKeycode = static_cast<keycode_t>(keycode);

        if (realKeycode >= MOUSE_BUTTONS_OFFSET)
            throw Error("passed mouse button code in KeyPressed function", RVL_RUNTIME_ERROR);
        return EventListener::GetKeyWithFrame(realKeycode);
    }

    glm::vec2 Input::GetCursorPosition()
    {
        return Renderer::ConvertToWorldCoords(EventListener::GetCursorPosX(), EventListener::GetCursorPosY());
    }
}
