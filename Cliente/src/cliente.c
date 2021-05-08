/*
 ============================================================================
 Name        : cliente.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "cliente.h"

void main(void) {
	// ---------- Conectamos al Cliente con el Servidor del Discordiador ---------- //
	struct sockaddr_in direccion_cliente;

	direccion_cliente.sin_family = AF_INET;
	direccion_cliente.sin_addr.s_addr = inet_addr(IP);
	direccion_cliente.sin_port = htons(PUERTO);

	// Pedimos un socket y lo guardamos en la variable cliente que es su id.
	int cliente = socket(AF_INET,SOCK_STREAM,0);

	if(connect(cliente, (void*) &direccion_cliente, sizeof(direccion_cliente)) !=0) {
		perror("Error al conectarse al Servidor.\n");
		return;
	}

	while(1) {
		char mensaje[1000];

		scanf("%s", mensaje);
		send(cliente, mensaje, strlen(mensaje), 0);

		printf("Se envio al Servidor %s \n", mensaje);
	}

	return;

}
