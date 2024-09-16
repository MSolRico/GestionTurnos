#include "Cliente.h"
#include <iostream>

using namespace std;

    //Constructores
Cliente::Cliente(ConexionBD* con) : conexion(con), id_Cliente(0), dni(""), nombre(""), apellido(""),
obraSocial(""), fechaNac(""), direccion(""), telefono(""), created_at(""), updated_at("") {}

Cliente::Cliente(ConexionBD* con, int id_c, const string& dn, const string& nom, const string& ape,
    const string& os, const string& fecha, const string& dire, const string& tel,
    const string& cre_at, const string& up_at)
    : conexion(con), id_Cliente(id_c), dni(dn), nombre(nom), apellido(ape), obraSocial(os),
    fechaNac(fecha), direccion(dire), telefono(tel), created_at(cre_at), updated_at(up_at) {}

    //Metodos setter
void Cliente::setId_Cliente(int e) { id_Cliente = e; }
void Cliente::setDni(const string& d) { dni = d; }
void Cliente::setNombre(const string& n) { nombre = n; }
void Cliente::setApellido(const string& a) { apellido = a; }
void Cliente::setObraSocial(const string& o) { obraSocial = o; }
void Cliente::setFechaNac(const string& f) { fechaNac = f; }
void Cliente::setDireccion(const string& di) { direccion = di; }
void Cliente::setTelefono(const string& t) { telefono = t; }
void Cliente::setCreated_at(const string& c) { created_at = c; }
void Cliente::setUpdated_at(const string& u) { updated_at = u; }

    //Metodos getter
int Cliente::getId_Cliente() const { return id_Cliente; }
string Cliente::getDni() const { return dni; }
string Cliente::getNombre() const { return nombre; }
string Cliente::getApellido() const { return apellido; }
string Cliente::getObraSocial() const { return obraSocial; }
string Cliente::getFechaNac() const { return fechaNac; }
string Cliente::getDireccion() const { return direccion; }
string Cliente::getTelefono() const { return telefono; }
string Cliente::getCreated_at() const { return created_at; }
string Cliente::getUpdated_at() const { return updated_at; }

    //METODOS CRUD
void Cliente::crearCliente() {
    string consulta = "INSERT INTO cliente (dni, nombre, apellido, obraSocial, fechaNac, direccion, telefono, created_at, updated_at) VALUES ('" +
        dni + "', '" + nombre + "', '" + apellido + "', '" + obraSocial + "', '" + fechaNac + "', '" +
        direccion + "', '" + telefono + "', '" + created_at + "', '" + updated_at + "')";
    conexion->ejecutarConsulta(consulta);
}

void Cliente::leerClientes() {
    const char* consulta = "SELECT * FROM cliente";
    if (mysql_query(conexion->getConector(), consulta)) {
        cerr << "Error al leer los clientes: " << mysql_error(conexion->getConector()) << endl;
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

void Cliente::actualizarCliente() {
    string consulta = "UPDATE cliente SET dni='" + dni + "', nombre='" + nombre + "', apellido='" + apellido +
        "', obraSocial='" + obraSocial + "', fechaNac='" + fechaNac + "', direccion='" + direccion +
        "', telefono='" + telefono + "', created_at='" + created_at + "', updated_at='" + updated_at +
        "' WHERE id_Cliente=" + to_string(id_Cliente);
    conexion->ejecutarConsulta(consulta);
}

void Cliente::eliminarCliente() {
    string consulta = "DELETE FROM cliente WHERE id_Cliente=" + to_string(id_Cliente);
    conexion->ejecutarConsulta(consulta);
}
