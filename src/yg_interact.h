/*
Copyright (c) 2019-2024 Alexander Scholz

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef YG_INTERACT_H
#define YG_INTERACT_H

#include <vector>
#include <string>

namespace mygame
{
    enum class InteractItemType
    {
        NUMBER,
        INTEGER,
        VECTOR2,
        VECTOR3,
        BINARY,
        RGB,
        RGBA,
        ACTION,
        SELECT
    };

    struct InteractItem
    {
        /**
        \brief holds the state (data) regardless of type (InteractItemType)

        - NUMBER    num0
        - INTEGER   integer
        - VECTOR2   num0, num1
        - VECTOR3   num0, num1, num2
        - BINARY    binary
        - RGB       num0, num1, num2
        - RGBA      num0, num1, num2, num3
        - ACTION    binary
        - SELECT    integer
        */
        union InteractItemData
        {
            struct
            {
                float num0, num1, num2, num3;
            };
            int integer;
            bool binary;
        };

        /**
        \brief holds min or max value for types NUMBER or INTEGER
        */
        union InteractItemMinMax
        {
            float number;
            int integer;
        };

        std::string name = "";
        std::string unit = "1";
        InteractItemType type = InteractItemType::NUMBER;

        InteractItemData data = {0.0f, 0.0f, 0.0f, 0.0f};
        InteractItemMinMax min = {0.0f};
        InteractItemMinMax max = {1.0f};

        std::vector<std::string> selectItems;
    };
}

#endif
