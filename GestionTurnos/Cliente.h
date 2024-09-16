#pragma once
#include "ConexionBD.h"
#include <string>
#include <vector>

using namespace std;

class Cliente {
private:
    ConexionBD* conexion;
    int id_Cliente;
    string dni;
    string nombre;
    string apellido;
    string obraSocial;
    string fechaNac;
    string direccion;
    string telefono;
    string created_at;
    string updated_at;

public:
    Cliente(ConexionBD* con);
    Cliente(ConexionBD* con, int id_c, const string& dn, const string& nom, const string& ape,
        const string& os, const string& fecha, const string& dire, const string& tel,
        const string& cre_at, const string& up_at);

    // Métodos set (modificar)
    void setId_Cliente(int e);
    void setDni(const string& d);
    void setNombre(const string& n);
    void setApellido(const string& a);
    void setObraSocial(const string& o);
    void setFechaNac(const string& f);
    void setDireccion(const string& di);
    void setTelefono(const string& t);
    void setCreated_at(const string& c);
    void setUpdated_at(const string& u);

    // Métodos get (mostrar)
    int getId_Cliente() const;
    string getDni() const;
    string getNombre() const;
    string getApellido() const;
    string getObraSocial() const;
    string getFechaNac() const;
    string getDireccion() const;
    string getTelefono() const;
    string getCreated_at() const;
    string getUpdated_at() const;

    // Métodos CRUD
    void crearCliente();
    void leerClientes();
    void actualizarCliente();
    void eliminarCliente();
};
