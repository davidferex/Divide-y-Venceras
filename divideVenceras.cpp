
#include <stdio.h>
#include "math.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include "generador.hpp"

using namespace std;


int n;
int m;
int * diferencias;

struct Solucion{
    int posicion;
    int suma;
};

Solucion solucion_directa (int inicio, int fin){
    int i = inicio;
    int j = inicio + m-1;
    int suma = 0;
    int suma_max = 0;
    int pos = i;
    //Se calcula la primera suma
    for (int h = i; h <= j; h++){
        suma = suma + diferencias[h];
    }
    suma_max = suma;
    i++;
    j++;
    while (j <= fin && suma_max < m*25) {
        //Se hace la suma usando la anterior
        suma = suma + diferencias[j] - diferencias[i - 1];
        //Actualizamos la mejor solución si procede.
        if (suma > suma_max){
            suma_max = suma;
            pos = i;
        }
        i++;
        j++;
    }
    Solucion sol;
    sol.suma = suma_max;
    sol.posicion = pos;
    return sol;
}

Solucion combinar (Solucion sol1, Solucion sol2, int punto_medio){
    Solucion s;
    s.suma = 0;
    s.posicion = 0;
    int suma = 0;
    //Si la solucion de la izquierda esta lo suficientemente cerca se reutiliza
    if ((sol1.posicion + sol1.posicion + m)/2 >= punto_medio - m + 2){
        suma = sol1.suma;
        //Se calcula la primera suma usando la solución de la izquierda
        for (int h = sol1.posicion; h <= punto_medio - m + 1; h++){
            suma = suma - diferencias[h];
        }
        for (int h = sol1.posicion + m; h <= punto_medio + 1; h++){
            suma = suma + diferencias[h];
        }
        s.suma = suma;
        s.posicion = punto_medio - m + 2;
        int i = s.posicion + 1;
        int j = punto_medio + 2;
        //Iteramos haciendo las demás sumas
        while (j <= punto_medio + m - 1 && s.suma < 25*m){
            suma = suma + diferencias[j] - diferencias[i - 1];
            if (suma > s.suma){
                s.suma = suma;
                s.posicion = i;
            }
            i++;
            j++;
        }
        //Si la solucion de la derecha esta lo suficientemente cerca se reutiliza
    } else if ((sol2.posicion + sol2.posicion + m)/2 <= punto_medio + m - 1){
        suma = sol2.suma;
        //Se calcula la primera suma usando la solución de la derecha
        for (int h = punto_medio + m; h <= sol2.posicion + m - 1; h++){
            suma = suma - diferencias[h];
        }
        for (int h = sol2.posicion - 1; h >= punto_medio; h--){
            suma = suma + diferencias[h];
        }
        s.suma = suma;
        s.posicion = punto_medio;
        int i = punto_medio + m - 2;
        int j = punto_medio - 1;
        //Iteramos haciendo las demás sumas
        while (j >= punto_medio - m + 2 && s.suma < 25*m){
            suma = suma + diferencias[j] - diferencias[i + 1];
            if (suma >= s.suma){
                s.suma = suma;
                s.posicion = j;
            }
            i--;
            j--;
        }
    //Si no se puede usar ninguna de las dos soluciones se llama a solcuión directa
    } else{
        s = solucion_directa(punto_medio - m + 2, punto_medio + m - 1);
    }
    //Se devuelve la mayor de las tres soluciones, la más a la izquierda en caso de empate.
    if (sol1.suma >= s.suma){
        s = sol1;
    }
    if (sol2.suma > s.suma){
        s = sol2;
    }
    return s;
}

bool pequeno(int inicio, int fin){
    if (fin - inicio + 1 < 2*m || fin - inicio + 1 < n/1000){
        return true;
    }
    return false;
    
}

Solucion divide_venceras(int inicio, int fin){
    if (pequeno(inicio, fin)){
        return solucion_directa(inicio, fin);
    } else{
        Solucion sol1 = divide_venceras(inicio, (inicio + fin)/2);
        //Si es la solución optima se devuelve directamente.
        if (sol1.suma == m*25){
            return sol1;
        }
        Solucion sol2 = divide_venceras((inicio + fin)/2 + 1, fin);
        //Si es la solución optima se devuelve directamente.
        if (sol2.suma == m*25){
            return sol2;
        }
        return combinar(sol1, sol2, (inicio + fin)/2);
    }
}
                      
int main (){
    cout << "Inserte el tamaño del array" << endl;
    cin >> n;
    cout << "Inserte la m que desee" << endl;
    cin >> m;
    if (m > n){
        cout << "La m debe ser menor o igual que la n" << endl;
        return 0;
    }
    cout << "Inserte 1 si desea el peor caso, 2 si desea el mejor, 3 si desea un caso promedio" << endl;
    int caso;
    cin >> caso;
    if (caso == 1){
        diferencias = genera_peor_caso(n, m);
    } else if (caso == 2){
        diferencias = genera_mejor_caso(n, m);
    } else if (caso == 3){
        diferencias = genera_caso_promedio(n, m);
    } else {
        cout << "Opción inválida" << endl;
        return 0;
    }
    Solucion sol = divide_venceras(0, n-1);
    cout << "Posicion " << sol.posicion << " y diferencia maxima " << sol.suma << endl;
    delete[] diferencias;
}
