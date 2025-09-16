#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MODULE "/dev/teste1"

int main(){
	int fd;

	char buf[64];

	fd = open(MODULE, O_WRONLY);

	if (fd < 0) {
		perror("open");
		return fd;
	}

	printf("Digite:\n");
	scanf("%63s", buf);

	int tam = write(fd, buf, strlen(buf));


	printf("Writing %d bytes to " MODULE "\n", tam);

	close(fd);

	return 0;

}
