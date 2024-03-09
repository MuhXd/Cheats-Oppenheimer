#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include "../funcs/globalbtns.hpp"
#include <Geode/modify/CCDrawNode.hpp>


// Solid Wave Trail
struct $modify(CCDrawNode) {
#ifndef GEODE_IS_MACOS
    bool drawPolygon(CCPoint *p0, unsigned int p1, const ccColor4F &p2, float p3, const ccColor4F &p4) {
        if (!SolidWaveTrail) return CCDrawNode::drawPolygon(p0,p1,p2,p3,p4);
        if (p2.r == 1.F && p2.g == 1.F && p2.b == 1.F && p2.a != 1.F) return true; 
        this->setBlendFunc(CCSprite::create()->getBlendFunc());
        this->setZOrder(-1);
        return CCDrawNode::drawPolygon(p0,p1,p2,p3,p4);
    }
#else 
    void drawPolygon(CCPoint *p0, unsigned int p1, const ccColor4F &p2, float p3, const ccColor4F &p4) {
        if (!SolidWaveTrail) return CCDrawNode::drawPolygon(p0,p1,p2,p3,p4);
        if (p2.r == 1.F && p2.g == 1.F && p2.b == 1.F && p2.a != 1.F) return; 
        this->setBlendFunc(CCSprite::create()->getBlendFunc());
        this->setZOrder(-1);
        return CCDrawNode::drawPolygon(p0,p1,p2,p3,p4);
    }
#endif
};