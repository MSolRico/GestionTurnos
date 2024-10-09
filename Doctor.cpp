#include "Doctor.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

void insertarDoctoresPorDefecto(ConexionBD* conexion) {
    string consulta = "INSERT IGNORE INTO doctor (numMatricula, nombre, apellido, especialidad, created_at, updated_at) VALUES "
        "('3748294', 'Juan', 'Perez', 'Cardiologia', '2023-01-15 09:30:00', '2023-07-10 15:45:00'), "
        "('4819372', 'Maria', 'Gonzales', 'Ginecologia', '2022-12-20 08:15:00', '2023-08-05 17:00:00'),"
        "('5820193', 'Pedro', 'Ramirez', 'Otorrinolaringologia', '2023-03-12 10:00:00', '2023-06-15 14:30:00'),"
        "('3950123', 'Laura', 'Fernandez', 'Pediatria', '2023-02-08 11:00:00', '2023-05-30 16:15:00'),"
        "('6738209', 'Diego', 'Martinez', 'Urologia', '2023-04-20 13:30:00', '2023-07-25 09:00:00')";
    conexion->ejecutarConsulta(consulta);
}

vector<string> mostrarDoctores(ConexionBD* conexion) {
    string consulta = "SELECT id_Doctor, numMatricula, nombre, apellido, especialidad FROM doctor;";
    vector<string> doctores;
    
    if (mysql_query(conexion->getConector(), consulta.c_str())) {
        cerr << "Error al mostrar los doctores: " << mysql_error(conexion->getConector()) << endl;
        return doctores;
    }

    MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
    if (!resultado) {
        cerr << "Error al almacenar el resultado de los doctores: " << mysql_error(conexion->getConector()) << endl;
        return doctores;
    }

    MYSQL_ROW fila;
    stringstream ss;

    ss << left << setw(3) << "Id"
        << setw(10) << "Matricula"
        << setw(7) << "Nombre"
        << setw(10) << "Apellido"
        << setw(10) << "Especialidad";
    doctores.push_back(ss.str());

    doctores.push_back("--------------------------------------------------");

    while ((fila = mysql_fetch_row(resultado))) {
        ss.str("");
        ss << left << setw(3) << fila[0]   // Id_Doctor
            << setw(10) << fila[1]    // Num. Matricula
            << setw(7) << fila[2]    // Nombre
            << setw(10) << fila[3]    // Apellido
            << setw(10) << fila[4];    // Especialidad
        doctores.push_back(ss.str()); // Nuevo elemento se coloca después del último elemento
    }

    mysql_free_result(resultado);
    return doctores;
}
