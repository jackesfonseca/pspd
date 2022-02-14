Pré-requisitos
	* Python 3.5 ou superior
	* pip versão 9.0.1 ou superior

Se necessário, atualize sua versão do pip:
	$ python -m pip install --upgrade pip
 
 
Instale o gRPC:
	$ python -m pip instalar grpcio

Ou, para instalá-lo em todo o sistema:
	$ sudo python -m pip install grpcio
	

Entendendo o funcionamento:
	1. O arquivo greeter_server.py é o servidor e o arquivo greeter_client.py é o cliente 
	2. Tanto o servidor quanto o stub do cliente possuem um método RPC SayHello e SayHelloAgain que recebe um parâmetro HelloRequest do cliente e retorna um HelloReply do servidor.
	3. O arquivo helloworld_pb2.py contém nossas classes de solicitação e resposta geradas e helloworld_pb2_grpc.py contém nossas classes de cliente e servidor geradas.
	
Para rodar a aplicação execute o servidor:
	$ python greeter_server.py
	
De outro terminal, execute o cliente:	
	$ python greeter_client.py
