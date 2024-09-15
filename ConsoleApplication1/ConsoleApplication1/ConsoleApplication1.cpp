#include <iostream>
#include <string>
#include <vector>
using namespace std;

void dibujarRectangulo(int ancho, int alto, const vector<string>& lineas) {
    for (int i = 0; i < alto; i++) {
        for (int j = 0; j < ancho; j++) {
            if (i == 0 || i == alto - 1) {
                cout << "-";  // Bordes horizontales
            }
            else if (j == 0 || j == ancho - 1) {
                cout << ".";  // Bordes verticales
            }
            else if (i - 1 < lineas.size() && j - 1 < lineas[i - 1].size()) {
                cout << lineas[i - 1][j - 1];  // Mostrar el texto dentro del rectángulo
            }
            else {
                cout << " ";  // Espacio vacío en el interior
            }
        }
        cout << endl;
    }
}

vector<string> crearMenu() {
    vector<string> menu = {
        "                                      ",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "                                      ",
        "======================================",
        "       Menu de Consulta Medica",
        "======================================",
        "1. Clinica",
        "2. Direccion de la clinica",
        "3. Contacto de la clinica",
        "4. Salir"
    };
    return menu;
}
vector<string> crearMenuDescrip() {
    vector<string> menudos = {
        "                                      ",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "                                      ",
        "======================================",
        "       Menu de Consulta Medica",
        "======================================",
        " ",
        "1. Atras"
    };
    return menudos;
}
vector<string> crearMenuDireccion() {
    vector<string> menutres = {
        "                                      ",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "                                      ",
        "======================================",
        "       Menu de Consulta Medica",
        "======================================",
        "San Lorenzo 2575",
        "1. Atras"
    };
    return menutres;
}
vector<string> crearMenuContacto() {
    vector<string> menucuatro = {
        "                                      ",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "                                      ",
        "======================================",
        "       Menu de Consulta Medica",
        "======================================",
        "Numero de Telefono: 474879",
        "1. Registro",
        "2. Atras"
    };
    return menucuatro;
}
vector<string> crearMenuRegistro() {
    vector<string> menucinco = {
        "                                      ",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "                                      ",
        "======================================",
        "       Menu de Consulta Medica",
        "======================================",
        "1. Iniciar Sesion",
        "2. Ver disponibilidad",
        "3. Ver Especialidades",
        "4. Atras"
    };
    return menucinco;
}
vector<string> crearMenuSesion() {
    vector<string> menuseis = {
        "                                      ",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "                                      ",
        "======================================",
        "       Menu de Consulta Medica",
        "======================================",
        "1. Ingresar con DNI",
        "2. Registrarse con DNI",
        "3. Atras"
    };
    return menuseis;
}
vector<string> crearMenuDisponibilidades() {
    vector<string> menusiete = {
        "                                      ",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "                                      ",
        "======================================",
        "       Menu de Consulta Medica",
        "======================================",
        "Lunes a Viernes de 08:00 a 18:00",
        " ",
        "Sabados de 10:00 a 16:00 ",
        " ",
        "1. Atras"
    };
    return menusiete;
}


vector<string> crearMenuEspecialidad() {
    vector<string> menuocho = {
        "                                      ",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "       ++++++++++++++++++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "               ++++++++",
        "                                      ",
        "======================================",
        "       Menu de Consulta Medica",
        "======================================",
        "Cardiologia",
        " ",
        "Ginecologia",
        " ",
        "Otorrino",
        " ",
        "Pediatra",
        " ",
        "Urologo",
        " ",
        "1. Atras"
    };
    return menuocho;
}






int main() {
    int ancho = 40;  // Ajusta el ancho según sea necesario
    int alto = 40;    // Ajusta el alto según sea necesario
    int DNI;

    int opcion;
    bool salir;
    do { //opciones del menu
        vector<string> menu = crearMenu();
        dibujarRectangulo(ancho, alto, menu);
        std::cout << "Ingrese la opcion que se requiera (1-4)" << std::endl;
        std::cin >> opcion;
        switch (opcion) {
        case 1:
            do {
                vector<string> menudos = crearMenuDescrip();
                dibujarRectangulo(ancho, alto, menudos);
                std::cout << "Ingrese la opcion 1 para regresar" << std::endl;
                std::cin >> opcion;

            } while (opcion != 1);
            break;
        case 2:
            do {
                vector<string> menutres = crearMenuDireccion();
                dibujarRectangulo(ancho, alto, menutres);
                std::cout << "Ingrese la opcion 1 para regresar" << std::endl;
                std::cin >> opcion;

            } while (opcion != 1);
            break;
        case 3:
            do {
                vector<string> menucuatro = crearMenuContacto();
                dibujarRectangulo(ancho, alto, menucuatro);
                std::cout << "Ingrese la opcion que requiera (1-2)" << std::endl;
                std::cin >> opcion;

                switch (opcion) {
                case 1:
                    do {
                        vector<string> menucinco = crearMenuRegistro();
                        dibujarRectangulo(ancho, alto, menucinco);
                        std::cout << "Ingrese la opcion que requiera (1-4)" << std::endl;
                        std::cin >> opcion;

                        switch (opcion) {
                        case 1:
                            do {
                                vector<string> menuseis = crearMenuSesion();
                                dibujarRectangulo(ancho, alto, menuseis);
                                std::cout << "Ingrese la opcion que requiera (1-3)" << std::endl;
                                std::cin >> opcion;
                            } while (opcion != 3);  // Salir del sub-menú cuando opcion sea 3
                            break;
                            do {

                            }while();
                        case 2:
                            do {
                                vector<string> menusiete = crearMenuDisponibilidades();
                                dibujarRectangulo(ancho, alto, menusiete);
                                std::cout << "Ingrese la opcion 1 para regresar" << std::endl;
                                std::cin >> opcion;
                            } while (opcion != 1);  // Salir del sub-menú cuando opcion sea 1
                            break;

                        case 3:
                            do {
                                vector<string> menuocho = crearMenuEspecialidad();
                                dibujarRectangulo(ancho, alto, menuocho);
                                std::cout << "Ingrese la opcion 1 para regresar" << std::endl;
                                std::cin >> opcion;
                            } while (opcion != 1);  // Salir del sub-menú cuando opcion sea 1
                            break;

                        case 4:
                            std::cout << "Volviendo al menu..." << std::endl;
                            break;

                        default:
                            std::cout << "Opcion incorrecta. Ingrese otra opcion" << std::endl;
                            break;
                        }

                    } while (opcion != 4);  // Volver al menú principal hasta que se elija la opción 4
                    opcion = 0;  // Restablecer opcion después de salir del menú registro
                    break;

                case 2:
                    std::cout << "Volviendo al menú principal..." << std::endl;
                    break;

                default:
                    std::cout << "Opcion incorrecta. Ingrese otra opcion" << std::endl;
                    break;
                }

            } while (opcion != 2);  // Volver al menú principal hasta que se elija la opción 2






        case 4:
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opcion incorrecta. Ingrese otra opcion" << std::endl;
            break;
            }
        
    } while (opcion != 4);
    return 0;
}
