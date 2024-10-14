#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include "Cliente.h"
#include "Turno.h"
#include "Doctor.h"
#include "ConexionBD.h"

using namespace std;

class Menu {
private:
    int ancho, alto;         // Dimensiones del menú
    Cliente cliente;         // Instancia del cliente para manejar operaciones relacionadas con clientes
    Turno turno;             // Instancia del turno para manejar operaciones relacionadas con turnos
    ConexionBD* con;         // Puntero a la conexión de base de datos

    // Métodos privados para manejar la lógica interna del menú
    void dibujarRectangulo(const vector<string>& lineas) const;   // Dibuja un rectángulo en la consola
    vector<string> crearMenu(const vector<string>& opciones) const; // Crea el diseño de un menú
    void mostrarMenu(const vector<string>& opciones);             // Muestra un menú
    int validarOpcion(int min, int max);                          // Valida la opción seleccionada
    bool iniciarSesion();                                         // Inicia sesión del cliente
    void registrarCliente();                                      // Registra un nuevo cliente
    void solicitarTurno();                                        // Solicita un nuevo turno
    void modificarCliente();                                      // Modificar cliente existente
    void modificarTurno();                                        // Modificar turno existente

public:
    // Constructor del menú, recibe las dimensiones del menú y la conexión a la base de datos
    Menu(int ancho, int alto, ConexionBD* con);

    // Método principal para iniciar la aplicación
    void iniciar();
};

#endif // MENU_H
