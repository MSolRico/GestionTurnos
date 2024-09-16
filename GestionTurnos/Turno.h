#pragma once
#include "ConexionBD.h"
#include <string>

using namespace std;

class Turno {
private:
    ConexionBD* conexion;
    int id_Turno;
    string fecha;
    string hora;
    string observacion;
    int id_Cliente;
    int id_Doctor;
    string created_at;
    string updated_at;

public:
    // Constructores
    Turno(ConexionBD* con);
    Turno(ConexionBD* con, int id_t, const string& f, const string& h, const string& obs,
        int id_cl, int id_do, const string& cre_at, const string& up_at);

    // Métodos set (modificar)
    void setId_Turno(int e);
    void setFecha(const string& f);
    void setHora(const string& h);
    void setObservacion(const string& obs);
    void setId_Cliente(int id);
    void setId_Doctor(int id);
    void setCreated_at(const string& c);
    void setUpdated_at(const string& u);

    // Métodos get (mostrar)
    int getId_Turno() const;
    string getFecha() const;
    string getHora() const;
    string getObservacion() const;
    int getId_Cliente() const;
    int getId_Doctor() const;
    string getCreated_at() const;
    string getUpdated_at() const;

    // Métodos CRUD
    void crearTurno();
    void leerTurnos();
    void actualizarTurno();
    void eliminarTurno();
};
