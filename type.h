#ifndef LAB0_TYPE_H
#define LAB0_TYPE_H

/*
 * Implement buffered I/O using variant of RIO package from CS:APP
 * Must create stack of buffers to handle I/O with nested source commands.
 */

#define RIO_BUFSIZE 1024
typedef struct RIO_ELE rio_t, *rio_ptr;

struct RIO_ELE {
    int fd;                /* File descriptor */
    int cnt;               /* Unread bytes in internal buffer */
    char *bufptr;          /* Next unread byte in internal buffer */
    char buf[RIO_BUFSIZE]; /* Internal buffer */
    rio_ptr prev;          /* Next element in stack */
};

#endif