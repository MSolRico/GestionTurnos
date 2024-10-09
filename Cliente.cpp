#include "Cliente.h"
#include <iostream>
#include <regex>

using namespace std;

// Constructores
Cliente::Cliente(ConexionBD* con) : conexion(con), id_Cliente(0), dni(""), nombre(""), apellido(""),
obraSocial(""), fechaNac(""), direccion(""), telefono(""), created_at(""), updated_at("") {}

Cliente::Cliente(ConexionBD* con, int id_c, const string& dn, const string& nom, const string& ape,
    const string& os, const string& fecha, const string& dire, const string& tel,
    const string& cre_at, const string& up_at)
    : conexion(con), id_Cliente(id_c), dni(dn), nombre(nom), apellido(ape), obraSocial(os),
    fechaNac(fecha), direccion(dire), telefono(tel), created_at(cre_at), updated_at(up_at) {}

// M�todos setter
void Cliente::setId_Cliente(int e) { id_Cliente = e; }
void Cliente::setDni(const string& d) { dni = d; }
void Cliente::setNombre(const string& n) { nombre = n; }
void Cliente::setApellido(const string& a) { apellido = a; }
void Cliente::setObraSocial(const string& o) { obraSocial = o; }

bool Cliente::setFechaNac(const string& f) {
    if (validarFecha(f)) {
        fechaNac = f;
        return true;
    } else {
        cerr << "Fecha de nacimiento invalida. Asegurate de ingresarla en formato YYYY-MM-DD." << endl;
        return false;
    }
}

void Cliente::setDireccion(const string& di) { direccion = di; }
void Cliente::setTelefono(const string& t) { telefono = t; }
void Cliente::setCreated_at(const string& c) { created_at = c; }
void Cliente::setUpdated_at(const string& u) { updated_at = u; }

// M�todos getter

int Cliente::getId_Cliente() const {
    if (!dni.empty()) {
        string consultaStr = "SELECT id_Cliente FROM cliente WHERE dni = '" + dni + "';";
        const char* consulta = consultaStr.c_str();

        // Ejecutar la consulta
        if (mysql_query(conexion->getConector(), consulta)) {
            cerr << "Error al buscar el id_Cliente: " << mysql_error(conexion->getConector()) << endl;
            return -1;  // Retorna -1 en caso de error
        }

        // Obtener el resultado
        MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
        if (!resultado) {
            cerr << "Error al obtener el resultado: " << mysql_error(conexion->getConector()) << endl;
            return -1;
        }

        MYSQL_ROW fila = mysql_fetch_row(resultado);
        if (fila) {
            int id = atoi(fila[0]);  // Convertir el valor de id_Cliente a entero
            mysql_free_result(resultado);
            return id;
        }
        else {
            cerr << "No se encontr� un cliente con el DNI: " << dni << endl;
            mysql_free_result(resultado);
            return -1;
        }
    } else {
        cerr << "DNI no proporcionado." << endl;
        return -1;
    }
}

string Cliente::getDni() const { return dni; }
string Cliente::getNombre() const { return nombre; }
string Cliente::getApellido() const { return apellido; }
string Cliente::getObraSocial() const { return obraSocial; }
string Cliente::getFechaNac() const { return fechaNac; }
string Cliente::getDireccion() const { return direccion; }
string Cliente::getTelefono() const { return telefono; }
string Cliente::getCreated_at() const { return created_at; }
string Cliente::getUpdated_at() const { return updated_at; }

// Validaci�n de la fecha
bool Cliente::validarFecha(const string& fecha) {
    // Validaci�n de formato usando regex
    regex formatoFecha(R"(\d{4}-\d{2}-\d{2})");
    if (!regex_match(fecha, formatoFecha)) {
        return false;
    }

    // Extrae el a�o, mes y d�a
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
    return true;
}

// Valida la opci�n seleccionada dentro de un rango permitido
int Cliente::validarOpcion(int min, int max) {
    int opcion;
    string entrada;
    while (true) {
        getline(cin, entrada); // Lee la entrada como string

        // Convertir la entrada a un n�mero entero
        opcion = atoi(entrada.c_str()); // Usar atoi para convertir string a int

        // Verificar si la entrada es v�lida
        if (entrada.empty() || (opcion < min || opcion > max)) {
            cout << "Opci�n incorrecta. Intente nuevamente." << endl;
        }
        else {
            return opcion; // Devuelve la opci�n v�lida
        }
    }
}

// M�todos CRUD
void Cliente::crearCliente() {
    string consulta = "INSERT INTO cliente (dni, nombre, apellido, obraSocial, fechaNac, direccion, telefono, created_at, updated_at) VALUES ('" +
        dni + "', '" + nombre + "', '" + apellido + "', '" + obraSocial + "', '" + fechaNac + "', '" +
        direccion + "', '" + telefono + "', NOW(), NOW())";
    conexion->ejecutarConsulta(consulta);
}

int Cliente::buscarCliente() {
    string consultaStr = "SELECT COUNT(*) FROM cliente WHERE dni = '" + dni + "';";
    const char* consulta = consultaStr.c_str();
    if (mysql_query(conexion->getConector(), consulta)) {
        cerr << "Error al buscar el cliente: " << mysql_error(conexion->getConector()) << endl;
        return -1;
    }

    MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
    if (!resultado) {
        cerr << "Error al almacenar el resultado: " << mysql_error(conexion->getConector()) << endl;
        return -1;
    }

    MYSQL_ROW fila = mysql_fetch_row(resultado);
    if (!fila) {
        cerr << "Error al obtener la fila: " << mysql_error(conexion->getConector()) << endl;
        mysql_free_result(resultado);
        return -1;
    }

    int count = atoi(fila[0]);  // Convertir el valor a entero
    mysql_free_result(resultado);

    return count;
}

