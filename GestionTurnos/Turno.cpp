#include "Turno.h"
#include <iostream>

using namespace std;

    //Constructores
Turno::Turno(ConexionBD* con) : conexion(con), id_Turno(0), fecha(""), hora(""), observacion(""),
id_Cliente(0), id_Doctor(0), created_at(""), updated_at("") {}

Turno::Turno(ConexionBD* con, int id_t, const string& f, const string& h, const string& obs,
    int id_cl, int id_do, const string& cre_at, const string& up_at)
    : conexion(con), id_Turno(id_t), fecha(f), hora(h), observacion(obs), id_Cliente(id_cl),
    id_Doctor(id_do), created_at(cre_at), updated_at(up_at) {}

    //Metodos setter
void Turno::setId_Turno(int e) { id_Turno = e; }
void Turno::setFecha(const string& f) { fecha = f; }
void Turno::setHora(const string& h) { hora = h; }
void Turno::setObservacion(const string& obs) { observacion = obs; }
void Turno::setId_Cliente(int id) { id_Cliente = id; }
void Turno::setId_Doctor(int id) { id_Doctor = id; }
void Turno::setCreated_at(const string& c) { created_at = c; }
void Turno::setUpdated_at(const string& u) { updated_at = u; }

    //Metodos getter
int Turno::getId_Turno() const { return id_Turno; }
string Turno::getFecha() const { return fecha; }
string Turno::getHora() const { return hora; }
string Turno::getObservacion() const { return observacion; }
int Turno::getId_Cliente() const { return id_Cliente; }
int Turno::getId_Doctor() const { return id_Doctor; }
string Turno::getCreated_at() const { return created_at; }
string Turno::getUpdated_at() const { return updated_at; }

    //Metodos CRUD
void Turno::crearTurno() {
    string consulta = "INSERT INTO turno (fecha, hora, observacion, id_Cliente, id_Doctor, created_at, updated_at) VALUES ('" +
        fecha + "', '" + hora + "', '" + observacion + "', " + to_string(id_Cliente) +
        ", " + to_string(id_Doctor) + ", '" + created_at + "', '" + updated_at + "')";
    conexion->ejecutarConsulta(consulta);
}

void Turno::leerTurnos() {
    const char* consulta = "SELECT * FROM turno";
    if (mysql_query(conexion->getConector(), consulta)) {
        cerr << "Error al leer los turnos: " << mysql_error(conexion->getConector()) << endl;
        return;
    }

    MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
    if (!resultado) {
        cerr << "Error al almacenar el resultado: " << mysql_error(conexion->getConector()) << endl;
        return;
    }

    int numCampos = mysql_num_fields(resultado);
    MYSQL_ROW fila;
    while ((fila = mysql_fetch_row(resultado))) {
        for (int i = 0; i < numCampos; i++) {
            cout << fila[i] << " ";
        }
        cout << endl;
    }

    mysql_free_result(resultado);
}

void Turno::actualizarTurno() {
    string consulta = "UPDATE turno SET fecha='" + fecha + "', hora='" + hora + "', observacion='" + observacion +
        "', id_Cliente=" + to_string(id_Cliente) + ", id_Doctor=" + to_string(id_Doctor) +
        ", created_at='" + created_at + "', updated_at='" + updated_at +
        "' WHERE id_Turno=" + to_string(id_Turno);
    conexion->ejecutarConsulta(consulta);
}

void Turno::eliminarTurno() {
    string consulta = "DELETE FROM turno WHERE id_Turno=" + to_string(id_Turno);
    conexion->ejecutarConsulta(consulta);
}
