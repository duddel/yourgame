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
#include <algorithm> // std::replace()
#include <cstring>
#include <vector>
#include <set>
#include "yourgame/yourgame.h"
#include "mygame_version.h"
#include "ygif_glue.h"
#include "imgui.h"
#include "TextEditor.h" // this is ImGuiColorTextEdit
#include "imgui_memory_editor.h"
#include "yg_interact.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
#include "LuaBridge/LuaBridge.h"

namespace yg = yourgame; // convenience

namespace mygame
{
    struct FileTextEditor
    {
        bool *winOpened;
        TextEditor editor;
        FileTextEditor()
        {
            winOpened = new bool{true};
        }
        ~FileTextEditor()
        {
            delete winOpened;
        }
    };

    struct FileHexEditor
    {
        bool *winOpened;
        MemoryEditor editor;
        std::vector<uint8_t> data;
        FileHexEditor()
        {
            winOpened = new bool{true};
        }
        ~FileHexEditor()
        {
            delete winOpened;
        }
    };

    const std::set<std::string> g_excludeFiles = {
        "./",
        "../",
        "yg_LICENSES.txt"};

    // initial Lua script name to execute
    std::string g_luaScriptName = "a//main.lua";
    bool g_reinitEnvironment = false;

    std::map<std::string, FileTextEditor> g_openedEditors;
    std::map<std::string, FileHexEditor> g_openedHexEditors;
    std::string *g_licenseStr = nullptr;
    lua_State *g_Lua = nullptr;

    // accessed in ygif_glue.cpp via extern:
    std::map<std::string, size_t> g_interact;
    std::vector<InteractItem> g_interactItems;
    yg::util::AssetManager g_assets;

    bool g_renderImgui = true;

    // forward declarations
    void renderImgui();
    void initLua();
    void tickLua();
    void shutdownLua();
    void createEnvironment();
    void destroyEnvironment();

    void createEnvironment()
    {
        yg::time::reset();
        loadBaseAssets();
        initLua();
    }

    void destroyEnvironment()
    {
        shutdownLua();
        g_assets.clear();
        g_interact.clear();
        g_interactItems.clear();
        if (yg::audio::isInitialized())
        {
            yg::audio::shutdown();
        }
    }

    void init(int argc, char *argv[])
    {
        yg::log::info("project: %v (%v)", mygame::version::PROJECT_NAME, mygame::version::git_commit);
        yg::log::info("based on: %v (%v)", yg::version::PROJECT_NAME, yg::version::git_commit);

        // load license info file
        {
            std::vector<uint8_t> data;
            yg::file::readFile("a//yg_LICENSES.txt", data);
            g_licenseStr = new std::string(data.begin(), data.end());
        }

        // assuming argv[1] is a path to a directory: set it as project directory
        if (argc > 1)
        {
            std::string projFilePathFromArgv = argv[1];
            std::replace(projFilePathFromArgv.begin(), projFilePathFromArgv.end(), '\\', '/');
            yg::file::setProjectPath(projFilePathFromArgv);
        }

        // enable Vsync by default
        yg::control::enableVSync(true);

        createEnvironment();
    }

