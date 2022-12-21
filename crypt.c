// Autores:
// Dante Eleutério dos Santos (GRR20206686)
// Richard Fernando Heise Ferreira (GRR20191053)

// THIS CODE IS *HEAVILY* INSPIRED BY https://rosettacode.org/wiki/UTF-8_encode_and_decode#C

#include "crypt.h"

typedef struct {
    char mask;    /* char data will be bitwise AND with this */
    char lead;    /* start bytes of current char in utf-8 encoded character */
    uint32_t beg; /* beginning of codepoint range */
    uint32_t end; /* end of codepoint range */
    int bits_stored; /* the number of bits from the codepoint that fits in char */
}utf_t;

utf_t* utf[] = {
    /*             mask        lead        beg      end       bits */
    [0] = &(utf_t){0b00111111, 0b10000000, 0,       0,        6    },
    [1] = &(utf_t){0b01111111, 0b00000000, 0000,    0177,     7    },
    [2] = &(utf_t){0b00011111, 0b11000000, 0200,    03777,    5    },
    [3] = &(utf_t){0b00001111, 0b11100000, 04000,   0177777,  4    },
    [4] = &(utf_t){0b00000111, 0b11110000, 0200000, 04177777, 3    },
    &(utf_t){0},
};

int utf32_len(const uint32_t utf32_char) {

    int len = 0;
    for(utf_t **char_p = utf; *char_p; ++char_p) {
        if((utf32_char >= (*char_p)->beg) && (utf32_char <= (*char_p)->end)) {
            break;
        }
        ++len;
    }
    if(len > 4) /* Out of bounds */
        exit(1);

    return len;
}

int utf8_len(const char utf8_char) {

    int len = 0;
    for(utf_t **char_p = utf; *char_p; ++char_p) {
        if((utf8_char & ~(*char_p)->mask) == (*char_p)->lead) {
            break;
        }
        ++len;
    }
    if(len > 4) { /* Malformed leading byte */
        exit(1);
    }
    return len;
}


char *to_utf8(const uint32_t utf32_char) {

    static char ret[5];
    const int bytes = utf32_len(utf32_char);

    int shift = utf[0]->bits_stored * (bytes - 1);
    ret[0] = (utf32_char >> shift & utf[bytes]->mask) | utf[bytes]->lead;
    shift -= utf[0]->bits_stored;
    for(int i = 1; i < bytes; ++i) {
        ret[i] = (utf32_char >> shift & utf[0]->mask) | utf[0]->lead;
        shift -= utf[0]->bits_stored;
    }
    ret[bytes] = '\0';
    return ret;
}


uint32_t to_utf32(const char chr[4]) {

    int bytes = utf8_len(*chr);
    int shift = utf[0]->bits_stored * (bytes - 1);
    uint32_t codep = (*chr++ & utf[bytes]->mask) << shift;

    for(int i = 1; i < bytes; ++i, ++chr) {
        shift -= utf[0]->bits_stored;
        codep |= ((char)*chr & utf[0]->mask) << shift;
    }

    return codep;
}


uint32_t oneTimePad(uint32_t charTxt, uint32_t charKey) {
    return (charTxt ^ charKey);
}

uint32_t* generateKey() {
    uint32_t* key = malloc(sizeof(uint32_t)*MAX_ALLOC);

    unsigned char date[10];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(date, "%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    unsigned char* in;
    int x = 0;
    for (in = date; *in != '\0'; in += utf8_len(*in)) {
        key[x++] = to_utf32(in);
    }

    return key;
}


uint32_t* readText(int* n) {
    uint32_t* inputUTF32 = malloc(sizeof(uint32_t) * MAX_ALLOC);
    unsigned char buffer[MAX_ALLOC];
    fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), stdin);

    unsigned char* in;
    for (in = buffer; *in != '\n'; in += utf8_len(*in)) {
        inputUTF32[(*n)++] = to_utf32(in);
    }

    return inputUTF32;
}
