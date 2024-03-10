#pragma once
#include <Geode/Geode.hpp>

static std::string binfo() {
   #ifdef GITHUB_ACTIONS
       return fmt::format("{})", Mod::get()->getVersion().toString());
   #else 
       return fmt::format("{}-TestBuild", Mod::get()->getVersion().toString());
   #endif
};
static std::string Platform() {
   #ifdef GEODE_IS_WINDOWS
      return "Windows";
   #else 
      #ifdef GEODE_IS_ANDROID
         return "Android";
      #else
         #ifdef GEODE_IS_IOS
            return "iOS";
         #endif
         #ifdef GEODE_IS_MACOS
            return "macOS";
         #endif
      #endif
   #endif
   return "Unknown (maybe a samsung toaster idk)";
};

static std::string getver() {
auto version = fmt::format("");

return fmt::format("{} - {}", binfo(),Platform());
};