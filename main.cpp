//
//  main.cpp
//  Tarea3ED
//
//  Creado por Felipe Benavides y Nathaniel Motykiewicz
//

#include <iostream>
#include <cstdlib>
#include <string>
#include "Matrix.h"

using namespace std;

int random(int min, int max) { // lo saqué de la tarea 2
    return min + rand() % (max - min + 1);
}

int main() {
    setlocale(LC_CTYPE, "Spanish");
    
    int filas;
    int columnas;
    
    while (true) {
        cout << "por favor ingrese la cantidad de filas para la matriz: " << endl;
        cin >> filas;
        cout <<"por favor ingrese la cantidad de columnas para la matriz: " << endl;
        cin >> columnas;
        
        if (filas <= 0 && columnas <=0){
            cout << "las filas y columnas deben ser mayores que cero, por favor intente de nuevo." << endl;
        }
        else{
            break;
        }
    }
        
    
    Matrix<int> *matriz = new Matrix<int>(filas,columnas);
    for (int i = 0; i < matriz->getRows(); i++){
        for (int j = 0; j < matriz->getColumns(); j++){
            matriz->setValue(i,j, 0); //carga la matriz inicial con 0
        }
    }
    matriz->print();
    
    
    
    delete matriz;
    return 0;
}
