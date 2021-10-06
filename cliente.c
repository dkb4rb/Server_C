/*
 * File: cliente.c
 * Author: Juan_Duque0
 */

#include "service.h"
/*main - Este programa Realizara una coneccion por socket a un servidor*/

int main(int argc, char **argv)
{
    char *fd;

    if (argv[1] == NULL || argc < 2)
    {
        dprintf(STDERR_FILENO, "Usage: %s <IP> <PORT>\n", argv[0]);
        printf("jkjsadjs");
        return (EXIT_FAILURE);
    }

    if (argv[2] == NULL)
    {
        dprintf(STDERR_FILENO, "Ingresa el puerto %s PORT \n", argv[1]);
        return (EXIT_FAILURE);
    }

    if (strcmp(argv[1], "IP") == 0)
        printf("Escribistes ==> %s\n", argv[1]);

    if (strcmp(argv[2], "PORT") == 0)
        printf("Escribistes ==> %s\n", argv[2]);

    struct sockaddr_in cliente;
    struct hostent *servidor;
    servidor = gethostbyname(argv[1]);
    if (servidor == NULL)
    {
        dprintf(STDERR_FILENO, "El Host = %s no Existe \n", argv[1]);
        return (EXIT_FAILURE);
    }

    int puerto, conexion;
    char buffer[100];
    conexion = socket(AF_INET, SOCK_STREAM, 0);        //Asignación del socket
    puerto = (atoi(argv[2]));                          //conversion del argumento
    bzero((char *)&cliente, sizeof((char *)&cliente)); //Rellena toda la estructura de 0's
                                                       //La función bzero() es como memset() pero inicializando a 0 todas la variables
    cliente.sin_family = AF_INET;                      //asignacion del protocolo
    cliente.sin_port = htons(puerto);                  //asignacion del puerto
    bcopy((char *)servidor->h_addr_list, (char *)&cliente.sin_addr.s_addr, sizeof(servidor->h_length));
    //bcopy(); copia los datos del primer elemendo en el segundo con el tamaño máximo
    //del tercer argumento.

    //cliente.sin_addr = *((struct in_addr *)servidor->h_addr); //<--para empezar prefiero que se usen
    //inet_aton(argv[1],&cliente.sin_addr); //<--alguna de estas dos funciones
    if (connect(conexion, (struct sockaddr *)&cliente, sizeof(cliente)) < 0)
    { //conectando con el host
        printf("Error conectando con el host\n");
        close(conexion);
        return 1;
    }
    printf("Conectado con %s:%d\n", inet_ntoa(cliente.sin_addr), htons(cliente.sin_port));
    //inet_ntoa(); está definida en <arpa/inet.h>

    while (1)
    {
        printf("Escribe un mensaje: ");
        fgets(buffer, 100, stdin);
        send(conexion, buffer, 100, 1); //envio
        bzero(buffer, 100);
        recv(conexion, buffer, 100, 0); //recepción
        printf("%s", buffer);
    }

    printf("Tus argv[1] es: %s\n", argv[1]);
    printf("Tu argc = %d\n", argc);
    return (EXIT_SUCCESS);
}