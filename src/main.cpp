
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
bool doingThing = false;
bool dragging = false;
bool placedbtn = false;
bool EnableButton = false;

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
    ImGui::Begin(fmt::format("Oppenheimer: {}", getver()).c_str());
    ImGui::Checkbox("Noclip",&Noclip);
    ImGui::Checkbox("Enable Mobile Ui",&EnableButton);
    if (!LoadedPos) {
        auto winSize = CCDirector::get()->getWinSize();
        ImGui::SetWindowSize({300,100});
         ImGui::SetWindowPos({winSize.width / 2,winSize.height});
        LoadedPos=true;
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


auto getplat = Platform().c_str();
class $modify(MenuLayer) { 


bool init() {
        if (!MenuLayer::init())
            return false;
        
        if (getplat == "Android" || getplat == "IOS" || EnableButton) {
            placeMobilehackmenu();
        }
       
        return true;
    }

};

