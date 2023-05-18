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

    char* txt_ptr = calloc(1, len);
    unsigned char* ptr = calloc(1, 30000);

    

    char* ops = "+-<>.,[]"; //clean input
    char temp;
    int l = 0;
    while((temp = fgetc(fp)) != EOF){
        for (int i = 0; i < 8; ++i) {
            if(txt_ptr[l] == ops[i]){
                txt_ptr[l] = temp;
                break;
                }
        }
        ++l;
    }

    l = 0;

    unsigned char* ptr_0 = ptr;
    char* txt_ptr_0 = txt_ptr;
    unsigned char* ref_ptr;

    while(txt_ptr - txt_ptr_0 < len && ptr - ptr_0 < 30000 && *txt_ptr != 0){
        switch (*txt_ptr) {
            case '+':
                ++*ptr;
            case '-':
                --*ptr;
            case '>':
                ++ptr;
            case '<':
                --ptr;
            case '.':
                printf("%c", *ptr);
            case ',':
                *ptr = getc(stdin);
            case '[': 
                (*ptr == 0 ? txt_ptr = seek_forward(ptr, txt_ptr) : ++txt_ptr);
            case ']':
                (*ptr != 0 ? txt_ptr = seek_back(ptr, txt_ptr) : ++txt_ptr);
            default:
                break;
        }
        ++txt_ptr;
    }

    free(ptr);
    free(txt_ptr);
    return 0;
}