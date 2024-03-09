
#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <imgui-cocos.hpp>
#include "funcs/version.hpp"
#include "funcs/globalbtns.hpp"
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
bool CustomWave = false;

class FakeLayer : public CCLayer {
public:
    void OpenUi(CCObject*) {
        ShowUi=!ShowUi;
    }
};
void placeMobilehackmenu() {
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
}

$on_mod(Loaded) {
#ifndef NO_IMGUI
ImGuiCocos::get().setup([] {

    // this runs after imgui has been setup,
    // its a callback as imgui will be re initialized when toggling fullscreen,
    // so use this to setup any themes and or fonts!
    LoadedPos = false;
}).draw([] {
    if (!ShowUi) {
        return true;
    }
    if (!LoadedPos) {
        auto winSize = CCDirector::get()->getWinSize();
        ImGui::SetWindowSize({300,100});
        ImGui::SetWindowPos({winSize.width / 2,winSize.height});
        LoadedPos=true;
    }
    ImGui::Begin(fmt::format("Oppenheimer: {}", getver()).c_str());
    ImGui::Checkbox("Noclip",&Noclip);
    ImGui::Checkbox("Safe Mode",&SafeMode);
    ImGui::Checkbox("Auto Safe Mode",&AutoSafeMode);
    ImGui::Checkbox("Auto Safe Mode",&AutoSafeMode);
    ImGui::Checkbox("Hide Wave Trail",&NoWaveTail);
    ImGui::Checkbox("Solid Wave Trail",&SolidWaveTrail);
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
        
            #ifndef GEODE_IS_DESKTOP
            placeMobilehackmenu();
            #else
                 #ifndef GITHUB_ACTIONS
                    placeMobilehackmenu();
                #endif
            #endif
            
        return true;
    }

};

