#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Menu {
private:
    int ancho;
    int alto;

public:
    Menu(int ancho, int alto) : ancho(ancho), alto(alto) {}

    // Método principal que controla la aplicación
    void iniciar() {
        int opcion;
        do {
            mostrarMenu({ "1. Clinica", "2. Direccion de la clinica", "3. Contacto de la clinica", "4. Salir" }); //Principal
            cout << "Ingrese la opcion que se requiera (1-4)" << endl;
            cin >> opcion;

            switch (opcion) {
            case 1:
                do {
                    mostrarMenu({ " ", "1. Atras" }); //Descripcion
                    cout << "Ingrese la opcion 1 para regresar" << endl;
                    cin >> opcion;
                } while (opcion != 1);
                break;
            case 2:
                do {
                    mostrarMenu({ "San Lorenzo 2575", "1. Atras" }); //Direccion
                    cout << "Ingrese la opcion 1 para regresar" << endl;
                    cin >> opcion;
                } while (opcion != 1);
                break;
            case 3:
                do {
                    mostrarMenu({ "Numero de Telefono: 474879", "1. Registro", "2. Atras" }); //Contacto
                    cout << "Ingrese la opcion que requiera (1-2)" << endl;
                    cin >> opcion;
                    switch (opcion) {
                    case 1:
                        do {
                            mostrarMenu({ "1. Iniciar Sesion", "2. Ver disponibilidad", "3. Ver Especialidades", "4. Atras" }); //Registro
                            cout << "Ingrese la opcion que requiera (1-4)" << endl;
                            cin >> opcion;
                            switch (opcion) {
                            case 1:
                                do {
                                    mostrarMenu({ "1. Ingresar con DNI", "2. Registrarse con DNI", "3. Atras" }); //Sesion
                                    cout << "Ingrese la opcion que requiera (1-3)" << endl;
                                    cin >> opcion;
                                } while (opcion != 3);  // Salir del sub-menú cuando opcion sea 3
                                break;
                            case 2:
                                do {
                                    mostrarMenu({ "Lunes a Viernes de 08:00 a 18:00", " ", "Sabados de 10:00 a 16:00", " ", "1. Atras" }); //Disponibilidades
                                    cout << "Ingrese la opcion 1 para regresar" << endl;
                                    cin >> opcion;
                                } while (opcion != 1);  // Salir del sub-menú cuando opcion sea 1
                                break;
                            case 3:
                                do {
                                    mostrarMenu({ "Cardiologia", " ", "Ginecologia", " ", "Otorrinolaringologia", " ", "Pediatria", " ", "Urologia", " ", "1. Atras" }); //Especialidad
                                    cout << "Ingrese la opcion 1 para regresar" << endl;
                                    cin >> opcion;
                                } while (opcion != 1);  // Salir del sub-menú cuando opcion sea 1
                                break;
                            case 4:
                                cout << "Volviendo al menu..." << endl;
                                break;
                            default:
                                cout << "Opcion incorrecta. Ingrese otra opcion" << endl;
                                break;
                            }
                        } while (opcion != 4);  // Volver al menú principal hasta que se elija la opción 4
                        opcion = 0;  // Restablecer opcion después de salir del menú registro
                        break;
                    case 2:
                        cout << "Volviendo al menú principal..." << endl;
                        break;
                    default:
                        cout << "Opcion incorrecta. Ingrese otra opcion" << endl;
                        break;
                    }
                } while (opcion != 2);  // Volver al menú principal hasta que se elija la opción 2
            case 4:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion incorrecta. Ingrese otra opcion" << endl;
                break;
            }
        } while (opcion != 4);
    }

private:
    // Dibuja un rectángulo en la consola con los bordes y el contenido pasado
    void dibujarRectangulo(const vector<string>& lineas) const {
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
    vector<string> crearMenu(const vector<string>& opciones) const {
        vector<string> menu = { " ", "               ++++++++", "               ++++++++", "               ++++++++", "               ++++++++",
                                "       ++++++++++++++++++++++++", "       ++++++++++++++++++++++++",
                                "       ++++++++++++++++++++++++", "               ++++++++", "               ++++++++",
                                "               ++++++++", "               ++++++++", " ",
                                "======================================",
                                "       Menu de Consulta Medica",
                                "======================================" };

        menu.insert(menu.end(), opciones.begin(), opciones.end());
        return menu;
    }

    // Muestra un submenú con las opciones dadas
    void mostrarMenu(const vector<string>& opciones) {
        vector<string> menu = crearMenu(opciones);
        dibujarRectangulo(menu);
    }
};