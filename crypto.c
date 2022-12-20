#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

typedef struct {
    char mask;    /* char data will be bitwise AND with this */
    char lead;    /* start bytes of current char in utf-8 encoded character */
    uint32_t beg; /* beginning of codepoint range */
    uint32_t end; /* end of codepoint range */
    int bits_stored; /* the number of bits from the codepoint that fits in char */
}utf_t;

utf_t * utf[] = {
    /*             mask        lead        beg      end       bits */
    [0] = &(utf_t){0b00111111, 0b10000000, 0,       0,        6    },
    [1] = &(utf_t){0b01111111, 0b00000000, 0000,    0177,     7    },
    [2] = &(utf_t){0b00011111, 0b11000000, 0200,    03777,    5    },
    [3] = &(utf_t){0b00001111, 0b11100000, 04000,   0177777,  4    },
    [4] = &(utf_t){0b00000111, 0b11110000, 0200000, 04177777, 3    },
    &(utf_t){0},
};

/* All lengths are in bytes */
int codepoint_len(const uint32_t cp); /* len of associated utf-8 char */
int utf8_len(const char ch);          /* len of utf-8 encoded char */

char *to_utf8(const uint32_t cp);
uint32_t to_utf32(const char chr[4]);

int codepoint_len(const uint32_t cp)
{
    int len = 0;
    for(utf_t **u = utf; *u; ++u) {
        if((cp >= (*u)->beg) && (cp <= (*u)->end)) {
            break;
        }
        ++len;
    }
    if(len > 4) /* Out of bounds */
        exit(1);

    return len;
}

int utf8_len(const char ch)
{
    int len = 0;
    for(utf_t **u = utf; *u; ++u) {
        if((ch & ~(*u)->mask) == (*u)->lead) {
            break;
        }
        ++len;
    }
    if(len > 4) { /* Malformed leading byte */
        exit(1);
    }
    return len;
}

char *to_utf8(const uint32_t cp)
{
    static char ret[5];
    const int bytes = codepoint_len(cp);

    int shift = utf[0]->bits_stored * (bytes - 1);
    ret[0] = (cp >> shift & utf[bytes]->mask) | utf[bytes]->lead;
    shift -= utf[0]->bits_stored;
    for(int i = 1; i < bytes; ++i) {
        ret[i] = (cp >> shift & utf[0]->mask) | utf[0]->lead;
        shift -= utf[0]->bits_stored;
    }
    ret[bytes] = '\0';
    return ret;
}

uint32_t to_utf32(const char chr[4])
{
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
    uint32_t* key = malloc(sizeof(uint32_t)*8500);

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
    uint32_t* inputUTF32 = malloc(sizeof(uint32_t) * 8500);
    unsigned char buffer[8500];
    fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), stdin);

    unsigned char* in;
    for (in = buffer; *in != '\n'; in += utf8_len(*in)) {
        inputUTF32[(*n)++] = to_utf32(in);
    }

    return inputUTF32;
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Usage:\n  encrypting: %s -c\n  decrypting: %s -d\n", argv[0], argv[0]);
        return 1;
    }

    uint32_t* key = malloc(sizeof(uint32_t) * 8500);
    uint32_t* inputUTF32 = malloc(sizeof(uint32_t) * 8500);
    uint32_t* aux = malloc(sizeof(uint32_t) * 8500);

    int inputSize = 0;
    key = generateKey();
    inputUTF32 = readText(&inputSize);

    bcopy(inputUTF32, aux, inputSize*4);

    for (int i = 0; i < inputSize; i++) {
        if (strcmp(argv[1], "-c") == 0) {

            if (i < 10)
                inputUTF32[i] = oneTimePad(inputUTF32[i], key[i]);
            else 
                inputUTF32[i] = oneTimePad(inputUTF32[i], aux[i - 10]);

            inputUTF32[i] += (0x3061);
        } else {
            inputUTF32[i] -= (0x3061);

            if (i < 10)
                inputUTF32[i] = oneTimePad(inputUTF32[i], key[i]);
            else
                inputUTF32[i] = oneTimePad(inputUTF32[i], inputUTF32[i - 10]);
        }
    }

    for (int i = 0; i < inputSize; i++) {
        printf("%s", to_utf8(inputUTF32[i]));
    }
    printf("\n");
}
