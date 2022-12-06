
// Autor: Creado Por Cristopher Angulo
// Archivo Contenedor de TDAS y Operaciones

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tiempo.h"

/// @brief Estructura de Dato Paciente
/// Representación: Un Paciente con sus hora de llegada
/// y su hora de atención
typedef struct Paciente
{
    int ordenLlegada;
    int tiempoEspera;
    int tiempoLlegada;
    int tiempoAtencion;
    int vacunado; // 0 o 1
    struct Paciente *siguiente;
} Paciente;

/// @brief Estructura de Dato Vacunatorio:
/// Representa: Cola o Fila del Vacunatorio
typedef struct Vacunatorio
{
    Paciente *primerPaciente;
    Paciente *ultimoPaciente;
    int tiempoSimulacion;
    int intervaloLlegada;
    int cantidadMaxPacientes;
    int cantidadActualPacientes;
} Vacunatorio;

/// @brief  Estructura de Datos Pacientes:
/// Representa: Pacientes Atendidos y Vacunados
typedef struct Pacientes
{
    Paciente *inicio;
    int cantidad;
} PacientesAtendidos;

// Operaciones
Vacunatorio *generarVacunatorioVacio();
Paciente *crearPaciente();
PacientesAtendidos *crearPacientesAtendidosVacio();
void insertarPacienteAtendido(PacientesAtendidos *pacientesAtendidos, Paciente *paciente);
void ingresarPaciente(Vacunatorio *vacunatorio, int tiempoLlegada, int ordenLlegada);
void atenderPaciente(Vacunatorio *vacunatorio, Paciente *paciente, PacientesAtendidos *pacientesAtendidos);
int atender(float probabilidad);
Vacunatorio *generarFilaVacunatorio(int cantidadMaxPacientes, int tiempoSimulacion, int intervaloLlegada);
void iniciarSimulacion(Vacunatorio *vacunatorio, PacientesAtendidos *pacientesAtendidos, float probabilidad);
void verResultados(Vacunatorio *vacunatorio, PacientesAtendidos *pacientesAtendidos, float probabilidad);
TiempoSimulaciones *generarTiemposAtencionAleatorios(Vacunatorio *vacunatorio, float probabilidad);

/// @brief Generar Vacunatorio Vacio
/// @return Vacunatorio
Vacunatorio *generarVacunatorioVacio()
{
    Vacunatorio *vacunatorio = (Vacunatorio *)malloc(sizeof(Vacunatorio));
    vacunatorio->tiempoSimulacion = 0;
    vacunatorio->intervaloLlegada = 0;
    vacunatorio->ultimoPaciente = NULL;
    vacunatorio->primerPaciente = NULL;
    vacunatorio->cantidadMaxPacientes = 0;
    return vacunatorio;
}

/// @brief Crear Paciente
/// @return Paciente
Paciente *crearPaciente()
{
    Paciente *paciente = (Paciente *)malloc(sizeof(Paciente));
    paciente->tiempoLlegada = -1;
    paciente->tiempoEspera = -1;
    paciente->tiempoAtencion = -1;
    paciente->ordenLlegada = 0;
    paciente->vacunado = 0;
    paciente->siguiente = NULL;
    return paciente;
}
/// @brief Ingresar Paciente a lista de pacientes atendidos/vacunados
/// @param pacientesAtendidos
/// @param paciente
void insertarPacienteAtendido(PacientesAtendidos *pacientesAtendidos, Paciente *paciente)
{
    Paciente *pacienteAtendido = (Paciente *)malloc(sizeof(Paciente));
    pacienteAtendido->tiempoEspera = paciente->tiempoAtencion - paciente->tiempoLlegada;
    pacienteAtendido->tiempoLlegada = paciente->tiempoLlegada;
    pacienteAtendido->tiempoAtencion = paciente->tiempoAtencion;
    pacienteAtendido->vacunado = paciente->vacunado;
    pacienteAtendido->ordenLlegada = paciente->ordenLlegada;
    pacienteAtendido->siguiente = pacientesAtendidos->inicio;
    pacientesAtendidos->inicio = pacienteAtendido;
    pacientesAtendidos->cantidad++;
}
/// @brief Ingresar Paciente a la fila del vacunatorio
/// @param vacunatorio
/// @param paciente
void ingresarPaciente(Vacunatorio *vacunatorio, int tiempoLlegada, int ordenLlegada)
{
    if (vacunatorio->cantidadMaxPacientes == vacunatorio->cantidadActualPacientes)
        return;

    Paciente *paciente = crearPaciente();
    paciente->tiempoLlegada = tiempoLlegada;
    paciente->ordenLlegada = ordenLlegada;
    if (vacunatorio->primerPaciente == NULL)
    {
        vacunatorio->primerPaciente = paciente;
        vacunatorio->ultimoPaciente = paciente;
        vacunatorio->cantidadActualPacientes = 1;
    }
    else
    {
        vacunatorio->ultimoPaciente->siguiente = paciente;
        vacunatorio->ultimoPaciente = paciente;
        vacunatorio->cantidadActualPacientes++;
    }
}

