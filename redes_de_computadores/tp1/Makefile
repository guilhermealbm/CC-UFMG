all:
	gcc -Wall -c common.c
	gcc -Wall -c userList.c
	gcc -Wall -c tagList.c
	gcc -Wall cliente.c common.o -lpthread -o cliente
	gcc -Wall servidor.c common.o userList.o tagList.o -lpthread -o servidor

clean:
	rm common.o cliente servidor tagList.o userList.o
