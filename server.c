#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define MAXLINE 20000

int main(int argc, char *argv[]) {
	int n, listenfd, connfd, read_len, file_len, caddrlen;
	struct hostent *h;
	struct sockaddr_in saddr, caddr;
	char buf[MAXLINE];
	char str[] = "_copy";
	int port = atoi(argv[1]);

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket() failed.\n");
		exit(1);
	}

	memset((char *)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);
	
	if(bind(listenfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		printf("bind() failed.\n");
		exit(2);
	}
	
	if(listen(listenfd, 5) < 0) {
		printf("listen() failed.\n");
		exit(3);
	}

	while(1) {
		char file_name[MAXLINE];
		memset(buf, 0x00, MAXLINE);

		caddrlen = sizeof(caddr);
		if((connfd = accept(listenfd, (struct sockaddr *)&caddr, (socklen_t *)&caddrlen)) < 0) {
			printf("accept() failed.\n");
			continue;
		}

		if((read_len = read(connfd, buf, MAXLINE)) > 0) {
			strcpy(file_name, buf);
			strcat(file_name, str);
		} else {
			close(connfd);
			break;
		}

		n = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0700);
		while(1) {
			memset(buf, 0x00, MAXLINE);
			file_len = read(connfd, buf, MAXLINE);
			write(n, buf, file_len);

			if(file_len == EOF | file_len == 0) {
				break;
			}
		}
		close(connfd);
		close(n);
	}
	close(listenfd);
	return 0;
}


