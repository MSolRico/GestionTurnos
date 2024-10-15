#include "Doctor.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

// Constructor de la clase Menu
Menu::Menu(int ancho, int alto, ConexionBD* con) : ancho(ancho), alto(alto), cliente(con), turno(con), con(con) {}

// Método principal que controla la aplicación
void Menu::iniciar() {
	int opcion;
	bool iniciado = false; // Para saber si inicio sesion
	bool continuar = true;  // Para controlar si se debe seguir mostrando el menú
	vector<string> aux;
	do {
		mostrarMenu({ "1. Contacto de la clinica", "2. Profesionales de la salud", "3. Iniciar Sesion", "4. Salir" }); // Principal
		cout << "Ingrese la opcion que se requiera (1-4)" << endl;
		opcion = validarOpcion(1, 4);
		switch (opcion) {
		case 1: // Contacto
			mostrarMenu({ "Direccion: San Lorenzo 2575", "", "Numero de Telefono: 474879", "",
						  "Horario de atencion:", "Lunes a Viernes de 08:00 a 18:00",
						  "Sabados de 10:00 a 16:00", "", "1. Atras" });
			cout << "Ingrese la opcion 1 para regresar" << endl;
			opcion = validarOpcion(1, 1);
			break;
		case 2: // Doctores
			aux.clear();
			aux = mostrarDoctores(con);
			aux.push_back(""); // Nuevo elemento se coloca después del último elemento
			aux.push_back("1. Atras");
			mostrarMenu(aux);
			cout << "Ingrese la opcion 1 para regresar" << endl;
			opcion = validarOpcion(1, 1);
			break;
		case 3: // Sesion Clientes
			if (!iniciado) {
				iniciado = iniciarSesion(); // Crear Cliente
				if (!iniciado) {
					continue; // Regresar al menú principal por no iniciar sesión
				}
			}
			do {
				mostrarMenu({ "1. Perfil", "2. Turnos", "3. Cerrar Sesion" });
				cout << "Ingrese la opcion que se requiera (1-3)" << endl;
				opcion = validarOpcion(1, 3);
				switch (opcion) {
				case 1: // CRUD Cliente
					do {
						aux.clear();
						aux = cliente.mostrarCliente(cliente.getDni());
						aux.push_back(""); // Nuevo elemento se coloca después del último elemento
						aux.push_back("1. Modificar dato");
						aux.push_back("2. Eliminar cuenta");
						aux.push_back("3. Atras");
						mostrarMenu(aux);
						cout << "Ingrese la opcion que se requiera (1-3)" << endl;
						opcion = validarOpcion(1, 3);
						switch (opcion) {
						case 1: // Actualizar
							modificarCliente();
							cliente.actualizarCliente(cliente.getId_Cliente());
							break;
						case 2: // Eliminar
							cliente.eliminarCliente(cliente.getDni());
							continuar = false;
							break;
						}
					} while (opcion == 1 && continuar);
					break;
				case 2: // CRUD Turno
					do {
						mostrarMenu({ "1. Pedir un turno", "2. Ver mis turnos", "3. Atras" });
						cout << "Ingrese la opcion que se requiera (1-3)" << endl;
						opcion = validarOpcion(1, 3);
						switch (opcion) {
						case 1: // Ver si ya existe y crear turno
							solicitarTurno();
							break;
						case 2: // Ver turnos
							aux.clear();
							aux = turno.leerTurnos(cliente.getId_Cliente()); // Mostrar turnos
							if (aux.empty()) {
								aux.push_back("No tienes ningun turno registrado");
								aux.push_back("");
								aux.push_back("1. Atras");
								mostrarMenu(aux);
								cout << "Ingrese la opcion 1 para regresar" << endl;
								opcion = validarOpcion(1, 1);
								break;
							}
							else {
								do {
									aux.clear();
									aux = turno.leerTurnos(cliente.getId_Cliente());
									aux.push_back(""); // Nuevo elemento se coloca después del último elemento
									aux.push_back("1. Modificar turno");
									aux.push_back("2. Eliminar turno");
									aux.push_back("3. Atras");
									mostrarMenu(aux);
									cout << "Ingrese la opcion que se requiera (1-3)" << endl;
									opcion = validarOpcion(1, 3);
									switch (opcion) {
									case 1: // Modificar turnos
										modificarTurno();
										break;
									case 2: // Eliminar turnos
										aux.clear();
										aux = turno.leerTurnos(cliente.getId_Cliente()); // Mostrar turnos
										aux.push_back(""); // Nuevo elemento se coloca después del último elemento
										aux.push_back("Ingrese el numero del turno a eliminar");
										mostrarMenu(aux);
										vector<int> turnos = turno.getId_Turno(cliente.getId_Cliente()); 
										cout << "Ingrese la opcion que se requiera: " << endl;
										bool encontrado = false;
										do {
											opcion = validarOpcion(1, turnos.back());
											if (find(turnos.begin(), turnos.end(), opcion) == turnos.end()) { // Verificar si el Id_Turno está en la lista de turnos
												cout << "Opcion no valida. Intente nuevamente." << endl;
											}
											else {
												encontrado = true; // Si el Id_Turno es válido, salir del bucle
											}

										} while (!encontrado); // Repetir hasta que se encuentre una opción válida
										turno.eliminarTurno(opcion); // Eliminar turno
										break;
									}
								} while (opcion != 3);
							}
							break;
						}
					} while (opcion != 3);
					break;
				case 3: // Cerrar sesion
					iniciado = false; // Cerró sesion
					break;
				}
			} while (iniciado && continuar); // Mientras no se cierre sesión ni se haya eliminado la cuenta
			break;
		case 4: // Cerrar el programa
			cout << "\nSaliendo del programa..." << endl;
			break;
		}
	} while (opcion != 4);
}

