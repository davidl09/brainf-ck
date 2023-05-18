#include "bf_v1.h"

char* seek_forward(unsigned char* ptr, char* txt_ptr){
    int num_brackets = 0;
    do{
        if(*txt_ptr == '[')
            ++num_brackets;
        else if(*txt_ptr == ']')
            --num_brackets;
        ++txt_ptr;
    }while(num_brackets > 0);
    return txt_ptr;
}

char* seek_back(unsigned char* ptr, char* txt_ptr){
int num_brackets = 0;
    do{
        if(*txt_ptr == '[')
            --num_brackets;
        else if(*txt_ptr == ']')
            ++num_brackets;
        --txt_ptr;
    }while(num_brackets > 0);
    return txt_ptr;
}