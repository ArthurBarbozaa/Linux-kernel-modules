#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MODULE "/dev/teste1"

int main(){
	int fd;

	char c;
	int i = 0;
	char buf[64] = {0};

	fd = open(MODULE, O_RDONLY);

	if (fd < 0) {
		perror("open");
		return 1;
	}

	int tam = read(fd, buf, sizeof(buf));

	if (tam < 0) {
		perror("read");
		close(fd);
		return 1;
	}

	buf[tam] = '\0';

	printf("Read: %s, size: %d\n", buf, tam);

	close(fd);

	return 0;

}
