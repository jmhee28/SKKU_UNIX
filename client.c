#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAXLINE 5000

int main(int argc, char *argv[]) {
	int n, fdnum, fdmax, connfd;
	struct hostent *h;
	struct sockaddr_in saddr;
	char buf[MAXLINE];
	char str[] = "quit";
	char *host = argv[1];
	int port = atoi(argv[2]);
	fd_set readset, copyset;

	if((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket() failed.\n");
		exit(1);
	}

	if((h = gethostbyname(host)) == NULL) {
		printf("invalid hostname %s\n", host);
		exit(2);
	}

	memset((char *)&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *)&saddr.sin_addr.s_addr, (char *)h->h_addr, h->h_length);
	saddr.sin_port = htons(port);

	if(connect(connfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		printf("connect() failed.\n");
		exit(3);
	}
	memset(buf, 0x00, MAXLINE);
	printf("Insert your name : ");
	scanf("%s", buf);
	n = strlen(buf);
	write(connfd, buf, n);

	FD_ZERO(&readset);
	FD_SET(connfd, &readset);
	FD_SET(0, &readset);
	fdmax = connfd;

	while(1) {
		copyset = readset;
		if((fdnum = select(fdmax + 1, &copyset, NULL, NULL, NULL)) < 0) {
			printf("select() failed\n");
			exit(0);
		}
		for(int i = 0; i < fdmax + 1; i++) {
			if(FD_ISSET(i, &copyset)) {
				if(i == connfd) {
					memset(buf, 0, sizeof(buf));
					if((n = read(connfd, buf, MAXLINE)) > 0) write(1, buf, n);
				} else {
					memset(buf, 0, sizeof(buf));
					fgets(buf, MAXLINE, stdin);
					buf[strlen(buf) - 1] = '\0';
					if(strcmp(buf, str) == 0) exit(1);
					write(connfd, buf, strlen(buf));
				}		
			}
		}
	}
	close(connfd);
	return 0;
}
