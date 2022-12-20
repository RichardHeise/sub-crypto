// Autores:
// Dante Eleutério dos Santos (GRR20206686)
// Richard Fernando Heise Ferreira (GRR20191053)

#include "crypt.h"

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        printf("Usage:\n  encrypting: %s -c\n  decrypting: %s -d\n", argv[0], argv[0]);
        return 1;
    }

    uint32_t* key = alloca(sizeof(uint32_t) * MAX_ALLOC);
    uint32_t* inputUTF32 = alloca(sizeof(uint32_t) * MAX_ALLOC);
    uint32_t* aux = alloca(sizeof(uint32_t) * MAX_ALLOC);

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

    return 0;
}
