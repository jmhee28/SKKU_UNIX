#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define MAXLINE 5000

int main(int argc, char *argv[]) {
	int n, listenfd, connfd, caddrlen;
	struct sockaddr_in saddr, caddr;
	char buf[MAXLINE];
	char msg[MAXLINE];
	char user_id[100][25];
	int fdmax, fdnum;
	fd_set readset, copyset;
	int port = atoi(argv[1]);
	int count;

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

	FD_ZERO(&readset);
	FD_SET(listenfd, &readset);
	fdmax = listenfd;
	count = 0;

	while(1) {
		copyset = readset;
		if((fdnum = select(fdmax + 1, &copyset, NULL, NULL, NULL)) < 0) {
			printf("select() failed.\n");
			continue;
		}
		for(int i = 0; i < fdmax + 1; i++) {
			if(FD_ISSET(i, &copyset)) {
				if(i == listenfd) {
					caddrlen = sizeof(caddr);
					if((connfd = accept(listenfd, (struct sockaddr *)&caddr, (socklen_t *)&caddrlen)) < 0) {
						printf("accept() failed.\n");
						continue;
					} 
					count++;					
					
					if((n = read(connfd, user_id[connfd], 100)) > 0) {
						memset(msg, 0, sizeof(msg));
						sprintf(msg, "%s joined. %d current users.\n", user_id[connfd], count);
						printf("%s", msg);
					}	
					FD_SET(connfd, &readset);
					if(fdmax < connfd) fdmax = connfd;
				} else {
					memset(buf, 0, sizeof(buf));
					memset(msg, 0, sizeof(msg));
					if((n = read(i, buf, MAXLINE)) > 0) {
						sprintf(msg, "got %d bytes from user %s.", n, user_id[i]);
						printf("%s\n", msg);
						memset(msg, 0, sizeof(msg));
						sprintf(msg, "Delivered : %s\n", buf);
						for(int j = 4; j < fdmax + 1; j++) {
							if(j == i) write(j, msg, strlen(msg));
						}
					} else {
						count--;
						FD_CLR(i, &readset);
						memset(msg, 0, sizeof(msg));
						sprintf(msg, "%s leaved. %d current users.\n", user_id[i], count);
						printf("%s", msg);
						close(i);
					}
				}
			}
		}
	}
	close(connfd);
	close(listenfd);
	return 0;
}


