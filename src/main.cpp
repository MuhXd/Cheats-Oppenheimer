
#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <imgui-cocos.hpp>
#include "funcs/version.hpp"
#include "funcs/globalbtns.hpp"
#include "funcs/theme.hpp"
#include "includes.hpp"
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/MenuLayer.hpp>

bool Noclip = false;
bool LoadedPos = true;
bool ShowUi = true;
bool SafeMode = false;
bool AutoSafeMode = false;
bool doingThing = false;
bool SolidWaveTrail = false; 
bool NoWaveTail = false; 
bool dragging = false;
bool placedbtn = false;
bool EnableButton = false;
bool NoWaveTrail = false;
bool oldstart = false;
bool CustomWave = false;
bool StartposSwitcher = false;
ccColor3B color = {255, 0, 0}; // Create a ccColor3B object
auto colorPointer = static_cast<ccColor3B>(color);
float imgui_color[3] = {colorPointer.r / 255.0f, colorPointer.g / 255.0f, colorPointer.b / 255.0f};

class FakeLayer : public CCLayer {
public:
    void OpenUi(CCObject*) {
        ShowUi=!ShowUi;
    }
};

void placeMobilehackmenu() {
#if !defined(GEODE_IS_DESKTOP) || !defined(GITHUB_ACTIONS) // If not mac then
            if (!placedbtn) {
                placedbtn=true;
                auto winSize = CCDirector::get()->getWinSize();
                auto btnee = Dragged::create(2, menu_selector(FakeLayer::OpenUi));
                btnee->setID("Oppenheimer"_spr);
                btnee->setPosition({0,0});
                btnee->setZOrder(20002);
                CCScene::get()->addChild(btnee);
                SceneManager::get()->keepAcrossScenes(btnee);
            }
#endif
}

void SettingsStuff(bool Save) {
    if (!Save) {
        // Saving settings
        Mod::get()->setSavedValue("StartposSwitcher", StartposSwitcher);
        Mod::get()->setSavedValue("Noclip", Noclip);
        Mod::get()->setSavedValue("SolidWaveTrail", SolidWaveTrail);
        Mod::get()->setSavedValue("Safe-Mode", SafeMode);
        Mod::get()->setSavedValue("Auto-Safe-Mode", AutoSafeMode);
        Mod::get()->setSavedValue("CustomWaveTrail", CustomWave);
        // Saving individual color components
        Mod::get()->setSavedValue("WaveColorR", imgui_color[0]);
        Mod::get()->setSavedValue("WaveColorG", imgui_color[1]);
        Mod::get()->setSavedValue("WaveColorB", imgui_color[2]);
    } else {
        // Loading settings
        StartposSwitcher = Mod::get()->getSavedValue<bool>("StartposSwitcher");
        Noclip = Mod::get()->getSavedValue<bool>("Noclip");
        SolidWaveTrail = Mod::get()->getSavedValue<bool>("SolidWaveTrail");
        SafeMode = Mod::get()->getSavedValue<bool>("Safe-Mode");
        AutoSafeMode = Mod::get()->getSavedValue<bool>("Auto-Safe-Mode");
        CustomWave = Mod::get()->getSavedValue<bool>("CustomWaveTrail");
        // Loading individual color components
        float waveColorR = Mod::get()->getSavedValue<float>("WaveColorR");
        float waveColorG = Mod::get()->getSavedValue<float>("WaveColorG");
        float waveColorB = Mod::get()->getSavedValue<float>("WaveColorB");
        color.r = static_cast<GLubyte>(waveColorR * 255.0f);
        color.g = static_cast<GLubyte>(waveColorG * 255.0f);
        color.b = static_cast<GLubyte>(waveColorB * 255.0f);
    }
}



$on_mod(Unloaded) {
SettingsStuff(false);
}
$on_mod(Loaded) {
#ifndef NO_IMGUI
SettingsStuff(true);
ImGuiCocos::get().setup([] {

    // this runs after imgui has been setup,
    // its a callback as imgui will be re initialized when toggling fullscreen,
    // so use this to setup any themes and or fonts!
    beforeRunTimeThemeify();
    LoadedPos = false;
}).draw([] {
    if (!ShowUi) {
        return true;
    }
    //ImGui::ShowStyleEditor();
    //ImVec4* colors = ImGui::GetStyle().Colors;
    if (!LoadedPos) {
        auto winSize = CCDirector::get()->getWinSize();
        ImGui::SetWindowSize({300,100});
        ImGui::SetWindowPos({winSize.width / 2,winSize.height});
        LoadedPos=true;
    }
    theme();
    ImGui::Begin(fmt::format("Oppenheimer: {}", getver()).c_str());
    ImGui::Checkbox("Noclip",&Noclip);
    ImGui::Checkbox("Safe Mode",&SafeMode);
    ImGui::Checkbox("Auto Safe Mode",&AutoSafeMode);
    if (ImGui::Checkbox("Startpos Switcher",&StartposSwitcher)) {
        if (oldstart != StartposSwitcher) {
            if (!PlayLayer::get()) {
                return  true;
            }
            if (auto ui = PlayLayer::get()->m_uiLayer->getChildByID("startpos-switcher"_spr)) {
                ui->setVisible(StartposSwitcher);
            }
            oldstart = StartposSwitcher;
        };
    };

    ImGui::Checkbox("Hide Wave Trail",&NoWaveTail);
    ImGui::Checkbox("Solid Wave Trail",&SolidWaveTrail);
  //  ImGui::Checkbox("No Wave Pulse",&NoWaveTrail);
    ImGui::Checkbox("Custom Wave Trail Color",&CustomWave);
   if (ImGui::ColorEdit3("Color", imgui_color)) {
        // If the color is edited, update the ccColor3B object
        color.r = static_cast<GLubyte>(imgui_color[0] * 255.0f);
        color.g = static_cast<GLubyte>(imgui_color[1] * 255.0f);
        color.b = static_cast<GLubyte>(imgui_color[2] * 255.0f);
    }
    ImGui::End();
    return true;
});
#endif
}

// setup keybinds
class $modify(CCKeyboardDispatcher) {
bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool arr) {
    if (down && (key == KEY_G)) {
        ShowUi = !ShowUi;
        return true;
    }
    return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, arr);
}
};


class $modify(MenuLayer) { 
    bool init() {
        if (!MenuLayer::init())
            return false;
    
        placeMobilehackmenu();
        return true;
    }

};

