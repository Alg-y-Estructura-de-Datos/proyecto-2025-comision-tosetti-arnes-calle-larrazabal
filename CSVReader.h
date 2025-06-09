#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include "Venta.h"
#include "Lista.h"

Lista<Venta> leerVentasCSV(const std::string& rutaArchivo);

#endif
