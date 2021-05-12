#pragma once

#include <stdlib.h>

#include <arpa/inet.h>

void logexit(const char *msg);

int addrparse(const char *addrstr, const char *portstr, 
    struct sockaddr_storage *storage);

void addrtostr(const struct sockaddr *addr, char *str, size_t strsize);

int server_sockaddr_init(const char *portstr, struct sockaddr_storage *storage);

int checkStringValid(const char s[]); // 0 if invalid, 1 if valid

int checkStringSubscribe(const char s[]); // 0 if not a tag, 1 if subscribe tag, 2 if unsubscribe tag