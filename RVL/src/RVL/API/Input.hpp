#ifndef RVL_INPUT_HPP
#define RVL_INPUT_HPP

#include <Core/Core.hpp>
#include <glm/glm.hpp>

namespace rvl
{    

    class Input
    {
    public:
        /**
         * @brief Checks if key is pressed 
         * 
         * @returns Function returns true all the time while key is pressed 
         *
         * @note If you need to check key press once use "IsKeyPressedDown" function
         * @ingroup input
        */
        static bool IsKeyPressed(keycode_e keycode);

        /**
         * @brief Checks if key is pressed once
         * 
         * @returns Function returns true only when key is preesed
         *
         * @ingroup input
        */
        static bool IsKeyPressedOnce(keycode_e keycode);

        /**
         * @brief Get current cursor position
         * 
         * @returns vec2 containing world cursor position
         *
         * @ingroup input
        */
        static glm::vec2 GetCursorPosition();

    };
}

#endif
