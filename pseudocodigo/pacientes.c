

.. Definción de TDAS

Paciente: Registro  
    ordenLlegada
    tiempoEspera
    tiempoLlegada
    tiempoAtencion
    vacunado
    *siguiente
Fin Registro

Vacunatorio: Registro
    *primerPaciente
    *ultimoPaciente
    tiempoSimulacion
    intervaloLlegada
    cantidadMaxPacientes
    cantidadActualPacientes
Fin Registro

Pacientes: Registro
    *inicio
    cantidad
Fin Registro


.. Definción de Operaciones

.. Complejidad O(1)
generarVacunatorioVacio(): Vacunatorio*
    vacunatorio <- asignarMemoria
    vacunatorio->tiempoSimulacion <- 0
    vacunatorio->intervaloLlegada <- 0
    vacunatorio->ultimoPaciente <- NULL
    vacunatorio->primerPaciente <- NULL
    vacunatorio->cantidadMaxPacientes <- 0
    return vacunatorio

.. Complejidad O(1)
crearPaciente(): Paciente*
    paciente <- asignarMemoria
    paciente->tiempoLlegada <- -1
    paciente->tiempoEspera <- -1
    paciente->tiempoAtencion <- -1
    paciente->ordenLlegada <- 0
    paciente->vacunado <- 0
    paciente->siguiente <- NULL
    return paciente


.. Complejidad O(1)
insertarPacienteAtendido(PacientesAtendidos *pacientesAtendidos, Paciente *paciente): void
    pacienteAtendido <- asignarMemoria
    pacienteAtendido->tiempoEspera <- paciente->tiempoAtencion - paciente->tiempoLlegada
    pacienteAtendido->tiempoLlegada <- paciente->tiempoLlegada
    pacienteAtendido->tiempoAtencion <- paciente->tiempoAtencion
    pacienteAtendido->vacunado <- paciente->vacunado
    pacienteAtendido->ordenLlegada <- paciente->ordenLlegada
    pacienteAtendido->siguiente <- pacientesAtendidos->inicio
    pacientesAtendidos->inicio <- pacienteAtendido
    pacientesAtendidos->cantidad++


.. Complejidad O(1)
ingresarPaciente(Vacunatorio *vacunatorio, num tiempoLlegada, num ordenLlegada): void
    IF vacunatorio->cantidadMaxPacientes = vacunatorio->cantidadActualPacientes THEN
        return        
    paciente <- crearPaciente()
    paciente->tiempoLlegada <- tiempoLlegada
    paciente->ordenLlegada <- ordenLlegada
    IF  vacunatorio->primerPaciente = NULL THEN
        vacunatorio->primerPaciente <- paciente
        vacunatorio->ultimoPaciente <- paciente
        vacunatorio->cantidadActualPacientes <- 1
    else
        vacunatorio->ultimoPaciente->siguiente <- paciente
        vacunatorio->ultimoPaciente <- paciente
        vacunatorio->cantidadActualPacientes++
    


.. Complejidad O(1)
atenderPaciente(Vacunatorio *vacunatorio, Paciente *paciente, PacientesAtendidos *pacientesAtendidos): void
    IF (vacunatorio->cantidadActualPacientes = 1) THEN
        insertarPacienteAtendido(pacientesAtendidos, paciente)
        vacunatorio->primerPaciente <- NULL
        vacunatorio->ultimoPaciente <- NULL
        vacunatorio->cantidadActualPacientes <- 0
        liberar(vacunatorio->primerPaciente)
    ELSE IF (vacunatorio->cantidadActualPacientes > 1)
        insertarPacienteAtendido(pacientesAtendidos, paciente)
        Paciente *primerPaciente <- vacunatorio->primerPaciente
        vacunatorio->primerPaciente <- vacunatorio->primerPaciente->siguiente
        liberar(primerPaciente)
        vacunatorio->cantidadActualPacientes--
    

.. Complejidad O(1)
crearPacientesAtendidosVacio(): PacientesAtendidos*
    PacientesAtendidos *pacienteAtendidos <- asignarMemoria
    pacienteAtendidos->inicio <- NULL
    pacienteAtendidos->cantidad <- 0
    return pacienteAtendidos



.. Complejidad O(n)
generarFilaVacunatorio(num cantidadMaxPacientes, num tiempoSimulacion, num intervaloLlegada):Vacunatorio*
    Vacunatorio *vacunatorio <- generarVacunatorioVacio()
    vacunatorio->cantidadMaxPacientes <- cantidadMaxPacientes
    vacunatorio->tiempoSimulacion <- tiempoSimulacion
    vacunatorio->intervaloLlegada <- intervaloLlegada
    intervaloLlegadaAux <- 0,
    FOR i <- 0 TO vacunatorio->cantidadMaxPacientes STEP 1
        ingresarPaciente(vacunatorio, intervaloLlegadaAux, i + 1)
        intervaloLlegadaAux <- intervaloLlegadaAux + vacunatorio->intervaloLlegada
    return vacunatorio


