
.. Funcion Main
main(): num

    .. Setear Valores 
    tiempoSimulacion <- 50
    intervaloLlegada <- 7
    cantidadMaxPacientes <- 8

    .. Inicializar
    pacientesAtendidos <- crearPacientesAtendidosVacio()
    vacunatorio <- generarVacunatorioVacio()
    vacunatorio <- generarFilaVacunatorio(cantidadMaxPacientes, tiempoSimulacion, intervaloLlegada)

    ..  Comenzar Simulacion
    iniciarSimulacion(vacunatorio, pacientesAtendidos)

    .. Ver Resultados
    verResultados(vacunatorio, pacientesAtendidos)

    return 1


