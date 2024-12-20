#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "desplazar.h"

void desplazar(char *str, int from, int nbytes, int by) {
    // Limites patron
    char *bottom_pa = str + from;
    char *top_pa = str + from + nbytes - 1;
    // Limites str
    char *bottom_str = str;
    char *top_str = str + strlen(str);
    // Se mueve a la derecha
    if(by>0){
        for(int i = 0; i < nbytes; i++){
            char *tmp = top_pa + by;
            if(tmp < top_str){
                *tmp = *top_pa;
            }
            top_pa--;
        }
    }
    // Se mueve a la izquierda
    else if(by<0){
        for(int i = 0; i < nbytes; i++){
            char *tmp = bottom_pa + by;
            if(tmp >= bottom_str){
                *tmp = *bottom_pa;
            }
            bottom_pa++;
        }
    }            
}

char *desplazamiento(char *str, int from, int nbytes, int by) {
    char *n_str = malloc(strlen(str) + 1);
    strcpy(n_str, str);
    desplazar(n_str, from, nbytes, by);
    return n_str;
}
