#ifndef CLIENT_H_
#define CLIENT_H_

#include<stdio.h>
#include<stdlib.h>
#include<commons/log.h>
#include<commons/string.h>
#include<commons/config.h>
#include<readline/readline.h>
#include <string.h>
#include </home/utnso/TP0/tp0/server/src/utils.h>
#include </home/utnso/TP0/tp0/server/src/server.h>

#include "utils.h"
t_log* logger_cliente;

t_log* iniciar_logger(void);
t_config* iniciar_config(void);
void leer_consola(t_log*);
void paquete(int);
void terminar_programa(int, t_log*, t_config*);

void iterator(char* value);

#endif /* CLIENT_H_ */
