#include "ConexionBD.h"
#include "Migracion.h"
#include "Doctor.h"
#include "Cliente.h"
#include "Turno.h"
#include "Menu.h"
#include <iostream>

int main() {
	cout << "Creando la conexion a la base de datos:" << endl;
	ConexionBD conexion;
	conexion.abrir_conexion();

	cout << "\nCreando e inicializando migraciones:" << endl;
	Migracion migraciones(&conexion);
	migraciones.ejecutar_migraciones();

	cout << "\nCreando doctores en la base de datos:" << endl;
	insertarDoctoresPorDefecto(&conexion);
	cout << "\n";

	//      MENÚ
	Menu app(52, 40, &conexion);
	app.iniciar();

	// Cerrar la conexión
	conexion.cerrar_conexion();

	return 0;
}
