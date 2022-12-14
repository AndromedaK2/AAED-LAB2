
.. Definición de TDAS

TiempoSimulacion: Registro
    tiempo
    *siguiente
Fin Registro

TiempoSimulaciones: Registro
    tamano
    *primero
    *ultimo
Fin Registro

.. Definción de Operaciones

.. Complejidad: O(1)
crearTiempoSimulacionesVacio(): TiempoSimulaciones*
    tiempoSimulaciones <- asignarMemoria
    tiempoSimulaciones->primero <- NULL
    tiempoSimulaciones->ultimo <- NULL
    tiempoSimulaciones->tamano <- 0
    return tiempoSimulaciones

.. Complejidad O(1)
insertarTiempoSimulacion(TiempoSimulaciones *tiempoSimulaciones, num tiempo): void
    tiempoSimulacion <- asignarMemoria
    IF  tiempoSimulaciones->tamano = 0 THEN
        tiempoSimulacion->tiempo <- tiempo
        tiempoSimulaciones->primero <- tiempoSimulacion
        tiempoSimulaciones->ultimo <- tiempoSimulacion
        tiempoSimulaciones->tamano <- 1
    ELSE
        tiempoSimulacion->tiempo <- tiempo
        tiempoSimulaciones->ultimo->siguiente <- tiempoSimulacion
        tiempoSimulaciones->ultimo <- tiempoSimulacion
        tiempoSimulaciones->tamano++
