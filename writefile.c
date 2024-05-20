#include <stdio.h>
#include "writefile.h"

FILE *fptr;

void init_reader(char* name){
    fptr = fopen(name, "a");
}

void end_reader(){
    fclose(fptr);
}

void p_int(int value){
    fprintf(fptr, "%d", value);
}

void add_comma(){
    fprintf(fptr, ",");
}

void endl(){
    fprintf(fptr, "\n", "");
}

void print_rgb(int r, int g, int b){
    p_int(r);
    add_comma();
    p_int(g);
    add_comma();
    p_int(b);
    endl();
}