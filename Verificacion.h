# pragma once
#include <iostream>
#include <string>
using namespace std;

// Métodos validación
bool validarFecha(const string& fecha);              // Validación de la fecha
bool validarFechaTurno(const string& fecha);         // Validar que no acepten dias domingo
bool validarHora(const string& hora, string& fecha); // Valida que sea dentro del horario de atención
int validarOpcion(int min, int max);                 // Valida la opción seleccionada
void validarTexto(string& cadena);                   // Valida que sea un texto
bool validarNumero(const string& cadena);            // Valida que sean solo numeros
void textoVacio(string& texto);			             // Valida que la entrada no este vacia