#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "info.h"

void
recv_vetor (int sd, vetor *argp)
{
        recv (sd, &argp->vetor_val[0], sizeof (float), 0);
        printf("%f", argp->vetor_val[0]);
        for (int i = 1; i < argp->vetor_len; i++) {
                recv (sd, &argp->vetor_val[i], sizeof (float), 0);
                //printf(", %f", argp->vetor_val[i]);
        }
        printf("\n");
}

void
listen_client (int sd, struct sockaddr_in infoCli)
{
        vetor bufferIn;
        int tmp;

        // Recebe informarcoes do Cliente
        recv (sd, &tmp, sizeof (tmp), 0);
        bufferIn.vetor_len = ntohl(tmp);
        printf("[%s:%u] => Recebido tamanho do vetor: %d\n", inet_ntoa (infoCli.sin_addr), ntohs (infoCli.sin_port), bufferIn.vetor_len);

        bufferIn.vetor_val = malloc (sizeof (float) * bufferIn.vetor_len);
        printf("[%s:%u] => Recebido vetor: ", inet_ntoa (infoCli.sin_addr), ntohs (infoCli.sin_port));
        recv_vetor(sd, &bufferIn);

        // Manda resposta em 2 send's
        printf("[%s:%u] => Enviando resposta para cliente\n", inet_ntoa (infoCli.sin_addr), ntohs (infoCli.sin_port));
        send (sd, &bufferIn.vetor_val[0], sizeof (float), 0);
        send (sd, &bufferIn.vetor_val[bufferIn.vetor_len - 1], sizeof (float), 0);

        printf("Encerrando conexao com %s:%u ...\n\n", inet_ntoa (infoCli.sin_addr), ntohs (infoCli.sin_port));
        close (sd);
}

int
main (int argc, char *argv[])
{
        /* contem dados do servidor, contem dados do cliente, socket descriptors */
       struct sockaddr_in infoServ;  
       struct sockaddr_in infoCli;   
       int sd, novo_sd;              
       int socketLen; 

       if (argc < 3) {
               fprintf (stderr, "Uso correto: %s <ip_do_servidor> <porta_do_servidor>\n", argv[0]);
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

        // Ligacao (bind) da porta com o ip do socket
        if (bind (sd, (struct sockaddr *) &infoServ, sizeof (infoServ)) < 0) {
                fprintf (stderr, "Ligacao Falhou!\n");
                exit(1);
        }

        // Ouve (listen) na porta, para QLEN clientes
        if (listen (sd, QLEN) < 0) {
                fprintf (stderr, "Falhou ouvindo porta!\n");
                exit(1);
        }

        printf("Servidor ouvindo no IP %s, na porta %s ...\n\n", argv[1], argv[2]);

        // Aceita conexoes
        socketLen = sizeof (infoCli);
        // Nova conexao com o cliente
        if ((novo_sd=accept (sd, (struct sockaddr *) &infoCli, &socketLen)) < 0) {
                fprintf(stdout, "Falha na conexao\n");
                exit(1);
        }

        printf("Cliente %s:%u conectado.\n", inet_ntoa (infoCli.sin_addr), ntohs (infoCli.sin_port)); 
        listen_client (novo_sd, infoCli);
        return (0);
}