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


static bool Sm_Mod = true;
static bool HidePush = false;


class $modify(GJGameLevel) {
    void savePercentage(int p0, bool p1, int p2, int p3, bool p4) {
        if (!SafeMode && (!SafeModeMods(true))) {
            GJGameLevel::savePercentage(p0, p1, p2, p3, p4);
        }
    }
};
static void updatePractice() {
    if (!PlayLayer::get()) return;
    if (PlayLayer::get()->m_uiLayer == nullptr) {
        return;
    }
    // display practice mode buttons bugfix
    if (auto menu = PlayLayer::get()->m_uiLayer->getChildByID("checkpoint-menu")) {
        if (!menu) return;
        if (HasUiUp || HidePush) menu->setVisible(false); else menu->setVisible(PlayLayer::get()->m_isPracticeMode);
    };
}



class $modify(UILayer) {
    bool init(GJBaseGameLayer* layer) {
        if (!UILayer::init(layer))
            return false;
       
        // delay by a single frame
        geode::Loader::get()->queueInMainThread([this] {
            updatePractice();
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
    void levelComplete() {
        HidePush = true;
        if (SafeMode || (SafeModeMods(true)) ) {
            Sm_Mod = true;
            PlayLayer::get()->m_isTestMode = true;     
        }
        else {
            Sm_Mod = false;
        }
        geode::Loader::get()->queueInMainThread([this] {
            if (PlayLayer::get()->m_uiLayer) {
                updatePractice();
            }
        });
        PlayLayer::levelComplete();
    };
    void resetLevel() {
        HasUiUp = nullptr;
        HidePush = false;
        geode::Loader::get()->queueInMainThread([this] {
             if (PlayLayer::get()->m_uiLayer) {
                updatePractice();
             }
         });
        
        PlayLayer::resetLevel();
    }
};
class $modify(endLayer,EndLevelLayer){
static void onModify(auto & self)
    {
       (void) self.setHookPriority("EndLevelLayer::showLayer", -100);
    };
       #ifndef GEODE_IS_MACOS
    void onReplay(CCObject* Sender) {
        EndLevelLayer::onReplay(Sender);
        HasUiUp = nullptr;
        HidePush = false;
        geode::Loader::get()->queueInMainThread([this] {
            if (PlayLayer::get()->m_uiLayer) {
             updatePractice();
            }
         });
        
    }
    #endif
    void showLayer(bool p0) {
 	    EndLevelLayer::showLayer(p0);
        HasUiUp = this;
        geode::Loader::get()->queueInMainThread([this] {
            if (PlayLayer::get()->m_uiLayer) {
                updatePractice();
            }
        });
        HidePush = false;
        if (!Sm_Mod) {
            return;
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
         if  (auto levelcomp = Layer->getChildByID("level-complete-text")) {
			levelcomp->setVisible(false);
            CCSprite* SafeMode = nullptr;
            if (SafeModeMods(false)) {
                SafeMode = CCSprite::createWithSpriteFrameName("Bad_SafeMode.png"_spr);
            }
            else {
                SafeMode = CCSprite::createWithSpriteFrameName("Good_SafeMode.png"_spr);
            };

            SafeMode->setID("Safe-complete-text"_spr);
            Layer->addChild(SafeMode);
            SafeMode->setPosition(levelcomp->getPosition());
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
