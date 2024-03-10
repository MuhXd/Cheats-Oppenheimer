#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;
#include <imgui-cocos.hpp>
#include "version.hpp"
#include "globalbtns.hpp"

static float rgbvaluefloat(int lenumber) {return lenumber/255.f;}
static void beforeRunTimeThemeify() {
#ifndef GEODE_IS_DESKTOP
// Get the window size using CCDirector
auto winSize = CCDirector::get()->getWinSize();
float scaleFactor = winSize.width / 500.0f;  // use a screen size idk.
ImGui::GetIO().FontGlobalScale = scaleFactor;
ImGuiStyle& style = ImGui::GetStyle();
style.ScaleAllSizes(scaleFactor);
#endif
}

static void theme() {
ImGuiStyle& style = ImGui::GetStyle();
style.WindowRounding = 5.3f;
style.FrameRounding = 2.3f;
style.Colors[ImGuiCol_CheckMark] = ImVec4(0.04f, 1.00f, 0.00f, 1.00f);
style.Colors[ImGuiCol_TitleBg]  = ImVec4(0.64f, 0.80f, 0.58f, 1.00f);
style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.75f, 0.80f, 0.58f, 1.00f);
style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.39f, 0.96f, 0.34f, 0.51f);
style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.18f, 0.00f, 0.94f);
style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.18f, 0.00f, 0.94f);
}