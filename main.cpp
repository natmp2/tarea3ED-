// Tarea 3 ED
// Realizado por Felipe Benavides y Nathaniel Motykiewicz
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// traer funciones de archivo matrix
#include "Matrix.h"

int random(int min, int max) { // funcion para generar numeros aleatorios
    static bool first = true;
    if (first) {
        srand(static_cast<unsigned int>(time(nullptr))); // funcion para generar los valores
        first = false;
    }
    return min + rand() % (max - min + 1);
}

int main() {
    int rows, columns;
    bool validInput = false;

    // solicitar filas y columnas hasta que se ingresen valores válidos
    do {
        cout << "Ingrese el número de filas de la matriz (número entero positivo): ";
        if (!(cin >> rows) || rows <= 0) {
            cout << "Entrada inválida. Intente de nuevo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // para que no explote después del enter
        }
        else {
            validInput = true;
        }
    } while (!validInput);

    validInput = false;

    do {
        cout << "Ingrese el número de columnas de la matriz (número entero positivo): ";
        if (!(cin >> columns) || columns <= 0) {
            cout << "Entrada inválida. Intente de nuevo." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // para que no explote después del enter
        }
        else {
            validInput = true;
        }
    } while (!validInput);

    // crear objeto de tipo Matrix con las dimensiones ingresadas y llenarlo con ceros
    Matrix<int>* miMatriz = new Matrix<int>(rows, columns);
    miMatriz->setAll(0);
    cout << "Matriz vacía creada exitosamente:" << endl;
    miMatriz->print();

    int opcion;
    do {
        validInput = false;
        do {
            try {
                cout << "\n--- MENU ---\n";
                cout << "1. Imprimir matriz\n";
                cout << "2. Obtener valor de una posición\n";
                cout << "3. Modificar valor de una posición\n";
                cout << "4. Obtener número de filas\n";
                cout << "5. Obtener número de columnas\n";
                cout << "6. Establecer todos los valores\n";
                cout << "7. Transponer la matriz\n";
                cout << "8. Agregar una fila\n";
                cout << "9. Agregar una columna\n";
                cout << "10. Eliminar una fila\n";
                cout << "11. Eliminar una columna\n";
                cout << "12. Cargar números aleatorios\n";
                cout << "13. Salir\n";
                cout << "Ingrese una opción: ";
                cin >> opcion;
                validInput = true;
            }
            catch (...) {
                cout << "Entrada inválida. Intente de nuevo." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // para que no explote después del enter
            }
        } while (!validInput);

        switch (opcion) {
        case 1: // imprimir la matriz
            miMatriz->print(); 
            break;
        case 2: { // retornar valor de la posición ingresada
            int row, col;
            cout << "Ingrese la fila: ";
            cin >> row;
            cout << "Ingrese la columna: ";
            cin >> col;
            try {
                cout << "El valor en la posición (" << row << ", " << col << ") es: " << miMatriz->getValue(row, col) << endl; 
            }
            catch (runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        }
        case 3: { // cambiar el valor de la posición seleccionada
            int row, col, value;
            cout << "Ingrese la fila: ";
            cin >> row;
            cout << "Ingrese la columna: ";
            cin >> col;
            cout << "Ingrese el nuevo valor: ";
            cin >> value;
            try {
                miMatriz->setValue(row, col, value);
                cout << "Valor modificado correctamente." << endl;
                miMatriz->print();
            }
            catch (runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        }
        case 4: // retornar la cantidad de filas
            cout << "El número de filas de la matriz es: " << miMatriz->getRows() << endl;
            break;
        case 5: // retornar la cantidad de columnas
            cout << "El número de columnas de la matriz es: " << miMatriz->getColumns() << endl;
            break;
        case 6: { // poner el mismo valor a toda la matriz
            int value;
            cout << "Ingrese el valor para establecer en toda la matriz: ";
            cin >> value;
            miMatriz->setAll(value);
            cout << "Valores establecidos correctamente." << endl;
            miMatriz->print();
            break;
        }
        case 7: // transponer la matriz
            miMatriz->transpose();
            cout << "Transposición exitosa." << endl;
            miMatriz->print();
            break;
        case 8: { // agregar una fila a la matriz
            int value;
            cout << "Ingrese el valor para la nueva fila: ";
            cin >> value;
            miMatriz->addRow(value);
            cout << "Fila agregada correctamente." << endl;
            miMatriz->print();
            break;
        }
        case 9: { // agregar una columna a la matriz
            int value;
            cout << "Ingrese el valor para la nueva columna: ";
            cin >> value;
            miMatriz->addColumn(value);
            cout << "Columna agregada correctamente." << endl;
            miMatriz->print();
            break;
        }
        case 10: { // eliminar una fila a la matriz
            int row;
            cout << "Ingrese la fila a eliminar: ";
            cin >> row;
            try {
                miMatriz->removeRow(row);
                cout << "Fila eliminada correctamente." << endl;
                miMatriz->print();
            }
            catch (runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        }
        case 11: { // eliminar una columna a la matriz
            int col;
            cout << "Ingrese la columna a eliminar: ";
            cin >> col;
            try {
                miMatriz->removeColumn(col);
                cout << "Columna eliminada correctamente." << endl;
                miMatriz->print();
            }
            catch (runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            }
            break;
        }
        case 12: { // llenar matriz con valores aleatorios (el usuario escoge el rango)
            int min, max;
            cout << "Ingrese el valor mínimo para los números aleatorios: ";
            cin >> min;
            cout << "Ingrese el valor máximo para los números aleatorios: ";
            cin >> max;
            for (int i = 0; i < miMatriz->getRows(); i++) {
                for (int j = 0; j < miMatriz->getColumns(); j++) {
                    miMatriz->setValue(i, j, random(min, max));
                }
            }
            cout << "Números aleatorios cargados correctamente." << endl;
            miMatriz->print();
            break;
        }
        case 13: // salir del programa
            break;
        default:
            cout << "Opción inválida, intente de nuevo." << endl;
        }
    } while (opcion != 13);

    // liberar la memoria del objeto
    delete miMatriz;

    return 0;
}
