#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

BigNum *parArrayProd(int a[ ], int i, int j, int p){
    if(i==j){
        return smallNum(a[i]);
    }
    if(p==1){
        return seqArrayProd(a,i,j);
    }
    else{
        int step = (i+j)/2;
        int pr_child = p/2;
        int pr_father = p - pr_child;

        int fds[2];
        pipe(fds);

        pid_t pid = fork();//procesos pesados
        if(pid==0){// hijo
            close(fds[0]);//cerramos canal de lectura
            BigNum *prod_child = parArrayProd(a, i, step, pr_child);
            write(fds[1], &prod_child->n, sizeof(int));
            write(fds[1], prod_child->bits, prod_child->n*sizeof(BigInt_t));
            close(fds[1]);
            exit(0);
        }
        else { // padre
            close(fds[1]);//cerramos canal de escritura

            BigNum *prod_father = parArrayProd(a, step+1, j, pr_father);
            BigNum *prod_child = malloc(sizeof(BigNum));
            leer(fds[0], &prod_child->n, sizeof(int));
            prod_child->bits=malloc(prod_child->n*sizeof(BigInt_t));
            leer(fds[0], prod_child->bits, prod_child->n*sizeof(BigInt_t));

            waitpid(pid, NULL, 0);//enterramos al hijo
            close(fds[0]);//cerramos el canal de lectura

            BigNum *prod_result = bigMul(prod_child, prod_father);
            freeBigNum(prod_child);
            freeBigNum(prod_father);
            return prod_result;
        }
    }
}
