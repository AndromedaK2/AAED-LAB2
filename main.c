// Autor: Creado Por Cristopher Angulo
// Archivo: Main Cliente para la ejecucion principal de la simulacion de vacunacion

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacientes.h"

int main(int argc, char *argv[])
{

    srand(time(NULL));
    int tiempoSimulacion = argv[0];
    int intervaloLlegada = argv[1];
    int probabilidad   = argv[2];   
    int cantidadMaxPacientes = argv[3];
   
    // Inicializar
    PacientesAtendidos *pacientesAtendidos = crearPacientesAtendidosVacio();
    Vacunatorio *vacunatorio = generarVacunatorioVacio();
    vacunatorio = generarFilaVacunatorio(cantidadMaxPacientes, tiempoSimulacion, intervaloLlegada);

    // Comenzar Simulacion
    iniciarSimulacion(vacunatorio, pacientesAtendidos, probabilidad);

    // Ver Resultados
    verResultados(vacunatorio, pacientesAtendidos, probabilidad);

    return 0;
}
