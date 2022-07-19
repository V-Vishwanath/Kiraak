
#ifndef KIRAAK_TOKENTYPES_H
#define KIRAAK_TOKENTYPES_H

enum class TOKENTYPE {
    EOF_, ERR_,

    PLUS, MINUS, STAR, POW, MOD, DIV_I, DIV_D,

    LPAREN, RPAREN, COMMA,

    NONE, BOOL, INT, DOUBLE,

    VAR,
    KW_BOLETHO, KW_BANAKE, KW_RAKH,

    KW_HAI,
    KW_JITTA,
    KW_KE, KW_BARAABAR,
    KW_SE, KW_CHOTA, KW_BADA,
    GTE_LTE_PREFIX, LTE, GTE, NE,

    KW_AUR, KW_YA, KW_NAHI,

    KW_AGAR, KW_PHIR, ELSE, KW_THO,

    KW_FOR, KW_FROM, KW_TO, KW_STEP,
};

#endif //KIRAAK_TOKENTYPES_H
