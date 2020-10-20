#include "common_socket.h"
#define LONGITUD_COLA 10

void socket_init(socket_t *self){
	self->fd=-1;
}

void socket_uninit(socket_t *self){
	shutdown(self->fd,SHUT_RDWR);
	close(self->fd);
}

void socket_connect(socket_t *self, const char *host, const char *service){
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    int codigo_getaddrinfo,socketfd;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;
    codigo_getaddrinfo = getaddrinfo(host, service, &hints, &result);
    if (codigo_getaddrinfo != 0) {
    	fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(codigo_getaddrinfo));
    	return;
    }
    for (rp = result; rp != NULL; rp = rp->ai_next) {
    	socketfd = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
        if (socketfd == -1)
        	continue;
        if (connect(socketfd, rp->ai_addr, rp->ai_addrlen) != -1)
        	break;
        close(socketfd);
    }
    self->fd=socketfd;
    freeaddrinfo(result);
    if (rp == NULL) {
    	fprintf(stderr, "No se pudo conectar\n");
    	return;
    }
}


void socket_bind_and_listen(socket_t *self,\
		const char *host,const char *service){
    int fd = -1;
    struct addrinfo hints;
	struct addrinfo *result, *rp;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    //Obtengo la lista de resultados para el servicio
    getaddrinfo(NULL, service, &hints, &result);
	int val_opt=1;
	setsockopt(self->fd,SOL_SOCKET,SO_REUSEADDR,&val_opt,sizeof(val_opt));
	//Itero la lista, si no puedo bindear sigo intentando
	//con los siguientes resultados
    for (rp = result; rp != NULL; rp = rp->ai_next) {
        fd = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
        if (fd == -1)
            continue;
        if (bind(fd, rp->ai_addr, rp->ai_addrlen) == 0)
            break;                  /* Success */
        close(fd);
    }
    if (rp == NULL) {               /* No address succeeded */
        fprintf(stderr, "No se pudo hacer el bind\n");
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

    int newSocket = accept(listener->fd, \
    		(struct sockaddr *)&address,&addressLength);

    inet_ntop(AF_INET, &(address.sin_addr), addressBuf, INET_ADDRSTRLEN);
    peer->fd = newSocket;
}

ssize_t socket_send(socket_t *self, unsigned char *buffer, size_t length){
	ssize_t longitud_restante=length;
	unsigned char* puntero_a_caracter_actual=buffer;

    while (longitud_restante>0){
    	ssize_t caracteres_enviados;
    	caracteres_enviados=send(self->fd,puntero_a_caracter_actual\
    			,longitud_restante,MSG_NOSIGNAL);
    	// Si caracteres enviados=-1, hubo un error en el intento de envio
        if (caracteres_enviados==-1){
        	if (errno==EACCES){
        		fprintf(stderr,"No esta permitida la escritura en el fd de destino\n");
        		}
        	else if (errno==EAGAIN){
        		fprintf(stderr,"El socket no esta ligado a una direccion \n");
        	}
        	else if (errno==EBADF){
        		fprintf(stderr,"sockfd no es un file descriptor valido\n");
        	}
        	else{
        		fprintf(stderr,"Error al enviar \n");
        	}
        	break;
        }
        puntero_a_caracter_actual=caracteres_enviados+puntero_a_caracter_actual;
        longitud_restante=longitud_restante-caracteres_enviados;
    }
    return longitud_restante;
}


ssize_t socket_receive(socket_t *self,unsigned char *buffer, size_t length){
	ssize_t longitud_restante=length;
	unsigned char* puntero_a_caracter_actual=buffer;

	while (longitud_restante>0){
		ssize_t caracteres_recibidos;

		caracteres_recibidos=recv(self->fd,puntero_a_caracter_actual\
				,longitud_restante,0);
		//Si es -1, hubo un error al recibir
		if (caracteres_recibidos==-1){
			fprintf(stderr,"Error al recibir \n");
			break;
		}else if (caracteres_recibidos==0){//Si es 0, llegue al 'end of file', paro de recibir
			return length-longitud_restante;
		}else{
	        puntero_a_caracter_actual=caracteres_recibidos\
	        		+puntero_a_caracter_actual;
	        longitud_restante=longitud_restante-caracteres_recibidos;
		}
	}
	return length-longitud_restante;
}
