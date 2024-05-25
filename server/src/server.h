#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <commons/log.h>
#include "utils.h"
//#include "../../client/src/utils.h"

void iterator(char* value);
void enviar_mensaje(char* mensaje, int socket_cliente);

#endif /* SERVER_H_ */
