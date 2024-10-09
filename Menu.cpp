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
    vector<string> aux;
    do {
        mostrarMenu({ "1. Contacto de la clinica", "2. Profesionales de la salud", "3. Iniciar Sesion", "4. Salir" }); // Principal
        cout << "Ingrese la opcion que se requiera (1-4)" << endl;
        opcion = validarOpcion(1, 4);
        switch (opcion) {
        case 1: // Contacto
            do {
                mostrarMenu({ "Direccion: San Lorenzo 2575", "", "Numero de Telefono: 474879", "",
                              "Horario de atencion:", "Lunes a Viernes de 08:00 a 18:00",
                              "Sabados de 10:00 a 16:00", "", "1. Atras" });
                cout << "Ingrese la opcion 1 para regresar" << endl;
                opcion = validarOpcion(1, 1);
            } while (opcion != 1);
            break;
        case 2: // Doctores
            do {
                aux = mostrarDoctores(con);
                aux.push_back(""); // Nuevo elemento se coloca después del último elemento
                aux.push_back("1. Atras");
                mostrarMenu(aux);
                cout << "Ingrese la opcion 1 para regresar" << endl;
                opcion = validarOpcion(1, 1);
            } while (opcion != 1);
            break;
        case 3: // Sesion Clientes
            iniciarSesion(); // Crear Cliente
            mostrarMenu({ "1. Perfil", "2. Turnos", "3. Cerrar Sesion" });
            cout << "Ingrese la opcion que se requiera (1-3)" << endl;
            opcion = validarOpcion(1, 3);
            switch (opcion) {
            case 1:
                do {
                    aux = cliente.mostrarCliente(cliente.getDni()); // CRUD Cliente
                    aux.push_back(""); // Nuevo elemento se coloca después del último elemento
                    aux.push_back("1. Modificar dato");
                    aux.push_back("2. Eliminar cuenta");
                    aux.push_back("3. Atras");
                    mostrarMenu(aux);
                    cout << "Ingrese la opcion que se requiera (1-3)" << endl;
                    opcion = validarOpcion(1, 3);
                    switch (opcion) {
                    case 1:
                        cliente.actualizarCliente(cliente.getDni()); // Actualizar
                        break;
                    case 2:
                        cliente.eliminarCliente(cliente.getDni()); // Eliminar
                        break;
                    }
                } while (opcion == 1);
            case 2:
                do {
                    mostrarMenu({ "1. Pedir un turno", "2. Ver mis turnos", "3. Atras" }); // CRUD Turno
                    cout << "Ingrese la opcion que se requiera (1-3)" << endl;
                    opcion = validarOpcion(1, 3);
                    switch (opcion) {
                    case 1:
                        solicitarTurno(); // Ver si ya existe y crear turno
                        break;
                    case 2:
                        do {
                            aux = turno.leerTurnos(cliente.getId_Cliente()); // Mostrar turnos
                            aux.push_back(""); // Nuevo elemento se coloca después del último elemento
                            aux.push_back("1. Modificar turno");
                            aux.push_back("2. Eliminar turno");
                            aux.push_back("3. Atras");
                            mostrarMenu(aux);
                            cout << "Ingrese la opcion que se requiera (1-3)" << endl;
                            opcion = validarOpcion(1, 3);
                            switch (opcion)
                            {
                            case 1:
                                modificarTurno();
                                break;
                            case 2:
                                aux = turno.leerTurnos(cliente.getId_Cliente()); // Mostrar turnos
                                aux.push_back(""); // Nuevo elemento se coloca después del último elemento
                                aux.push_back("Ingrese el numero del turno a eliminar");
                                int m = turno.buscarTurno(cliente.getId_Cliente()); // Cantidad de turnos
                                cout << "Ingrese la opcion que se requiera (1-" + to_string(m) + ")" << endl;
                                opcion = validarOpcion(1, m);
                                turno.eliminarTurno(opcion); // Eliminar turno
                                break;
                            }
                        } while (opcion != 3);
                        break;
                    }
                } while (opcion != 3);
                break;
            }
            break;
        case 4:
            cout << "Saliendo del programa..." << endl;
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
    vector<string> menu = crearMenu(opciones);
    dibujarRectangulo(menu);
}

// Valida la opción seleccionada dentro de un rango permitido
int Menu::validarOpcion(int min, int max) {
    int opcion;
    string entrada;
    while (true) {
        getline(cin, entrada); // Lee la entrada como string

        // Convertir la entrada a un número entero
        opcion = atoi(entrada.c_str()); // Usar atoi para convertir string a int

        // Verificar si la entrada es válida
        if (entrada.empty() || (opcion < min || opcion > max)) {
            cout << "Opción incorrecta. Intente nuevamente." << endl;
        }
        else {
            return opcion; // Devuelve la opción válida
        }
    }
}

// Inicia sesión del cliente
void Menu::iniciarSesion() {
    string dni;
    do {
        mostrarMenu({ "Ingrese su DNI","", "1. Atras" });
        cout << "Ingrese su DNI o la opcion 1 para regresar: " << endl;
        cin >> dni;
        if (dni == "1") break;

        cliente.setDni(dni);
        if (cliente.buscarCliente() > 0) {
            cout << "El cliente con DNI " << dni << " ya esta registrado." << endl;
            break;
        }
        else {
            registrarCliente();
            break;
        }
    } while (dni != "1");
}

void Menu::registrarCliente() {
    string nombre, apellido, obraSocial, fechaNac, direccion, telefono, created_at, updated_at;
    cin.ignore();

    mostrarMenu({"Ingrese su nombre: "});
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
    int opcion;
    mostrarDoctores(con);
    cout << "Ingrese la opcion que se requiera (1-5)" << endl;
    opcion = validarOpcion(1, 5);
    turno.setId_Doctor(opcion);

    turno.setId_Cliente(cliente.getId_Cliente());

    string fecha, hora;
    do {
        mostrarMenu({ "Ingrese la fecha (YYYY-MM-DD): " });
        std::getline(cin, fecha);
    } while (!turno.setFecha(fecha));

    do {
        mostrarMenu({ "Ingrese la hora (HH-MM): " });
        std::getline(cin, hora);
    } while (!turno.setHora(hora));

    if (turno.existeTurno(opcion, fecha, hora)>0) {
        cerr << "Error: El turno ya está reservado para este doctor, fecha y hora." << endl;
        return;
    }

    turno.crearTurno();
}

void Menu::modificarTurno() {
    vector<string> aux3;
    int opcion, id;
    aux3 = turno.leerTurnos(cliente.getId_Cliente()); // Mostrar turnos
    aux3.push_back(""); // Nuevo elemento se coloca después del último elemento
    aux3.push_back("Ingrese el numero del turno que quiere modificar:");
    int m = turno.buscarTurno(cliente.getId_Cliente()); // Cantidad de turnos
    cout << "Ingrese la opcion que se requiera (1-" + to_string(m) + ")" << endl;
    id = validarOpcion(1, m);  
    do {
        mostrarMenu({ "1. Cambiar doctor", "2. Cambiar fecha", "3. Cambiar hora", "4. Atras" });
        cout << "Ingrese la opcion que se requiera (1-4)" << endl;
        opcion = validarOpcion(1, 4);
        string fecha, hora;
        switch (opcion) {
        case 1:
            mostrarDoctores(con);
            cout << "Ingrese la opcion que se requiera (1-5)" << endl;
            opcion = validarOpcion(1, 5);
            turno.actualizarTurno({ "id_Doctor" }, to_string(opcion), id);
            break;
        case 2:
            do {
                mostrarMenu({ "Ingrese la fecha (YYYY-MM-DD): " });
                std::getline(cin, fecha);
            } while (!turno.setFecha(fecha));
            turno.actualizarTurno({ "fecha" }, fecha, id);
            break;
        case 3:
            do {
                mostrarMenu({ "Ingrese la hora (HH-MM): " });
                std::getline(cin, hora);
            } while (!turno.setHora(hora));
            turno.actualizarTurno({ "hora" }, hora, id);
            break;
        }
    } while (opcion != 4);
}