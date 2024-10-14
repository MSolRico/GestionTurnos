#include "Turno.h"
#include <regex>
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

    //Constructores
Turno::Turno(ConexionBD* con) : conexion(con), id_Turno(0), fecha(""), hora(""),
id_Cliente(0), id_Doctor(0), created_at(""), updated_at("") {}

Turno::Turno(ConexionBD* con, int id_t, const string& f, const string& h,
    int id_cl, int id_do, const string& cre_at, const string& up_at)
    : conexion(con), id_Turno(id_t), fecha(f), hora(h), id_Cliente(id_cl),
    id_Doctor(id_do), created_at(cre_at), updated_at(up_at) {}

    //Metodos setter
void Turno::setId_Turno(int e) { id_Turno = e; }

bool Turno::setFecha(const string& f) {
    if (validarFecha(f)) {
        fecha = f;
        return true;
    } else {
        cerr << "Fecha invalida o anterior a la actual. Asegurate de ingresarla en formato YYYY-MM-DD." << endl;
        return false;
    }
}

bool Turno::setHora(const string& h) {
    if (validarHora(h)) {
        hora = h;
        return true;
    } else {
        cerr << "Hora invalida. Asegurate de ingresarla en formato HH:MM." << endl;
        return false;
    }
}

void Turno::setId_Cliente(int id) { id_Cliente = id; }
void Turno::setId_Doctor(int id) { id_Doctor = id; }
void Turno::setCreated_at(const string& c) { created_at = c; }
void Turno::setUpdated_at(const string& u) { updated_at = u; }

    //Metodos getter
vector<int> Turno::getId_Turno(int id_Cliente) {
    vector<int> idTurnos;

    // Consulta SQL para obtener los id_Turno asociados al id_Cliente
    string consultaStr = "SELECT id_Turno FROM turno WHERE id_Cliente = " + to_string(id_Cliente);

    const char* consulta = consultaStr.c_str();  // Convertir a const char* para usarlo en mysql_query

    if (mysql_query(conexion->getConector(), consulta)) {
        cerr << "Error al obtener los ID de turnos: " << mysql_error(conexion->getConector()) << endl;
        return idTurnos; // Devuelve un vector vacío si hay error
    }

    MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
    if (!resultado) {
        cerr << "Error al almacenar el resultado: " << mysql_error(conexion->getConector()) << endl;
        return idTurnos; // Devuelve un vector vacío si hay error
    }

    MYSQL_ROW fila;
    // Iterar sobre los resultados de la consulta
    while ((fila = mysql_fetch_row(resultado))) {
        int idTurno = atoi(fila[0]); // Convertir el resultado a entero
        idTurnos.push_back(idTurno); // Agregar el id_Turno al vector
    }

    mysql_free_result(resultado); // Liberar el resultado

    return idTurnos; // Devuelve el vector con los ID de turnos
}

string Turno::getFecha(int id) const { 
    string consultaStr = "SELECT fecha FROM turno WHERE id_Turno = " + to_string(id);
    const char* consulta = consultaStr.c_str();

    if (mysql_query(conexion->getConector(), consulta)) {
        cerr << "Error al buscar el id_Turno: " << mysql_error(conexion->getConector()) << endl;
        return "";  // Retorna una cadena vacía en caso de error
    }

    MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
    if (!resultado) {
        cerr << "Error al obtener el resultado: " << mysql_error(conexion->getConector()) << endl;
        return "";
    }

    MYSQL_ROW fila = mysql_fetch_row(resultado);
    string fecha = "";
    if (fila) {
        fecha = fila[0] ? fila[0] : "";  // Asegurarse de que fila[0] no sea nulo
    }
    else {
        cerr << "No se encontro una fecha con el id_Turno: " << id << endl;
    }

    mysql_free_result(resultado);
    return fecha;
    
}

string Turno::getHora(int id) const {
    string consultaStr = "SELECT hora FROM turno WHERE id_Turno = " + to_string(id);
    const char* consulta = consultaStr.c_str();

    if (mysql_query(conexion->getConector(), consulta)) {
        cerr << "Error al buscar el id_Turno: " << mysql_error(conexion->getConector()) << endl;
        return "";  // Retorna una cadena vacía en caso de error
    }

    MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
    if (!resultado) {
        cerr << "Error al obtener el resultado: " << mysql_error(conexion->getConector()) << endl;
        return "";
    }

    MYSQL_ROW fila = mysql_fetch_row(resultado);
    string hora = "";  
    if (fila) {
        hora = fila[0] ? fila[0] : "";  // Asegurarse de que fila[0] no sea nulo
    } else {
        cerr << "No se encontró una hora con el id_Turno: " << id << endl;
    }

    mysql_free_result(resultado);
    return hora;
}

