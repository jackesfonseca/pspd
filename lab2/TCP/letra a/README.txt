1 Worker e 1 Client
# Entre na pasta letra_a/
$ cd letra_a/

# Execute o comando make para compilar o servidor e o cliente
# obs.: esse comando irar gerar o server tcps e o client tcpc
$ make

# Inicie o server no seguinte formato
# ./tcps [ip_servidor] [porta_servidor]
$ ./tcps 127.0.0.1 1234

# Inicie o client no seguinte formato
# ./tcpc [ip_server] [porta_server] [tamanho_vetor]
$ ./tcpc 127.0.0.1 1234 1000000