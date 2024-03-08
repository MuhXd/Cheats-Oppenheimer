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
      return fmt::format("Windows");
   #else 
      #ifdef GEODE_IS_ANDROID
         return fmt::format("Android");
      #else
         #ifdef GEODE_IS_IOS
            return fmt::format("IOS");
         #endif
         #ifdef GEODE_IS_MACOS
            return fmt::format("MAC-OS");
         #endif
      #endif
   #endif
};

static std::string getver() {
auto version = fmt::format("");

return fmt::format("{} - {}", binfo(),Platform());
};