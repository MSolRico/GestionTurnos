#include "Verificacion.h"
#include <iostream>
#include <string>
#include <cctype>
#include <regex>
#include <ctime>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

// Validaci�n de la fecha
bool validarFecha(const string& fecha) {
    // Validaci�n de formato usando regex (formato: YYYY-MM-DD)
    regex formatoFecha(R"(\d{4}-\d{2}-\d{2})");
    if (!regex_match(fecha, formatoFecha)) {
        return false;
    }

    // Extrae el a�o, mes y d�a de la fecha ingresada
    int anio = stoi(fecha.substr(0, 4));
    int mes = stoi(fecha.substr(5, 2));
    int dia = stoi(fecha.substr(8, 2));

    // Verifica que el mes sea v�lido
    if (mes < 1 || mes > 12) return false;

    // Verifica los d�as v�lidos para cada mes
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return false;
    if (mes == 2) {
        bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if (dia > 29 || (dia == 29 && !esBisiesto)) return false;
    }
    else if (dia > 31) {
        return false;
    }

    return true;  // La fecha es v�lida hasta este punto
}

bool validarFechaTurno(const string& fecha) {
    if (!validarFecha(fecha)) {
        return false;  // Si la fecha no es v�lida, retornamos false
    }

    // Obtener la fecha actual del sistema
    time_t t = time(0);   // tiempo actual
    tm ahora;
    localtime_s(&ahora, &t);

    // Extrae el a�o, mes y d�a de la fecha ingresada nuevamente
    int anio = stoi(fecha.substr(0, 4));
    int mes = stoi(fecha.substr(5, 2));
    int dia = stoi(fecha.substr(8, 2));

    // Comparar la fecha ingresada con la fecha actual
    if (anio < (1900 + ahora.tm_year)) return false;  // A�o anterior al actual
    if (anio == (1900 + ahora.tm_year)) {
        if (mes < (1 + ahora.tm_mon)) return false;   // Mes anterior al actual
        if (mes == (1 + ahora.tm_mon) && dia <= ahora.tm_mday) return false;  // D�a igual o anterior al actual
    }

    // Verificaci�n del d�a de la semana
    tm fechaTm = {};
    fechaTm.tm_year = anio - 1900;  // A�o desde 1900
    fechaTm.tm_mon = mes - 1;       // Mes desde 0 (enero es 0)
    fechaTm.tm_mday = dia;

    // Convierte la fecha en una estructura de tiempo
    mktime(&fechaTm);

    // Verifica si es domingo (tm_wday: 0 es domingo, 6 es s�bado)
    if (fechaTm.tm_wday == 0) {
        return false;
    }

    return true;  // La fecha de turno es v�lida
}

bool validarHora(const std::string& hora, std::string& fecha) {
    // Validaci�n de formato usando regex
    regex formatoHora(R"(\d{2}:\d{2})");
    if (!regex_match(hora, formatoHora)) {
        return false;
    }

    // Extrae la hora y los minutos
    int h = stoi(hora.substr(0, 2));
    int m = stoi(hora.substr(3, 2));

    // Verifica que la hora y los minutos sean v�lidos
    if (h < 0 || h > 23 || m < 0 || m > 59) return false;

    // Verifica los d�as y horarios
    tm tm = {};
    istringstream ss(fecha);
    ss >> get_time(&tm, "%Y-%m-%d");
    mktime(&tm); // Normaliza el tiempo

    // D�as de la semana (0=domingo, 6=s�bado)
    int diaSemana = tm.tm_wday;

    if ((diaSemana >= 1 && diaSemana <= 5 && (h < 8 || h > 18)) || // Lunes a Viernes
        (diaSemana == 6 && (h < 10 || h > 16)) || // S�bados
        (diaSemana == 0)) { // Domingos
        return false;
    }

    return true;
}

// Valida la opci�n seleccionada dentro de un rango permitido
int validarOpcion(int min, int max) {
    int opcion;
    string entrada;
    while (true) {
        getline(cin, entrada); // Lee la entrada como string
        // Verificar si la entrada es v�lida (no vac�a)
        if (entrada.empty()) {
            cout << "Entrada vacia. Intente nuevamente." << endl;
            continue; // Volver al inicio del bucle
        }
        try {
            opcion = stoi(entrada); // Usar stoi para convertir string a int
            if (opcion < min || opcion > max) { // Verificar si la opci�n est� dentro del rango permitido
                cout << "Opcion incorrecta. Intente nuevamente." << endl;
            }
            else {
                return opcion; // Devuelve la opci�n v�lida
            }
        }
        catch (const invalid_argument& e) {
            cout << "Error: debe ingresar un numero valido." << endl; // Manejo de excepci�n si no se puede convertir
        }
        catch (const out_of_range& e) {
            cout << "Error: el numero ingresado esta fuera del rango permitido." << endl; // Manejo si el n�mero es muy grande
        }
    }
}

void validarTexto(string& cadena) { // Que solo sean letras
    do {
        getline(cin, cadena); // Captura la entrada del usuario
        textoVacio(cadena); // Primero se asegura que el texto no est� vac�o

        bool esValido = true;
        for (char c : cadena) {
            if (!isalpha(c) && !isspace(c)) {
                cout << "Error: Solo se permiten letras. Intentalo nuevamente." << endl;
                esValido = false;
                break;
            }
        }

        if (esValido) {
            break; // Salimos del bucle si la cadena es v�lida
        }

    } while (true);
}

bool validarNumero(const string& cadena) {
    for (char c : cadena) {
        if (!isdigit(c)) {
            return false; // Contiene un car�cter que no es n�mero
        }
    }
    return true;

}

void textoVacio(string& cadena) {
    do {
        if (cadena.empty()) {
            cout << "Error: Entrada vacia. Intente nuevamente.\n";
            getline(cin, cadena);
        }
    } while (cadena.empty());
}
