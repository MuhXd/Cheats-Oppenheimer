#ifndef GEODE_IS_MACOS

#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/StartPosObject.hpp>
#include <Geode/modify/UILayer.hpp>
#include "../funcs/globalbtns.hpp"

using namespace geode::prelude;

static std::vector<StartPosObject*> startPos = {};
static int selectedStartpos = 0;

static CCLabelBMFont* label;
static CCMenu* switcher;
static void FadeObjectIn(auto spr,int to, int time, bool StopAllActions = false) {
    if (!spr) {
        return;
    }
    if (StopAllActions) {
        spr->stopAllActions();
    };

    spr->runAction(CCFadeTo::create(time, to));
}
static void FadeObjectOut(auto spr,int to, int time, bool StopAllActions = false) {
    if (!spr || !dynamic_cast<CCNodeRGBA*>(spr)) {
        return;
    }
     if (StopAllActions) {
        spr->stopAllActions();
    };
    static_cast<CCMenuItemSpriteExtra*>(spr)->setOpacity(to);
}
static void ActivateStartPos(int incBy, bool actuallySwitch = true)
{
     
    selectedStartpos += incBy;

    if (selectedStartpos < -1)
        selectedStartpos = startPos.size() - 1;
        
    if (selectedStartpos >= startPos.size())
        selectedStartpos = -1;
    
    if (actuallySwitch)
    {
        StartPosObject* startPosObject = selectedStartpos == -1 ? nullptr : startPos[selectedStartpos];
        // No Bindings >:( 
       #ifdef GEODE_IS_WINDOWS
            int* startPosCheckpoint = (int*)GameManager::get()->getPlayLayer() + 2949;
            *startPosCheckpoint = 0;
        #else
            GameManager::get()->getPlayLayer()->removeAllCheckpoints();
        #endif
        if (PlayLayer::get()->m_isPracticeMode) {
            // test
        };

        if (!startPosObject && selectedStartpos != -1 || !StartposSwitcher) {
            if (!StartposSwitcher && startPosObject) {
                 PlayLayer::get()->setStartPosObject(nullptr);

                 GameManager::get()->getPlayLayer()->resetLevel();


                 GameManager::get()->getPlayLayer()->startMusic();
            };
            return;
        }

       
        PlayLayer::get()->setStartPosObject(startPosObject);

        GameManager::get()->getPlayLayer()->resetLevel();


        GameManager::get()->getPlayLayer()->startMusic();
    }
    label->setString(fmt::format("{} / {}",selectedStartpos + 1,startPos.size()).c_str() );
}



class StartPosStuff : public CCLayer {
public:
    void Switch(CCObject* sender) {
        ActivateStartPos(sender->getTag());
    }
};

class $modify(PlayLayer)
{
    static PlayLayer* create(GJGameLevel* p0, bool p1, bool p2)
    {
        startPos.clear();
        selectedStartpos = -1;
        auto res = PlayLayer::create(p0, p1, p2);

        if (startPos.size() == 0 || !StartposSwitcher) {
            if (auto ui = PlayLayer::get()->m_uiLayer->getChildByID("startpos-switcher"_spr)) {
                 ui->setVisible(false);
            }
        }
        ActivateStartPos(0, false);

        return res;
    }
};

class $modify (UILayer)
{

    bool init(GJBaseGameLayer* ui)
    {
        if (!UILayer::init(ui)) return false;

        if (!typeinfo_cast<PlayLayer*>(ui)) return true;
        
        if (auto startpos = this->getChildByID("startpos-switcher"_spr)) {
            startpos->removeFromParent();
            startpos->release();
        };

        switcher = CCMenu::create();
        switcher->setPosition(ccp(CCDirector::get()->getWinSize().width / 2, 16));
        switcher->setContentSize(ccp(0, 0));
        switcher->setScale(0.475f);
        switcher->setVisible(true);
        switcher->setID("startpos-switcher"_spr);

        label = CCLabelBMFont::create("0/0", "bigFont.fnt");
        label->setPosition(ccp(0, 0));
        label->setOpacity(50);
        label->setID("Text");

        auto leftSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
        leftSpr->setOpacity(50);

        auto leftBtn = CCMenuItemSpriteExtra::create(leftSpr, switcher, menu_selector(StartPosStuff::Switch));
        leftBtn->setContentSize(leftBtn->getContentSize() * 2.5);
        leftSpr->setPosition(leftBtn->getContentSize() / 2);
        leftBtn->setPosition(ccp(-85, 0));
        leftBtn->setTag(-1);
        leftBtn->setID("L_Arrow");
        auto rightSpr = CCSprite::createWithSpriteFrameName("GJ_arrow_01_001.png");
        rightSpr->setFlipX(true);
        rightSpr->setOpacity(50);

        auto rightBtn = CCMenuItemSpriteExtra::create(rightSpr, switcher, menu_selector(StartPosStuff::Switch));
        rightBtn->setContentSize(rightBtn->getContentSize() * 2.5);
        rightSpr->setPosition(rightBtn->getContentSize() / 2);
        rightBtn->setPosition(ccp(85, 0));
        rightBtn->setTag(1);
        rightBtn->setID("R_Arrow");

        switcher->addChild(label);
        switcher->addChild(leftBtn);
        switcher->addChild(rightBtn);
        this->addChild(switcher);
        return true;
    }
};

class $modify (StartPosObject)
{
    virtual bool init()
    {
        if (!StartPosObject::init())
            return false;

        startPos.push_back(static_cast<StartPosObject*>(this));
        selectedStartpos = -1;

        return true;
    }
};

#endif