vector<string> Cliente::mostrarCliente(const string& dni) {
    vector<string> datosCliente;
    string consultaStr = "SELECT dni, nombre, apellido, obraSocial, fechaNac, direccion, telefono FROM cliente WHERE dni = '" + dni + "'";
    const char* consulta = consultaStr.c_str();

    // Ejecutar la consulta
    if (mysql_query(conexion->getConector(), consulta)) {
        cerr << "Error al obtener el cliente: " << mysql_error(conexion->getConector()) << endl;
        return datosCliente;  // Devuelve un vector vac�o en caso de error
    }

    MYSQL_RES* resultado = mysql_store_result(conexion->getConector());
    if (!resultado) {
        cerr << "Error al almacenar el resultado: " << mysql_error(conexion->getConector()) << endl;
        return datosCliente;  // Devuelve un vector vac�o en caso de error
    }

    MYSQL_ROW fila = mysql_fetch_row(resultado);
    if (fila) {
        // Asignar los datos con las etiquetas correspondientes
        datosCliente.push_back("DNI: " + string(fila[0] ? fila[0] : ""));
        datosCliente.push_back("Nombre: " + string(fila[1] ? fila[1] : ""));
        datosCliente.push_back("Apellido: " + string(fila[2] ? fila[2] : ""));
        datosCliente.push_back("Obra Social: " + string(fila[3] ? fila[3] : ""));
        datosCliente.push_back("Fecha de Nacimiento: " + string(fila[4] ? fila[4] : ""));
        datosCliente.push_back("Direccion: " + string(fila[5] ? fila[5] : ""));
        datosCliente.push_back("Telefono: " + string(fila[6] ? fila[6] : ""));
    }
    else {
        cerr << "No se encontr� el cliente con DNI: " << dni << endl;
    }

    mysql_free_result(resultado);
    return datosCliente;  // Retorna el vector con los datos del cliente
}

void Cliente::actualizarCliente(const string& dni) {
    vector<string> datos = mostrarCliente(dni);

    if (datos.empty()) {
        cerr << "Cliente no encontrado. No se puede modificar." << endl;
        return;
    }

    // Mostrar los datos del cliente y el men� para elegir qu� campo modificar
    cout << "\nElige el numero del campo que deseas modificar:\n";
    for (size_t i = 0; i < datos.size(); i++) {
        cout << i + 1 << ". " << datos[i] << endl;
    }

    int opcion;
    cout << "\nIngrese la opcion que se requiera (1-7)" << endl;
    opcion = validarOpcion(1, 7);

    if (opcion < 1 || opcion > 7) {
        cerr << "Opcion no valida." << endl;
        return;
    }

    string nuevoValor;

    if (opcion == 5) { // Si se selecciona la opci�n 5 (fecha de nacimiento), usar la funci�n de validaci�n
        bool fechaValida = false;
        do {
            cout << "Introduce la nueva fecha de nacimiento (aaaa-mm-dd): ";
            cin.ignore();  // Limpiar el buffer antes de pedir el nuevo valor
            getline(cin, nuevoValor);
            if (validarFecha(nuevoValor)) {
                fechaValida = true;
            }
            else {
                cout << "Formato de fecha incorrecto. Intentalo de nuevo.\n";
            }
        } while (!fechaValida);
    }
    else {
        // Pedir el nuevo valor para los otros campos
        cout << "Introduce el nuevo valor: ";
        cin.ignore();  // Limpiar el buffer antes de pedir el nuevo valor
        getline(cin, nuevoValor);
    }

    // Definir el nombre del campo correspondiente a la opci�n seleccionada
    string campo;
    switch (opcion) {
    case 1: campo = "dni"; break;
    case 2: campo = "nombre"; break;
    case 3: campo = "apellido"; break;
    case 4: campo = "obraSocial"; break;
    case 5: campo = "fechaNac"; break;
    case 6: campo = "direccion"; break;
    case 7: campo = "telefono"; break;
    }

    // Actualizar el campo seleccionado y la fecha de actualizaci�n (updated_at)
    string consulta = "UPDATE cliente SET " + campo + " = '" + nuevoValor + "', updated_at = NOW() WHERE dni = '" + dni + "'";

    if (mysql_query(conexion->getConector(), consulta.c_str())) {
        cerr << "Error al actualizar el cliente: " << mysql_error(conexion->getConector()) << endl;
    }
    else {
        cout << "El cliente ha sido actualizado correctamente." << endl;
    }
}

void Cliente::eliminarCliente(const string& dni) {
    // Confirmar antes de eliminar
    char confirmacion;
    cout << "�Estas seguro de que deseas eliminar al cliente con DNI: " << dni << "? (s/n): ";
    cin >> confirmacion;

    if (confirmacion != 's' && confirmacion != 'S') {
        cout << "Eliminacion cancelada." << endl;
        return;
    }

    // Consulta SQL para eliminar el cliente
    string consulta = "DELETE FROM cliente WHERE dni = '" + dni + "'";

    // Ejecutar la consulta
    if (mysql_query(conexion->getConector(), consulta.c_str())) {
        cerr << "Error al eliminar el cliente: " << mysql_error(conexion->getConector()) << endl;
    }
    else {
        cout << "Cliente eliminado correctamente." << endl;
    }
}