#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/wait.h>
#include <string>
#include <regex>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>



std::vector<std::string> split_by_str(const std::string& str, const std::string& d) {
    std::vector<std::string> res;
    size_t pos = str.find(d);

    if (pos == std::string::npos) {
        res.push_back(str);
    }
     else {
        res.push_back(str.substr(0, pos));
        res.push_back(str.substr(pos + d.length()));
    }
    return res;
}


std::vector<std::string> split(const std::string& str, char d) {
    std::vector<std::string> res;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, d)) {
        if (!token.empty()) {
            res.push_back(token);
        }
    }
    return res;
}

int run(std::string cmnd, int OUTPUT = 1) {
    const char* char_cmnd = cmnd.data();
    int pid = fork();

    if (pid == 0) {
        if (OUTPUT != 1) {
            dup2(OUTPUT, 1);
            close(OUTPUT);
        }

        std::vector<std::string> args = split(cmnd, ' ');
        std::vector<char*> argv;

        for (const auto& arg : args) {
            argv.push_back(const_cast<char*>(arg.c_str()));
        }

        argv.push_back(nullptr);
        execvp(argv[0], argv.data());
        std::cerr << "Fail execution of " << cmnd << std::endl;
        exit(EXIT_FAILURE);
    } else if (pid > 0) {

        int status_code;

        if(wait(&status_code) == -1) {
            std::cerr << "Fail waiting for a child " << cmnd << std::endl;
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status_code)) {
            return WEXITSTATUS(status_code);
        }
    } else {
        std::cerr << "Fork fail "
                  << cmnd << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}

int foo(std::string& command) {
    if (command.find("&&") != std::string::npos) {
            std::vector<std::string> args = split_by_str(command, " && ");
            if (foo(args[0]) == 0) {
                foo(args[1]);
            }
    } else if (command.find("||") != std::string::npos)
            {
            std::vector<std::string> args = split_by_str(command, " || ");
            if (foo(args[0]) != 0) {
                foo(args[1]);
            }
        } else if (command.find(';') != std::string::npos) {
            std::vector<std::string> args = split_by_str(command, "; ");
            foo(args[0]);
            foo(args[1]);

        } else if (command.find(">>") != std::string::npos)
            {
            std::vector<std::string> args = split_by_str(command, " >> ");
            int fd = open(args[1].c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);

            if (fd == -1) {
                std::cerr << "Failed to open file: \n";
                exit(EXIT_FAILURE);
            }

            run(args[0], fd);
            close(fd);

        } else if (command.find('>') != std::string::npos) {
            std::vector<std::string> args = split_by_str(command, " > ");
            int fd = open(args[1].c_str(), O_WRONLY | O_CREAT, 0644);

            if (fd == -1) {
                std::cerr << "Failed to open file: \n";
                exit(EXIT_FAILURE);
            }

            run(args[0], fd);
            close(fd);

        }else{
            return run(command);
        }

        return 0;
}

int main() {
    std::string command;
    std::cout << "> ";
    std::getline(std::cin, command);

    while (command != "EXIT") {
        if (command.empty()) {
            continue;
        }

        foo(command);

        std::cout << "> ";
        std::getline(std::cin, command);
    }

    return 0;
}
