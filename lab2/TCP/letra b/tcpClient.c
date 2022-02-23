
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "info.h"


typedef struct {
        struct sockaddr_in infoServ; /* contem dados do servidor */
        int sd;        	             /* socket descriptor  */
} servidor_socket;


void
generate_vetor (vetor *argp, int tam, int start, int end)
{
        int len = end - start;
        argp->vetor_len = len;
        argp->vetor_val = malloc (sizeof (float) * len);
        printf("[VETOR] => Criando vetor com start = %d, end = %d e tamanho = %d\n", start, end, len);

        for (int i = 0; i < len; i++)
                argp->vetor_val[i] = ((start + i) - tam / 2);
}

void
validate_argv(int argc, char *argv[], int *qtdClnts, int *tam)
{
  	if (argc < 5) {
                fprintf (stderr, "Uso correto: %s <qtd_servers> <ip_do_servidor> <porta_do_servidor> <tam_vetor>\n", argv[0]);
                exit(1);
        }

        *qtdClnts = atoi (argv[1]);
        if (*qtdClnts <= 0) {
                fprintf (stderr, "qtd_servers deve ser inteiro maior que 0\n");
                exit (1);
        }

        if (argc < 3 + (*qtdClnts * 2)) {
		fprintf (stderr, "Uso correto: %s <qtd_servers> [<ip_do_servidor> <porta_do_servidor>] <tam_vetor>\n", argv[0]);
		exit (1);
        }

        *tam = atoi (argv[argc - 1]);
        if (*tam <= 0) {
                fprintf (stderr, "len vetor deve ser inteiro maior que 0\n");
                exit (1);
        }
}


int
main (int argc, char *argv[])
{
        // Estrutura de servidores
        servidor_socket *servers;

        // Estruturas temporarias
        struct sockaddr_in infoServ;
        float menor, maior;
        int sd;

        // Validacao dos dados de entrada
        int tam, qtdClnts;
        validate_argv (argc, argv, &qtdClnts, &tam);
        int tam_por_server = tam / qtdClnts;

        servers = malloc (sizeof (servidor_socket) * qtdClnts);

        // Loop para criacao e envio das infos nos sockets
        for (int i = 0; i < qtdClnts; i++) {
                infoServ = servers[i].infoServ;
                sd = servers[i].sd;
                
                // Configuracao de socket
                int servidor = 2 * (i + 1);
                infoServ.sin_family = AF_INET;
                infoServ.sin_addr.s_addr = inet_addr (argv[servidor]);
                infoServ.sin_port = htons (atoi (argv[servidor + 1]));

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

                // Calculo de start e end do vetor
                int start = i * tam_por_server;
                int end;

                if (i + 1 < qtdClnts) end = start + tam_por_server;
                else end = start + tam_por_server + (tam % qtdClnts);

                int tmp = htonl(end - start);
                send (sd, &tmp, sizeof (tmp), 0);

                // Envia dados para os sockets ja conectados
                vetor bufout;
                generate_vetor (&bufout, tam, start, end);
                send (sd, bufout.vetor_val, sizeof (float) * bufout.vetor_len, 0);

                // Calcula o menor e o maior valor retornado
                float menorTmp, maiorTmp;
                recv (sd, &menorTmp, sizeof (float), 0);
                recv (sd, &maiorTmp, sizeof (float), 0);
                // printf("%f %f\n", menorTmp, maiorTmp);

                if (i == 0) menor = menorTmp;
                if (i == qtdClnts - 1) maior = maiorTmp;

                close (sd);
                free(bufout.vetor_val);
        }

        free(servers);
        printf("Menor valor: %f\nMaior valor: %f\n", menor, maior);
	return (0);
}