#include "client.h"


int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger_cliente = iniciar_logger();
	
	log_info(logger_cliente, "hola soy un log");

	log_destroy(logger_cliente);
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */
	logger_cliente = iniciar_logger();
	config = iniciar_config();

	valor = config_get_string_value(config,"CLAVE");
	ip = config_get_string_value(config,"IP");
	puerto = config_get_string_value(config,"PUERTO");
	
	log_info(logger_cliente,"Key leida de la config: %s",valor);
	log_info(logger_cliente,"Key leida de la config: %s",ip);
	log_info(logger_cliente,"Key leida de la config: %s",puerto);

	
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config


	/* ---------------- LEER DE CONSOLA ---------------- */
	
	
	// leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

		
	t_list* lista;
	
		while (1)
		{
			
		int cod_op = recibir_operacion(conexion);
		switch (cod_op) {
		case MENSAJE:
			recibir_mensaje(conexion);
			enviar_mensaje("Recibi el mensaje K-po",conexion);
			break;
		case PAQUETE:
			lista = recibir_paquete(conexion);
			log_info(logger_cliente, "Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			
			break;
		case -1:
			log_error(logger_cliente, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger_cliente,"Operacion desconocida. No quieras meter la pata");
			break;
		}

		}
		


	leer_consola(logger_cliente);
	
	terminar_programa(conexion, logger_cliente, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
	printf("\nCliente finalizado");



	
}




t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tpo.log","codigo", true,LOG_LEVEL_DEBUG);

	
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("cliente.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");
	log_info(logger,">> %s", leido);
	
printf("\nLeido check= %s",leido);
	
	while (strcmp(leido, "") != 0 )
	{
		free(leido);
		leido = readline("\n> ");
		log_info(logger,">> %s", leido);
	}
	free(leido);

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío

		
	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();

	// Leemos y esta vez agregamos las lineas al paquete
		leido = readline("> ");

		while (strcmp(leido, "")!=0)
		{
			free(leido);
			leido = readline("> ");
			agregar_a_paquete(paquete,leido,strlen(leido) +1);
		}

	enviar_paquete(paquete, conexion);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */

	  log_destroy(logger);
	  config_destroy(config);
	  liberar_conexion(conexion);
}


void iterator(char* value) {
	log_info(logger_cliente,"%s", value);
}
