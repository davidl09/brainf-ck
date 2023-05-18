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
    int l = len = 0;
    while((temp = fgetc(fp)) != EOF){
        for (int i = 0; i < 8; ++i) {
            if(temp == ops[i]){
                txt_ptr[len] = temp;
                ++len;
                break;
            }
        }
        ++l;
    }

    l = 0;
    fclose(fp);

    for (int i = 0; i < len; ++i) {
        l = (txt_ptr[i] == '[' ? l + 1 : (txt_ptr[i] == ']' ? l - 1 : l));
    }
    if(l != 0){
        fprintf(stderr, "Mismatched brackets\n");
        return 1;
    }


    const unsigned char* ptr_0 = ptr;
    const char* txt_ptr_0 = txt_ptr;
    unsigned char* ref_ptr;

    while(txt_ptr - txt_ptr_0 < len && ptr - ptr_0 < 30000 && *txt_ptr != 0){
        
        if(*txt_ptr ==  '+')
            ++(*ptr);

        else if(*txt_ptr ==  '-')
            --(*ptr);

        else if(*txt_ptr ==  '>')
            ++ptr;

        else if(*txt_ptr ==  '<')
            --ptr;

        else if(*txt_ptr ==  '.')
            printf("%c", *ptr);

        else if(*txt_ptr ==  ',')
            *ptr = getc(stdin);

        else if(*txt_ptr ==  '[')
            (*ptr == 0 ? txt_ptr = seek_forward(ptr, txt_ptr) : txt_ptr);

        else if(*txt_ptr ==  ']')
            (*ptr != 0 ? txt_ptr = seek_back(ptr, txt_ptr) : txt_ptr);

        else continue;
        ++txt_ptr;
    }

    free((void*)ptr_0);
    free((void*)txt_ptr_0);
    printf("\nProgram executed successfully\n");
    return 0;
}