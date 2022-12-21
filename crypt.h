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

// Function to return the length of a UTF-32 char
// Receives an uint32_t char
// Returns an int
int utf32_len(const uint32_t utf32_char); /* len of associated utf-8 char */

// Function to return the length of a UTF-8 char
// Receives a char
// Returns an int
int utf8_len(const char utf8_char);          /* len of utf-8 encoded char */

// Function to transform a UTF-32 char to UTF-8.
// Receives an uint32_t char.
// Returns a char pointer.
char *to_utf8(const uint32_t utf32_char);

// Function to transform a UTF-8 char to UTF-32.
// Receives a char array of size 4.
// Returns a uint32_t.
uint32_t to_utf32(const char chr[4]);

// Function to apply the One-Time Pad cryptography algorithm
// This only makes a XOR between a plaintext UTF-32 char and
// a key UTF-32 char.
// Receives two uint32_t chars.
// Returns a uint32_t.
uint32_t oneTimePad(uint32_t charTxt, uint32_t charKey);

// Function to generate a key.
// Creates a key based on the current day, month and year
// Returns a uint32_t pointer
uint32_t* generateKey();

// Function to read a text from stdin.
// Receives a int pointer to be update as size.
// Returns a uint32_t pointer.
uint32_t* readText(int* n);

#endif