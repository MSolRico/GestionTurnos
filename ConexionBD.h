#pragma once
#include <mysql.h>
#include <string>
#include <vector>
using namespace std;

class ConexionBD {
private:
    MYSQL* conector;
    void crearBaseDeDatos(const string& nombreBD);
public:
    ConexionBD();
    ~ConexionBD();
    void abrir_conexion();
    MYSQL* getConector();
    void cerrar_conexion();
    void ejecutarConsulta(const string& consulta);
};
