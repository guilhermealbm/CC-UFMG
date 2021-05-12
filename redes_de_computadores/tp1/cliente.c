#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFSZ 1024

void usage(int argc, char **argv) {
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

struct clientData {
    int sock;
};

void * listenThread(void *data) {
	struct clientData *cData = (struct clientData *)data;
	while (1) {
		char buf[BUFSZ];
		memset(buf, 0, BUFSZ);

		fgets(buf, BUFSZ-1, stdin);
	
		int size = send(cData->sock, buf, strlen(buf) + 1, 0);
		if (size != strlen(buf) + 1) {
			close(cData->sock);
			free(cData);
			logexit("send");
		}
	}
	

}

#define BUFSZ 1024

int main(int argc, char **argv) {
	if (argc < 3) {
		usage(argc, argv);
	}

	struct sockaddr_storage storage;
	if (0 != addrparse(argv[1], argv[2], &storage)) {
		usage(argc, argv);
	}

	int s;
	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1) {
		logexit("socket");
	}
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(s, addr, sizeof(storage))) {
		logexit("connect");
	}

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	printf("connected to %s\n", addrstr);

	struct clientData *cData = malloc(sizeof(*cData));
	cData->sock = s;

	pthread_t thread;
    pthread_create(&thread, NULL, listenThread, cData);

	while(1) {

		char buf[BUFSZ];
		memset(buf, 0, BUFSZ);
		int total = 0;
		
		while(1) {

			int size = recv(s, buf + total, BUFSZ - total, 0);
			total += size;
			if (size == 0 || buf[strlen(buf) - 1] == '\n')
				break;

		}

		if (total == 0) {
			printf("connection closed\n");
			close(s);
			break;
		}

		printf("%s", buf);

	}

	pthread_cancel(thread);
	pthread_join(thread, NULL);

	if (cData != NULL)
		free(cData);

	exit(EXIT_SUCCESS);
}