int Turno::getId_Cliente() const { return id_Cliente; }

int Turno::getId_Doctor(int id) const {
    string consulta = "SELECT id_Doctor FROM turno WHERE id_Turno = " + to_string(id);
    conexion->ejecutarConsulta(consulta);
    MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
    if (!resultado) {
        cerr << "Error al obtener el resultado: " << mysql_error(conexion->getConector()) << endl;
        return -1;
    }
    MYSQL_ROW fila = mysql_fetch_row(resultado);
    if (fila) {
        int id = atoi(fila[0]);  // Convertir el valor de id_Doctor a entero
        mysql_free_result(resultado);
        return id;
    } else {
        cerr << "No se encontró un id_Doctor con el id_Turno: " << id << endl;
        mysql_free_result(resultado);
        return -1;
    }
}

string Turno::getCreated_at() const { return created_at; }
string Turno::getUpdated_at() const { return updated_at; }

    //Validar Fecha y hora
bool Turno::validarFecha(const string& fecha) {
    // Validación de formato usando regex (formato: YYYY-MM-DD)
    regex formatoFecha(R"(\d{4}-\d{2}-\d{2})");
    if (!regex_match(fecha, formatoFecha)) {
        return false;
    }

    // Extrae el año, mes y día de la fecha ingresada
    int anio = stoi(fecha.substr(0, 4));
    int mes = stoi(fecha.substr(5, 2));
    int dia = stoi(fecha.substr(8, 2));

    // Verifica que el mes sea válido
    if (mes < 1 || mes > 12) return false;

    // Verifica los días válidos para cada mes
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) return false;
    if (mes == 2) {
        bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if (dia > 29 || (dia == 29 && !esBisiesto)) return false;
    }
    else if (dia > 31) {
        return false;
    }

    // Obtener la fecha actual del sistema
    time_t t = time(0);   // tiempo actual
    tm ahora;
    localtime_s(&ahora, &t);

    // Comparar la fecha ingresada con la fecha actual
    if (anio < (1900 + ahora.tm_year)) return false;  // Año anterior al actual
    if (anio == (1900 + ahora.tm_year)) {
        if (mes < (1 + ahora.tm_mon)) return false;   // Mes anterior al actual
        if (mes == (1 + ahora.tm_mon) && dia <= ahora.tm_mday) return false;  // Día igual o anterior al actual
    }

    return true;  // La fecha es válida y posterior a la actual
}

bool Turno::validarHora(const std::string& hora) {
    // Validación de formato usando regex
    regex formatoHora(R"(\d{2}:\d{2})");
    if (!regex_match(hora, formatoHora)) {
        return false;
    }

    // Extrae la hora y los minutos
    int h = stoi(hora.substr(0, 2));
    int m = stoi(hora.substr(3, 2));

    // Verifica que la hora y los minutos sean válidos
    if (h < 0 || h > 23 || m < 0 || m > 59) return false;

    // Verifica los días y horarios
    tm tm = {};
    istringstream ss(fecha);
    ss >> get_time(&tm, "%Y-%m-%d");
    mktime(&tm); // Normaliza el tiempo

    // Días de la semana (0=domingo, 6=sábado)
    int diaSemana = tm.tm_wday;

    if ((diaSemana >= 1 && diaSemana <= 5 && (h < 8 || h > 18)) || // Lunes a Viernes
        (diaSemana == 6 && (h < 10 || h > 16)) || // Sábados
        (diaSemana == 0)) { // Domingos
        return false;
    }

    return true;
}


    //Metodos CRUD
void Turno::crearTurno() {
    string consulta = "INSERT INTO turno (fecha, hora, id_Cliente, id_Doctor, created_at, updated_at) VALUES ('" +
        fecha + "', '" + hora + "', " + to_string(id_Cliente) + ", " + to_string(id_Doctor) + ", NOW(), NOW())";
    conexion->ejecutarConsulta(consulta);
}

