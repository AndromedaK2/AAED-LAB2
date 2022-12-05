
// Autor: Creado Por Cristopher Angulo
// Archivo Contenedor de TDAS y Operaciones

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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

/// @brief Estructura de Datos TiempoSimulacion
/// Representa: Tiempo de Atención
typedef struct TiempoSimulacion
{
    int tiempo;
    struct TiempoSimulacion *siguiente;
} TiempoSimulacion;

/// @brief Estructura de Dato TiempoSimulaciones
/// Representa: Tiempos de Atención
typedef struct TiempoSimulaciones
{
    int tamano;
    TiempoSimulacion *primero;
    TiempoSimulacion *ultimo;
} TiempoSimulaciones;

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
/// @param tiempoSimulaciones
/// @param valor
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

/// @brief
/// @param probabilidad
/// @return
int atender(float probabilidad)
{
    // printf("probabilidad:  %f \n", probabilidad);
    float aleatorio = 1.0 * rand() / RAND_MAX;
    // printf("numero aleatorio:  %f \n", aleatorio);
    return (probabilidad < aleatorio) ? 1 : 0;
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
        printf("ingresar paciente %d \n", i);
        ingresarPaciente(vacunatorio, intervaloLlegadaAux, i);
        intervaloLlegadaAux = intervaloLlegadaAux + vacunatorio->intervaloLlegada;
    }

    return vacunatorio;
}

/// @brief Generar tiempos de atencion aleatorios
/// @param vacunatorio
/// @return Tiempo de Simulaciones
TiempoSimulaciones *generarTiemposAtencionAleatorios(Vacunatorio *vacunatorio)
{
    TiempoSimulaciones *tiempoSimulaciones = crearTiempoSimulacionesVacio();
    int j;
    for (j = 0; j < vacunatorio->tiempoSimulacion + vacunatorio->intervaloLlegada;)
    {
        float rangoMaximo = 1.0;
        float probabilidad = ((float)rand() / (float)(RAND_MAX)) * rangoMaximo;
        probabilidad = roundf(10 * probabilidad) / 10;
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

/// @brief Comenzar la Simulación de Vacunación
/// @param vacunatorio
/// @param pacientesAtendidos
void iniciarSimulacion(Vacunatorio *vacunatorio, PacientesAtendidos *pacientesAtendidos)
{
    TiempoSimulaciones *tiempoSimulaciones = generarTiemposAtencionAleatorios(vacunatorio);

    TiempoSimulacion *tiempoSimulacion = tiempoSimulaciones->primero;
    Paciente *paciente = vacunatorio->primerPaciente;
    int i = 0, j = 0, tiempoSimulacionAux = 0;

    printf("Inicio Tiempo simulacion \n");
    printf("Cantidad de pacientes %d \n", vacunatorio->cantidadActualPacientes);
    for (i = 0; i < tiempoSimulaciones->tamano; i++)
    {

        // printf("Tiempo Simulacion auxiliar:%d \n", tiempoSimulacion->tiempo);
        Paciente *paciente = vacunatorio->primerPaciente;

        tiempoSimulacionAux = tiempoSimulacion->tiempo;
        for (j = 0; j < vacunatorio->cantidadActualPacientes; j++)
        {
            //  printf("Tiempo llegada paciente %d \n", paciente->tiempoLlegada);

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

/// @brief Imprimir Resultados por Pantalla
/// @param vacunatorio
/// @param pacientesAtendidos
void verResultados(Vacunatorio *vacunatorio, PacientesAtendidos *pacientesAtendidos)
{
    int i = 0, tiempoPromedioEsperaVacunacion = 0, totalTiempoEsperaVacunacion = 0;

    Paciente *pacienteAtendido = pacientesAtendidos->inicio;
    printf("\n Total Pacientes Atendidos \n");
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

    tiempoPromedioEsperaVacunacion = totalTiempoEsperaVacunacion / pacientesAtendidos->cantidad;
    printf("\n Total Pacientes No Atendidos: %d \n", vacunatorio->cantidadActualPacientes);
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

    printf("\n Resumen \n");
    printf("Cantidad de Pacientes Vacunados %d \n", pacientesAtendidos->cantidad);
    printf("Cantidad de Pacientes No Vacunados %d \n", vacunatorio->cantidadActualPacientes);
    printf("Tiempo Promedio de Espera de Vacunacion %d \n", tiempoPromedioEsperaVacunacion);
}
