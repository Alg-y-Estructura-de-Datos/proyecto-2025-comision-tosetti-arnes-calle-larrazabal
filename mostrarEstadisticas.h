#ifndef MOSTRAR_ESTADISTICAS_H
#define MOSTRAR_ESTADISTICAS_H

#include "HashMapList.h"
#include <string>
#include <utility>

void mostrarEstadisticas(
    const HashMapList<std::string, double>& ventasPorCiudad,
    const HashMapList<std::string, double>& ventasPorProductoPais,
    const HashMapList<std::string, std::pair<double, int>>& promedioCategoriaPais,
    const HashMapList<std::string, int>& enviosPorPais,
    const HashMapList<std::string, int>& enviosPorCategoria,
    const HashMapList<std::string, double>& ventasPorFecha,
    const HashMapList<std::string, int>& estadoEnvioPorPais,
    const HashMapList<std::string, int>& cantidadVendidaPorProducto
);

#endif
