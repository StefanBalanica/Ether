#pragma once
#include <string_view>
constexpr std::string_view BLUE = "\033[34m";
constexpr std::string_view RED = "\033[31m";
constexpr std::string_view RESET = "\033[0m";

enum class GameMode {
    Modul_antrenament,
    Duelul_vrajitorilor,
    Duelul_elementelor,
    Duelul_elemWizz
};
