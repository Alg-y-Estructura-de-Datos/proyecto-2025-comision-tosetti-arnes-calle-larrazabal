//consultasDinamicas.cpp
// Descripción: Contiene funciones para consultas dinámicas del sistema de ventas

#include <iostream>
#include <string>
#include <limits>
#include "Venta.h"
#include "Lista.h"
#include "HashMapList.h"
#include "consultasDinamicas.h"
using namespace std;

// Consulta 1: Mostrar ventas realizadas en una ciudad específica
void consultarVentasPorCiudad(const Lista<Venta>& ventas) {
    string ciudad;
    cout << "Ingrese el nombre de la ciudad: ";
    cin >> ws;
    getline(cin, ciudad);

    cout << "\nVentas realizadas en la ciudad '" << ciudad << "':\n" << endl;
    bool encontradas = false;
    for (int i = 0; i < ventas.getTamanio(); i++) {
        Venta v = ventas.getDato(i);
        if (v.ciudad == ciudad) {
            cout << "- ID: " << v.id << " | Producto: " << v.producto << " | Monto: $" << v.montoTotal << " | Fecha: " << v.fecha << endl;
            encontradas = true;
        }
    }

    if (!encontradas) {
        cout << "No se encontraron ventas registradas en esa ciudad." << endl;
    }
}

// Consulta 2: Ventas por rango de fechas y país
void consultarPorFechaYPais(const Lista<Venta>& ventas) {
    string pais, desde, hasta;
    cout << "Ingrese el país: ";
    cin >> ws;
    getline(cin, pais);
    cout << "Ingrese fecha desde (YYYY-MM-DD): ";
    getline(cin, desde);
    cout << "Ingrese fecha hasta (YYYY-MM-DD): ";
    getline(cin, hasta);

    cout << "\nVentas en " << pais << " entre " << desde << " y " << hasta << ":" << endl;
    bool encontradas = false;

    for (int i = 0; i < ventas.getTamanio(); i++) {
        Venta v = ventas.getDato(i);
        if (v.pais == pais && v.fecha >= desde && v.fecha <= hasta) {
            cout << "- " << v.fecha << " | " << v.producto << " | $" << v.montoTotal << endl;
            encontradas = true;
        }
    }
    if (!encontradas)
        cout << "No se encontraron ventas en ese rango." << endl;
}

// Consulta 3: Comparación entre dos países (monto, producto más vendido, envío más usado)
void compararDosPaises(const Lista<Venta>& ventas) {
    string pais1, pais2;
    cout << "Ingrese el primer país: ";
    cin >> ws;
    getline(cin, pais1);
    cout << "Ingrese el segundo país: ";
    getline(cin, pais2);

    double total1 = 0, total2 = 0;
    for (int i = 0; i < ventas.getTamanio(); i++) {
        Venta v = ventas.getDato(i);
        if (v.pais == pais1) total1 += v.montoTotal;
        if (v.pais == pais2) total2 += v.montoTotal;
    }

    cout << "\nTotal de ventas en " << pais1 << ": $" << total1 << endl;
    cout << "Total de ventas en " << pais2 << ": $" << total2 << endl;
}

// Consulta 4: Comparar dos productos (cantidad total y monto total por país)
void compararProductosPorPais(const Lista<Venta>& ventas) {
    string producto1, producto2;
    cout << "Ingrese el primer producto: ";
    cin >> ws;
    getline(cin, producto1);
    cout << "Ingrese el segundo producto: ";
    getline(cin, producto2);

    int cantidad1 = 0, cantidad2 = 0;
    double monto1 = 0, monto2 = 0;

    for (int i = 0; i < ventas.getTamanio(); i++) {
        Venta v = ventas.getDato(i);
        if (v.producto == producto1) {
            cantidad1 += v.cantidad;
            monto1 += v.montoTotal;
        }
        if (v.producto == producto2) {
            cantidad2 += v.cantidad;
            monto2 += v.montoTotal;
        }
    }

    cout << "\n" << producto1 << ": " << cantidad1 << " unidades, $" << monto1 << endl;
    cout << producto2 << ": " << cantidad2 << " unidades, $" << monto2 << endl;
}

// Consulta 5: Productos vendidos por debajo o encima de un umbral de monto promedio
void productosPorPromedio(const Lista<Venta>& ventas) {
    string pais;
    double umbral;
    char criterio;
    cout << "Ingrese el país: ";
    cin >> ws;
    getline(cin, pais);
    cout << "Ingrese el monto umbral: ";
    cin >> umbral;
    cout << "¿Buscar por debajo (b) o por encima (a)? ";
    cin >> criterio;

    HashMapList<string, pair<double, int>> acumulador(100);

    for (int i = 0; i < ventas.getTamanio(); i++) {
        Venta v = ventas.getDato(i);
        if (v.pais == pais) {
            string clave = v.producto;
            try {
                auto p = acumulador.get(clave);
                acumulador.remove(clave);
                acumulador.put(clave, {p.first + v.montoTotal, p.second + 1});
            } catch (...) {
                acumulador.put(clave, {v.montoTotal, 1});
            }
        }
    }

    cout << "\nProductos en " << pais << " con promedio " << (criterio == 'b' ? "menor" : "mayor") << " a $" << umbral << ":" << endl;
    for (int i = 0; i < 100; i++) {
        Lista<HashEntry<string, pair<double, int>>>* lista = acumulador.getListaEnPos(i);
        if (lista != nullptr) {
            for (int j = 0; j < lista->getTamanio(); j++) {
                auto entry = lista->getDato(j);
                double promedio = entry.getValor().first / entry.getValor().second;
                if ((criterio == 'b' && promedio < umbral) || (criterio == 'a' && promedio > umbral)) {
                    cout << "- " << entry.getClave() << " ($" << promedio << " promedio)" << endl;
                }
            }
        }
    }
}

// Menú de consultas dinámicas
void menuConsultasDinamicas(const Lista<Venta>& ventas) {
    int opcion;
    do {
        cout << "\n--- CONSULTAS DINÁMICAS ---" << endl;
        cout << "1. Listado de ventas en una ciudad específica" << endl;
        cout << "2. Ventas por rango de fechas y país" << endl;
        cout << "3. Comparación entre dos países (monto total)" << endl;
        cout << "4. Comparación entre dos productos por país" << endl;
        cout << "5. Productos vendidos por debajo o encima de un promedio" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                consultarVentasPorCiudad(ventas);
                break;
            case 2:
                consultarPorFechaYPais(ventas);
                break;
            case 3:
                compararDosPaises(ventas);
                break;
            case 4:
                compararProductosPorPais(ventas);
                break;
            case 5:
                productosPorPromedio(ventas);
                break;
            case 0:
                cout << "Volviendo al menú principal..." << endl;
                break;
            default:
                cout << "Opción inválida." << endl;
        }
    } while (opcion != 0);
}
