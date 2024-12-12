#include <iostream>
#include <fstream>
#include "monster.h"
#include <string>

#define MONSTERS_FILE "C:/Users/santi/source/repos/poo itc2/monster/monsters.csv"

using namespace std;
//prueba 1

// Regresa -1 si hay un error al leer el archivo o regresa
// la cantidad de lineas de 0 a la cantidad de datos en el csv
int countDataLinesInCSV(const string& fileName) {
    ifstream    file(fileName);
    int         lineCount = 0;
    string      line;

    // Contar la cantidad de líneas en el archivo csv
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return -1;
    }

    // skip header
    if(!getline(file, line)) {
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return -1;
    }

    // Contar lineas 
    while(getline(file, line)) {
        lineCount++;    
    }

    file.close();
    return(lineCount);
}

int main() {
    Monster *monsterArray = nullptr;
    int dataSize = 0;

    dataSize = countDataLinesInCSV(MONSTERS_FILE);
    if(dataSize == -1) {
        cerr << "No se pudo cargar el data set de " << MONSTERS_FILE << "\n";
        return 0;
    }

    cout << "Monsters.csv tiene: " << dataSize << " entradas\n";
    monsterArray = new(nothrow) Monster[dataSize];
    if(monsterArray == nullptr) {
        cerr << "No hubo memoria para el arreglo de " << MONSTERS_FILE << "\n";
        return 0;
    }

    if(!loadMonsterFromCSV(MONSTERS_FILE, monsterArray, dataSize)) {
        cerr << "Error al cargar el data set de " << MONSTERS_FILE << "\n";
        delete [] monsterArray;
        return 0;
    }

    cout << "Mostrando el dato: " << dataSize/2 << " del arreglo:\n";
    monsterArray[dataSize/2].printCreatureData();

    delete [] monsterArray;
    return 0;
}