..Complejidad O(n^2)
iniciarSimulacion(Vacunatorio *vacunatorio, PacientesAtendidos *pacientesAtendidos): void
    tiempoSimulaciones <- generarTiemposAtencionAleatorios(vacunatorio)
    tiempoSimulacion <- tiempoSimulaciones->primero
    paciente <- vacunatorio->primerPaciente
    tiempoSimulacionAux <- 0
    i <- 0 
    j <- 0 
    ESCRIBIR("Inicio Tiempo simulacion")
    FOR i <- 0 TO tiempoSimulaciones->tamano STEP 1
        paciente <- vacunatorio->primerPaciente
        tiempoSimulacionAux <- tiempoSimulacion->tiempo
        FOR j <- 0 TO vacunatorio->cantidadActualPacientes STEP 1         
            IF paciente->tiempoLlegada < tiempoSimulacion->tiempo THEN            
                paciente->tiempoAtencion <- tiempoSimulacionAux
                atenderPaciente(vacunatorio, paciente, pacientesAtendidos)
                tiempoSimulacionAux++
            paciente <- paciente->siguiente
        tiempoSimulacion <- tiempoSimulacion->siguiente
    


..Complejidad O(n)
verResultados(Vacunatorio *vacunatorio, PacientesAtendidos *pacientesAtendidos, num probabilidad): void

    tiempoPromedioEsperaVacunacion <- 0
    totalTiempoEsperaVacunacion <- 0
    i <- 0
    pacienteAtendido <- pacientesAtendidos->inicio
    ESCRIBIR("Total Pacientes Atendidos")

    FOR i <- 0 TO pacientesAtendidos->cantidad STEP 1
        ESCRIBIR("Paciente %d \n", pacienteAtendido->ordenLlegada)
        ESCRIBIR("Tiempo Espera %d \n", pacienteAtendido->tiempoEspera)
        ESCRIBIR("Tiempo llegada %d \n", pacienteAtendido->tiempoLlegada)
        ESCRIBIR("Tiempo atencion %d \n", pacienteAtendido->tiempoAtencion)
        totalTiempoEsperaVacunacion <- pacienteAtendido->tiempoEspera + totalTiempoEsperaVacunacion
        pacienteAtendido <- pacienteAtendido->siguiente
        ESCRIBIR("----------------------------------\n")
    

    tiempoPromedioEsperaVacunacion <- totalTiempoEsperaVacunacion / pacientesAtendidos->cantidad
    ESCRIBIR("Total Pacientes No Atendidos: %d ", vacunatorio->cantidadActualPacientes)
    pacienteNoAtendido <- vacunatorio->primerPaciente

    FOR i <- 0 i TO vacunatorio->cantidadActualPacientes STEP 1
        ESCRIBIR("Paciente %d", pacienteNoAtendido->ordenLlegada)
        ESCRIBIR("Tiempo Espera %d", pacienteNoAtendido->tiempoEspera)
        ESCRIBIR("Tiempo llegada %d", pacienteNoAtendido->tiempoLlegada)
        ESCRIBIR("Tiempo atencion %d", pacienteNoAtendido->tiempoAtencion)
        pacienteNoAtendido <- pacienteNoAtendido->siguiente
        ESCRIBIR("----------------------------------\n")

    ESCRIBIR("Resumen")
    ESCRIBIR("Cantidad de Pacientes Vacunados %d ", pacientesAtendidos->cantidad)
    ESCRIBIR("Cantidad de Pacientes No Vacunados %d ", vacunatorio->cantidadActualPacientes)
    ESCRIBIR("Tiempo Promedio de Espera de Vacunacion %d ", tiempoPromedioEsperaVacunacion)
    ESCRIBIR("Probabilidad %d ", probabilidad)




.. Complejidad O(N)
generarTiemposAtencionAleatorios(Vacunatorio *vacunatorio): TiempoSimulaciones*
    tiempoSimulaciones <- crearTiempoSimulacionesVacio()
    j = 0
    FOR j <- 0 TO vacunatorio->tiempoSimulacion + vacunatorio->intervaloLlegada
        probabilidad <- generarProbabilidad()
        seAtiende <- atender(probabilidad)
        IF seAtiende <- 1 THEN        
            insertarTiempoSimulacion(tiempoSimulaciones, j) 
        j <- j + vacunatorio->intervaloLlegada  
    return tiempoSimulaciones
