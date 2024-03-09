#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/GJGameLevel.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/binding/GameStatsManager.hpp>
#include <Geode/modify/GameStatsManager.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
#include <Geode/modify/UILayer.hpp>
#include "../funcs/globalbtns.hpp"
#include "../funcs/AutoSafeMod.hpp"
#include <Geode/modify/PlayerObject.hpp>

using namespace geode::prelude;

EndLevelLayer* HasUiUp = nullptr;
UILayer* Ui = nullptr;
bool Sm_Mod = true;


class $modify(GJGameLevel) {
    bool init() {
        if (!GJGameLevel::init())
            return false;
        return true;
    };
    void savePercentage(int p0, bool p1, int p2, int p3, bool p4) {
        if (!SafeMode && (!SafeModeMods(true) ) ) {
            GJGameLevel::savePercentage(p0, p1, p2, p3, p4);
        }
    }
};
void updatePractice(auto l) {
if (!PlayLayer::get()) return;
     // display practice mode buttons bugfix
            if (auto menu = l->getChildByID("checkpoint-menu")) {
                if (HasUiUp) {
                    menu->setVisible(false);
                }
                else {
                    menu->setVisible(PlayLayer::get()->m_isPracticeMode);
                };
            };
}



class $modify(UILayer) {
    bool init(GJBaseGameLayer* layer) {
        if (!UILayer::init(layer))
            return false;

        // delay by a single frame
        geode::Loader::get()->queueInMainThread([this] {
            Ui = this;
            updatePractice(this);
        });

        return true;
    }
};

class $modify(PlayLayer) {
    void showNewBest(bool po, int p1, int p2, bool p3, bool p4, bool p5) {
          if (!SafeMode && (!SafeModeMods(true) ) ) {
            PlayLayer::showNewBest(po, p1, p2 , p3 , p4 , p5);
          }
    };
    void togglePracticeMode(bool enabled) {
        PlayLayer::togglePracticeMode(enabled);
    }
    void levelComplete() {
        if (SafeMode || (SafeModeMods(true)) ) {
            PlayLayer::togglePracticeMode(true);
            Sm_Mod = true;
        }
        else {
            Sm_Mod = false;
        }
        PlayLayer::levelComplete();
    };
    void resetLevel() {
        HasUiUp = nullptr;
          if (Ui) {
            updatePractice(Ui);
        }
        PlayLayer::resetLevel();
    }
};
class $modify(endLayer,EndLevelLayer){
static void onModify(auto & self)
    {
       (void) self.setHookPriority("EndLevelLayer::init", -9999);
    };
    void onReplay(CCObject* Sender) {
        EndLevelLayer::onReplay(Sender);
        HasUiUp = nullptr;
        if (Ui) {
            updatePractice(Ui);
        }
    }
    void showLayer(bool p0) {
 	    EndLevelLayer::showLayer(p0);
        HasUiUp = this;
        if (!Sm_Mod) {
            return;
        }
        if (Ui) {
            updatePractice(Ui);
        }
        auto Layer = this->getChildByID("main-layer");
        if  (auto pract = Layer->getChildByID("practice-complete-text")) {
			pract->setVisible(false);
            CCSprite* SafeMode = nullptr;
            if (SafeModeMods(false)) {
                SafeMode = CCSprite::createWithSpriteFrameName("Bad_SafeMode.png"_spr);
            }
            else {
                SafeMode = CCSprite::createWithSpriteFrameName("Good_SafeMode.png"_spr);
            };

            SafeMode->setID("Safe-complete-text"_spr);
            Layer->addChild(SafeMode);
            SafeMode->setPosition(pract->getPosition());
		}
        if (auto CompleteText = Layer->getChildByID("complete-message")) {
            CompleteText->setVisible(false);
           CCLabelBMFont* weed = CCLabelBMFont::create("SAFE MODE ENABLED!", "bigFont.fnt");
			weed->setAnchorPoint(ccp(0.480f,1.0f));
			weed->setPosition(CompleteText->getPosition());
			weed->setScale(0.5f);	
			weed->setID("complete-message"_spr); // weed_spr
			Layer->addChild(weed);
        }
        }
};