/// @brief Atender Paciente (Sacarlo de la fila) e Insertar en pacientes atendidos
/// @param vacunatorio
/// @param paciente
/// @param pacientesAtendidos
void atenderPaciente(Vacunatorio *vacunatorio, Paciente *paciente, PacientesAtendidos *pacientesAtendidos)
{
    if (vacunatorio->cantidadActualPacientes == 1)
    {
        insertarPacienteAtendido(pacientesAtendidos, paciente);
        vacunatorio->primerPaciente = NULL;
        vacunatorio->ultimoPaciente = NULL;
        vacunatorio->cantidadActualPacientes = 0;
        free(vacunatorio->primerPaciente);
    }
    else if (vacunatorio->cantidadActualPacientes > 1)
    {
        insertarPacienteAtendido(pacientesAtendidos, paciente);
        Paciente *primerPaciente = vacunatorio->primerPaciente;
        vacunatorio->primerPaciente = vacunatorio->primerPaciente->siguiente;
        free(primerPaciente);
        vacunatorio->cantidadActualPacientes--;
    }
}

/// @brief Crear lista de pacientes atendidos vacío
/// @return
PacientesAtendidos *crearPacientesAtendidosVacio()
{
    PacientesAtendidos *pacienteAtendidos = (PacientesAtendidos *)malloc(sizeof(PacientesAtendidos));
    pacienteAtendidos->inicio = NULL;
    pacienteAtendidos->cantidad = 0;
    return pacienteAtendidos;
}

/// @brief
/// @param probabilidad
/// @return
int atender(float probabilidad)
{
    int falso = 0;
    int verdadero = 1;
    // printf("probabilidad:  %f \n", probabilidad);
    float aleatorio = 1.0 * rand() / RAND_MAX;
    // printf("numero aleatorio:  %f \n", aleatorio);

    // True Izquierda o False Derecha

    // ejemplo 1 probabilidad = 0.7
    // aleatorio = 0.72
    // retorna false

    // ejemplo 2 probabilidad = 0.7
    // aleatorio = 0.3
    // retorna verdadero

    // ejemplo 3 probabilidad = 1.0
    // aleatorio = 0.3
    // retorna verdadero porque siempre serán numero menores a 1
    return (probabilidad < aleatorio) ? falso : verdadero;
}

/// @brief
/// @param cantidadMaxPacientes
/// @param tiempoSimulacion
/// @param intervaloLlegada
/// @return
Vacunatorio *generarFilaVacunatorio(int cantidadMaxPacientes, int tiempoSimulacion, int intervaloLlegada)
{
    Vacunatorio *vacunatorio = generarVacunatorioVacio();
    vacunatorio->cantidadMaxPacientes = cantidadMaxPacientes;
    vacunatorio->tiempoSimulacion = tiempoSimulacion;
    vacunatorio->intervaloLlegada = intervaloLlegada;

    int intervaloLlegadaAux = 0, i = 0;

    for (i = 0; i < vacunatorio->cantidadMaxPacientes; i++)
    {
        // printf("ingresar paciente %d \n", i);
        ingresarPaciente(vacunatorio, intervaloLlegadaAux, i + 1);
        intervaloLlegadaAux = intervaloLlegadaAux + vacunatorio->intervaloLlegada;
    }

    return vacunatorio;
}

