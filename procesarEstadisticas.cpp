// Archivo: procesarEstadisticas.cpp
// Descripción: Este archivo contiene el procesamiento de estadísticas de ventas
// utilizando estructuras eficientes como HashMapList y Lista, con mínima cantidad de condicionales e impresión de tiempos.
#include <iostream>
#include <ctime>
#include <string>
#include "Venta.h"
#include "HashMapList.h"
#include "Lista.h"

using namespace std;

// Función para obtener clave combinada (por ejemplo: ciudad + país)
string claveCompuesta(const string& a, const string& b) {
    return a + "|" + b;
}

// Procesa todas las estadísticas principales
void reprocesarEstadisticas(const Lista<Venta>& ventas,
    HashMapList<string, double>& ventasPorCiudad,
    HashMapList<string, double>& ventasPorProductoPais,
    HashMapList<string, pair<double, int>>& promedioCategoriaPais,
    HashMapList<string, int>& enviosPorPais,
    HashMapList<string, int>& enviosPorCategoria,
    HashMapList<string, double>& ventasPorFecha,
    HashMapList<string, int>& estadoEnvioPorPais,
    HashMapList<string, int>& cantidadVendidaPorProducto)
{
    clock_t inicio = clock();
    int contadorIfs = 0;

    // Vaciamos estructuras
    ventasPorCiudad = HashMapList<string, double>(200);
    ventasPorProductoPais = HashMapList<string, double>(200);
    promedioCategoriaPais = HashMapList<string, pair<double, int>>(200);
    enviosPorPais = HashMapList<string, int>(200);
    enviosPorCategoria = HashMapList<string, int>(200);
    ventasPorFecha = HashMapList<string, double>(200);
    estadoEnvioPorPais = HashMapList<string, int>(200);
    cantidadVendidaPorProducto = HashMapList<string, int>(200);

    for (int i = 0; i < ventas.getTamanio(); i++) {
        Venta v = ventas.getDato(i);

        // 1. Top 5 ciudades por país (acumulador)
        string claveCiudad = claveCompuesta(v.pais, v.ciudad);
        try { ventasPorCiudad.put(claveCiudad, v.montoTotal); }
        catch (...) {
            double actual = ventasPorCiudad.get(claveCiudad);
            ventasPorCiudad.remove(claveCiudad);
            ventasPorCiudad.put(claveCiudad, actual + v.montoTotal);
        }

        // 2. Monto total por producto y país
        string claveProdPais = claveCompuesta(v.pais, v.producto);
        try { ventasPorProductoPais.put(claveProdPais, v.montoTotal); }
        catch (...) {
            double actual = ventasPorProductoPais.get(claveProdPais);
            ventasPorProductoPais.remove(claveProdPais);
            ventasPorProductoPais.put(claveProdPais, actual + v.montoTotal);
        }

        // 3. Promedio de ventas por categoría en cada país
        string claveCatPais = claveCompuesta(v.pais, v.categoria);
        try { promedioCategoriaPais.put(claveCatPais, {v.montoTotal, 1}); }
        catch (...) {
            auto p = promedioCategoriaPais.get(claveCatPais);
            promedioCategoriaPais.remove(claveCatPais);
            promedioCategoriaPais.put(claveCatPais, {p.first + v.montoTotal, p.second + 1});
        }

        // 4. Medio de envío más utilizado por país
        string claveEnvPais = claveCompuesta(v.pais, v.medioEnvio);
        try { enviosPorPais.put(claveEnvPais, 1); }
        catch (...) {
            int c = enviosPorPais.get(claveEnvPais);
            enviosPorPais.remove(claveEnvPais);
            enviosPorPais.put(claveEnvPais, c + 1);
        }

        // 5. Medio de envío más utilizado por categoría
        string claveEnvCat = claveCompuesta(v.categoria, v.medioEnvio);
        try { enviosPorCategoria.put(claveEnvCat, 1); }
        catch (...) {
            int c = enviosPorCategoria.get(claveEnvCat);
            enviosPorCategoria.remove(claveEnvCat);
            enviosPorCategoria.put(claveEnvCat, c + 1);
        }

        // 6. Día con mayor cantidad de ventas (por monto)
        try { ventasPorFecha.put(v.fecha, v.montoTotal); }
        catch (...) {
            double actual = ventasPorFecha.get(v.fecha);
            ventasPorFecha.remove(v.fecha);
            ventasPorFecha.put(v.fecha, actual + v.montoTotal);
        }

        // 7. Estado de envío más frecuente por país
        string claveEstado = claveCompuesta(v.pais, v.estadoEnvio);
        try { estadoEnvioPorPais.put(claveEstado, 1); }
        catch (...) {
            int c = estadoEnvioPorPais.get(claveEstado);
            estadoEnvioPorPais.remove(claveEstado);
            estadoEnvioPorPais.put(claveEstado, c + 1);
        }

        // 8 y 9. Productos más y menos vendidos (en cantidad total)
        try { cantidadVendidaPorProducto.put(v.producto, v.cantidad); }
        catch (...) {
            int actual = cantidadVendidaPorProducto.get(v.producto);
            cantidadVendidaPorProducto.remove(v.producto);
            cantidadVendidaPorProducto.put(v.producto, actual + v.cantidad);
        }
    }

clock_t fin = clock();
double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

cout << "\n--- Estadísticas Procesadas ---" << endl;
cout << "Estructuras utilizadas: HashMapList y Lista" << endl;
cout << "Algoritmo aplicado: Acumulación mediante manejo de colisiones por listas" << endl;
cout << "Condicionales (if) explícitos: " << contadorIfs << endl;
cout << "Tiempo de ejecución (segundos): " << tiempo << endl;

}
