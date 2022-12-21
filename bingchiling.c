// Autores:
// Dante Eleutério dos Santos (GRR20206686)
// Richard Fernando Heise Ferreira (GRR20191053)

#include "crypt.h"

int main(int argc, char* argv[]) {

    // Usage of inputs
    if (argc <= 1) {
        printf("Usage:\n  encrypting: %s -c\n  decrypting: %s -d\n", argv[0], argv[0]);
        return 1;
    }

    // Allocating arrays
    uint32_t* key = alloca(sizeof(uint32_t) * MAX_ALLOC);
    uint32_t* inputUTF32 = alloca(sizeof(uint32_t) * MAX_ALLOC);
    uint32_t* aux = alloca(sizeof(uint32_t) * MAX_ALLOC);

    // Generating key
    key = generateKey();

    int inputSize = 0;

    // Reading from stdin
    inputUTF32 = readText(&inputSize);

    // Copy input read to aux, size is in bytes*4
    bcopy(inputUTF32, aux, inputSize*4);

    // Encrypting/Decrypting
    for (int i = 0; i < inputSize; i++) {
        if (strcmp(argv[1], "-c") == 0) { // If it's encryption

            // In this code, key size is always equal 10
            if (i < 10)
                // While we have key size on range, we use the key
                inputUTF32[i] = oneTimePad(inputUTF32[i], key[i]);
            else 
                // When key size is already used, we use the very  input as key
                inputUTF32[i] = oneTimePad(inputUTF32[i], aux[i - 10]);

            // Sum to UTF-32 so the text becomes "japanese"
            inputUTF32[i] += (0x3061);
        } else {

            // Subtraction from UTF-32 so the text is not "japanese" anymore
            inputUTF32[i] -= (0x3061);

            // Key size is always 10
            if (i < 10)
                // While we have key size on range, we use the key
                inputUTF32[i] = oneTimePad(inputUTF32[i], key[i]);
            else
                // When key is already used, we use the very decrypted text to complete the decryption
                inputUTF32[i] = oneTimePad(inputUTF32[i], inputUTF32[i - 10]);
        }
    }

    // Prints output in UTF-8 so terminal can understand it
    for (int i = 0; i < inputSize; i++) {
        printf("%s", to_utf8(inputUTF32[i]));
    }
    printf("\n");

    return 0;
}
