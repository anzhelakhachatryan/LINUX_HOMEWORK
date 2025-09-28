#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#define BUFFER_SIZE 4096

int main(int argc, char** argv) {
	if(argc !=2 ) {
	fprintf(stderr, "Using: %s <read_posix>\n", argv[0]);
	exit(EXIT_FAILURE);
	}
	
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);
	ssize_t bytes_written;
	ssize_t total_written;

	while(bytes_read > 0){
		total_written = 0;
		while(total_written < bytes_read){
			bytes_written = write(STDOUT_FILENO, buffer + total_written, bytes_read- total_written);
			if(errno == EINTR) {
				continue;
			}
			perror("Error writing to standart output");
			close(fd);
			exit(EXIT_FAILURE);
	}
            total_written += bytes_written;
   }
   	if (bytes_read == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    if (close(fd) == -1) {
        perror("Error closing file");
        exit (EXIT_FAILURE);
    }

    return 0;
}

