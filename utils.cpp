#include "utils.hpp"

char *readInput(FILE* fp, unsigned int size){
    char *string;
    int one_char;
    unsigned int length = 0;
    string = (char*) malloc(sizeof(*string) * size);

    if(!string) {
        perror("Error while allocating input, aborting.\n");
        exit(READ_ERROR);
    }

    while(EOF != (one_char = fgetc(fp)) && one_char != '\n') {
        string[length++] = one_char;
        if(length == size){
            string = (char*) realloc(string, sizeof(*string)*(size += size/2));
            if(!string)return string;
        }
    }

    string[length++]='\0';

    return (char*) realloc(string, sizeof(*string)*length);
}