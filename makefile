compile: create_client forking_server persistent_server basic_server

create_client: basic_client.o pipe_networking.o
	@gcc -o client basic_client.o pipe_networking.o

basic_server: basic_server.o pipe_networking.o
	@gcc -o basic_server basic_server.o pipe_networking.o

persistent_server: persistent_server.o pipe_networking.o
	@gcc -o persistent_server persistent_server.o pipe_networking.o

forking_server: forking_server.o pipe_networking.o
	@gcc -o forking_server forking_server.o pipe_networking.o

basic_client.o: basic_client.c pipe_networking.h
	@gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	@gcc -c basic_server.c

persistent_server.o: persistent_server.c pipe_networking.h
	@gcc -c persistent_server.c

forking_server.o: forking_server.c pipe_networking.h
	@gcc -c forking_server.c

client: client
	@./client

server: forking_server
	@./forking_server

clean:
	rm server
	rm client
	rm *.o
	rm *~
