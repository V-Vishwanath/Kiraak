
#ifndef KIRAAK_KEYWORDS_H
#define KIRAAK_KEYWORDS_H


#include "TokenTypes.h"

#include <string>
#include <unordered_map>


inline std::unordered_map<std::string, TOKENTYPE> KEYWORD = { // NOLINT(cert-err58-cpp)
    { "khaali", TOKENTYPE::NONE },
    { "sahi", TOKENTYPE::BOOL }, { "galat", TOKENTYPE::BOOL },

    { "banake", TOKENTYPE::KW_BANAKE },
    { "rakh", TOKENTYPE::KW_RAKH },

    { "hai", TOKENTYPE::KW_HAI },

    { "boletho", TOKENTYPE::KW_BOLETHO },

    { "ke", TOKENTYPE::KW_KE },
    { "baraabar", TOKENTYPE::KW_BARAABAR },

    { "se", TOKENTYPE::KW_SE },
    { "jitta", TOKENTYPE::KW_JITTA },

    { "chota", TOKENTYPE::KW_CHOTA },
    { "bada", TOKENTYPE::KW_BADA },

    { "ya", TOKENTYPE::KW_YA },
    { "aur", TOKENTYPE::KW_AUR },
    { "nahi", TOKENTYPE::KW_NAHI },

    { "agar", TOKENTYPE::KW_AGAR },
    { "phir", TOKENTYPE::KW_PHIR },
    { "tho", TOKENTYPE::KW_THO },
};

#endif //KIRAAK_KEYWORDS_H
