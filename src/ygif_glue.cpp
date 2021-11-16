/*
Copyright (c) 2019-2023 Alexander Scholz

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
#include <array>
#include "yourgame/yourgame.h"
#include "ygif_trafo.h"
#include "ygif_camera.h"
#include "ygif_motion.h"
#include "yg_interact.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "LuaBridge/LuaBridge.h"
#include "LuaBridge/Array.h"
#include "LuaBridge/Vector.h"

// LuaBridge Stacks for glm
#include "LuaBridge_glmVec3.h"
#include "LuaBridge_glmQuat.h"

namespace yg = yourgame; // convenience

namespace mygame
{
    extern std::map<std::string, size_t> g_interact;
    extern std::vector<InteractItem> g_interactItems;
    extern yg::util::AssetManager g_assets;
    extern std::string g_luaScriptName;
    extern bool g_reinitEnvironment;
    extern lua_State *g_Lua;

    // log ...
    void log_debug(std::string s)
    {
        yg::log::debug("%v", s);
    }

    void log_info(std::string s)
    {
        yg::log::info("%v", s);
    }

    void log_warn(std::string s)
    {
        yg::log::warn("%v", s);
    }

    void log_error(std::string s)
    {
        yg::log::error("%v", s);
    }

    // input ...
    const std::map<std::string, yg::input::Source> str2input = {
        {"KEY_UNKNOWN", yg::input::KEY_UNKNOWN},
        {"KEY_SPACE", yg::input::KEY_SPACE},
        {"KEY_APOSTROPHE", yg::input::KEY_APOSTROPHE},
        {"KEY_COMMA", yg::input::KEY_COMMA},
        {"KEY_MINUS", yg::input::KEY_MINUS},
        {"KEY_PERIOD", yg::input::KEY_PERIOD},
        {"KEY_SLASH", yg::input::KEY_SLASH},
        {"KEY_0", yg::input::KEY_0},
        {"KEY_1", yg::input::KEY_1},
        {"KEY_2", yg::input::KEY_2},
        {"KEY_3", yg::input::KEY_3},
        {"KEY_4", yg::input::KEY_4},
        {"KEY_5", yg::input::KEY_5},
        {"KEY_6", yg::input::KEY_6},
        {"KEY_7", yg::input::KEY_7},
        {"KEY_8", yg::input::KEY_8},
        {"KEY_9", yg::input::KEY_9},
        {"KEY_SEMICOLON", yg::input::KEY_SEMICOLON},
        {"KEY_EQUAL", yg::input::KEY_EQUAL},
        {"KEY_A", yg::input::KEY_A},
        {"KEY_B", yg::input::KEY_B},
        {"KEY_C", yg::input::KEY_C},
        {"KEY_D", yg::input::KEY_D},
        {"KEY_E", yg::input::KEY_E},
        {"KEY_F", yg::input::KEY_F},
        {"KEY_G", yg::input::KEY_G},
        {"KEY_H", yg::input::KEY_H},
        {"KEY_I", yg::input::KEY_I},
        {"KEY_J", yg::input::KEY_J},
        {"KEY_K", yg::input::KEY_K},
        {"KEY_L", yg::input::KEY_L},
        {"KEY_M", yg::input::KEY_M},
        {"KEY_N", yg::input::KEY_N},
        {"KEY_O", yg::input::KEY_O},
        {"KEY_P", yg::input::KEY_P},
        {"KEY_Q", yg::input::KEY_Q},
        {"KEY_R", yg::input::KEY_R},
        {"KEY_S", yg::input::KEY_S},
        {"KEY_T", yg::input::KEY_T},
        {"KEY_U", yg::input::KEY_U},
        {"KEY_V", yg::input::KEY_V},
        {"KEY_W", yg::input::KEY_W},
        {"KEY_X", yg::input::KEY_X},
        {"KEY_Y", yg::input::KEY_Y},
        {"KEY_Z", yg::input::KEY_Z},
        {"KEY_LEFT_BRACKET", yg::input::KEY_LEFT_BRACKET},
        {"KEY_BACKSLASH", yg::input::KEY_BACKSLASH},
        {"KEY_RIGHT_BRACKET", yg::input::KEY_RIGHT_BRACKET},
        {"KEY_GRAVE_ACCENT", yg::input::KEY_GRAVE_ACCENT},
        {"KEY_WORLD_1", yg::input::KEY_WORLD_1},
        {"KEY_WORLD_2", yg::input::KEY_WORLD_2},
        {"KEY_ESCAPE", yg::input::KEY_ESCAPE},
        {"KEY_ENTER", yg::input::KEY_ENTER},
        {"KEY_TAB", yg::input::KEY_TAB},
        {"KEY_BACKSPACE", yg::input::KEY_BACKSPACE},
        {"KEY_INSERT", yg::input::KEY_INSERT},
        {"KEY_DELETE", yg::input::KEY_DELETE},
        {"KEY_RIGHT", yg::input::KEY_RIGHT},
        {"KEY_LEFT", yg::input::KEY_LEFT},
        {"KEY_DOWN", yg::input::KEY_DOWN},
        {"KEY_UP", yg::input::KEY_UP},
        {"KEY_PAGE_UP", yg::input::KEY_PAGE_UP},
        {"KEY_PAGE_DOWN", yg::input::KEY_PAGE_DOWN},
        {"KEY_HOME", yg::input::KEY_HOME},
        {"KEY_END", yg::input::KEY_END},
        {"KEY_CAPS_LOCK", yg::input::KEY_CAPS_LOCK},
        {"KEY_SCROLL_LOCK", yg::input::KEY_SCROLL_LOCK},
        {"KEY_NUM_LOCK", yg::input::KEY_NUM_LOCK},
        {"KEY_PRINT_SCREEN", yg::input::KEY_PRINT_SCREEN},
        {"KEY_PAUSE", yg::input::KEY_PAUSE},
        {"KEY_F1", yg::input::KEY_F1},
        {"KEY_F2", yg::input::KEY_F2},
        {"KEY_F3", yg::input::KEY_F3},
        {"KEY_F4", yg::input::KEY_F4},
        {"KEY_F5", yg::input::KEY_F5},
        {"KEY_F6", yg::input::KEY_F6},
        {"KEY_F7", yg::input::KEY_F7},
        {"KEY_F8", yg::input::KEY_F8},
        {"KEY_F9", yg::input::KEY_F9},
        {"KEY_F10", yg::input::KEY_F10},
        {"KEY_F11", yg::input::KEY_F11},
        {"KEY_F12", yg::input::KEY_F12},
        {"KEY_F13", yg::input::KEY_F13},
        {"KEY_F14", yg::input::KEY_F14},
        {"KEY_F15", yg::input::KEY_F15},
        {"KEY_F16", yg::input::KEY_F16},
        {"KEY_F17", yg::input::KEY_F17},
        {"KEY_F18", yg::input::KEY_F18},
        {"KEY_F19", yg::input::KEY_F19},
        {"KEY_F20", yg::input::KEY_F20},
        {"KEY_F21", yg::input::KEY_F21},
        {"KEY_F22", yg::input::KEY_F22},
        {"KEY_F23", yg::input::KEY_F23},
        {"KEY_F24", yg::input::KEY_F24},
        {"KEY_F25", yg::input::KEY_F25},
        {"KEY_KP_0", yg::input::KEY_KP_0},
        {"KEY_KP_1", yg::input::KEY_KP_1},
        {"KEY_KP_2", yg::input::KEY_KP_2},
        {"KEY_KP_3", yg::input::KEY_KP_3},
        {"KEY_KP_4", yg::input::KEY_KP_4},
        {"KEY_KP_5", yg::input::KEY_KP_5},
        {"KEY_KP_6", yg::input::KEY_KP_6},
        {"KEY_KP_7", yg::input::KEY_KP_7},
        {"KEY_KP_8", yg::input::KEY_KP_8},
        {"KEY_KP_9", yg::input::KEY_KP_9},
        {"KEY_KP_DECIMAL", yg::input::KEY_KP_DECIMAL},
        {"KEY_KP_DIVIDE", yg::input::KEY_KP_DIVIDE},
        {"KEY_KP_MULTIPLY", yg::input::KEY_KP_MULTIPLY},
        {"KEY_KP_SUBTRACT", yg::input::KEY_KP_SUBTRACT},
        {"KEY_KP_ADD", yg::input::KEY_KP_ADD},
        {"KEY_KP_ENTER", yg::input::KEY_KP_ENTER},
        {"KEY_KP_EQUAL", yg::input::KEY_KP_EQUAL},
        {"KEY_LEFT_SHIFT", yg::input::KEY_LEFT_SHIFT},
        {"KEY_LEFT_CONTROL", yg::input::KEY_LEFT_CONTROL},
        {"KEY_LEFT_ALT", yg::input::KEY_LEFT_ALT},
        {"KEY_LEFT_SUPER", yg::input::KEY_LEFT_SUPER},
        {"KEY_RIGHT_SHIFT", yg::input::KEY_RIGHT_SHIFT},
        {"KEY_RIGHT_CONTROL", yg::input::KEY_RIGHT_CONTROL},
        {"KEY_RIGHT_ALT", yg::input::KEY_RIGHT_ALT},
        {"KEY_RIGHT_SUPER", yg::input::KEY_RIGHT_SUPER},
        {"KEY_MENU", yg::input::KEY_MENU},
        {"MOUSE_X", yg::input::MOUSE_X},
        {"MOUSE_Y", yg::input::MOUSE_Y},
        {"MOUSE_BUTTON_1", yg::input::MOUSE_BUTTON_1},
        {"MOUSE_BUTTON_2", yg::input::MOUSE_BUTTON_2},
        {"MOUSE_BUTTON_3", yg::input::MOUSE_BUTTON_3},
        {"MOUSE_BUTTON_4", yg::input::MOUSE_BUTTON_4},
        {"MOUSE_BUTTON_5", yg::input::MOUSE_BUTTON_5},
        {"MOUSE_BUTTON_6", yg::input::MOUSE_BUTTON_6},
        {"MOUSE_BUTTON_7", yg::input::MOUSE_BUTTON_7},
        {"MOUSE_BUTTON_8", yg::input::MOUSE_BUTTON_8},
        {"SCROLL_OFFSET_X", yg::input::SCROLL_OFFSET_X},
        {"SCROLL_OFFSET_Y", yg::input::SCROLL_OFFSET_Y},
        {"TOUCH_0_DOWN", yg::input::TOUCH_0_DOWN},
        {"TOUCH_0_X", yg::input::TOUCH_0_X},
        {"TOUCH_0_Y", yg::input::TOUCH_0_Y},
        {"TOUCH_1_DOWN", yg::input::TOUCH_1_DOWN},
        {"TOUCH_1_X", yg::input::TOUCH_1_X},
        {"TOUCH_1_Y", yg::input::TOUCH_1_Y},
        {"TOUCH_2_DOWN", yg::input::TOUCH_2_DOWN},
        {"TOUCH_2_X", yg::input::TOUCH_2_X},
        {"TOUCH_2_Y", yg::input::TOUCH_2_Y},
        {"TOUCH_3_DOWN", yg::input::TOUCH_3_DOWN},
        {"TOUCH_3_X", yg::input::TOUCH_3_X},
        {"TOUCH_3_Y", yg::input::TOUCH_3_Y},
        {"TOUCH_4_DOWN", yg::input::TOUCH_4_DOWN},
        {"TOUCH_4_X", yg::input::TOUCH_4_X},
        {"TOUCH_4_Y", yg::input::TOUCH_4_Y},
        {"TOUCH_5_DOWN", yg::input::TOUCH_5_DOWN},
        {"TOUCH_5_X", yg::input::TOUCH_5_X},
        {"TOUCH_5_Y", yg::input::TOUCH_5_Y},
        {"TOUCH_6_DOWN", yg::input::TOUCH_6_DOWN},
        {"TOUCH_6_X", yg::input::TOUCH_6_X},
        {"TOUCH_6_Y", yg::input::TOUCH_6_Y},
        {"TOUCH_7_DOWN", yg::input::TOUCH_7_DOWN},
        {"TOUCH_7_X", yg::input::TOUCH_7_X},
        {"TOUCH_7_Y", yg::input::TOUCH_7_Y},
        {"TOUCH_8_DOWN", yg::input::TOUCH_8_DOWN},
        {"TOUCH_8_X", yg::input::TOUCH_8_X},
        {"TOUCH_8_Y", yg::input::TOUCH_8_Y},
        {"TOUCH_9_DOWN", yg::input::TOUCH_9_DOWN},
        {"TOUCH_9_X", yg::input::TOUCH_9_X},
        {"TOUCH_9_Y", yg::input::TOUCH_9_Y},
        {"GAMEPAD_0_CONNECTED", yg::input::GAMEPAD_0_CONNECTED},
        {"GAMEPAD_0_BUTTON_A", yg::input::GAMEPAD_0_BUTTON_A},
        {"GAMEPAD_0_BUTTON_B", yg::input::GAMEPAD_0_BUTTON_B},
        {"GAMEPAD_0_BUTTON_X", yg::input::GAMEPAD_0_BUTTON_X},
        {"GAMEPAD_0_BUTTON_Y", yg::input::GAMEPAD_0_BUTTON_Y},
        {"GAMEPAD_0_BUTTON_LEFT_BUMPER", yg::input::GAMEPAD_0_BUTTON_LEFT_BUMPER},
        {"GAMEPAD_0_BUTTON_RIGHT_BUMPER", yg::input::GAMEPAD_0_BUTTON_RIGHT_BUMPER},
        {"GAMEPAD_0_BUTTON_BACK", yg::input::GAMEPAD_0_BUTTON_BACK},
        {"GAMEPAD_0_BUTTON_START", yg::input::GAMEPAD_0_BUTTON_START},
        {"GAMEPAD_0_BUTTON_GUIDE", yg::input::GAMEPAD_0_BUTTON_GUIDE},
        {"GAMEPAD_0_BUTTON_LEFT_THUMB", yg::input::GAMEPAD_0_BUTTON_LEFT_THUMB},
        {"GAMEPAD_0_BUTTON_RIGHT_THUMB", yg::input::GAMEPAD_0_BUTTON_RIGHT_THUMB},
        {"GAMEPAD_0_BUTTON_DPAD_UP", yg::input::GAMEPAD_0_BUTTON_DPAD_UP},
        {"GAMEPAD_0_BUTTON_DPAD_RIGHT", yg::input::GAMEPAD_0_BUTTON_DPAD_RIGHT},
        {"GAMEPAD_0_BUTTON_DPAD_DOWN", yg::input::GAMEPAD_0_BUTTON_DPAD_DOWN},
        {"GAMEPAD_0_BUTTON_DPAD_LEFT", yg::input::GAMEPAD_0_BUTTON_DPAD_LEFT},
        {"GAMEPAD_0_AXIS_LEFT_X", yg::input::GAMEPAD_0_AXIS_LEFT_X},
        {"GAMEPAD_0_AXIS_LEFT_Y", yg::input::GAMEPAD_0_AXIS_LEFT_Y},
        {"GAMEPAD_0_AXIS_RIGHT_X", yg::input::GAMEPAD_0_AXIS_RIGHT_X},
        {"GAMEPAD_0_AXIS_RIGHT_Y", yg::input::GAMEPAD_0_AXIS_RIGHT_Y},
        {"GAMEPAD_0_AXIS_LEFT_TRIGGER", yg::input::GAMEPAD_0_AXIS_LEFT_TRIGGER},
        {"GAMEPAD_0_AXIS_RIGHT_TRIGGER", yg::input::GAMEPAD_0_AXIS_RIGHT_TRIGGER},
        {"GAMEPAD_1_CONNECTED", yg::input::GAMEPAD_1_CONNECTED},
        {"GAMEPAD_1_BUTTON_A", yg::input::GAMEPAD_1_BUTTON_A},
        {"GAMEPAD_1_BUTTON_B", yg::input::GAMEPAD_1_BUTTON_B},
        {"GAMEPAD_1_BUTTON_X", yg::input::GAMEPAD_1_BUTTON_X},
        {"GAMEPAD_1_BUTTON_Y", yg::input::GAMEPAD_1_BUTTON_Y},
        {"GAMEPAD_1_BUTTON_LEFT_BUMPER", yg::input::GAMEPAD_1_BUTTON_LEFT_BUMPER},
        {"GAMEPAD_1_BUTTON_RIGHT_BUMPER", yg::input::GAMEPAD_1_BUTTON_RIGHT_BUMPER},
        {"GAMEPAD_1_BUTTON_BACK", yg::input::GAMEPAD_1_BUTTON_BACK},
        {"GAMEPAD_1_BUTTON_START", yg::input::GAMEPAD_1_BUTTON_START},
        {"GAMEPAD_1_BUTTON_GUIDE", yg::input::GAMEPAD_1_BUTTON_GUIDE},
        {"GAMEPAD_1_BUTTON_LEFT_THUMB", yg::input::GAMEPAD_1_BUTTON_LEFT_THUMB},
        {"GAMEPAD_1_BUTTON_RIGHT_THUMB", yg::input::GAMEPAD_1_BUTTON_RIGHT_THUMB},
        {"GAMEPAD_1_BUTTON_DPAD_UP", yg::input::GAMEPAD_1_BUTTON_DPAD_UP},
        {"GAMEPAD_1_BUTTON_DPAD_RIGHT", yg::input::GAMEPAD_1_BUTTON_DPAD_RIGHT},
        {"GAMEPAD_1_BUTTON_DPAD_DOWN", yg::input::GAMEPAD_1_BUTTON_DPAD_DOWN},
        {"GAMEPAD_1_BUTTON_DPAD_LEFT", yg::input::GAMEPAD_1_BUTTON_DPAD_LEFT},
        {"GAMEPAD_1_AXIS_LEFT_X", yg::input::GAMEPAD_1_AXIS_LEFT_X},
        {"GAMEPAD_1_AXIS_LEFT_Y", yg::input::GAMEPAD_1_AXIS_LEFT_Y},
        {"GAMEPAD_1_AXIS_RIGHT_X", yg::input::GAMEPAD_1_AXIS_RIGHT_X},
        {"GAMEPAD_1_AXIS_RIGHT_Y", yg::input::GAMEPAD_1_AXIS_RIGHT_Y},
        {"GAMEPAD_1_AXIS_LEFT_TRIGGER", yg::input::GAMEPAD_1_AXIS_LEFT_TRIGGER},
        {"GAMEPAD_1_AXIS_RIGHT_TRIGGER", yg::input::GAMEPAD_1_AXIS_RIGHT_TRIGGER},
        {"GAMEPAD_2_CONNECTED", yg::input::GAMEPAD_2_CONNECTED},
        {"GAMEPAD_2_BUTTON_A", yg::input::GAMEPAD_2_BUTTON_A},
        {"GAMEPAD_2_BUTTON_B", yg::input::GAMEPAD_2_BUTTON_B},
        {"GAMEPAD_2_BUTTON_X", yg::input::GAMEPAD_2_BUTTON_X},
        {"GAMEPAD_2_BUTTON_Y", yg::input::GAMEPAD_2_BUTTON_Y},
        {"GAMEPAD_2_BUTTON_LEFT_BUMPER", yg::input::GAMEPAD_2_BUTTON_LEFT_BUMPER},
        {"GAMEPAD_2_BUTTON_RIGHT_BUMPER", yg::input::GAMEPAD_2_BUTTON_RIGHT_BUMPER},
        {"GAMEPAD_2_BUTTON_BACK", yg::input::GAMEPAD_2_BUTTON_BACK},
        {"GAMEPAD_2_BUTTON_START", yg::input::GAMEPAD_2_BUTTON_START},
        {"GAMEPAD_2_BUTTON_GUIDE", yg::input::GAMEPAD_2_BUTTON_GUIDE},
        {"GAMEPAD_2_BUTTON_LEFT_THUMB", yg::input::GAMEPAD_2_BUTTON_LEFT_THUMB},
        {"GAMEPAD_2_BUTTON_RIGHT_THUMB", yg::input::GAMEPAD_2_BUTTON_RIGHT_THUMB},
        {"GAMEPAD_2_BUTTON_DPAD_UP", yg::input::GAMEPAD_2_BUTTON_DPAD_UP},
        {"GAMEPAD_2_BUTTON_DPAD_RIGHT", yg::input::GAMEPAD_2_BUTTON_DPAD_RIGHT},
        {"GAMEPAD_2_BUTTON_DPAD_DOWN", yg::input::GAMEPAD_2_BUTTON_DPAD_DOWN},
        {"GAMEPAD_2_BUTTON_DPAD_LEFT", yg::input::GAMEPAD_2_BUTTON_DPAD_LEFT},
        {"GAMEPAD_2_AXIS_LEFT_X", yg::input::GAMEPAD_2_AXIS_LEFT_X},
        {"GAMEPAD_2_AXIS_LEFT_Y", yg::input::GAMEPAD_2_AXIS_LEFT_Y},
        {"GAMEPAD_2_AXIS_RIGHT_X", yg::input::GAMEPAD_2_AXIS_RIGHT_X},
        {"GAMEPAD_2_AXIS_RIGHT_Y", yg::input::GAMEPAD_2_AXIS_RIGHT_Y},
        {"GAMEPAD_2_AXIS_LEFT_TRIGGER", yg::input::GAMEPAD_2_AXIS_LEFT_TRIGGER},
        {"GAMEPAD_2_AXIS_RIGHT_TRIGGER", yg::input::GAMEPAD_2_AXIS_RIGHT_TRIGGER},
        {"GAMEPAD_3_CONNECTED", yg::input::GAMEPAD_3_CONNECTED},
        {"GAMEPAD_3_BUTTON_A", yg::input::GAMEPAD_3_BUTTON_A},
        {"GAMEPAD_3_BUTTON_B", yg::input::GAMEPAD_3_BUTTON_B},
        {"GAMEPAD_3_BUTTON_X", yg::input::GAMEPAD_3_BUTTON_X},
        {"GAMEPAD_3_BUTTON_Y", yg::input::GAMEPAD_3_BUTTON_Y},
        {"GAMEPAD_3_BUTTON_LEFT_BUMPER", yg::input::GAMEPAD_3_BUTTON_LEFT_BUMPER},
        {"GAMEPAD_3_BUTTON_RIGHT_BUMPER", yg::input::GAMEPAD_3_BUTTON_RIGHT_BUMPER},
        {"GAMEPAD_3_BUTTON_BACK", yg::input::GAMEPAD_3_BUTTON_BACK},
        {"GAMEPAD_3_BUTTON_START", yg::input::GAMEPAD_3_BUTTON_START},
        {"GAMEPAD_3_BUTTON_GUIDE", yg::input::GAMEPAD_3_BUTTON_GUIDE},
        {"GAMEPAD_3_BUTTON_LEFT_THUMB", yg::input::GAMEPAD_3_BUTTON_LEFT_THUMB},
        {"GAMEPAD_3_BUTTON_RIGHT_THUMB", yg::input::GAMEPAD_3_BUTTON_RIGHT_THUMB},
        {"GAMEPAD_3_BUTTON_DPAD_UP", yg::input::GAMEPAD_3_BUTTON_DPAD_UP},
        {"GAMEPAD_3_BUTTON_DPAD_RIGHT", yg::input::GAMEPAD_3_BUTTON_DPAD_RIGHT},
        {"GAMEPAD_3_BUTTON_DPAD_DOWN", yg::input::GAMEPAD_3_BUTTON_DPAD_DOWN},
        {"GAMEPAD_3_BUTTON_DPAD_LEFT", yg::input::GAMEPAD_3_BUTTON_DPAD_LEFT},
        {"GAMEPAD_3_AXIS_LEFT_X", yg::input::GAMEPAD_3_AXIS_LEFT_X},
        {"GAMEPAD_3_AXIS_LEFT_Y", yg::input::GAMEPAD_3_AXIS_LEFT_Y},
        {"GAMEPAD_3_AXIS_RIGHT_X", yg::input::GAMEPAD_3_AXIS_RIGHT_X},
        {"GAMEPAD_3_AXIS_RIGHT_Y", yg::input::GAMEPAD_3_AXIS_RIGHT_Y},
        {"GAMEPAD_3_AXIS_LEFT_TRIGGER", yg::input::GAMEPAD_3_AXIS_LEFT_TRIGGER},
        {"GAMEPAD_3_AXIS_RIGHT_TRIGGER", yg::input::GAMEPAD_3_AXIS_RIGHT_TRIGGER},
        {"WINDOW_WIDTH", yg::input::WINDOW_WIDTH},
        {"WINDOW_HEIGHT", yg::input::WINDOW_HEIGHT},
        {"WINDOW_ASPECT_RATIO", yg::input::WINDOW_ASPECT_RATIO},
        {"WINDOW_FULLSCREEN", yg::input::WINDOW_FULLSCREEN},
        {"VSYNC_ON", yg::input::VSYNC_ON},
        {"MOUSE_CATCHED", yg::input::MOUSE_CATCHED}};

    float input_get(std::string source)
    {
        auto i = str2input.find(source);
        return (i == str2input.end()) ? 0.0f : yg::input::get(i->second);
    }

    int input_geti(std::string source)
    {
        auto i = str2input.find(source);
        return (i == str2input.end()) ? 0 : yg::input::geti(i->second);
    }

    float input_getDelta(std::string source)
    {
        auto i = str2input.find(source);
        return (i == str2input.end()) ? 0.0f : yg::input::getDelta(i->second);
    }

    // gl ...
    const std::map<std::string, GLenum> str2texUnit = {
        {"diffuse", yg::gl::textureUnitDiffuse}};

    const std::map<std::string, GLint> str2texFilter = {
        {"linear", GL_LINEAR},
        {"nearest", GL_NEAREST}};

    const std::map<std::string, GLint> str2texWrap = {
        {"repeat", GL_REPEAT},
        {"mirrored_repeat", GL_MIRRORED_REPEAT},
        {"clamp_to_edge", GL_CLAMP_TO_EDGE}};
    //{"clamp_to_border", GL_CLAMP_TO_BORDER}};

    void gl_draw(yg::gl::Geometry *geo,
                 yg::gl::Lightsource *light,
                 yg::gl::Shader *shader,
                 yg::gl::Texture *texture, // todo make a list
                 yg::math::Camera *camera,
                 yg::math::Trafo *trafo)
    {
        shader->useProgram(light, camera);
        yg::gl::DrawConfig cfg;
        cfg.camera = camera;
        if (trafo != nullptr)
        {
            cfg.modelMat = trafo->mat();
        }
        cfg.shader = shader;

        // todo...
        if (texture)
            cfg.textures.push_back(texture);

        yg::gl::drawGeo(geo, cfg);
    }

    void gl_drawSprite(yg::gl::Texture *texture,
                       const yg::gl::TextureCoords &coords,
                       int x,
                       int y,
                       int width,
                       int height,
                       float angle)
    {
        yg::gl::DrawConfig cfg;

        cfg.shader = g_assets.get<yg::gl::Shader>("sprite");
        if (cfg.shader)
        {
            cfg.shader->useProgram();
        }

        cfg.textures.push_back(texture);

        float width_f = static_cast<float>(width);
        float height_f = static_cast<float>(height);
        if (texture)
        {
            cfg.subtex = {coords.uMin, coords.uMax, coords.vMin, coords.vMax};

            if (width == 0 && height == 0)
            {
                width_f = static_cast<float>(coords.xMaxPixel - coords.xMinPixel);
                height_f = static_cast<float>(coords.yMaxPixel - coords.yMinPixel);
            }
            else if (width == 0)
            {
                width_f = height_f * coords.aspectRatioPixel;
            }
            else if (height == 0)
            {
                height_f = width_f * coords.aspectRatioPixelInverse;
            }
        }

        {
            float windowWidth = yg::input::get(yg::input::WINDOW_WIDTH);
            float windowHeight = yg::input::get(yg::input::WINDOW_HEIGHT);

            yg::math::Trafo trafo;
            trafo.translateGlobal({static_cast<float>(x), static_cast<float>(-y), 0.0f});
            trafo.rotateGlobal(angle, yg::math::Axis::Z);
            trafo.setScaleLocal({static_cast<float>(width_f) * 0.5f, static_cast<float>(height_f) * 0.5f, 1.0f});

            cfg.modelMat = glm::ortho(0.0f, windowWidth, -windowHeight, 0.0f, -1.0f, 1.0f) *
                           trafo.mat();
        }

        yg::gl::drawGeo(g_assets.get<yg::gl::Geometry>("quad"), cfg);
    }

    void gl_depthTest(bool enable)
    {
        if (enable)
        {
            glEnable(GL_DEPTH_TEST);
        }
        else
        {
            glDisable(GL_DEPTH_TEST);
        }
    }

    void gl_clearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    // interact ...
    void interact_insert(InteractItem &flav)
    {
        auto it = g_interact.find(flav.name);
        if (it == g_interact.end())
        {
            g_interactItems.push_back(flav);
            g_interact[flav.name] = g_interactItems.size() - 1;
        }
        else
        {
            g_interactItems[it->second] = flav;
        }
    }

    void interact_addNumber(const std::string &name, const std::string &unit, float value, float min, float max)
    {
        InteractItem flav;
        flav.name = name;
        flav.unit = unit;
        flav.type = InteractItemType::NUMBER;
        flav.data.num0 = value;
        flav.min.number = min;
        flav.max.number = max;
        interact_insert(flav);
    }

    void interact_addInteger(const std::string &name, const std::string &unit, int value, int min, int max)
    {
        InteractItem flav;
        flav.name = name;
        flav.unit = unit;
        flav.type = InteractItemType::INTEGER;
        flav.data.integer = value;
        flav.min.integer = min;
        flav.max.integer = max;
        interact_insert(flav);
    }

    void interact_addVector2(const std::string &name, float x, float y)
    {
        InteractItem flav;
        flav.name = name;
        flav.type = InteractItemType::VECTOR2;
        flav.data.num0 = x;
        flav.data.num1 = y;
        interact_insert(flav);
    }

    void interact_addVector3(const std::string &name, float x, float y, float z)
    {
        InteractItem flav;
        flav.name = name;
        flav.type = InteractItemType::VECTOR3;
        flav.data.num0 = x;
        flav.data.num1 = y;
        flav.data.num2 = z;
        interact_insert(flav);
    }

    void interact_addBinary(const std::string &name, const std::string &unit, bool value)
    {
        InteractItem flav;
        flav.name = name;
        flav.unit = unit;
        flav.type = InteractItemType::BINARY;
        flav.data.binary = value;
        interact_insert(flav);
    }

    void interact_addRGB(const std::string &name, float r, float g, float b)
    {
        InteractItem flav;
        flav.name = name;
        flav.type = InteractItemType::RGB;
        flav.data.num0 = r;
        flav.data.num1 = g;
        flav.data.num2 = b;
        interact_insert(flav);
    }

    void interact_addRGBA(const std::string &name, float r, float g, float b, float a)
    {
        InteractItem flav;
        flav.name = name;
        flav.type = InteractItemType::RGBA;
        flav.data.num0 = r;
        flav.data.num1 = g;
        flav.data.num2 = b;
        flav.data.num3 = a;
        interact_insert(flav);
    }

    void interact_addAction(const std::string &name, const std::string &unit)
    {
        InteractItem flav;
        flav.name = name;
        flav.unit = unit;
        flav.type = InteractItemType::ACTION;
        interact_insert(flav);
    }

    void interact_addSelect(const std::string &name, std::vector<std::string> items, int value)
    {
        InteractItem flav;
        flav.name = name;
        flav.type = InteractItemType::SELECT;
        flav.selectItems = items;
        flav.data.integer = value % items.size();
        interact_insert(flav);
    }

    float interact_getNumber(const std::string &name)
    {
        auto it = g_interact.find(name);
        if (it != g_interact.end() && g_interactItems[it->second].type == InteractItemType::NUMBER)
        {
            return g_interactItems[it->second].data.num0;
        }
        return 0.0f;
    }

    int interact_getInteger(const std::string &name)
    {
        auto it = g_interact.find(name);
        if (it != g_interact.end() && g_interactItems[it->second].type == InteractItemType::INTEGER)
        {
            return g_interactItems[it->second].data.integer;
        }
        return 0;
    }

    std::array<float, 2> interact_getVector2(const std::string &name)
    {
        std::array<float, 2> data{0.0f, 0.0f};
        auto it = g_interact.find(name);
        if (it != g_interact.end() && g_interactItems[it->second].type == InteractItemType::VECTOR2)
        {
            data[0] = g_interactItems[it->second].data.num0;
            data[1] = g_interactItems[it->second].data.num1;
        }
        return data;
    }

    std::array<float, 3> interact_getVector3(const std::string &name)
    {
        std::array<float, 3> data{0.0f, 0.0f, 0.0f};
        auto it = g_interact.find(name);
        if (it != g_interact.end() && g_interactItems[it->second].type == InteractItemType::VECTOR3)
        {
            data[0] = g_interactItems[it->second].data.num0;
            data[1] = g_interactItems[it->second].data.num1;
            data[2] = g_interactItems[it->second].data.num2;
        }
        return data;
    }

    bool interact_getBinary(const std::string &name)
    {
        auto it = g_interact.find(name);
        if (it != g_interact.end() && g_interactItems[it->second].type == InteractItemType::BINARY)
        {
            return g_interactItems[it->second].data.binary;
        }
        return false;
    }

    std::array<float, 3> interact_getRGB(const std::string &name)
    {
        std::array<float, 3> data{0.0f, 0.0f, 0.0f};
        auto it = g_interact.find(name);
        if (it != g_interact.end() && g_interactItems[it->second].type == InteractItemType::RGB)
        {
            data[0] = g_interactItems[it->second].data.num0;
            data[1] = g_interactItems[it->second].data.num1;
            data[2] = g_interactItems[it->second].data.num2;
        }
        return data;
    }

    std::array<float, 4> interact_getRGBA(const std::string &name)
    {
        std::array<float, 4> data{0.0f, 0.0f, 0.0f, 0.0f};
        auto it = g_interact.find(name);
        if (it != g_interact.end() && g_interactItems[it->second].type == InteractItemType::RGBA)
        {
            data[0] = g_interactItems[it->second].data.num0;
            data[1] = g_interactItems[it->second].data.num1;
            data[2] = g_interactItems[it->second].data.num2;
            data[3] = g_interactItems[it->second].data.num3;
        }
        return data;
    }

    bool interact_getAction(const std::string &name)
    {
        auto it = g_interact.find(name);
        if (it != g_interact.end() && g_interactItems[it->second].type == InteractItemType::ACTION)
        {
            return g_interactItems[it->second].data.binary;
        }
        return false;
    }

    int interact_getSelect(const std::string &name)
    {
        auto it = g_interact.find(name);
        if (it != g_interact.end() && g_interactItems[it->second].type == InteractItemType::SELECT)
        {
            return g_interactItems[it->second].data.integer;
        }
        return 0;
    }

    // asset ...
    void asset_clear()
    {
        g_assets.clear();
    }

    bool asset_loadTexture(const std::string &name,
                           const std::string &imgFilename,
                           const std::string &atlasFilename,
                           const std::string &unit,
                           const std::string &filter,
                           const std::string &wrapmode,
                           bool mipmap)
    {
        yourgame::gl::TextureConfig cfg;

        // texture unit
        {
            auto i = str2texUnit.find(unit);
            if (i == str2texUnit.end())
            {
                yg::log::warn("loading texture %v: unknown texture unit %v", imgFilename, unit);
                cfg.unit = yg::gl::textureUnitDiffuse;
            }
            else
            {
                cfg.unit = i->second;
            }
        }

        // texture filter
        {
            auto i = str2texFilter.find(filter);
            if (i == str2texFilter.end())
            {
                yg::log::warn("loading texture %v: unknown filter mode %v", imgFilename, filter);
                cfg.minMagFilter = GL_LINEAR;
            }
            else
            {
                cfg.minMagFilter = i->second;
            }
        }

        // texture wrap mode
        {
            auto i = str2texWrap.find(wrapmode);
            if (i == str2texWrap.end())
            {
                yg::log::warn("loading texture %v: unknown wrap mode %v", imgFilename, wrapmode);
                cfg.wrapMode = GL_REPEAT;
            }
            else
            {
                cfg.wrapMode = i->second;
            }
        }

        // mipmap
        cfg.generateMipmap = mipmap;

        auto texture = yg::gl::loadTexture(imgFilename, atlasFilename, cfg);

        if (texture)
            g_assets.insert(name, texture);

        return texture != nullptr;
    }

    yg::gl::Texture *asset_getTexture(const std::string &name)
    {
        return g_assets.get<yg::gl::Texture>(name);
    }

    void asset_destroyTexture(const std::string &name)
    {
        g_assets.destroy<yg::gl::Texture>(name);
    }

    size_t asset_numOfTexture()
    {
        return g_assets.numOf<yg::gl::Texture>();
    }

    bool asset_loadVertFragShader(const std::string &name,
                                  const std::string &vertFilename,
                                  const std::string &fragFilename)
    {
        auto shader = yg::gl::loadShader({{GL_VERTEX_SHADER, vertFilename},
                                          {GL_FRAGMENT_SHADER, fragFilename}});
        if (shader)
            g_assets.insert(name, shader);

        return shader != nullptr;
    }

    yg::gl::Shader *asset_getShader(const std::string &name)
    {
        return g_assets.get<yg::gl::Shader>(name);
    }

    void asset_destroyShader(const std::string &name)
    {
        g_assets.destroy<yg::gl::Shader>(name);
    }

    size_t asset_numOfShader()
    {
        return g_assets.numOf<yg::gl::Shader>();
    }

    bool asset_loadGeometry(const std::string &name,
                            const std::string &objFilename,
                            const std::string &mtlFilename)
    {
        auto geometry = yg::gl::loadGeometry(objFilename, mtlFilename);
        if (geometry)
            g_assets.insert(name, geometry);

        return geometry != nullptr;
    }

    yg::gl::Geometry *asset_getGeometry(const std::string &name)
    {
        return g_assets.get<yg::gl::Geometry>(name);
    }

    void asset_destroyGeometry(const std::string &name)
    {
        g_assets.destroy<yg::gl::Geometry>(name);
    }

    size_t asset_numOfGeometry()
    {
        return g_assets.numOf<yg::gl::Geometry>();
    }

    void enableAudio()
    {
        yg::audio::init(2, 44100, 5);
    }

    void control_runScript(const std::string &filename)
    {
        g_luaScriptName = filename;
        g_reinitEnvironment = true;
    }

    void control_loadScript(const std::string &filename)
    {
        std::vector<uint8_t> data;
        if (g_Lua != nullptr &&
            yg::file::readFile(filename, data) == 0 &&
            data.size() > 0)
        {
            // add null terminator for luaL_dostring()
            data.push_back((uint8_t)0);

            // run the lua script
            if (luaL_dostring(g_Lua, (char *)(&data[0])) != 0)
            {
                yg::log::error("loadScript(): Lua error: %v", lua_tostring(g_Lua, -1));
            }
        }
    }

    void loadBaseAssets()
    {
        asset_loadVertFragShader("sprite", "a//sprite.vert", "a//sprite.frag");
        asset_loadGeometry("quad", "a//quad.obj", "");
    }

    void registerLua(lua_State *L)
    {
        luabridge::getGlobalNamespace(L)
            .beginNamespace("yg")

            // namespace audio ...
            .beginNamespace("audio")
            .addFunction("storeFile", yg::audio::storeFile)
            .addFunction("play", yg::audio::play)
            .addFunction("stop", yg::audio::stop)
            .addFunction("pause", yg::audio::pause)
            .addFunction("setChannelGains", yg::audio::setChannelGains)
            .endNamespace()

            // namespace log ...
            .beginNamespace("log")
            .addFunction("debug", log_debug)
            .addFunction("info", log_info)
            .addFunction("warn", log_warn)
            .addFunction("error", log_error)
            .endNamespace()

            // namespace control ...
            .beginNamespace("control")
            .addFunction("exit", yg::control::exit)
            .addFunction("sendCmdToEnv", yg::control::sendCmdToEnv)
            .addFunction("enableFullscreen", yg::control::enableFullscreen)
            .addFunction("enableVSync", yg::control::enableVSync)
            .addFunction("catchMouse", yg::control::catchMouse)
            .addFunction("enableAudio", enableAudio)
            .addFunction("runScript", control_runScript)
            .addFunction("loadScript", control_loadScript)
            .endNamespace()

            // namespace input ...
            .beginNamespace("input")
            .addFunction("get", input_get)
            .addFunction("geti", input_geti)
            .addFunction("getDelta", input_getDelta)
            .endNamespace()

            // namespace math ...
            .beginNamespace("math")
            // Lua class yg.math.Trafo (C++ class YgifTrafo) is derived from yg::math::Trafo
            .beginClass<yg::math::Trafo>("TrafoBase")
            .addConstructor<void (*)()>()
            .addFunction("setRotation", &yg::math::Trafo::setRotation)
            .addFunction("setTranslation", &yg::math::Trafo::setTranslation)
            .addFunction("pointTo", &yg::math::Trafo::pointTo)
            .addFunction("lookAt", &yg::math::Trafo::lookAt)
            .addFunction("lerp", &yg::math::Trafo::lerp)
            .addFunction("setIdentity", &yg::math::Trafo::setIdentity)
            .addFunction("getAxisLocal", &yg::math::Trafo::getAxisLocal)
            .addFunction("getAxisGlobal", &yg::math::Trafo::getAxisGlobal)
            .addFunction("getEye", &yg::math::Trafo::getEye)
            .addFunction("getRotation", &yg::math::Trafo::getRotation)
            .addFunction("getScale", &yg::math::Trafo::getScale)
            .endClass()
            .deriveClass<YgifTrafo, yg::math::Trafo>("Trafo")
            .addConstructor<void (*)()>()
            .addFunction("rotateLocal", &YgifTrafo::rotateLocal)
            .addFunction("rotateGlobal", &YgifTrafo::rotateGlobal)
            .addFunction("translateLocal", &YgifTrafo::translateLocal)
            .addFunction("translateGlobal", &YgifTrafo::translateGlobal)
            .addFunction("setScaleLocal", &YgifTrafo::setScaleLocal)
            .endClass()
            // Lua class yg.math.Camera (C++ class YgifCamera) is derived from yg::math::Camera
            .beginClass<yg::math::Camera>("CameraBase")
            .addConstructor<void (*)()>()
            .addFunction("setPerspective", &yg::math::Camera::setPerspective)
            .addFunction("setOrthographic", &yg::math::Camera::setOrthographic)
            .addFunction("setFovy", &yg::math::Camera::setFovy)
            .addFunction("setHeight", &yg::math::Camera::setHeight)
            .addFunction("setAspect", &yg::math::Camera::setAspect)
            .addFunction("setZNear", &yg::math::Camera::setZNear)
            .addFunction("setZFar", &yg::math::Camera::setZFar)
            .endClass()
            .deriveClass<YgifCamera, yg::math::Camera>("Camera")
            .addConstructor<void (*)()>()
            .addFunction("trafo", &YgifCamera::trafo)
            .addFunction("castRay", &YgifCamera::castRay)
            .endClass()
            .endNamespace()

            // namespace time ...
            .beginNamespace("time")
            .addFunction("getClockPeriod", yg::time::getClockPeriod)
            .addFunction("getDelta", yg::time::getDelta)
            .addFunction("getTime", yg::time::getTime)
            .endNamespace()

            // namespace gl ...
            .beginNamespace("gl")
            .addFunction("draw", gl_draw)
            .addFunction("drawSprite", gl_drawSprite)
            .addFunction("depthTest", gl_depthTest)
            .addFunction("clearColor", gl_clearColor)
            .beginClass<yg::gl::Lightsource>("Lightsource")
            .addConstructor<void (*)()>()
            .addFunction("setAmbient", &yg::gl::Lightsource::setAmbient)
            .addFunction("setDiffuse", &yg::gl::Lightsource::setDiffuse)
            .addFunction("setSpecular", &yg::gl::Lightsource::setSpecular)
            .addFunction("setPosition", &yg::gl::Lightsource::setPosition)
            .endClass()
            .beginClass<yg::gl::Texture>("Texture")
            .addFunction("getCoords", &yg::gl::Texture::getCoords)
            .addFunction("getFrameCoords", &yg::gl::Texture::getFrameCoords)
            .endClass()
            .beginClass<yg::gl::TextureCoords>("TextureCoords")
            .endClass()
            .beginClass<yg::gl::Shader>("Shader")
            .endClass()
            .beginClass<yg::gl::Geometry>("Geometry")
            .endClass()
            .endNamespace()

            // namespace interact ...
            .beginNamespace("interact")
            .addFunction("addNumber", interact_addNumber)
            .addFunction("addInteger", interact_addInteger)
            .addFunction("addVector2", interact_addVector2)
            .addFunction("addVector3", interact_addVector3)
            .addFunction("addBinary", interact_addBinary)
            .addFunction("addRGB", interact_addRGB)
            .addFunction("addRGBA", interact_addRGBA)
            .addFunction("addAction", interact_addAction)
            .addFunction("addSelect", interact_addSelect)
            .addFunction("getNumber", interact_getNumber)
            .addFunction("getInteger", interact_getInteger)
            .addFunction("getVector2", interact_getVector2)
            .addFunction("getVector3", interact_getVector3)
            .addFunction("getBinary", interact_getBinary)
            .addFunction("getRGB", interact_getRGB)
            .addFunction("getRGBA", interact_getRGBA)
            .addFunction("getAction", interact_getAction)
            .addFunction("getSelect", interact_getSelect)
            .endNamespace()

            // namespace util ...
            .beginNamespace("util")
            // Lua class yg.util.Motion (C++ class YgifMotion) is derived from yg::util::Motion
            .beginClass<yg::util::Motion>("MotionBase")
            .addFunction("addIdle", &yg::util::Motion::addIdle)
            .addFunction("tick", &yg::util::Motion::tick)
            .addFunction("val", &yg::util::Motion::val)
            .addFunction("pause", &yg::util::Motion::pause)
            .addFunction("restart", &yg::util::Motion::restart)
            .addFunction("setDirection", &yg::util::Motion::setDirection)
            .addFunction("isFinished", &yg::util::Motion::isFinished)
            .addFunction("isPaused", &yg::util::Motion::isPaused)
            .addFunction("getDirection", &yg::util::Motion::getDirection)
            .endClass()
            .deriveClass<YgifMotion, yg::util::Motion>("Motion")
            .addConstructor<void (*)(const std::string &)>()
            .addFunction("addRamp", &YgifMotion::addRamp)
            .endClass()
            .endNamespace()

            // namespace phys ...
            .beginNamespace("phys")
            .beginClass<yg::util::RigidBodyInfo>("RigidBodyInfo")
            .addConstructor<void (*)()>()
            .addProperty("mass", &yg::util::RigidBodyInfo::mass)
            .addProperty("linearDamping", &yg::util::RigidBodyInfo::linearDamping)
            .addProperty("angularDamping", &yg::util::RigidBodyInfo::angularDamping)
            .addProperty("friction", &yg::util::RigidBodyInfo::friction)
            .addProperty("rollingFriction", &yg::util::RigidBodyInfo::rollingFriction)
            .addProperty("spinningFriction", &yg::util::RigidBodyInfo::spinningFriction)
            .addProperty("restitution", &yg::util::RigidBodyInfo::restitution)
            .addProperty("linearSleepingThreshold", &yg::util::RigidBodyInfo::linearSleepingThreshold)
            .addProperty("angularSleepingThreshold", &yg::util::RigidBodyInfo::angularSleepingThreshold)
            .addProperty("kinematic", &yg::util::RigidBodyInfo::kinematic)
            .addProperty("disableDeactivation", &yg::util::RigidBodyInfo::disableDeactivation)
            .endClass() // add set spinningFrictio, rollingFriction, ... ?
            .beginClass<yg::util::RigidBody>("RigidBody")
            .addFunction("getTrafo", &yg::util::RigidBody::getTrafo)
            .addFunction("setTrafo", &yg::util::RigidBody::setTrafo)
            .addFunction("setRestitution", &yg::util::RigidBody::setRestitution)
            .addFunction("setFriction", &yg::util::RigidBody::setFriction)
            .addFunction("setSleepingThresholds", &yg::util::RigidBody::setSleepingThresholds)
            .addFunction("setLinearFactors", &yg::util::RigidBody::setLinearFactors)
            .addFunction("setAngularFactor", &yg::util::RigidBody::setAngularFactor)
            .addFunction("setAngularFactors", &yg::util::RigidBody::setAngularFactors)
            .addFunction("applyCentralForce", &yg::util::RigidBody::applyCentralForce)
            .addFunction("applyCentralImpulse", &yg::util::RigidBody::applyCentralImpulse)
            .addProperty("name", &yg::util::RigidBody::m_name)
            .endClass()
            .beginClass<yg::util::Collision>("Collision")
            .addFunction("involves", &yg::util::Collision::involves)
            .addFunction("involves2", &yg::util::Collision::involves2)
            .addProperty("body0", &yg::util::Collision::m_body0)
            .addProperty("body1", &yg::util::Collision::m_body1)
            .addProperty("impulse", &yg::util::Collision::m_impulse)
            .endClass()
            .beginClass<yg::util::RayTestResult>("RayTestResult")
            .addProperty("body", &yg::util::RayTestResult::m_rigidBody)
            .endClass()
            .beginClass<yg::util::PhysEnv>("PhysEnv")
            .addConstructor<void (*)()>()
            .addFunction("setGravity", &yg::util::PhysEnv::setGravity)
            .addFunction("newBoxShape", &yg::util::PhysEnv::newBoxShape)
            .addFunction("newSphereShape", &yg::util::PhysEnv::newSphereShape)
            .addFunction("newCylinderShape", &yg::util::PhysEnv::newCylinderShape)
            .addFunction("newConeShape", &yg::util::PhysEnv::newConeShape)
            .addFunction("deleteShape", &yg::util::PhysEnv::deleteShape)
            .addFunction("clearShapes", &yg::util::PhysEnv::clearShapes)
            .addFunction("numShapes", &yg::util::PhysEnv::numShapes)
            .addFunction("newRigidBody", &yg::util::PhysEnv::newRigidBody)
            .addFunction("deleteRigidBody", &yg::util::PhysEnv::deleteRigidBody)
            .addFunction("getRigidBody", &yg::util::PhysEnv::getRigidBody)
            .addFunction("getRigidBodiesStartingWith", &yg::util::PhysEnv::getRigidBodiesStartingWith)
            .addFunction("clearRigidBodies", &yg::util::PhysEnv::clearRigidBodies)
            .addFunction("numRigidBodies", &yg::util::PhysEnv::numRigidBodies)
            .addFunction("tick", &yg::util::PhysEnv::tick)
            .addFunction("getCollisions", &yg::util::PhysEnv::getCollisions)
            .addFunction("rayTest", &yg::util::PhysEnv::rayTest)
            .endClass()
            .endNamespace()

            // namespace asset ...
            .beginNamespace("asset")
            .addFunction("clear", asset_clear)
            // texture
            .addFunction("loadTexture", asset_loadTexture)
            .addFunction("getTexture", asset_getTexture)
            .addFunction("destroyTexture", asset_destroyTexture)
            .addFunction("numOfTexture", asset_numOfTexture)
            // shader
            .addFunction("loadVertFragShader", asset_loadVertFragShader)
            .addFunction("getShader", asset_getShader)
            .addFunction("destroyShader", asset_destroyShader)
            .addFunction("numOfShader", asset_numOfShader)
            // geometry
            .addFunction("loadGeometry", asset_loadGeometry)
            .addFunction("getGeometry", asset_getGeometry)
            .addFunction("destroyGeometry", asset_destroyGeometry)
            .addFunction("numOfGeometry", asset_numOfGeometry)
            .endNamespace()

            // end of namespace yg
            .endNamespace();
    }
}
