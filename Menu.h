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
    int ancho, alto;         // Dimensiones del men�
    Cliente cliente;         // Instancia del cliente para manejar operaciones relacionadas con clientes
    Turno turno;             // Instancia del turno para manejar operaciones relacionadas con turnos
    ConexionBD* con;         // Puntero a la conexi�n de base de datos

    // M�todos privados para manejar la l�gica interna del men�
    void dibujarRectangulo(const vector<string>& lineas) const;   // Dibuja un rect�ngulo en la consola
    vector<string> crearMenu(const vector<string>& opciones) const; // Crea el dise�o de un men�
    void mostrarMenu(const vector<string>& opciones);             // Muestra un men�
    int validarOpcion(int min, int max);                          // Valida la opci�n seleccionada
    bool iniciarSesion();                                         // Inicia sesi�n del cliente
    void registrarCliente();                                      // Registra un nuevo cliente
    void solicitarTurno();                                        // Solicita un nuevo turno
    void modificarCliente();                                      // Modificar cliente existente
    void modificarTurno();                                        // Modificar turno existente

public:
    // Constructor del men�, recibe las dimensiones del men� y la conexi�n a la base de datos
    Menu(int ancho, int alto, ConexionBD* con);

    // M�todo principal para iniciar la aplicaci�n
    void iniciar();
};

#endif // MENU_H
