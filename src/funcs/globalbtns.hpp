#pragma once
#include <Geode/Geode.hpp>
#include <Geode/modify/EndLevelLayer.hpp>
using namespace geode::prelude;
extern bool ShowUi; // Enable Ui

// output settings
static EndLevelLayer* HasUiUp = nullptr;
extern bool Noclip; // Noclip real
extern bool SolidWaveTrail; // Noclip real
extern bool NoWaveTail; // Noclip real
extern bool SafeMode; // Safe Mode
extern bool AutoSafeMode; // Auto Safe Mode
extern bool CustomWave;
extern bool NoWaveTrail;
extern bool StartposSwitcher;
extern ccColor3B color;