// Dibuja un rectángulo en la consola con los bordes y el contenido pasado
void Menu::dibujarRectangulo(const vector<string>& lineas) const {
	string output;
	for (int i = 0; i < alto; i++) {
		for (int j = 0; j < ancho; j++) {
			if (i == 0 || i == alto - 1) {
				output += "-";  // Bordes horizontales
			}
			else if (j == 0 || j == ancho - 1) {
				output += ".";  // Bordes verticales
			}
			else if (i - 1 < lineas.size() && j - 1 < lineas[i - 1].size()) {
				output += lineas[i - 1][j - 1];  // Mostrar el texto dentro del rectángulo
			}
			else {
				output += " ";  // Espacio vacío en el interior
			}
		}
		output += "\n";
	}
	cout << output;
}

// Crea el contenido de un menú a partir de un título y una lista de opciones
vector<string> Menu::crearMenu(const vector<string>& opciones) const {
	vector<string> menu = { " ", "                     ++++++++", "                     ++++++++", "                     ++++++++",
							"                     ++++++++", "             ++++++++++++++++++++++++", "             ++++++++++++++++++++++++",
							"             ++++++++++++++++++++++++", "                     ++++++++", "                     ++++++++",
							"                     ++++++++", "                     ++++++++", " ",
							"==================================================",
							"             Menu de Consulta Medica",
							"==================================================" };

	menu.insert(menu.end(), opciones.begin(), opciones.end());
	return menu;
}

// Muestra un submenú con las opciones dadas
void Menu::mostrarMenu(const vector<string>& opciones) {
	system("cls");
	vector<string> menu = crearMenu(opciones);
	dibujarRectangulo(menu);
}

// Valida la opción seleccionada dentro de un rango permitido
int Menu::validarOpcion(int min, int max) {
	int opcion;
	string entrada;
	while (true) {
		getline(cin, entrada); // Lee la entrada como string
		// Verificar si la entrada es válida (no vacía)
		if (entrada.empty()) {
			cout << "Entrada vacia. Intente nuevamente." << endl;
			continue; // Volver al inicio del bucle
		}
		try {
			opcion = stoi(entrada); // Usar stoi para convertir string a int
			if (opcion < min || opcion > max) { // Verificar si la opción está dentro del rango permitido
				cout << "Opcion incorrecta. Intente nuevamente." << endl;
			}
			else {
				return opcion; // Devuelve la opción válida
			}
		}
		catch (const invalid_argument& e) {
			cout << "Error: debe ingresar un numero valido." << endl; // Manejo de excepción si no se puede convertir
		}
		catch (const out_of_range& e) {
			cout << "Error: el numero ingresado esta fuera del rango permitido." << endl; // Manejo si el número es muy grande
		}
	}
}

// Inicia sesión del cliente
bool Menu::iniciarSesion() {
	string dni;
		mostrarMenu({ "Ingrese su DNI","", "1. Atras" });
		cout << "Ingrese su DNI o la opcion 1 para regresar: " << endl;
		cin >> dni;
		if (dni == "1") {
			return false; // El usuario eligió regresar
		}

		cliente.setDni(dni);
		if (cliente.buscarCliente() > 0) {
			cout << "El cliente con DNI " << dni << " ya esta registrado." << endl;
			return true;
		}
		else {
			registrarCliente();
			return true;
		}
}

void Menu::registrarCliente() {
	string nombre, apellido, obraSocial, fechaNac, direccion, telefono, created_at, updated_at;
	cin.ignore();

	mostrarMenu({ "Ingrese su nombre: " });
	std::getline(cin, nombre);
	cliente.setNombre(nombre);

	mostrarMenu({ "Ingrese su apellido: " });
	std::getline(cin, apellido);
	cliente.setApellido(apellido);

	mostrarMenu({ "Ingrese su obra social: " });
	std::getline(cin, obraSocial);
	cliente.setObraSocial(obraSocial);

	do {
		mostrarMenu({ "Ingrese su fecha de nacimiento (YYYY-MM-DD): " });
		std::getline(cin, fechaNac);
	} while (!cliente.setFechaNac(fechaNac));  // Se encarga de mostrar el mensaje de error si la fecha es inválida

	mostrarMenu({ "Ingrese su direccion: " });
	std::getline(cin, direccion);
	cliente.setDireccion(direccion);

	mostrarMenu({ "Ingrese su telefono: " });
	std::getline(cin, telefono);
	cliente.setTelefono(telefono);

	cliente.crearCliente();
}

