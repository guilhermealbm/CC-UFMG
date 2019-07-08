#include <iostream>


//metodo recursivo para calculo do fatorial de um numero n
int fatorial(int n){
    
    if (n == 0)
        return 1;
    
    return (n * fatorial(n-1));
}