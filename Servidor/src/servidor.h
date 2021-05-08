/*
 * servidor.h
 *
 *  Created on: 7 may. 2021
 *      Author: utnso
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>

// Variables globales
int PUERTO = 8000;
char* IP = "127.0.0.1";
int servidor;
int cliente;

// Prototipos
void atender_cliente(void);

#endif /* SERVIDOR_H_ */