    void tick()
    {
        // trigger reinit if F5 was hit
        if (yg::input::getDelta(yg::input::KEY_P) > 0.0f)
        {
            g_reinitEnvironment = true;
        }

        // reinit environment if requested
        if (g_reinitEnvironment)
        {
            destroyEnvironment();
            createEnvironment();
            g_reinitEnvironment = false;
        }

        // Exit
        if (yg::input::getDelta(yg::input::KEY_ESCAPE) > 0.0f)
        {
            yg::control::exit();
        }

        // toggle GUI
        if (yg::input::getDelta(yg::input::KEY_TAB) > 0.0f)
        {
            g_renderImgui = !g_renderImgui;
        }

        // fullscreen
        if (yg::input::getDelta(yg::input::KEY_I) > 0.0f)
        {
            yg::control::enableFullscreen(!yg::input::geti(yg::input::WINDOW_FULLSCREEN));
        }

        // VSync
        if (yg::input::getDelta(yg::input::KEY_O) > 0.0f)
        {
            yg::control::enableVSync(!yg::input::geti(yg::input::VSYNC_ON));
        }

        // Catch Mouse
        if (yg::input::getDelta(yg::input::KEY_M) > 0.0f)
        {
            yg::control::catchMouse(!yg::input::geti(yg::input::MOUSE_CATCHED));
        }

        // set gl for this frame (viewport from window size, and clear gl buffers)
        glViewport(0,
                   0,
                   yg::input::geti(yg::input::WINDOW_WIDTH),
                   yg::input::geti(yg::input::WINDOW_HEIGHT));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (g_renderImgui)
        {
            renderImgui();
        }

        // remove closed Code Editor windows
        for (auto it = g_openedEditors.cbegin(); it != g_openedEditors.cend();)
        {
            if (!*(it->second.winOpened))
            {
                it = g_openedEditors.erase(it);
            }
            else
            {
                ++it;
            }
        }

        // remove closed Code Hex Editor windows
        for (auto it = g_openedHexEditors.cbegin(); it != g_openedHexEditors.cend();)
        {
            if (!*(it->second.winOpened))
            {
                it = g_openedHexEditors.erase(it);
            }
            else
            {
                ++it;
            }
        }

        tickLua();
    }

    int shutdown()
    {
        if (g_licenseStr != nullptr)
        {
            delete g_licenseStr;
            g_licenseStr = nullptr;
        }

        destroyEnvironment();

        return 0;
    }

    void renderImgui()
    {
        float mainMenuBarHeight = 0.0f;
        float sideBarHeight = 0.0f;

        static bool showLicenseWindow = false;
        static bool showAboutWindow = false;
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", "ESC"))
                {
                    yg::control::exit();
                }
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Control"))
            {
                ImGui::MenuItem("Render GUI", "TAB", &g_renderImgui);

                if (ImGui::MenuItem("Fullscreen", "I", yg::input::geti(yg::input::WINDOW_FULLSCREEN)))
                {
                    yg::control::enableFullscreen(!yg::input::geti(yg::input::WINDOW_FULLSCREEN));
                }

                if (ImGui::MenuItem("Vertical Sync", "O", yg::input::geti(yg::input::VSYNC_ON)))
                {
                    yg::control::enableVSync(!yg::input::geti(yg::input::VSYNC_ON));
                }

                if (ImGui::MenuItem("Catch Mouse", "M", yg::input::geti(yg::input::MOUSE_CATCHED)))
                {
                    yg::control::catchMouse(!yg::input::geti(yg::input::MOUSE_CATCHED));
                }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Run"))
            {
                if (ImGui::MenuItem("Restart", "P"))
                {
                    destroyEnvironment();
                    createEnvironment();
                }

                std::vector<std::string> luaFilesAssets = yg::file::ls("a//*.lua");
                if (luaFilesAssets.size() > 0)
                {
                    ImGui::Separator();
                    for (const auto &file : luaFilesAssets)
                    {
                        if (ImGui::MenuItem(file.c_str(), ""))
                        {
                            g_luaScriptName = "a//" + file;
                            destroyEnvironment();
                            createEnvironment();
                        }
                    }
                }

                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("License"))
                {
                    showLicenseWindow = true;
                }
                if (ImGui::MenuItem("About"))
                {
                    showAboutWindow = true;
                }
                ImGui::EndMenu();
            }
            mainMenuBarHeight = ImGui::GetWindowSize().y;
            ImGui::EndMainMenuBar();
        }

        sideBarHeight = yg::input::get(yg::input::WINDOW_HEIGHT) - mainMenuBarHeight;

        if (showLicenseWindow)
        {
            ImGui::Begin("License", &showLicenseWindow, (ImGuiWindowFlags_NoCollapse));
            ImGui::SetWindowSize(ImVec2(yg::input::get(yg::input::WINDOW_WIDTH) * 0.5f,
                                        yg::input::get(yg::input::WINDOW_HEIGHT) * 0.5f),
                                 ImGuiCond_FirstUseEver);

            // TextUnformatted() displays raw text without formatting. Relies
            // on zero terminator if called like this, without 2nd argument:
            ImGui::TextUnformatted(g_licenseStr->c_str());
            ImGui::End();
        }

