
#pragma once
#include <Geode/Geode.hpp>
#include "globalbtns.hpp"

static bool SafeModeMods(bool t) {
    if (t) {
        if (!AutoSafeMode) {
            return false;
        }
    };
    return Noclip;
};