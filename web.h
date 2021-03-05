#ifndef LAB0_WEB_H
#define LAB0_WEB_H

#include <arpa/inet.h> /* inet_ntoa */
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sendfile.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "console.h"
#include "type.h"

#define LISTENQ 1024 /* second argument to listen() */
#define MAXLINE 1024 /* max length of a line */

#ifndef DEFAULT_PORT
#define DEFAULT_PORT 9999 /* use this port if none given as arg to main() */
#endif

#ifndef FORK_COUNT
#define FORK_COUNT 4
#endif

#ifndef NO_LOG_ACCESS
#define LOG_ACCESS
#endif


/* Simplifies calls to bind(), connect(), and accept() */
typedef struct sockaddr SA;

typedef struct {
    char function_name[512];
    off_t offset; /* for support Range */
    size_t end;
} http_request;

typedef struct {
    const char *extension;
    const char *mime_type;
} mime_map;



void rio_readinitb(rio_t *rp, int fd);
ssize_t writen(int fd, void *usrbuf, size_t n);
ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n);
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
void handle_request(int out_fd, char *function_name);
const char *get_mime_type(char *filename);
int open_listenfd(int port);
void url_decode(char *src, char *dest, int max);
void parse_request(int fd, http_request *req);
#ifdef LOG_ACCESS
void log_access(int status, struct sockaddr_in *c_addr, http_request *req);
#endif
char *process(int fd, struct sockaddr_in *clientaddr);
int socket_init();

#endif