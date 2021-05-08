/*
 * servidor.c
 *
 *  Created on: 7 may. 2021
 *      Author: utnso
 */

#include "servidor.h"

void main(void) {
	// ---------- Creamos el Servidor ---------- //
	struct sockaddr_in direccion_servidor;

	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_addr.s_addr = inet_addr(IP);
	direccion_servidor.sin_port = htons(PUERTO);

	// Pedimos un socket y lo guardamos en la variable servidor que es su id.
	servidor = socket(AF_INET, SOCK_STREAM, 0);

	// Para reutilizar direcciones.
	int activado = 1;
	setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

	if(bind(servidor, (void*) &direccion_servidor, sizeof(direccion_servidor)) != 0) {
		perror("No se pudo asociar el socket con la direccion del servidor!\n");
		return;
	}

	printf("El servidor esta escuchando\n");

	listen(servidor, SOMAXCONN);

	atender_cliente();
}

void atender_cliente(void) {
	// ---------- Aceptamos a los clientes que quieran conectarse ---------- //
	// Creamos la direccion del cliente.
	struct sockaddr direccion_cliente;
	unsigned int tamanio_direccion_cliente = sizeof(direccion_cliente);

	// ---------- Recibimos datos por parte del Cliente -----------//
	cliente = accept(servidor, (void*) (struct sockaddr*)&direccion_cliente, &tamanio_direccion_cliente);
	if(cliente == -1) {
		perror("El cliente no se pudo conectar.\n");
		return;
	}

	while(1) {
		char* buffer = malloc(5);

		// Guardamos en el buffer lo que recibamos del cliente.
		int bytesRecibidos = recv(cliente, buffer, 4, 0);

		if(bytesRecibidos < 0) {
			perror("Se desconecto el cliente!\n");
			return;
		}

		buffer[bytesRecibidos] = '\0';
		printf("Recibimos la siguiente cantidad de bytes: %d\n", bytesRecibidos);

		printf("Recibi una conexion por parte de un cliente en: %d \n", cliente);

		// Le enviamos un mensaje al cliente.
		send(cliente, "Bienvenido al Servidor del Discordiador!\n", 50, 0);

		free(buffer);
	}

}