/// @brief Comenzar la Simulación de Vacunación
/// @param vacunatorio
/// @param pacientesAtendidos
void iniciarSimulacion(Vacunatorio *vacunatorio, PacientesAtendidos *pacientesAtendidos, float probabilidad)
{
    TiempoSimulaciones *tiempoSimulaciones = generarTiemposAtencionAleatorios(vacunatorio, probabilidad);

    TiempoSimulacion *tiempoSimulacion = tiempoSimulaciones->primero;
    Paciente *paciente = vacunatorio->primerPaciente;
    int i = 0, j = 0, tiempoSimulacionAux = 0;

    printf("Inicio Tiempo simulacion \n");
    printf("Cantidad de pacientes %d \n", vacunatorio->cantidadActualPacientes);
    if (tiempoSimulaciones->tamano > 0)
    {
        for (i = 0; i < tiempoSimulaciones->tamano; i++)
        {

            // printf("Tiempo Simulacion auxiliar:%d \n", tiempoSimulacion->tiempo);
            Paciente *paciente = vacunatorio->primerPaciente;

            tiempoSimulacionAux = tiempoSimulacion->tiempo;
            for (j = 0; j < vacunatorio->cantidadActualPacientes; j++)
            {
                // printf("Tiempo llegada paciente %d \n", paciente->tiempoLlegada);

                if (paciente->tiempoLlegada <= tiempoSimulacion->tiempo)
                {
                    paciente->tiempoAtencion = tiempoSimulacionAux;
                    atenderPaciente(vacunatorio, paciente, pacientesAtendidos);
                    tiempoSimulacionAux++;
                }
                paciente = paciente->siguiente;
            }
            // printf("Fin recorrido: %d \n", i);
            tiempoSimulacion = tiempoSimulacion->siguiente;
        }
    }
}

/// @brief Imprimir Resultados por Pantalla
/// @param vacunatorio
/// @param pacientesAtendidos
void verResultados(Vacunatorio *vacunatorio, PacientesAtendidos *pacientesAtendidos, float probabilidad)
{
    int i = 0, tiempoPromedioEsperaVacunacion = 0, totalTiempoEsperaVacunacion = 0;

    Paciente *pacienteAtendido = pacientesAtendidos->inicio;


    printf("\nTotal Pacientes Atendidos: %d\n", pacientesAtendidos->cantidad);

    for (i = 0; i < pacientesAtendidos->cantidad; i++)
    {

        printf("Paciente %d \n", pacienteAtendido->ordenLlegada);
        printf("Tiempo Espera %d \n", pacienteAtendido->tiempoEspera);
        printf("Tiempo llegada %d \n", pacienteAtendido->tiempoLlegada);
        printf("Tiempo atencion %d \n", pacienteAtendido->tiempoAtencion);
        totalTiempoEsperaVacunacion = pacienteAtendido->tiempoEspera + totalTiempoEsperaVacunacion;
        pacienteAtendido = pacienteAtendido->siguiente;
        printf("----------------------------------\n");
    }

    if (pacientesAtendidos->cantidad > 0)
    {
        tiempoPromedioEsperaVacunacion = totalTiempoEsperaVacunacion / pacientesAtendidos->cantidad;
    }

    printf("\nTotal Pacientes No Atendidos: %d \n", vacunatorio->cantidadActualPacientes);
    Paciente *pacienteNoAtendido = vacunatorio->primerPaciente;
    for (i = 0; i < vacunatorio->cantidadActualPacientes; i++)
    {
        printf("Paciente %d \n", pacienteNoAtendido->ordenLlegada);
        printf("Tiempo Espera %d \n", pacienteNoAtendido->tiempoEspera);
        printf("Tiempo llegada %d \n", pacienteNoAtendido->tiempoLlegada);
        printf("Tiempo atencion %d \n", pacienteNoAtendido->tiempoAtencion);
        pacienteNoAtendido = pacienteNoAtendido->siguiente;
        printf("----------------------------------\n");
    }

    printf("\nResumen:\n");
    printf("1. Cantidad de Pacientes Vacunados %d \n", pacientesAtendidos->cantidad);
    printf("2. Cantidad de Pacientes No Vacunados %d \n", vacunatorio->cantidadActualPacientes);
    printf("3. Tiempo Promedio de Espera de Vacunacion %d \n", tiempoPromedioEsperaVacunacion);
    printf("4. Probabilidad %f \n", probabilidad);
}

/// @brief Generar tiempos de atencion aleatorios
/// @param vacunatorio
/// @return Tiempo de Simulaciones
TiempoSimulaciones *generarTiemposAtencionAleatorios(Vacunatorio *vacunatorio, float probabilidad)
{
    TiempoSimulaciones *tiempoSimulaciones = crearTiempoSimulacionesVacio();
    int j;
    for (j = 0; j < vacunatorio->tiempoSimulacion + vacunatorio->intervaloLlegada;)
    {

        int seAtiende = atender(probabilidad);
        // printf("j: %d \n", j);
        // printf("probabilidad:  %f \n", probabilidad);
        // printf("se atiende?:  %d \n", seAtiende);

        if (seAtiende == 1)
        {
            insertarTiempoSimulacion(tiempoSimulaciones, j);
        }

        j = j + vacunatorio->intervaloLlegada;
    }
    return tiempoSimulaciones;
}
