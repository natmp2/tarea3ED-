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
            matrix[i] = new E[columns]; // para cada fila asignele un puntero a columnas?
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
        E** matrixTranspuesta = new E* [columns]; //tambien podia ser rows
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
        matrix = tempRow; // no me estaba dejando usar matrix->temp por alguna razon
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
    
    void removeRow(int row){
        
    }
    
    void removeColumn(int column){
        
    }
    
    void print(){
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << getValue(i, j) << "\t";
            }
            cout << endl;
        }
    }
    
};

#endif /* Matrix_h */

