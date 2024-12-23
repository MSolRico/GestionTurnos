#include "Doctor.h"
#include "Menu.h"
#include "Verificacion.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

// Constructor de la clase Menu
Menu::Menu(int ancho, int alto, ConexionBD* con) : ancho(ancho), alto(alto), cliente(con), turno(con), con(con) {}

// M�todo principal que controla la aplicaci�n
void Menu::iniciar() {
	int opcion;
	bool iniciado = false; // Para saber si inicio sesion
	bool continuar = true;  // Para controlar si se debe seguir mostrando el men�
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
			aux.push_back(""); // Nuevo elemento se coloca despu�s del �ltimo elemento
			aux.push_back("1. Atras");
			mostrarMenu(aux);
			cout << "Ingrese la opcion 1 para regresar" << endl;
			opcion = validarOpcion(1, 1);
			break;
		case 3: // Sesion Clientes
			if (!iniciado) {
				iniciado = iniciarSesion(); // Crear Cliente
				if (!iniciado) {
					continue; // Regresar al men� principal por no iniciar sesi�n
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
						aux.push_back(""); // Nuevo elemento se coloca despu�s del �ltimo elemento
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
							if (cliente.eliminarCliente(cliente.getDni())) {
								continuar = false;  // La cuenta fue eliminada, salir al men� principal
								iniciado = false;   // La cuenta fue eliminada, por lo que no est� iniciada la sesi�n
							}
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
							do {
								aux.clear();
								aux = turno.leerTurnos(cliente.getId_Cliente()); // Mostrar turnos
								if (aux.empty()) {
									aux.push_back("No tienes ningun turno registrado");
									aux.push_back("");
									aux.push_back("1. Atras");
									mostrarMenu(aux);
									cout << "Ingrese la opcion 1 para regresar" << endl;
									opcion = validarOpcion(1, 1);
									break; // Salir al men� anterior si no hay turnos;
								}
								else {
									aux.clear();
									aux = turno.leerTurnos(cliente.getId_Cliente());
									aux.push_back(""); // Nuevo elemento se coloca despu�s del �ltimo elemento
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
										aux.push_back(""); // Nuevo elemento se coloca despu�s del �ltimo elemento
										aux.push_back("Ingrese el numero del turno a eliminar");
										mostrarMenu(aux);
										vector<int> turnos = turno.getId_Turno(cliente.getId_Cliente());
										cout << "Ingrese la opcion que se requiera: " << endl;
										bool encontrado = false;
										do { // Verificar si el Id_Turno est� en la lista de turnos
											opcion = validarOpcion(1, turnos.back());
											if (find(turnos.begin(), turnos.end(), opcion) == turnos.end()) {
												cout << "Opcion no valida. Intente nuevamente." << endl;
											}
											else {
												encontrado = true; // Si el Id_Turno es v�lido, salir del bucle
											}
										} while (!encontrado); // Repetir hasta que se encuentre una opci�n v�lida
										turno.eliminarTurno(opcion);
										break;
									}
								}
							} while (opcion != 3);
							break;
						}
					} while (opcion != 3);
					break;
				case 3: // Cerrar sesion
					iniciado = false; // Cerr� sesion
					break;
				}
			} while (iniciado && continuar); // Mientras no se cierre sesi�n ni se haya eliminado la cuenta
			break;
		case 4: // Cerrar el programa
			cout << "\nSaliendo del programa..." << endl;
			break;
		}
	} while (opcion != 4);
}

// Dibuja un rect�ngulo en la consola con los bordes y el contenido pasado
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
				output += lineas[i - 1][j - 1];  // Mostrar el texto dentro del rect�ngulo
			}
			else {
				output += " ";  // Espacio vac�o en el interior
			}
		}
		output += "\n";
	}
	cout << output;
}

// Crea el contenido de un men� a partir de un t�tulo y una lista de opciones
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

// Muestra un submen� con las opciones dadas
void Menu::mostrarMenu(const vector<string>& opciones) {
	cout << "Presione Enter para continuar";
	cin.get(); // Espera a que el usuario presione Enter
	system("cls");
	vector<string> menu = crearMenu(opciones);
	dibujarRectangulo(menu);
}

