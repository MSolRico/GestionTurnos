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
    int id_Cliente;
    int id_Doctor;
    string created_at;
    string updated_at;

public:
    // Constructores
    Turno(ConexionBD* con);
    Turno(ConexionBD* con, int id_t, const string& f, const string& h,
        int id_cl, int id_do, const string& cre_at, const string& up_at);

    // Métodos set (modificar)
    void setId_Turno(int e);
    bool setFecha(const string& f);
    bool setHora(const string& h, string& fe);
    void setId_Cliente(int id);
    void setId_Doctor(int id);
    void setCreated_at(const string& c);
    void setUpdated_at(const string& u);

    // Métodos get (mostrar)
    vector<int> getId_Turno(int id_Cliente);
    string getFecha(int id) const;
    string getHora(int id) const;
    int getId_Cliente() const;
    int getId_Doctor(int id) const;
    string getCreated_at() const;
    string getUpdated_at() const;

    // Métodos CRUD
    void crearTurno();
    bool existeTurno(int id_Doctor, const string& fecha, const string& hora);
    vector<string> leerTurnos(int id_Cliente);
    void actualizarTurno(const vector<string>& campos, const vector<string>& nuevosValores, int id);
    void eliminarTurno(int id_Turno);
};