void Menu::solicitarTurno() {
	mostrarMenu(mostrarDoctores(con));
	cout << "Ingrese el ID del doctor con quien desea programar el turno (1-5)" << endl;
	int opcion = validarOpcion(1, 5);
	turno.setId_Doctor(opcion);

	turno.setId_Cliente(cliente.getId_Cliente());

	string fecha, hora;
	do {
		mostrarMenu({ "Ingrese la fecha (YYYY-MM-DD): " });
		std::getline(cin, fecha);
	} while (!turno.setFecha(fecha));

	do {
		mostrarMenu({ "Ingrese la hora (HH:MM): " });
		std::getline(cin, hora);
	} while (!turno.setHora(hora));

	if (turno.existeTurno(opcion, fecha, hora)) {
		cerr << "Error: El turno ya está reservado para este doctor, fecha y hora." << endl;
		return;
	}

	turno.crearTurno();
}

void Menu::modificarCliente() {
	vector<string> datos = cliente.mostrarCliente(cliente.getDni());
	vector <string> aux4;

	if (datos.empty()) {
		cerr << "Cliente no encontrado. No se puede modificar." << endl;
		return;
	}

	// Mostrar los datos del cliente y el menú para elegir qué campo modificar
	aux4.push_back("Elige el numero del campo que deseas modificar :" );
	for (size_t i = 0; i < datos.size(); i++) {
		aux4.push_back(to_string(i+1) + ". " + datos[i]);
	}
	mostrarMenu(aux4);
}

void Menu::modificarTurno() {
	vector<string> aux3;
	int opcion, id;
	aux3 = turno.leerTurnos(cliente.getId_Cliente()); // Mostrar turnos
	aux3.push_back(""); // Nuevo elemento se coloca después del último elemento
	aux3.push_back("Ingrese el numero del turno que quiere modificar:");
	mostrarMenu(aux3);
	vector<int> turnos = turno.getId_Turno(cliente.getId_Cliente()); // Id_Turnos del Cliente
	cout << "Ingrese la opcion que se requiera: " << endl;
	bool encontrado = false;
	do {
		id = validarOpcion(1, turnos.back());
		if (find(turnos.begin(), turnos.end(), id) == turnos.end()) { // Verificar si el Id_Turno está en la lista de turnos
			cout << "Opcion no valida. Intente nuevamente." << endl;
		}
		else {
			encontrado = true; // Si el Id_Turno es válido, salir del bucle
		}
	} while (!encontrado); // Repetir hasta que se encuentre una opción válida
	int doctor = turno.getId_Doctor(id);
	string fecha = turno.getFecha(id);
	string hora = turno.getHora(id);
	do {
		mostrarMenu({ "1. Cambiar doctor", "2. Cambiar fecha", "3. Cambiar hora", "4. Aplicar cambios", "5. Cancelar"});
		cout << "Ingrese la opcion que se requiera (1-5)" << endl;
		opcion = validarOpcion(1, 5);
		switch (opcion) {
		case 1: // Cambiar doctor
			mostrarMenu(mostrarDoctores(con));
			cout << "Ingrese la opcion que se requiera (1-5)" << endl;
			doctor = validarOpcion(1, 5);
			break;
		case 2: // Cambiar fecha
			do {
				mostrarMenu({ "Ingrese la fecha (YYYY-MM-DD): " });
				std::getline(cin, fecha);
			} while (!turno.setFecha(fecha));
			break;
		case 3: // Cambiar hora
			do {
				mostrarMenu({ "Ingrese la hora (HH:MM): " });
				std::getline(cin, hora);
			} while (!turno.setHora(hora));
			break;
		case 4: // Aplicar cambios
			// Verificamos si ya existe un turno con esa combinación de doctor, fecha y hora
			if (!turno.existeTurno(doctor, fecha, hora)) {
				turno.actualizarTurno({ "id_Doctor", "fecha", "hora" }, { to_string(doctor), fecha, hora }, id);
				cout << "Turno modificado exitosamente." << endl;
			} else {
				cout << "Ya existe un turno con ese doctor, fecha y hora." << endl;
			}
			break;
		case 5: // Cancelar
			cout << "Modificación cancelada." << endl;
			break;
		}
	} while (opcion != 4 && opcion != 5); // Salimos si aplica cambios o cancela
}