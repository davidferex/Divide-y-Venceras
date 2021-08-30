
#include "generador.hpp"
#include <stdio.h>
#include "math.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

//generador del mejor caso, que pone en la primera subcadena la sol. optima.
int * genera_mejor_caso(int n, int m){
    string cadena1 = "";
    string cadena2 = "";
    for (int i = 0; i < m; i++){
        cadena1 = cadena1 + "a";
        cadena2 = cadena2 + "z";
    }
    for (int i = m; i < n; i++){
        cadena1 = cadena1 + "p";
        cadena2 = cadena2 + "p";
    }
    int * dife = new int[n];
    for (int i = 0; i < n; i++){
        dife[i] = abs(cadena1[i] - cadena2[i]);
    }
    return dife;
}

int * genera_peor_caso(int n, int m){
    string cadena1 = "";
    string cadena2 = "";
    int i = 0;
    //creamos una cadena con todo 'a'
    for (int h = 0; h < n; h++){
        cadena2 = cadena2 + "a";
    }
    //la otra cadena la hacemos como se explica en la memoria.
    while(cadena1.length() < n){
        char letra = 'a' + i;
        int j = 0;
        if (i < 25){
            while (cadena1.length() < n && j < m){
                cadena1 = cadena1 + letra;
                j++;
            }
        } else {
            while (cadena1.length() < n && j < m-1){
                cadena1 = cadena1 + letra;
                j++;
            }
        }
        
        if (i < 25){
            i++;
        } else {
            i = 0;
        }
    }
    int * dife = new int[n];
    for (int i = 0; i < n; i++){
        dife[i] = abs(cadena1[i] - cadena2[i]);
    }
    return dife;
}

//En el caso promedio se generan cadenas aleatorias.
int * genera_caso_promedio (int n, int m){
    string cadena1 = "";
    string cadena2 = "";
    srand(time(NULL) + rand());
    int random;
    for (int i = 0; i < n; i++){
        random = rand()%26;
        char letra1 = 'a' + random;
        cadena1 = cadena1 + letra1;
        random = rand()%26;
        char letra2 = 'a' + random;
        cadena2 = cadena2 + letra2;
    }
    int * dife = new int[n];
    for (int i = 0; i < n; i++){
        dife[i] = abs(cadena1[i] - cadena2[i]);
    }
    return dife;
}