// Inicia sesi�n del cliente
bool Menu::iniciarSesion() {
	string dni;
	mostrarMenu({ "Ingrese su DNI","", "1. Atras" });
	cout << "Ingrese su DNI o la opcion 1 para regresar: " << endl;
	getline(cin, dni);
	while (!validarNumero(dni)) {
		cout << "Error: Solo se permiten numeros. Intentalo nuevamente." << endl;
		getline(cin, dni);
	}
	if (dni == "1") {
		return false; // El usuario eligi� regresar
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

	mostrarMenu({ "Ingrese su nombre: " });
	validarTexto(nombre);
	cliente.setNombre(nombre);

	mostrarMenu({ "Ingrese su apellido: " });
	validarTexto(apellido);
	cliente.setApellido(apellido);

	mostrarMenu({ "Ingrese su obra social: " });
	validarTexto(obraSocial);
	cliente.setObraSocial(obraSocial);

	do {
		mostrarMenu({ "Ingrese su fecha de nacimiento (YYYY-MM-DD): " });
		std::getline(cin, fechaNac);
	} while (!cliente.setFechaNac(fechaNac));  // Se encarga de mostrar el mensaje de error si la fecha es inv�lida

	mostrarMenu({ "Ingrese su direccion: " });
	std::getline(cin, direccion);
	textoVacio(direccion);
	cliente.setDireccion(direccion);

	mostrarMenu({ "Ingrese su telefono: " });
	std::getline(cin, telefono);
	while (!validarNumero(telefono)) {
		cout << "Error: Solo se permiten numeros. Intentalo nuevamente." << endl;
		getline(cin, telefono);
	}
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
		mostrarMenu({ "Horario de atencion: ", "Lunes a Viernes de 08:00 a 18:00",
						  "Sabados de 10:00 a 16:00","","Ingrese la fecha (YYYY-MM-DD): " });
		std::getline(cin, fecha);
	} while (!turno.setFecha(fecha));

	do {
		mostrarMenu({ "Horario de atencion: ", "Lunes a Viernes de 08:00 a 18:00",
						  "Sabados de 10:00 a 16:00","","Ingrese la hora (HH:MM): " });
		std::getline(cin, hora);
	} while (!turno.setHora(hora, fecha));

	if (turno.existeTurno(opcion, fecha, hora)) {
		cerr << "Error: El turno ya est� reservado para este doctor, fecha y hora." << endl;
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

	// Mostrar los datos del cliente y el men� para elegir qu� campo modificar
	aux4.push_back("Elige el numero del campo que deseas modificar :");
	for (size_t i = 0; i < datos.size(); i++) {
		aux4.push_back(to_string(i + 1) + ". " + datos[i]);
	}
	mostrarMenu(aux4);
}

void Menu::modificarTurno() {
	vector<string> aux3;
	int opcion, id;
	aux3 = turno.leerTurnos(cliente.getId_Cliente()); // Mostrar turnos
	aux3.push_back(""); // Nuevo elemento se coloca despu�s del �ltimo elemento
	aux3.push_back("Ingrese el numero del turno que quiere modificar:");
	mostrarMenu(aux3);
	vector<int> turnos = turno.getId_Turno(cliente.getId_Cliente()); // Id_Turnos del Cliente
	cout << "Ingrese la opcion que se requiera: " << endl;
	bool encontrado = false;
	do {
		id = validarOpcion(1, turnos.back());
		if (find(turnos.begin(), turnos.end(), id) == turnos.end()) { // Verificar si el Id_Turno est� en la lista de turnos
			cout << "Opcion no valida. Intente nuevamente." << endl;
		}
		else {
			encontrado = true; // Si el Id_Turno es v�lido, salir del bucle
		}
	} while (!encontrado); // Repetir hasta que se encuentre una opci�n v�lida
	int doctor = turno.getId_Doctor(id);
	string fecha = turno.getFecha(id);
	string hora = turno.getHora(id);
	do {
		mostrarMenu({ "1. Cambiar doctor", "2. Cambiar fecha", "3. Cambiar hora", "4. Aplicar cambios", "5. Cancelar" });
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
				mostrarMenu({ "Horario de atencion: ", "Lunes a Viernes de 08:00 a 18:00",
						  "Sabados de 10:00 a 16:00","","Ingrese la fecha (YYYY-MM-DD): " });
				std::getline(cin, fecha);
			} while (!turno.setFecha(fecha));
			break;
		case 3: // Cambiar hora
			do {
				mostrarMenu({ "Horario de atencion: ", "Lunes a Viernes de 08:00 a 18:00",
						  "Sabados de 10:00 a 16:00","","Ingrese la hora (HH:MM): " });
				std::getline(cin, hora);
			} while (!turno.setHora(hora, fecha));
			break;
		case 4: // Aplicar cambios
			// Verificamos si ya existe un turno con esa combinaci�n de doctor, fecha y hora
			if (!turno.existeTurno(doctor, fecha, hora)) {
				turno.actualizarTurno({ "id_Doctor", "fecha", "hora" }, { to_string(doctor), fecha, hora }, id);
			}
			else {
				cout << "Ya existe un turno con ese doctor, fecha y hora." << endl;
			}
			break;
		case 5: // Cancelar
			cout << "Modificaci�n cancelada." << endl;
			break;
		}
	} while (opcion != 4 && opcion != 5); // Salimos si aplica cambios o cancela
}