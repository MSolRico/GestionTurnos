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
    return {
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
}

int main() {
    int ancho = 40;  // Ajusta el ancho según sea necesario
    int alto = 40;   // Ajusta el alto según sea necesario
    int opcion;

    do {
        vector<string> menu = crearMenu();
        dibujarRectangulo(ancho, alto, menu);
        std::cout << "Ingrese la opcion que se requiera (1-4): ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            do {
                vector<string> menudos = crearMenuDescrip();
                dibujarRectangulo(ancho, alto, menudos);
                std::cout << "Ingrese la opcion 1 para regresar: ";
                std::cin >> opcion;
            } while (opcion != 1);
            break;
        case 2:
            do {
                vector<string> menutres = crearMenuDireccion();
                dibujarRectangulo(ancho, alto, menutres);
                std::cout << "Ingrese la opcion 1 para regresar: ";
                std::cin >> opcion;
            } while (opcion != 1);
            break;
        case 3:
            do {
                vector<string> menucuatro = crearMenuContacto();
                dibujarRectangulo(ancho, alto, menucuatro);
                std::cout << "Ingrese la opcion que requiera (1-2): ";
                std::cin >> opcion;
                if (opcion == 1) {
                    vector<string> menucinco = crearMenuRegistro();
                    dibujarRectangulo(ancho, alto, menucinco);
                    std::cout << "Registro en desarrollo... Volviendo al menú." << std::endl;
                }
            } while (opcion != 2);
            break;
        case 4:
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opcion incorrecta. Ingrese otra opcion." << std::endl;
            break;
        }

    } while (opcion != 4);

    return 0;
}
