// Autores:
// Dante Eleutério dos Santos (GRR20206686)
// Richard Fernando Heise Ferreira (GRR20191053)

#ifndef __CRYPT__
#define __CRYPT__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#define MAX_ALLOC 5000

/* All lengths are in bytes */
int codepoint_len(const uint32_t cp); /* len of associated utf-8 char */
int utf8_len(const char ch);          /* len of utf-8 encoded char */
char *to_utf8(const uint32_t cp);
uint32_t to_utf32(const char chr[4]);
uint32_t oneTimePad(uint32_t charTxt, uint32_t charKey);
uint32_t* generateKey();
uint32_t* readText(int* n);

#endif