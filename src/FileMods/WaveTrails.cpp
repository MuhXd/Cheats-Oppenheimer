#pragma once 
#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include "../funcs/globalbtns.hpp"
#include <Geode/modify/PlayerObject.hpp>



class $modify(PlayerObject) {
    bool N_DartObject;

    void toggleDartMode(bool p0, bool p1) {
        m_fields->N_DartObject = p0;
        PlayerObject::toggleDartMode(p0, p1);
    }
    void activateStreak() { 
        if (m_fields->N_DartObject && NoWaveTail) return;
        if (PlayerObject::m_waveTrail && CustomWave){
                    PlayerObject::m_waveTrail->setColor(static_cast<ccColor3B>(color));
        }
        PlayerObject::activateStreak();
    }
};
