
// mostrarEstadisticas.cpp
// Descripción: Muestra las estadísticas ya procesadas de forma explicativa

#include <iostream>
#include <string>
#include <limits>
#include "HashMapList.h"
#include "procesarEstadisticas.h"
#include "mostrarEstadisticas.h"

using namespace std;

// Función auxiliar para imprimir el top 5 de ciudades por país
void mostrarTop5Ciudades(const HashMapList<string, double>& ventasPorCiudad) {
    struct Registro {
        string pais;
        string ciudad;
        double monto;
    };

    Lista<Registro> registros;

    for (int i = 0; i < 200; i++) {
        if (!ventasPorCiudad.esVacio()) {
            try {
                ventasPorCiudad.getList("x"); // dummy para forzar la carga de claves
            } catch (...) {}
        }
    }

    // Extraer claves y convertir a lista de registros
    for (int i = 0; i < 200; i++) {
        // claves como: "Peru|Lima"
        try {
            Lista<HashEntry<string, double>>* lista = ventasPorCiudad.getListaEnPos(i);
            if (lista != nullptr) {
                for (size_t j = 0; j < lista->getTamanio(); j++) {
                    auto entry = lista->getDato(j);
                    string clave = entry.getClave();
                    double monto = entry.getValor();
                    size_t posSeparador = clave.find("|");//Porque std::string::find() devuelve size_t, no int, y std::string::npos también es size_t

                    if (posSeparador != string::npos) {
                        string pais = clave.substr(0, posSeparador);
                        string ciudad = clave.substr(posSeparador + 1);
                        registros.insertarUltimo({pais, ciudad, monto});
                    }
                }
            }
        } catch (...) {}
    }

    // Mostrar top 5 por país (sin orden real, ya que ordenar requeriría árbol o sort extra)
    cout << "\nTop ciudades por país (hasta 5):\n";
    Lista<string> paisesMostrados;

    for (int i = 0; i < registros.getTamanio(); i++) {
        string paisActual = registros.getDato(i).pais;
        int yaMostradas = 0;

        for (int j = 0; j < paisesMostrados.getTamanio(); j++) {
            if (paisesMostrados.getDato(j) == paisActual) {
                yaMostradas = 1;
                break;
            }
        }

        if (!yaMostradas) {
            cout << "- País: " << paisActual << endl;
            int count = 0;
            for (int k = 0; k < registros.getTamanio() && count < 5; k++) {
                if (registros.getDato(k).pais == paisActual) {
                    cout << "   Ciudad: " << registros.getDato(k).ciudad << " - $" << registros.getDato(k).monto << endl;
                    count++;
                }
            }
            paisesMostrados.insertarUltimo(paisActual);
        }
    }
}

// Función principal de visualización
void mostrarEstadisticas(
    const HashMapList<string, double>& ventasPorCiudad,
    const HashMapList<string, double>& ventasPorProductoPais,
    const HashMapList<string, pair<double, int>>& promedioCategoriaPais,
    const HashMapList<string, int>& enviosPorPais,
    const HashMapList<string, int>& enviosPorCategoria,
    const HashMapList<string, double>& ventasPorFecha,
    const HashMapList<string, int>& estadoEnvioPorPais,
    const HashMapList<string, int>& cantidadVendidaPorProducto)
{
    cout << "\n--- Estadísticas Generales ---\n" << endl;

    mostrarTop5Ciudades(ventasPorCiudad);

    cout << "\nMonto total vendido por producto y país:" << endl;
    ventasPorProductoPais.print();

    cout << "\nPromedio de ventas por categoría y país:" << endl;
    promedioCategoriaPais.print();

    cout << "\nMedio de envío más utilizado por país:" << endl;
    enviosPorPais.print();

    cout << "\nMedio de envío más utilizado por categoría:" << endl;
    enviosPorCategoria.print();

    cout << "\nEstado de envío más frecuente por país:" << endl;
    estadoEnvioPorPais.print();

    // Día con mayor venta por monto
    double maxMonto = -1;
    string diaMax;
    for (int i = 0; i < 200; i++) {
        try {
            Lista<HashEntry<string, double>>* lista = ventasPorFecha.getListaEnPos(i);
            if (lista != nullptr) {
                for (int j = 0; j < lista->getTamanio(); j++) {
                    auto entry = lista->getDato(j);
                    if (entry.getValor() > maxMonto) {
                        maxMonto = entry.getValor();
                        diaMax = entry.getClave();
                    }
                }
            }
        } catch (...) {}
    }
    cout << "\nDía con mayor monto de ventas: " << diaMax << " ($" << maxMonto << ")" << endl;

    // Producto más y menos vendido (por cantidad)
    int maxCant = -1, minCant = std::numeric_limits<int>::max();
    string prodMax, prodMin;
    for (int i = 0; i < 200; i++) {
        try {
            Lista<HashEntry<string, int>>* lista = cantidadVendidaPorProducto.getListaEnPos(i);
            if (lista != nullptr) {
                for (int j = 0; j < lista->getTamanio(); j++) {
                    auto entry = lista->getDato(j);
                    int cantidad = entry.getValor();
                    if (cantidad > maxCant) {
                        maxCant = cantidad;
                        prodMax = entry.getClave();
                    }
                    if (cantidad < minCant) {
                        minCant = cantidad;
                        prodMin = entry.getClave();
                    }
                }
            }
        } catch (...) {}
    }
    cout << "Producto más vendido (en unidades): " << prodMax << " (" << maxCant << " unidades)" << endl;
    cout << "Producto menos vendido (en unidades): " << prodMin << " (" << minCant << " unidades)" << endl;

    cout << "\n--- Fin de estadísticas ---" << endl;
}
