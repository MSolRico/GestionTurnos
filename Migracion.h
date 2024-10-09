#pragma once
#include "ConexionBD.h"
#include <vector>
#include <string>
using namespace std;

class Migracion {
private:
    ConexionBD* conexion;
    vector<string> migraciones;
public:
    Migracion(ConexionBD* con);
    void ejecutar_migraciones();
};
