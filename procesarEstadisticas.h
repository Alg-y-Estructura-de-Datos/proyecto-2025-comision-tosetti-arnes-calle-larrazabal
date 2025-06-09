#ifndef PROCESAR_ESTADISTICAS_H
#define PROCESAR_ESTADISTICAS_H

#include <string>
#include "Venta.h"
#include "HashMapList.h"
#include "Lista.h"

using namespace std;

string claveCompuesta(const string& a, const string& b);

void reprocesarEstadisticas(
    const Lista<Venta>& ventas,
    HashMapList<string, double>& ventasPorCiudad,
    HashMapList<string, double>& ventasPorProductoPais,
    HashMapList<string, pair<double, int>>& promedioCategoriaPais,
    HashMapList<string, int>& enviosPorPais,
    HashMapList<string, int>& enviosPorCategoria,
    HashMapList<string, double>& ventasPorFecha,
    HashMapList<string, int>& estadoEnvioPorPais,
    HashMapList<string, int>& cantidadVendidaPorProducto
);
