#include "utils.cpp"

using namespace std;

int main() {
    printf("Hello, I'm an encrypter :D\n");
    printf("Waiting for text to ENCRYPT via stdin, output on stdout\n");

    char* input = readInput(stdin, 100);

    printf("%s\n", input);

    return 0;
}