        if (showAboutWindow)
        {
            ImGui::Begin("About", &showAboutWindow, (ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize));
            ImGui::Text("%s", (version::PROJECT_NAME + "\n\n" +
                               "Version: " + version::verstr + "\n" +
                               "Commit: " + version::git_commit + "\n" +
                               "Commit Date: " + version::git_date + "\n")
                                  .c_str());
            ImGui::End();
        }

        // Explorer
        if (false) // disabled
        {
            // get asset files
            std::vector<std::string> assetFiles = yg::file::ls("a//*");

            // get project files
            std::vector<std::string> projectFiles;
            if (yg::file::getProjectFilePath("") != "")
            {
                projectFiles = yg::file::ls("p//*");
            }

            ImGui::SetNextWindowPos({0.0f, mainMenuBarHeight});
            ImGui::SetNextWindowSizeConstraints({200.0f, sideBarHeight}, {500.0f, sideBarHeight});
            ImGui::Begin("Explorer", nullptr, (0));

            // lambda for button drawing, used multiple times below (collapsing headers)
            auto drawButtons = [](const std::vector<std::string> &filenames, const std::string &filePrefix)
            {
                for (const auto &f : filenames)
                {
                    if (g_excludeFiles.find(f) != g_excludeFiles.end())
                    {
                        continue;
                    }

                    std::string file = filePrefix + f;

                    if (ImGui::Button((std::string("txt##") + f + filePrefix).c_str()))
                    {
                        // open new Code Editor window
                        if (g_openedEditors.find(file) == g_openedEditors.end())
                        {
                            // read file
                            std::vector<uint8_t> data;
                            yg::file::readFile(file, data);

                            // insert new default-constructed FileTextEditor
                            g_openedEditors[file];

                            // set editor language
                            if (yg::file::getFileExtension(file).compare("lua") == 0)
                            {
                                g_openedEditors[file].editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());
                            }
                            else if ((yg::file::getFileExtension(file).compare("vert") == 0) ||
                                     (yg::file::getFileExtension(file).compare("frag") == 0))
                            {
                                g_openedEditors[file].editor.SetLanguageDefinition(TextEditor::LanguageDefinition::GLSL());
                            }

                            // fill editor with initial content
                            std::string dataStr = std::string(data.begin(), data.end());
                            g_openedEditors[file].editor.SetText(dataStr);
                        }
                    }

                    ImGui::SameLine();
                    if (ImGui::Button((std::string("bin##") + f + filePrefix).c_str()))
                    {
                        // insert new default-constructed FileHexEditor
                        g_openedHexEditors[file];

                        // read file
                        yg::file::readFile(file, g_openedHexEditors[file].data);
                    }
                    ImGui::SameLine();
                    ImGui::Text("%s", f.c_str());
                }
            };

            if (ImGui::CollapsingHeader("Assets", ImGuiTreeNodeFlags_DefaultOpen))
            {
                drawButtons(assetFiles, "a//");
            }

            if (ImGui::CollapsingHeader("Project", ImGuiTreeNodeFlags_DefaultOpen))
            {
                drawButtons(projectFiles, "p//");
            }

