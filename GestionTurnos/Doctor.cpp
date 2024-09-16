#include "Doctor.h"
#include <iostream>

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
