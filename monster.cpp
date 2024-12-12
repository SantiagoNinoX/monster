#include "monster.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void Monster::setName(string nName) {
    name = nName;
}

void Monster::setCR(double nCR) {
    cr = nCR;
}

void Monster::setType(string nType) {
    type = nType;
}

void Monster::setSize(string nSize) {
    size = nSize;
}

void Monster::setAC(int nAC) {
    ac = nAC;
}

void Monster::setHP(int nHP) {
    hp = nHP;
}

void Monster::setAlign(string nAlign) {
    align = nAlign;
}

void Monster::printCreatureData() {
    cout << "Name: " << name << endl;
    cout << "cr: " << cr << endl;
    cout << "type: " << type << endl;
    cout << "size: " << size << endl;
    cout << "ac: " << ac << endl;
    cout << "hp: " << hp << endl;
    cout << "align: " << align << endl;
}

bool loadMonsterFromCSV(const string& fileName, Monster *monsterArray, unsigned int arraySize) {
    ifstream        file(fileName);
    string          line;
    unsigned int    size = 0;

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << fileName << endl;
        return false;
    }

    // skip header
    if(!getline(file, line)) {
        cerr << "El archivo no tiene header" << endl;
        file.close();
        return false;
    }

    cout << "Cargando archivo: " << fileName << endl;

    while (getline(file, line)) {
        Monster         nMonstruo;
        stringstream    ss(line);
        string          cell;
        int             campo = 0, errores = 0;

        while (getline(ss, cell, ',')) {
            if(!cell.length())
                errores ++;
            
            // ir coma por coma, esta version no valida que sean enteros o floats
            // por simplicidad
            switch(campo) {
                case 0:
                    nMonstruo.setName(cell);
                    break;
                case 1:
                    nMonstruo.setCR(stod(cell));
                    break;
                case 2:
                    nMonstruo.setType(cell);
                    break;
                case 3:
                    nMonstruo.setSize(cell);
                    break;
                case 4:
                    nMonstruo.setAC(stoi(cell));
                    break;
                case 5:
                    nMonstruo.setHP(stoi(cell));
                    break;
                case 6:
                    nMonstruo.setAlign(cell);
                    break;
                default:
                    errores ++;
                    break;
            }
            campo ++;
        }

        // Comparar si son 7 campos, aqui depende de cuantas 
        // entradas tiene cada clase, el 7 esta definido en el h
        // como MONSTER_ATTRIB_SIZE
        if(errores || campo != MONSTER_ATTRIB_SIZE) {
            cerr << "Error en la linea: " << endl << line << endl;
            file.close();
            return false;
        }

        if(size < arraySize) {
            monsterArray[size] = nMonstruo;
            size ++;
        }
        else {
            cerr << "Error, el arreglo es muy pequeño" << endl;
            file.close();
            return false;
        }
    }

    file.close();
    
    return true;
}
