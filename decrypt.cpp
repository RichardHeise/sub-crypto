#include "utils.hpp"

#define READ_ERROR 1

int main() {
    printf("Hello, I'm an decrypter :D\n");
    printf("Waiting for text to DECRYPT via stdin, output on stdout\n");

    char* input = readInput(stdin, 100);

    printf("%s\n", input);
    return 0;
}