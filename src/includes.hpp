#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;

#ifndef GEODE_IS_MACOS
#include "funcs/Draggedbtn.hpp"
#endif

// Mods
#include "FileMods/Noclip.cpp"
#include "FileMods/Safemode.cpp"
#include "FileMods/SolidWaveTrail.cpp"
#include "FileMods/WaveTrails.cpp"
// Not on Macos
#include "FileMods/StartposSwitcher.cpp"

