#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
  if(argc != 2) {
        perror("error ");
        exit(EXIT_FAILURE);
    }
  int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("error");
        exit(EXIT_FAILURE);
    }
	int size = 4096;
    char buf1[size];
    char buf2[size];
    for (int i = 0; i < 4096; i++) {
        buf2[i] = '\0';
    }

    int  bytes_read = read(fd, buf1, size);
    int  file_size = bytes_read;
  while (bytes_read  > 0) {
        bytes_read = read(fd, buf1, size);
        file_size += bytes_read;
    }

    lseek(fd, 0, SEEK_SET);
    while(file_size != 0) {
        if(size > file_size) {
            size = file_size;
        }
        int bytes_wr = write(fd, bf_write, size);
        file_size -= bytes_wr;
    }

    close(fd);
    return 0;
  
}

