#include "ConexionBD.h"
#include <iostream>
using namespace std;

ConexionBD::ConexionBD() : conector(nullptr) {}

ConexionBD::~ConexionBD() {
    cerrar_conexion();
}

void ConexionBD::abrir_conexion() {
    conector = mysql_init(nullptr);
    if (!conector) {
        cerr << "Error al inicializar MySQL: No se pudo asignar memoria para la conexion." << endl;
        return;
    }

    conector = mysql_real_connect(conector, "localhost", "root", "", "", 3306, nullptr, 0);
    if (!conector) {
        cerr << "Error al conectar a MySQL: " << mysql_error(conector) << endl;
        return;
    }

    // Crear la base de datos si no existe
    crearBaseDeDatos("gestionturnos");

    // Seleccionar la base de datos
    if (mysql_select_db(conector, "gestionturnos")) {
        cerr << "Error al seleccionar la base de datos: " << mysql_error(conector) << endl;
    }
    else {
        cout << "Base de datos seleccionada correctamente." << endl;
    }
}

void ConexionBD::crearBaseDeDatos(const string& nombreBD) {
    string consulta = "CREATE DATABASE IF NOT EXISTS " + nombreBD;
    if (mysql_query(conector, consulta.c_str())) {
        cerr << "Error al crear la base de datos: " << mysql_error(conector) << endl;
    }
    else {
        cout << "Base de datos creada o ya existe." << endl;
    }
}

MYSQL* ConexionBD::getConector() {
    return conector;
}

void ConexionBD::cerrar_conexion() {
    if (conector) {
        mysql_close(conector);
        conector = nullptr;  // Asegúrate de no intentar usar el puntero después de cerrarlo.
        cout << "Conexion cerrada correctamente." << endl;
    }
}

void ConexionBD::ejecutarConsulta(const string& consulta) {
    if (!conector) {
        cerr << "Error: Conexion no establecida." << endl;
        return;
    }

    if (mysql_query(conector, consulta.c_str())) {
        cerr << "Error al ejecutar la consulta: " << mysql_error(conector) << endl;
    }
    else {
        cout << "Consulta ejecutada con exito." << endl;
    }
}
