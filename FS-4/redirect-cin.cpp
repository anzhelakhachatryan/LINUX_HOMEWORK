#include <iostream>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <algorithm>

void initialize(int argc, char** argv)
{
  if(argc != 2) {
    perror("error");
    exit(EXIT_FAILURE);
  }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1) {
    perror("cant open");
    exit(EXIT_FAILURE);
  }

  int newfd = dup2(fd, 0);
  if (newfd == -1) {
    perror("cant dup fd");
    close(fd);
    exit(EXIT_FAILURE);
  }

  close(fd);
}
 
int main(int argc, char** argv)
{
  initialize(argc, argv);
 
  std::string input;
  std::cin >> input;

  std::string rev = input;
  std::reverse(rev.begin(), rev.end());
  std::cout << rev << std::endl;
 
  return 0;
}
