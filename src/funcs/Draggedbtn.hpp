#pragma once
#include <Geode/Geode.hpp>
#include "globalbtns.hpp"
#include <Geode/ui/BasedButtonSprite.hpp>
using namespace geode::prelude;

class Dragged : public CCMenu {
protected:
    bool isHovering;
    float width;
    static inline bool hasPos = false;
    static inline CCPoint position = ccp(32, CCDirector::get()->getWinSize().height / 2);
    static inline bool dragging = false;
    static inline bool doingThing = false;
public:
    static Dragged* create(float width, SEL_MenuHandler selector) {
        auto ret = new Dragged();
        if (ret && ret->init(width, selector)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }

    bool init(float width, SEL_MenuHandler selector) {
        this->width = width;
        auto menu = CCMenu::create();
    	menu->setPosition({0, 0});
        auto l = CCLabelBMFont::create(" ", "bigFont.fnt");
        auto ADDBUTTONFAKE = CCSprite::createWithSpriteFrameName("oppenheimer.png"_spr);
        ADDBUTTONFAKE->setAnchorPoint(ccp(0.5f, 0.5f));
        l->setAnchorPoint(ccp(0.5f, 0.35f));
        auto btn = CircleButtonSprite::create(l, CircleBaseColor::Green);
        ADDBUTTONFAKE->setPosition(l->getPosition());
        btn->setID("MainFunction"_spr);
        menu->addChild(btn);
        btn->addChild(ADDBUTTONFAKE);
        menu->setID("HOLDID"_spr);
        menu->setPositionX(Mod::get()->getSavedValue<float>("posX",50));
        menu->setPositionY(Mod::get()->getSavedValue<float>("posY",50));
        this->addChild(menu);
        this->scheduleUpdate();
        this->setScale(1.0f);
        this->setAnchorPoint({0, 0});
        this->isHovering = false;
        this->setTouchPriority(-10000);
        menu->setTouchPriority(-10000);
        this->setTouchEnabled(true);
        this->setMouseEnabled(true);
        return true;
    }

virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {

            //auto d = DialogLayer::create(DialogObject::create("title", "text", 0, 1.0f, false, {255, 255, 255}), 0);'
           

            auto btn =this->getChildByIDRecursive("MainFunction"_spr);
            auto space =btn->convertTouchToNodeSpace(touch);

            doingThing = false;
            dragging = false;
            if (space.x > 0 && space.y > 0)
            {
                if (space.x < btn->getContentSize().width && space.y < btn->getContentSize().height)
                {
                    btn->stopAllActions();
                    btn->runAction(CCEaseInOut::create(CCScaleTo::create(0.1f, 0.8f), 2));
                    doingThing = true;
                }
            }

            return doingThing;
        }

        void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {

            if (doingThing)
            {
                    this->getChildByIDRecursive("MainFunction"_spr)->stopAllActions();
                    if (!dragging) {
                        ShowUi=!ShowUi;
                    };
                    this->getChildByIDRecursive("MainFunction"_spr)->runAction(CCEaseBackOut::create(CCScaleTo::create(0.35f, 1)));
                    doingThing = false;
                    Mod::get()->setSavedValue<float>("posX", position.x);
                    Mod::get()->setSavedValue<float>("posY", position.y);
            }
        }
        void update(float dt) {
            this->setTouchEnabled(true);
            this->setMouseEnabled(true);
        }
         void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) {
          

            if (doingThing && (this->getChildByIDRecursive("MainFunction"_spr)->numberOfRunningActions() == 0))
            {
                if (this->getChildByIDRecursive("MainFunction"_spr)->getPosition().getDistance(touch->getLocation()) > 7.5f)
                {
                    dragging = true;
                }

               

                if (dragging)
                {
                    position = touch->getLocation();
                     this->getChildByIDRecursive("HOLDID"_spr)->setPosition(position);
                }
            }
        }

   

};
