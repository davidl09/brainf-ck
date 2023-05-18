#include "bf_v1.h"

unsigned char* ptr;
char* txt_ptr;


unsigned char* evaluate_char(){
    switch (*txt_ptr) {
        case '+':
            ++*ptr;
            return ptr;
        case '-':
            --*ptr;
            return ptr;
        case '>':
            return ++ptr;
        case '<':
            return --ptr;
        case '.':
            printf("%c", *ptr);
            return ptr;
        case ',':
            *ptr = getc(stdin);
            return ptr;
        case '[':
            return mov_bracket();
        case ']':
            return ptr;
    }
}

unsigned char* mov_bracket(){
    int num_brackets = 0;


}