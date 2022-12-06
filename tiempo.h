// Autor: Creado Por Cristopher Angulo
// Archivo Contenedor de TDAS y Operaciones

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/// @brief Estructura de Datos TiempoSimulacion
/// Representa: Tiempo de Atención
typedef struct TiempoSimulacion
{
    int tiempo;
    struct TiempoSimulacion *siguiente;
} TiempoSimulacion;

/// @brief Estructura de Dato TiempoSimulaciones
/// Representa: Tiempos de Atencion
typedef struct TiempoSimulaciones
{
    int tamano;
    TiempoSimulacion *primero;
    TiempoSimulacion *ultimo;
} TiempoSimulaciones;


TiempoSimulaciones *crearTiempoSimulacionesVacio();
void insertarTiempoSimulacion(TiempoSimulaciones *tiempoSimulaciones, int tiempo);

/// @brief Crear Tiempo de simulaciones vacio
/// @return Tiempo de Simulaciones
TiempoSimulaciones *crearTiempoSimulacionesVacio()
{
    TiempoSimulaciones *tiempoSimulaciones = (TiempoSimulaciones *)malloc(sizeof(TiempoSimulaciones));
    tiempoSimulaciones->primero = NULL;
    tiempoSimulaciones->ultimo = NULL;
    tiempoSimulaciones->tamano = 0;
    return tiempoSimulaciones;
}

/// @brief Insertar un tiempo de simulacion
/// @param tiempoSimulaciones
/// @param tiempo
void insertarTiempoSimulacion(TiempoSimulaciones *tiempoSimulaciones, int tiempo)
{
    TiempoSimulacion *tiempoSimulacion = (TiempoSimulacion *)malloc(sizeof(TiempoSimulacion));
    if (tiempoSimulaciones->tamano == 0)
    {
        tiempoSimulacion->tiempo = tiempo;
        tiempoSimulaciones->primero = tiempoSimulacion;
        tiempoSimulaciones->ultimo = tiempoSimulacion;
        tiempoSimulaciones->tamano = 1;
    }
    else
    {
        tiempoSimulacion->tiempo = tiempo;
        tiempoSimulaciones->ultimo->siguiente = tiempoSimulacion;
        tiempoSimulaciones->ultimo = tiempoSimulacion;
        tiempoSimulaciones->tamano++;
    }
}
