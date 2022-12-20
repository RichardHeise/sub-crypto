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
uint32_t to_cp(const char chr[4]);

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

uint32_t to_cp(const char chr[4])
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

void oneTimePad(uint32_t *charTxt, uint32_t charKey) {
    *charTxt = (*charTxt ^ charKey);
}

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Usage:\n  encrypting: %s -c\n  decrypting: %s -d\n", argv[0], argv[0]);
        return 1;
    }

    uint32_t key[8500];

    unsigned char date[10];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(date, "%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    unsigned char* in;
    int x = 0;
    for (in = date; *in != '\0'; in += utf8_len(*in)) {
        key[x++] = to_cp(in);
    }

    unsigned char buffer[8500];
    uint32_t codepoints[8500];
    fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), stdin);

    int n = 0;
    for (in = buffer; *in != '\n'; in += utf8_len(*in)) {
        codepoints[n++] = to_cp(in);
    }

    uint32_t aux[8500];
    bcopy(codepoints, aux, n*4);

    for (int i = 0; i < n; i++) {
        if (strcmp(argv[1], "-c") == 0) {

            if (i < 10)
                oneTimePad(&codepoints[i], key[i]);
            else 
                oneTimePad(&codepoints[i], aux[i - 10]);

            codepoints[i] += (0x3000 + 0x61);
        } else {
            codepoints[i] -= (0x3000 + 0x61);
            if (i < 10)
                oneTimePad(&codepoints[i], key[i]);
            else
                oneTimePad(&codepoints[i], codepoints[i - 10]);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s", to_utf8(codepoints[i]));
    }
    printf("\n");
}
