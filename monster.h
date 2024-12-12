#pragma once
#define MONSTER_ATTRIB_SIZE 7
#include <string>

class Monster {
private:
    std::string name;
    double cr;
    std::string type;
    std::string size;
    int ac;
    int hp;
    std::string align;

public:
    Monster() : name(""), cr(0), type(""), size(""), ac(0), hp(0), align("") {}

    void setName(std::string nName);
    void setCR(double nCR);
    void setType(std::string nType);
    void setSize(std::string nSize);
    void setAC(int nAC);
    void setHP(int nHP);
    void setAlign(std::string nAlign);
    void printCreatureData();
};

// Funcion extra para cargar monstruos de un CSV a un arreglo ya definido
bool loadMonsterFromCSV(const std::string& fileName, Monster *monsterArray, unsigned int arraySize);
