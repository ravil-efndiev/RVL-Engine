#include "EventListener.hpp"
#include "Rvlglpch.hpp"

namespace rvl
{
    std::array<bool, 1032> EventListener::_keysPressed;
    std::array<int, 1032>  EventListener::_changeFrames;

    double EventListener::_cursorPosX = 0.0;
    double EventListener::_cursorPosY = 0.0;

    int EventListener::_currentFrame;

    void EventListener::Init()
    {
        _keysPressed.fill(false);
        _changeFrames.fill(0);
    }

    void EventListener::Listen(const Event* event)
    {
        switch (event->GetCategory())
        {
            case EventCategory::WINDOW_EVENTS:
                ListenWindowEvents(event);
                break;
            case EventCategory::KEY_EVENTS:
                ListenKeyEvents(event);
                break;
            case EventCategory::CURSOR_EVENTS:
                ListenCursorEvents(event);
                break;
            default:
                RVL_LOG_ERROR("invalid event category");
                RVL_DEBUG_BREAK;
        }
    }

    bool EventListener::GetKey(keycode_t keycode)
    {
        return _keysPressed[keycode];
    }

    bool EventListener::GetKeyWithFrame(keycode_t keycode)
    {
        return _keysPressed[keycode] && (_changeFrames[keycode] == _currentFrame);
    }

    double EventListener::GetCursorPosX()
    {
        return _cursorPosX;
    }

    double EventListener::GetCursorPosY()
    {
        return _cursorPosY;
    }

    void EventListener::ListenWindowEvents(const Event* event)
    {
        switch (event->GetType())
        {
            case EventType::WINDOW_RESIZE: {
                auto castedEvent = dynamic_cast<const WindowResizeEvent*>(event);
                RVL_ASSERT(castedEvent, "passed event instance does not have proper type")

                glViewport(0, 0, castedEvent->GetWidth(), castedEvent->GetHeight());
                break;
            }
            default: {
                RVL_LOG_ERROR("invalid event type for category");
                RVL_DEBUG_BREAK;
            }
        }   
    }

    void EventListener::ListenKeyEvents(const Event* event)
    {
        switch (event->GetType())
        {
            case EventType::KEY_PRESSED: {
                auto castedEvent = dynamic_cast<const KeyPressEvent*>(event);
                RVL_ASSERT(castedEvent, "passed event instance does not have proper type")
                
                _keysPressed[castedEvent->GetKeyCode()] = true;
                _changeFrames[castedEvent->GetKeyCode()] = _currentFrame;

                break;
            }
            case EventType::KEY_RELEASED: {
                auto castedEvent = dynamic_cast<const KeyReleaseEvent*>(event);
                RVL_ASSERT(castedEvent, "passed event instance does not have proper type")

                _keysPressed[castedEvent->GetKeyCode()] = false;
                _changeFrames[castedEvent->GetKeyCode()] = _currentFrame;

                break;
            }
            default: {
                RVL_LOG_ERROR("invalid event type for category");
                RVL_DEBUG_BREAK;
            }
        }   
    }

    void EventListener::ListenCursorEvents(const Event* event)
    {
        RVL_ASSERT((event->GetType() == EventType::CURSOR_MOVED), "invalid event type for cursor category");

        auto castedEvent = dynamic_cast<const CursorPosEvent*>(event);

        _cursorPosX = castedEvent->GetX();
        _cursorPosY = castedEvent->GetY();
    }

    void EventListener::PollEvents()
    {
        _currentFrame++;
        glfwPollEvents();
    }

}