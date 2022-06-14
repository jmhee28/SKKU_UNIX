#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MAXLINE 20000

int main(int argc, char *argv[]) {
	int n, fd, cfd;
	struct hostent *h;
	struct sockaddr_in saddr;
	char buf[MAXLINE];
	char str[] = "quit";
	int file_len;
	char *host = argv[1];
	int port = atoi(argv[2]);

	if((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
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

	if(connect(cfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		printf("connect() failed.\n");
		exit(3);
	}

	while(1) {
		memset(buf, 0x00, MAXLINE);
		scanf("%s", buf);
                printf("File name :%s ", buf);
		if(strcmp(buf, str) == 0){
			printf("\n");  
			break;	
		}
		file_len = strlen(buf);

		send(cfd, buf, file_len, 0);
		fd = open(buf, O_RDONLY | O_CREAT, 0700);
		
		while(1) {
			memset(buf, 0x00, MAXLINE);
			n = read(fd, buf, MAXLINE);
			send(cfd, buf, n, 0);
			if(n == 0) break;
			printf("\ngot %d bytes from client.\n", n);
		}
	}
	close(cfd);
	return 0;
}
