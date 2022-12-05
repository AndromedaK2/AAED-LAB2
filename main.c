// Autor: Creado Por Cristopher Angulo
// Archivo: Main Cliente para la ejecucion principal de la simulaci�n de vacunacion

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacientes.h"

int main(int argc, char *argv[])
{

    srand(time(NULL));
    // int tiempoSimulacion = argv[1];
    // int intervaloLlegada = argv[2];
    int tiempoSimulacion = 50;
    int intervaloLlegada = 7;
    int cantidadMaxPacientes = 8;
    float probabilidad = 1;

    // Inicializar
    PacientesAtendidos *pacientesAtendidos = crearPacientesAtendidosVacio();
    Vacunatorio *vacunatorio = generarVacunatorioVacio();
    vacunatorio = generarFilaVacunatorio(cantidadMaxPacientes, tiempoSimulacion, intervaloLlegada);

    // Comenzar Simulacion
    iniciarSimulacion(vacunatorio, pacientesAtendidos, probabilidad);

    // Ver Resultados
    verResultados(vacunatorio, pacientesAtendidos);

    return 0;
}
