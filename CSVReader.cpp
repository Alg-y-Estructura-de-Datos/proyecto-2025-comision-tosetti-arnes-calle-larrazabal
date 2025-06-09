#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Lista<Venta> leerVentasCSV(const std::string& rutaArchivo) {
    Lista<Venta> listaVentas;
    std::ifstream archivo(rutaArchivo);
    std::string linea;

    if (!archivo.is_open()) {
        std::cout << "Error al abrir el archivo CSV." << std::endl;
        return listaVentas;
    }

    getline(archivo, linea); // saltar encabezado

    while (getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string campo;
        Venta v;

        getline(ss, v.id, ',');
        getline(ss, v.fecha, ',');
        getline(ss, v.pais, ',');
        getline(ss, v.ciudad, ',');
        getline(ss, v.cliente, ',');
        getline(ss, v.producto, ',');
        getline(ss, v.categoria, ',');

        getline(ss, campo, ',');
        v.cantidad = std::stoi(campo);
        getline(ss, campo, ',');
        v.precioUnitario = std::stof(campo);
        getline(ss, campo, ',');
        v.montoTotal = std::stof(campo);

        getline(ss, v.medioEnvio, ',');
        getline(ss, v.estadoEnvio, ',');

        listaVentas.insertarUltimo(v);
    }

    archivo.close();
    return listaVentas;
}
