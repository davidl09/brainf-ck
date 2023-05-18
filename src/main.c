#include "bf_v1.h"
#include <stdio.h>
#include <stdlib.h>

FILE* fp;



int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(stderr, "Missing file name\n");
        return 1;
    }

    if((fp = fopen(argv[1], "r")) == NULL){
        fprintf(stderr, "File not found\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END); //get length of text
    size_t len = ftell(fp);
    fseek(fp, 0, 0);

    extern char* txt_ptr;
    txt_ptr = malloc(len);
    extern unsigned char* ptr;
    ptr = malloc(30000);

    for (int i = 0; i < 30000; ++i) {
        ptr[i] = 0;
    }

    



    free(ptr);
    free(txt_ptr);
    return 0;
}