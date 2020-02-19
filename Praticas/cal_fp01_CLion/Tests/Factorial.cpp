/*
 * Factorial.cpp
 */

#include "Factorial.h"

int factorialRecurs(int n){
    if(n > 1){
        return n * factorialRecurs(n - 1);
    }
    else{
        return 1;
    }
}

int factorialDinam(int n){
    int fac = 1;
    if(n == 0 || n == 1){
        return fac;
    }
    for(int i = 1; i <= n; i++){
        fac *= i;
    }
    return fac;
}