            ImGui::End();
        }

        // Interact Editor
        if (g_interactItems.size() > 0)
        {
            // use this to force the scale of the interact window as right panel
            // ImGui::SetNextWindowSizeConstraints({200.0f, sideBarHeight}, {500.0f, sideBarHeight});

            // make the interact window floating, collapsed and initializes at position 0,0
            ImGui::SetNextWindowCollapsed(true, (ImGuiCond_Once));
            ImGui::SetNextWindowPos({0.0f, 0.0f}, (ImGuiCond_Once));
            ImGui::Begin("Interact", nullptr, (ImGuiWindowFlags_AlwaysAutoResize));

            // use this to force interact window as right panel
            // ImGui::SetWindowPos({yg::input::get(yg::input::WINDOW_WIDTH) - ImGui::GetWindowSize().x, mainMenuBarHeight});

            for (auto &f : g_interactItems)
            {
                ImGui::PushID(f.name.c_str());
                if (ImGui::CollapsingHeader(f.name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
                {
                    switch (f.type)
                    {
                    case InteractItemType::NUMBER:
                    {
                        float data = f.data.num0;
                        ImGui::SliderFloat(f.unit.c_str(), &data, f.min.number, f.max.number, "%.3f");
                        f.data.num0 = data;
                    }
                    break;
                    case InteractItemType::INTEGER:
                    {
                        int data = f.data.integer;
                        ImGui::SliderInt(f.unit.c_str(), &data, f.min.integer, f.max.integer);
                        f.data.integer = data;
                    }
                    break;
                    case InteractItemType::VECTOR2:
                    {
                        float data[2];
                        data[0] = f.data.num0;
                        data[1] = f.data.num1;
                        ImGui::DragFloat("X", &(data[0]), 0.1f);
                        ImGui::DragFloat("Y", &(data[1]), 0.1f);
                        f.data.num0 = data[0];
                        f.data.num1 = data[1];
                    }
                    break;
                    case InteractItemType::VECTOR3:
                    {
                        float data[3];
                        data[0] = f.data.num0;
                        data[1] = f.data.num1;
                        data[2] = f.data.num2;
                        ImGui::DragFloat("X", &(data[0]), 0.1f);
                        ImGui::DragFloat("Y", &(data[1]), 0.1f);
                        ImGui::DragFloat("Z", &(data[2]), 0.1f);
                        f.data.num0 = data[0];
                        f.data.num1 = data[1];
                        f.data.num2 = data[2];
                    }
                    break;
                    case InteractItemType::BINARY:
                    {
                        bool data = f.data.binary;
                        ImGui::Checkbox(f.unit.c_str(), &data);
                        f.data.binary = data;
                    }
                    break;
                    case InteractItemType::RGB:
                    {
                        float data[3];
                        data[0] = f.data.num0;
                        data[1] = f.data.num1;
                        data[2] = f.data.num2;
                        ImGui::ColorPicker3("", data);
                        f.data.num0 = data[0];
                        f.data.num1 = data[1];
                        f.data.num2 = data[2];
                    }
                    break;
                    case InteractItemType::RGBA:
                    {
                        float data[4];
                        data[0] = f.data.num0;
                        data[1] = f.data.num1;
                        data[2] = f.data.num2;
                        data[3] = f.data.num3;
                        ImGui::ColorPicker4("", data, ImGuiColorEditFlags_AlphaBar);
                        f.data.num0 = data[0];
                        f.data.num1 = data[1];
                        f.data.num2 = data[2];
                        f.data.num3 = data[3];
                    }
                    break;
                    case InteractItemType::ACTION:
                    {
                        f.data.binary = ImGui::Button(f.unit.c_str());
                    }
                    break;
                    case InteractItemType::SELECT:
                    {
                        int data = f.data.integer;
                        if (ImGui::BeginListBox(f.name.c_str()))
                        {
                            for (size_t i = 0; i < f.selectItems.size(); i++)
                            {
                                if (ImGui::Selectable(f.selectItems[i].c_str(), data == i))
                                {
                                    data = i;
                                }

                                if (data == i)
                                {
                                    ImGui::SetItemDefaultFocus();
                                }
                            }
                            ImGui::EndListBox();
                        }
                        f.data.integer = data;
                    }
                    break;
                    default:
                        break;
                    }
                }
                ImGui::PopID();
            }

            ImGui::End();
        }

        // Code Editor windows
        for (auto &w : g_openedEditors)
        {
            ImGui::Begin((w.first + "##txt").c_str(), w.second.winOpened,
                         (ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar));
            ImGui::SetWindowSize(ImVec2(yg::input::get(yg::input::WINDOW_WIDTH) * 0.5f,
                                        yg::input::get(yg::input::WINDOW_HEIGHT) * 0.75f),
                                 ImGuiCond_FirstUseEver);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Save"))
                    {
                        std::string textToSave = w.second.editor.GetText();
                        yg::file::writeFile(w.first, &(textToSave[0]), textToSave.size());
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            w.second.editor.Render("TextEditor");
            ImGui::End();
        }

        // Code Hex Editor windows
        for (auto &w : g_openedHexEditors)
        {
            ImGui::Begin((w.first + "##hex").c_str(), w.second.winOpened,
                         (ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_MenuBar));
            ImGui::SetWindowSize(ImVec2(yg::input::get(yg::input::WINDOW_WIDTH) * 0.5f,
                                        yg::input::get(yg::input::WINDOW_HEIGHT) * 0.75f),
                                 ImGuiCond_FirstUseEver);

            if (ImGui::BeginMenuBar())
            {
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Save"))
                    {
                        yg::file::writeFile(w.first, &(w.second.data[0]), w.second.data.size());
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar();
            }

            w.second.editor.DrawContents(&(w.second.data[0]), w.second.data.size());
            ImGui::End();
        }
    }

    void initLua()
    {
        if (g_Lua == nullptr)
        {
            // initialize Lua, register C++ components
            g_Lua = luaL_newstate();
            luaL_openlibs(g_Lua);
            mygame::registerLua(g_Lua);

            // load lua script
            std::vector<uint8_t> data;
            if (yg::file::readFile(g_luaScriptName, data) == 0)
            {
                bool luaInitSuccess = true;

                // add null terminator for luaL_dostring()
                data.push_back((uint8_t)0);

                // run the lua script
                if (luaL_dostring(g_Lua, (char *)(&data[0])) != 0)
                {
                    yg::log::error("Lua error: %v", lua_tostring(g_Lua, -1));
                    luaInitSuccess = false;
                }
                else
                {
                    // Lua: call init()
                    luabridge::LuaRef lInit = luabridge::getGlobal(g_Lua, "init");
                    if (lInit.isFunction())
                    {
                        try
                        {
                            lInit();
                        }
                        catch (luabridge::LuaException const &e)
                        {
                            yg::log::error("initLua(): Lua exception: %v", std::string(e.what()));
                            luaInitSuccess = false;
                        }
                    }
                }

                if (!luaInitSuccess)
                {
                    shutdownLua();
                }
            }
            else
            {
                yg::log::error("failed to load Lua code from file %v", g_luaScriptName);
            }
        }
        else
        {
            yg::log::error("initLua(): g_Lua != nullptr");
        }
    }

    void tickLua()
    {
        bool luaTickSuccess = true;

        if (g_Lua != nullptr)
        {
            // Lua: call tick()
            luabridge::LuaRef lTick = luabridge::getGlobal(g_Lua, "tick");
            if (lTick.isFunction())
            {
                try
                {
                    lTick();
                }
                catch (luabridge::LuaException const &e)
                {
                    yg::log::error("tickLua(): Lua exception: %v", std::string(e.what()));
                    luaTickSuccess = false;
                }
            }
        }

        if (!luaTickSuccess)
        {
            shutdownLua();
        }
    }

    void shutdownLua()
    {
        if (g_Lua != nullptr)
        {
            // Lua: call shutdown()
            // the extra scope is crucial. lShutdown has to be destroyed before
            // lua_close() is called.
            {
                luabridge::LuaRef lShutdown = luabridge::getGlobal(g_Lua, "shutdown");
                if (lShutdown.isFunction())
                {
                    try
                    {
                        lShutdown();
                    }
                    catch (luabridge::LuaException const &e)
                    {
                        yg::log::error("shutdownLua(): Lua exception: %v", std::string(e.what()));
                    }
                }
            }

            lua_close(g_Lua);
            g_Lua = nullptr;
        }
        else
        {
            yg::log::error("shutdownLua(): g_Lua == nullptr");
        }
    }
} // namespace mygame
