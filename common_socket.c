#include "common_socket.h"
#define BUFFER_SIZE 64
#define LONGITUD_COLA 10

void socket_init(socket_t *self){
	self->fd=-1;
}

void socket_uninit(socket_t *self){
	self->fd=-1;
}

void socket_connect(socket_t *self, const char *host, const char *service){
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    //int sfd, s, j;
    int s,sfd;
   /// size_t len;
   // ssize_t nread;
   // char buf[BUFFER_SIZE];

    /* Obtain address(es) matching host/port */

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
    hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    s = getaddrinfo(host, service, &hints, &result);
    if (s != 0) {
    	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    	return;
    	//exit(EXIT_FAILURE);
    }

    for (rp = result; rp != NULL; rp = rp->ai_next) {
    	sfd = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);

        if (sfd == -1)
        	continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
        	break;                  /* Success */

        close(sfd);
    }

    if (rp == NULL) {               /* No address succeeded */
    	fprintf(stderr, "Could not connect\n");
    	return;
               }
}


void socket_bind_and_listen(socket_t *self,const char *host,const char *service){
    int fd = -1;
    struct addrinfo hints;
	struct addrinfo *result, *rp;
	//int s;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    getaddrinfo(NULL, service, &hints, &result);

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        fd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);

        if (fd == -1)
            continue;

        if (bind(fd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */

        close(fd);
    }

    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "Could not bind\n");
        return;
    }

    freeaddrinfo(result);
    listen(fd, LONGITUD_COLA);

    self->fd=fd;
}


void socket_accept(socket_t *listener, socket_t *peer){

    char addressBuf[INET_ADDRSTRLEN];
    struct sockaddr_in address;
    socklen_t addressLength = (socklen_t) sizeof(address);

    int newSocket = accept(listener->fd, (struct sockaddr *)&address,&addressLength);

    inet_ntop(AF_INET, &(address.sin_addr), addressBuf, INET_ADDRSTRLEN);
    printf("Se conectó un usuario: %s\n", addressBuf);
    // Está rompiendo su encapsulamiento, coxhino!
    peer->fd = newSocket;

}


