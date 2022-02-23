Múltiplos Workers e 1 Client
# Entre na pasta letra_a/
$ cd letra_a/

# Execute o comando make para compilar o servidor e o cliente
# obs.: esse comando irar gerar o server tcps e o client tcpc
$ make

# Inicie o(s) server(s) no seguinte formato
# ./tcps [ip_servidor] [porta_servidor]
$ ./tcps 127.0.0.1 1234

# Inicie o client no seguinte formato
# ./tcpc [quantidade_servers] <[ip_server] [porta_server]> [tamanho_vetor]
$ ./tcpc 3 127.0.0.1 1234 127.0.0.1 1235 127.0.0.1 1236 1000000