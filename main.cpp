#include <iostream>
#include <ctime>
#include "CSVReader.h"

#include "Venta.h"
#include "HashMapList.h"
#include "procesarEstadisticas.h"
#include "mostrarEstadisticas.h"
#include "funcionesVenta.h"
#include "consultasDinamicas.h"
using namespace std;
/*procesarEstadisticas.cpp	Ahí está la función reprocesarEstadisticas(...)
CSVReader.cpp	Ahí está la función leerVentasCSV(...)
mostrarEstadisticas.cpp	Mostrará estadísticas, usás funciones de ahí en el menú
funcionesVenta.cpp	Ahí tenés agregarVenta, eliminarVenta, modificarVenta
consultasDinamicas (1).cpp	Usás menuConsultasDinamicas(...) en la opción 5 del menú*/


int main() {
    cout << "Cargando archivo ventas_sudamerica.csv..." << endl;
    Lista<Venta> ventas = leerVentasCSV("ventas_sudamerica.csv");
    cout << "Ventas cargadas: " << ventas.getTamanio() << endl;

    if (ventas.esVacia()) {
    cout << " El archivo no se pudo leer o está vacío. Cerrando programa." << endl;
    system("pause");
    return 1;
    }


    // Estructuras para estadísticas
    HashMapList<string, double> ventasPorCiudad(200);
    HashMapList<string, double> ventasPorProductoPais(200);
    HashMapList<string, pair<double, int>> promedioCategoriaPais(200);
    HashMapList<string, int> enviosPorPais(200);
    HashMapList<string, int> enviosPorCategoria(200);
    HashMapList<string, double> ventasPorFecha(200);
    HashMapList<string, int> estadoEnvioPorPais(200);
    HashMapList<string, int> cantidadVendidaPorProducto(200);
   
    // Procesamiento inicial
    reprocesarEstadisticas(ventas,
                            ventasPorCiudad,
                            ventasPorProductoPais,
                            promedioCategoriaPais,
                            enviosPorPais,
                            enviosPorCategoria,
                            ventasPorFecha,
                            estadoEnvioPorPais,
                            cantidadVendidaPorProducto);

    int opcion ;
    do {
        cout << "\n--- MENÚ PRINCIPAL ---" << endl;
        cout << "1. Mostrar estadísticas generales" << endl;
        cout << "2. Agregar nueva venta" << endl;
        cout << "3. Eliminar venta" << endl;
        cout << "4. Modificar venta" << endl;
        cout << "5. Consultas dinámicas" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opción: ";
        if (!(cin >> opcion)) {
        cerr << "[ERROR] Entrada inválida. Terminando programa." << endl;
        break;
}

        switch (opcion) {
            case 1: {
                clock_t inicio = clock();
                int ifs = 0;

                mostrarEstadisticas(
                    ventasPorCiudad,
                    ventasPorProductoPais,
                    promedioCategoriaPais,
                    enviosPorPais,
                    enviosPorCategoria,
                    ventasPorFecha,
                    estadoEnvioPorPais,
                    cantidadVendidaPorProducto);

                clock_t fin = clock();
                double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

                cout << "Proceso: Mostrar estadísticas" << endl;
                cout << "Estructura: HashMapList" << endl;
                cout << "Ifs explícitos: " << ifs << endl;
                cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
                break;
            }
            case 2: {
                clock_t inicio = clock();
                int ifs = 0;

                agregarVenta(ventas);
                reprocesarEstadisticas(ventas,
                    ventasPorCiudad,
                    ventasPorProductoPais,
                    promedioCategoriaPais,
                    enviosPorPais,
                    enviosPorCategoria,
                    ventasPorFecha,
                    estadoEnvioPorPais,
                    cantidadVendidaPorProducto);

                clock_t fin = clock();
                double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

                cout << "Proceso: Agregar venta + Reprocesamiento" << endl;
                cout << "Estructura: Lista + HashMapList" << endl;
                cout << "Ifs explícitos: " << ifs << endl;
                cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
                break;
            }
           case 3: {
                clock_t inicio = clock();
                int ifs = 1; // usamos 1 if explícito para verificar si se encontró el ID

                eliminarVenta(ventas);

                // Reprocesar después de eliminar
                reprocesarEstadisticas(ventas,
                    ventasPorCiudad,
                    ventasPorProductoPais,
                    promedioCategoriaPais,
                    enviosPorPais,
                    enviosPorCategoria,
                    ventasPorFecha,
                    estadoEnvioPorPais,
                    cantidadVendidaPorProducto);

                clock_t fin = clock();
                double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

                cout << "Proceso: Eliminar venta + Reprocesamiento" << endl;
                cout << "Estructura: Lista + Pila + HashMapList" << endl;
                cout << "Ifs explícitos: " << ifs << endl;
                cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
                break;
            }

            case 4: {
                clock_t inicio = clock();
                int ifs = 1; // también un solo if para verificar coincidencia por ID

                modificarVenta(ventas);

                // Reprocesar después de modificar
                reprocesarEstadisticas(ventas,
                    ventasPorCiudad,
                    ventasPorProductoPais,
                    promedioCategoriaPais,
                    enviosPorPais,
                    enviosPorCategoria,
                    ventasPorFecha,
                    estadoEnvioPorPais,
                    cantidadVendidaPorProducto);

                clock_t fin = clock();
                double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

                cout << "Proceso: Modificar venta + Reprocesamiento" << endl;
                cout << "Estructura: Lista + HashMapList" << endl;
                cout << "Ifs explícitos: " << ifs << endl;
                cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
                break;
            }
              case 5: {
                clock_t inicio = clock();
                int ifs = 1; // el menú interno tendrá al menos un if

                menuConsultasDinamicas(ventas);

                clock_t fin = clock();
                double tiempo = double(fin - inicio) / CLOCKS_PER_SEC;

                cout << "Proceso: Consultas dinámicas" << endl;
                cout << "Estructura: Lista" << endl;
                cout << "Ifs explícitos (aprox.): " << ifs << endl;
                cout << "Tiempo de ejecución: " << tiempo << " segundos" << endl;
                break;
            }
            case 0:
                cout << "Saliendo del sistema. ¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
        }

    } while (opcion != 0);
    system("pause");


    return 0;
    
}
