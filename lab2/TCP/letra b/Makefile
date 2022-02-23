CLIENT = tcpClient
SERVER = tcpServer

CFLAGS = -Wall

all : $(CLIENT) $(SERVER)

$(CLIENT) : tcpClient.c
	gcc tcpClient.c -o $(CLIENT)

$(SERVER) : tcpServer.c
	gcc tcpServer.c -o $(SERVER)