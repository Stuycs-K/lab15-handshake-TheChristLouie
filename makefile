all: client server persistent_server.o forking_server.o

client: basic_client.o pipe_networking.o
	gcc -o client basic_client.o pipe_networking.o

server: basic_server.o pipe_networking.o
	gcc -o server basic_server.o pipe_networking.o

persistent_server.o: persistent_server.c pipe_networking.h
	gcc -o persistent_server.o persistent_server.c

forking_server.o: forking_server.c pipe_networking.h
	gcc -o forking_server.o forking_server.c

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm server
	rm client
	rm *.o
	rm *~
