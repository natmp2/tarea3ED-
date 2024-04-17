//
//  main.cpp
//  Tarea3ED
//
//  Creado por Felipe Benavides y Nathaniel Motykiewicz
//

#include <iostream>
#include "Matrix.h"

using namespace std;

int main() {
    Matrix<int> *matriz = new Matrix<int>(3,2);
    for (int i = 0; i < matriz->getRows(); i++) {
        for (int j = 0; j < matriz->getColumns(); j++) {
            matriz->setValue(i, j, i+j);
        }
    }
    matriz->setAll(7);
    matriz->addRow(8);
    matriz->addColumn(6);
    matriz->print();
    matriz->transpose();
    cout << "\n" << endl;
    matriz->print();
    matriz->transpose();
    cout << "\n" << endl;
    matriz->print();
    delete matriz;
    return 0;
}
