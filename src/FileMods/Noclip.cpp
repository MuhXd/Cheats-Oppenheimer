#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
using namespace geode::prelude;
#include "../funcs/globalbtns.hpp"

using namespace geode::prelude;


class $modify (NoclipLayer, PlayLayer) {
    GameObject* disableCheat;
    bool m_noclip = Noclip;

    void destroyPlayer(PlayerObject * p0, GameObject * p1) {
        if (!m_fields->disableCheat)
            m_fields->disableCheat = p1;

        m_fields->m_noclip = Noclip;
        if (!Noclip || (m_fields->disableCheat == p1))
            PlayLayer::destroyPlayer(p0, p1);
    }
};


