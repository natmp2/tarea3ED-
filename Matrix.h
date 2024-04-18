//
//  Matrix.h
//  Tarea3ED
//
//  Creado por Felipe Benavides y Nathaniel Motykiewicz
//

#ifndef Matrix_h
#define Matrix_h

#include <iostream>
#include <stdexcept>

using namespace std;
using std::runtime_error;

template <typename E>
class Matrix{
private:
    int rows;
    int columns;
    E** matrix; //un puntero hacia un puntero de tipo E
    
public:
    Matrix(int rows, int columns) {
        if (rows <= 0 || columns <= 0)
            throw runtime_error("Number of rows and columns must be higher than zero.");
        this->rows = rows;
        this->columns = columns;
        matrix = new E*[rows]; //puntero matrix se le asigna la direccion de memoria de un nuevo arreglo de tipo puntero a E
        for (int i = 0; i < rows; i++) {
            matrix[i] = new E[columns]; // para cada fila se asigna "columns" elementos tipo E
        }
    }
    ~Matrix() {
        for (int i = 0; i < rows; i++){
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    
    E getValue(int row, int column){
        if (row < 0 || row >= rows)
            throw runtime_error("Invalid row");
        if (column < 0 || column >= columns)
            throw runtime_error("Invalid column");
        return matrix[row][column];
    }
    
    void setValue(int row, int column, E value){
        if (row < 0 || row >= rows)
            throw runtime_error("Invalid row");
        if (column < 0 || column >= columns)
            throw runtime_error("Invalid column");
        matrix[row][column] = value;
    }
    
    int getRows() {
        return rows;
    }
    
    int getColumns() {
        return columns;
    }
    
    void setAll(E value){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                matrix[i][j] = value;
            }
        }
    }
    
    void transpose(){
        int cantCol = columns; // para despues hacer el intercambio de la cantidad de rows y columns
        E** matrixTranspuesta = new E* [columns]; 
        for (int i = 0; i < columns; i++) {
            matrixTranspuesta[i] = new E[rows]; // se crea la cantidad de rows como el tamaño de las columns
        }
        
        for (int i = 0; i < rows; i++){
            for (int j = 0; j < columns; j++){
                matrixTranspuesta[j][i] = matrix[i][j]; // se agregan los valores a la nueva matriz, de orden inverso
            }
        }
        
        for (int i = 0; i < rows; i++){ // se elimina cada elemento de la matriz vieja
            delete[] matrix[i];
        }
        
        delete[] matrix; // se elimina el arreglo de punteros original
        matrix = matrixTranspuesta; // se copia a la nueva
        columns = rows;
        rows = cantCol; // finalmente se intercambian valores 
        
    }
    
    void addRow(E value){
        int nuevoRow = rows + 1;
        E** tempRow = new E* [nuevoRow]; // se crea un nuevo arreglo de punteros temp que apunta a la nueva columna inicial con la nueva cantidad de rows
        for (int i = 0; i < rows ; i++) {
            tempRow[i] = matrix[i]; // temp ahora apunta adonde apuntan los punteros de matrix (cada una de las filas)
        }
        
        tempRow[rows] = new E [columns]; // se crea la nueva fila con la misma longitud que tenia matrix
        for (int j = 0; j < columns; j++){
            tempRow[rows][j] = value; //se asigna la nueva fila con los valores de value
        }
        // no se borra temp
        matrix = tempRow; 
        rows++;
    
    }
    
    void addColumn(E value){
        int nuevaCol = columns + 1;
        E** temp = new E*[rows]; // temp apunta a una nueva fila
        
        for (int i = 0; i < rows; i++){
            temp[i] = new E[nuevaCol]; //fila de tamaño columns+1
            
            for (int j = 0; j < columns; j++){
                temp[i][j] = matrix[i][j]; //se rellenan los valores de la fila pasada
            }
            temp[i][columns] = value; // la ultima ranura de la fila se llena con value
        }
        
        for (int i = 0 ; i < rows; i++){
            delete[] matrix[i]; //se borran las filas pasadas
        }
        delete[] matrix; // se borra el arreglo de punteros viejo
        matrix = temp; //por lo que ahora apunta al nuevo y temp no hace falta borrarlo
        columns++;
    }
    
    void removeRow(int row) { // parecido al addrow se hace lo mismo pero quitandole la fila row en vez de añadirle uno
        if (row < 0 || row >= rows)
            throw runtime_error("Invalid row");

        if (rows == 1) {
            throw runtime_error("Cannot remove the last row"); // no se elimina si es la última fila
        }

        E** temp = new E * [rows - 1];
        int indiceNuevo = 0; // se van contando los nuevos indices porque no se sabe en que indice del viejo esta el valor que se quiere borrar
        for (int i = 0; i < rows; i++) {
            if (i != row) {
                temp[indiceNuevo] = matrix[i]; // se añaden todos los valores de la matriz a la nueva mientras sean diferentes del indice ingresado
                indiceNuevo++;
            }
            else {
                delete[] matrix[i]; // si es igual a la matriz que se desea borrar se borra de una vez porque sino queda ahi y hay fuga de memoria
            }
        }
        delete[] matrix; // se borra el arreglo de punteros viejo, no me acuerdo si era necesario pero como ya no se usa podemos aprovechar para borrarlo de una vez ya que está vacio.
        matrix = temp; // por lo que ahora apunta al nuevo y temp no hace falta borrarlo
        rows--;
    }

    void removeColumn(int column) {
        if (column < 0 || column >= columns)
            throw runtime_error("Invalid column");

        if (columns == 1) {
            throw runtime_error("Cannot remove the last column"); // no se elimina si es la última columna
        }

        E** temp = new E * [rows]; // se crea el arreglo de punteros
        for (int i = 0; i < rows; i++) {
            temp[i] = new E[columns - 1]; // asigna dinámicamente memoria para una fila de la matriz temporal temp, donde cada fila tiene columns - 1 elementos del tipo E
            int tempIndex = 0;

            for (int j = 0; j < columns; j++) {
                if (j != column) {
                    temp[i][tempIndex] = matrix[i][j]; //para cada columna, mientras no sea la que se va a borrar pase los datos a la nueva (temp)
                    tempIndex++;
                }
            }
            delete[] matrix[i]; //al haber añadido los valores de las nuevas filas, se elimina la fila vieja despues de completar el primer ciclo
        }
        matrix = temp;
        columns--;
    }

    
    void print(){ // estaba implementada en el video de la explicacion de matrices no hacia falta agregar mas
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << getValue(i, j) << "\t";
            }
            cout << endl;
        }
    }
};
#endif
