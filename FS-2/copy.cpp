#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
int main(int argc, char** argv){
	char buffer[4096];
	if(argc != 3){
		perror("ERROR!");
		exit(EXIT_FAILURE);
	}
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1){
		perror("Error");
		exit(EXIT_FAILURE);
	}
	
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("error");
        exit(EXIT_FAILURE);
    }
	
    int fd2 = open(argv[2], O_WRONLY | O_CREAT, 0644);
	   if (fd2 == -1){
        perror("erRor");
        exit(EXIT_FAILURE);
	    }


	while (bytes_read > 0 ){
        int write_read = write(fd2, buffer, bytes_read);
        if(write_read == -1){
            perror("eRror");
            exit(EXIT_FAILURE);
        }

	    bytes_read = read(fd, buffer, sizeof(buffer) - 1);
		 if (bytes_read == -1) {
        	perror("error");
        	exit(EXIT_FAILURE);
    		}
    

	}
	
	return 0;
}

