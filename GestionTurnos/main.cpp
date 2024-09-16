#include "ConexionBD.h"
#include "Migracion.h"
#include "Doctor.h"
#include "Cliente.h"
#include "Turno.h"
#include "Menu.h"
#include <iostream>

int main() {
    // Crear la conexión a la base de datos
    ConexionBD conexion;
    conexion.abrir_conexion();

    // Crear e inicializar las migraciones
    Migracion migraciones(&conexion);
    migraciones.ejecutar_migraciones();

    // Crear los doctores
    insertarDoctoresPorDefecto(&conexion);

    //      MENÚ
    Menu app(40, 40);
    app.iniciar();

    // Cerrar la conexión
    conexion.cerrar_conexion();

    return 0;
}