bool Turno::existeTurno(int id_Doctor, const string& fecha, const string& hora) {
    string consultaStr = "SELECT COUNT(*) FROM turno WHERE id_Doctor = " + to_string(id_Doctor) +
        " AND fecha = '" + fecha + "' AND hora = '" + hora + "'";

    const char* consulta = consultaStr.c_str();

    if (mysql_query(conexion->getConector(), consulta)) {
        cerr << "Error al verificar el turno: " << mysql_error(conexion->getConector()) << endl;
        return false; // En caso de error, asumimos que el turno no existe
    }

    MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
    if (!resultado) {
        cerr << "Error al almacenar el resultado: " << mysql_error(conexion->getConector()) << endl;
        return false; // En caso de error, asumimos que el turno no existe
    }

    MYSQL_ROW fila = mysql_fetch_row(resultado);
    bool existe = (atoi(fila[0])>0); // Si hay más de 0, existe el turno

    mysql_free_result(resultado);
    return existe;
}

vector<string> Turno::leerTurnos(int id_Cliente) {
    vector<string> turnos;

    string consultaStr = "SELECT turno.id_Turno, doctor.nombre, doctor.apellido, doctor.especialidad, "
        "turno.fecha, turno.hora FROM turno INNER JOIN doctor ON turno.id_Doctor = doctor.id_Doctor "
        "INNER JOIN cliente on turno.id_Cliente = cliente.id_Cliente WHERE "
        "cliente.id_Cliente = " + to_string(id_Cliente);

    const char* consulta = consultaStr.c_str();  // Convertir a const char* para usarlo en mysql_query

    if (mysql_query(conexion->getConector(), consulta)) {
        cerr << "Error al leer los turnos: " << mysql_error(conexion->getConector()) << endl;
        return turnos; // Devuelve un vector vacío si hay error
    }

    MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
    if (!resultado) {
        cerr << "Error al almacenar el resultado: " << mysql_error(conexion->getConector()) << endl;
        return turnos; // Devuelve un vector vacío si hay error
    }

    int numCampos = mysql_num_fields(resultado);
    MYSQL_ROW fila;
    // Iterar sobre los resultados de la consulta
    while ((fila = mysql_fetch_row(resultado))) {
        // Asegurarse de que los datos existen y no son NULL
        std::string idTurno = fila[0] ? fila[0] : "N/A"; // ID del turno
        std::string doctorNombre = fila[1] ? fila[1] : "N/A";
        std::string doctorApellido = fila[2] ? fila[2] : "N/A";
        std::string especialidad = fila[3] ? fila[3] : "N/A";
        std::string fecha = fila[4] ? fila[4] : "N/A";
        std::string hora = fila[5] ? fila[5] : "N/A"; // Asegurarse de que el índice sea correcto

        // Mostrar los resultados
        turnos.push_back({ "Turno: " + idTurno });
        turnos.push_back({ "Doctor: " + doctorApellido + ", " + doctorNombre });
        turnos.push_back({ "Especialidad: " + especialidad });
        turnos.push_back({ "Fecha: " + fecha });
        turnos.push_back({ "Hora: " + hora });
        turnos.push_back({ "--------------------------- " });
    }

    mysql_free_result(resultado);

    return turnos;
}

void Turno::actualizarTurno(const vector<string>& campos, const vector<string>& nuevosValores, int id) {
    if (campos.size() != nuevosValores.size()) { // Verificamos que el tamaño de ambos vectores sea igual
        cerr << "Error: La cantidad de campos y valores no coincide." << endl;
        return;
    }

    string consulta = "UPDATE turno SET ";

    for (size_t i = 0; i < campos.size(); ++i) {
        consulta += campos[i] + " = '" + nuevosValores[i] + "'";

        if (i < campos.size() - 1) { // Añadir una coma entre cada campo, excepto el último
            consulta += ", ";
        }
    }

    consulta += " WHERE id_Turno = " + to_string(id) + ";";

    if (mysql_query(conexion->getConector(), consulta.c_str())) {
        cout << "Turno actualizado correctamente." << endl;
    } else {
        cerr << "Error al actualizar el turno en la base de datos." << endl;
    }
}

void Turno::eliminarTurno(int id_Turno) {
    // Confirmar antes de eliminar
    char confirmacion;
    cout << "¿Estas seguro de que deseas eliminar el turno? (s/n): ";
    cin >> confirmacion;

    if (confirmacion != 's' && confirmacion != 'S') {
        cout << "Eliminacion cancelada." << endl;
        return;
    }

    string consulta = "DELETE FROM turno WHERE id_Turno=" + to_string(id_Turno);
    
    if (mysql_query(conexion->getConector(), consulta.c_str())) { // Ejecutar la consulta
        cerr << "Error al eliminar el turno: " << mysql_error(conexion->getConector()) << endl;
    }
    else {
        cout << "Turno eliminado correctamente." << endl;
    }

}
