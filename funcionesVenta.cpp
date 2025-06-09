
// Funciones para agregar, eliminar y modificar ventas con pila para deshacer
#include <iostream>
#include <string>
#include "Venta.h"
#include "Lista.h"
#include "Pila.h"
#include "funcionesVenta.h"
using namespace std;

// Pila global para deshacer eliminaciones (última venta eliminada)
Pila<Venta> pilaDeshacer;

void agregarVenta(Lista<Venta>& ventas) {
    Venta nueva;
    cout << "--- Ingreso de nueva venta ---" << endl;

    cout << "ID de venta: ";
    cin >> ws;//limpia el buffer de espacios/enters
    getline(cin, nueva.id);

    cout << "Fecha (YYYY-MM-DD): ";
    getline(cin, nueva.fecha);

    cout << "País: ";
    getline(cin, nueva.pais);

    cout << "Ciudad: ";
    getline(cin, nueva.ciudad);

    cout << "Cliente: ";
    getline(cin, nueva.cliente);

    cout << "Producto: ";
    getline(cin, nueva.producto);

    cout << "Categoría: ";
    getline(cin, nueva.categoria);

    cout << "Cantidad: ";
    cin >> nueva.cantidad;
    cin.ignore();

    cout << "Precio unitario: ";
    cin >> nueva.precioUnitario;
    cin.ignore();

    nueva.montoTotal = nueva.cantidad * nueva.precioUnitario;

    cout << "Medio de envío: ";
    cin >> ws;//limpia el buffer de espacios/enters
    getline(cin, nueva.medioEnvio);

    cout << "Estado del envío: ";
    getline(cin, nueva.estadoEnvio);

    ventas.insertarUltimo(nueva);

    cout << " Venta agregada correctamente." << endl;
}

void eliminarVenta(Lista<Venta>& ventas) {
    string filtro;
    cout << "--- Eliminación de venta ---" << endl;
    cout << "Ingrese ID de venta a eliminar: ";
    cin >> ws;//limpia el buffer de espacios/enters
    getline(cin, filtro);

    bool eliminado = false;
    for (int i = 0; i < ventas.getTamanio(); i++) {
        if (ventas.getDato(i).id == filtro) {
            Venta eliminada = ventas.getDato(i);
            pilaDeshacer.push(eliminada); // Guardar en pila
            ventas.remover(i);
            cout << " Venta eliminada y guardada para deshacer." << endl;
            eliminado = true;
            break;
        }
    }
    if (!eliminado) {
        cout << " No se encontró una venta con ese ID." << endl;
    }
}

void modificarVenta(Lista<Venta>& ventas) {
    string id;
    cout << "--- Modificación de venta ---" << endl;
    cout << "Ingrese ID de venta a modificar: ";
    cin >> ws;//limpia el buffer de espacios/enters
    getline(cin, id);

    bool modificado = false;
    for (int i = 0; i < ventas.getTamanio(); i++) {
        if (ventas.getDato(i).id == id) {
            Venta v = ventas.getDato(i);
            cout << "Modificando venta: " << v.id << " - " << v.producto << endl;

            cout << "Nuevo producto (actual: " << v.producto << "): ";
            getline(cin, v.producto);

            cout << "Nueva cantidad (actual: " << v.cantidad << "): ";
            cin >> v.cantidad;
            cin.ignore();

            cout << "Nuevo precio unitario (actual: " << v.precioUnitario << "): ";
            cin >> v.precioUnitario;
            cin.ignore();

            v.montoTotal = v.cantidad * v.precioUnitario;

            ventas.reemplazar(i, v);
            cout << "Venta modificada exitosamente." << endl;
            modificado = true;
            break;
        }
    }
    if (!modificado) {
        cout << " No se encontró una venta con ese ID." << endl;
    }
}
