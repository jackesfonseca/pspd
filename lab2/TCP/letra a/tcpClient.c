#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "info.h"


void
generate_vetor (vetor *argp, int tam, int start, int end)
{
        int tamanho_v = end - start;
        argp->vetor_len = tamanho_v;
        argp->vetor_val = malloc (sizeof (float) * tamanho_v);
        printf("Criando vetor => início = %d, final = %d\n", start, end);

        for (int i = 0; i < tamanho_v; i++)
                argp->vetor_val[i] = ((start + i) - tam / 2);
}


int
main (int argc, char *argv[])
{
        /* contem dados do servidor, socket descriptor, buffer de dados enviados */
        struct sockaddr_in infoServ; 
        int sd;                     
        vetor bufferOut;                
        
        // Validacao dos dados de entrada
        if (argc < 4) {
                fprintf (stderr, "Uso correto: %s <ip_do_servidor> <porta_do_servidor> <tam_vetor>\n", argv[0]);
                exit(1);
        }

        // Configuracao de socket
        infoServ.sin_family = AF_INET;
        infoServ.sin_addr.s_addr = inet_addr (argv[1]);
        infoServ.sin_port = htons (atoi (argv[2]));

        // Criacao de socket
        sd = socket (AF_INET, SOCK_STREAM, 0);
        if (sd < 0) {
                fprintf (stderr, "Criacao do socket falhou!\n");
                exit(1);
        }

        // Conexao socket
        if (connect (sd, (struct sockaddr *) &infoServ, sizeof (infoServ)) < 0) {
                fprintf (stderr, "Tentativa de conexao falhou!\n");
                exit(1);
        }

        // Envia dados para os sockets ja conectados
        int tam = atoi (argv[3]);
        generate_vetor (&bufferOut, tam, 0, tam);

        int tmp = htonl(bufferOut.vetor_len);
        send (sd, &tmp, sizeof (tmp), 0);

        for (int i = 0; i < bufferOut.vetor_len; i++)
            send (sd, &bufferOut.vetor_val[i], sizeof (float), 0);

        // Recebe resposta
        float menor, maior;
        recv (sd, &menor, sizeof (float), 0);
        recv (sd, &maior, sizeof (float), 0);

        printf("Menor valor: %f\n", menor);
        printf("Maior valor: %f\n", maior);

        close (sd); /* finaliza a conexão */
        return (0);
}