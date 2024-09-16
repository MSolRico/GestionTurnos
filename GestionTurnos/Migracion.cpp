#include "Migracion.h"
#include <iostream>
using namespace std;

Migracion::Migracion(ConexionBD* con) {
    conexion = con;

    // Aquí agregamos las migraciones en orden secuencial
    migraciones.push_back("CREATE TABLE IF NOT EXISTS cliente ("
        "id_Cliente INT(11) AUTO_INCREMENT PRIMARY KEY,"
        "dni VARCHAR(30) NOT NULL,"
        "nombre VARCHAR(100) NOT NULL,"
        "apellido VARCHAR(100) NOT NULL,"
        "obraSocial VARCHAR(100),"
        "fechaNac DATE,"
        "direccion VARCHAR(100),"
        "telefono VARCHAR(100),"
        "created_at timestamp NOT NULL DEFAULT current_timestamp(),"
        "updated_at timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()"
        ");");

    migraciones.push_back("CREATE TABLE IF NOT EXISTS doctor ("
        "id_Doctor INT(11) AUTO_INCREMENT PRIMARY KEY,"
        "numMatricula VARCHAR(40) UNIQUE,"
        "nombre VARCHAR(100) NOT NULL,"
        "apellido VARCHAR(100) NOT NULL,"
        "especialidad VARCHAR(100) NOT NULL,"
        "created_at timestamp NOT NULL DEFAULT current_timestamp(),"
        "updated_at timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp()"
        ");");

    migraciones.push_back("CREATE TABLE IF NOT EXISTS turno ("
        "id_Turno INT(11) AUTO_INCREMENT PRIMARY KEY,"
        "fecha DATE NOT NULL,"
        "hora TIME NOT NULL,"
        "observacion VARCHAR(100) DEFAULT NULL,"
        "id_Cliente INT(11) DEFAULT NULL,"
        "id_Doctor INT(11) DEFAULT NULL,"
        "created_at timestamp NOT NULL DEFAULT current_timestamp(),"
        "updated_at timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),"
        "FOREIGN KEY (id_Cliente) REFERENCES cliente(id_Cliente) ON DELETE CASCADE ON UPDATE CASCADE,"
        "FOREIGN KEY (id_Doctor) REFERENCES doctor (id_Doctor) ON DELETE CASCADE ON UPDATE CASCADE"
        ");");
}

void Migracion::ejecutar_migraciones() {
    for (const string& migracion : migraciones) {
        conexion->ejecutarConsulta(migracion);
    }
}
