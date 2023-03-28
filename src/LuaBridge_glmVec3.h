// This code is based on Array.h, taken from
// https://github.com/vinniefalco/LuaBridge (commit: 370a6245cf)
//
// Copyright 2020, Dmitry Tarakanov
// SPDX-License-Identifier: MIT

// modifications: replaced template arguments by fixed 3 floats,
//                representing a glm vec3.

#pragma once

#include <LuaBridge/detail/Stack.h>

#include <glm/glm.hpp>

namespace luabridge
{
    template <>
    struct Stack<glm::vec3>
    {
        static void push(lua_State *L, glm::vec3 const &vec)
        {
            lua_createtable(L, static_cast<int>(3), 0);
            for (std::size_t i = 0; i < 3; ++i)
            {
                lua_pushinteger(L, static_cast<lua_Integer>(i + 1));
                Stack<float>::push(L, vec[static_cast<glm::length_t>(i)]);
                lua_settable(L, -3);
            }
        }

        static glm::vec3 get(lua_State *L, int index)
        {
            if (!lua_istable(L, index))
            {
                luaL_error(L, "#%d argments must be table", index);
            }

            std::size_t const tableSize = static_cast<std::size_t>(get_length(L, index));

            if (tableSize != 3)
            {
                luaL_error(L, "glm::vec3 size should be %d ", 3);
            }

            glm::vec3 vec;

            int const absindex = lua_absindex(L, index);
            lua_pushnil(L);
            int arrayIndex = 0;
            while (lua_next(L, absindex) != 0)
            {
                vec[arrayIndex] = Stack<float>::get(L, -1);
                lua_pop(L, 1);
                ++arrayIndex;
            }
            return vec;
        }
    };

} // namespace luabridge
