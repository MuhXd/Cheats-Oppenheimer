#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include "../funcs/globalbtns.hpp"
#include <Geode/modify/PlayerObject.hpp>


struct $modify(PlayerObject) {
    bool N_DartObject;

    void toggleDartMode(bool p0, bool p1) {
        m_fields->N_DartObject = p0;
        PlayerObject::toggleDartMode(p0, p1);
    }
    void activateStreak() { 
        if (m_fields->N_DartObject && NoWaveTail) return;
          if (m_fields->N_DartObject && CustomWave) {
            auto object = m_fields->m_waveTrail;  
            ccColor3B myColor = {255, 0, 0};
            object->setColor(myColor);
        }
        PlayerObject::activateStreak();
    }
};


