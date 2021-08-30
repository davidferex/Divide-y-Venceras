
#include <stdio.h>
#include "math.h"
#include <iostream>
#include <string>

using namespace std;

string A = "";
string B = "";


int main (){
    cout << "Introduzca la primera cadena (en minusculas y sin ñ): " << endl;
    cin >> A;
    cout << "Introduzca la segunda cadena (en minusculas y sin ñ): " << endl;
    cin >> B;
    int n = A.length();
    if (n != B.length()){
        cout << "Las cadenas deben ser de la misma longitud" << endl;
        return 0;
    }
    int m = 0;
    cout << "Introduzca el valor de m: " << endl;
    cin >> m;
    if (m > n || m <= 0){
        cout << "m deber ser menor que n y mayor que 0" << endl;
        return 0;
    }
    int * dife = new int[n];
    for (int i = 0; i < n; i++){
        dife[i] = abs(A[i] - B[i]);
    }
    int i = 0;
    int j = m-1;
    int suma_max = 0;
    int suma = 0;
    int pos = i;
    for (int h = i; h <= j; h++){
        suma = suma + dife[h];
    }
    i++;
    j++;
    suma_max = suma;
    while (j <= n - 1 && suma_max < m*25) {
        suma = suma + dife[j] - dife[i - 1];
        if (suma > suma_max){
            suma_max = suma;
            pos = i;
        }
        i++;
        j++;
    }
    cout << "Posicion " << pos << " y diferencia maxima " << suma_max << endl;
    delete[] dife;

}
