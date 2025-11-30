#include <iostream>
#include <unistd.h>

bool isPrime(int n)
{
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int mthPrime(int m)
{
    int count = 0;
    int num = 1;
    while (count < m)
    {
        num++;
        if (isPrime(num)) count++;
    }
    return num;
}

/* ---------------- CHILD PROCESS ---------------- */

void childLoop(int readFd, int writeFd)
{
    while (true)
    {
        int m;
        ssize_t n = read(readFd, reinterpret_cast<void*>(&m), sizeof(m));
        if (n <= 0 || m <= 0) break;

        std::cout << "[Child] Calculating " << m << "-th prime number..." << std::endl;
        int prime = mthPrime(m);

        std::cout << "[Child] Sending calculation result of prime(" << m << ")..." << std::endl;
        n = write(writeFd, reinterpret_cast<const void*>(&prime), sizeof(prime));
        if (n != sizeof(prime))
        {
            std::cerr << "Writing error" << std::endl;
            break;
        }
    }

    close(readFd);
    close(writeFd);
}

/* ---------------- PARENT PROCESS ---------------- */

void parentLoop(int writeFd, int readFd)
{
    while (true)
    {
        std::cout << "[Parent] Please enter the number: ";
        std::string input;
        std::cin >> input;

        if (input == "exit")
        {
            int stop = 0;
            ssize_t n = write(writeFd, reinterpret_cast<const void*>(&stop), sizeof(stop));
            if (n != sizeof(stop)) std::cerr << "Writing error in exit" << std::endl;
            break;
        }

        int m = std::stoi(input);

        std::cout << "[Parent] Sending " << m << " to the child process..." << std::endl;
        ssize_t n = write(writeFd, reinterpret_cast<const void*>(&m), sizeof(m));
        if (n != sizeof(m)) std::cerr << "Writing error" << std::endl;

        std::cout << "[Parent] Waiting for the response from the child process..." << std::endl;

        int result;
        n = read(readFd, reinterpret_cast<void*>(&result), sizeof(result));
        if (n != sizeof(result)) std::cerr << "Reading error" << std::endl;

        std::cout << "[Parent] Received calculation result of prime(" << m << ") = " 
                  << result << "..." << std::endl;
    }

    close(writeFd);
    close(readFd);
}

/* ---------------- MAIN ---------------- */

int main()
{
    int p2c[2];
    int c2p[2];

    if (pipe(p2c) == -1)
    {
        std::cerr << "pipe parent->child failed" << std::endl;
        return 1;
    }

    if (pipe(c2p) == -1)
    {
        std::cerr << "pipe child->parent failed" << std::endl;
        close(p2c[0]); close(p2c[1]);
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0)
    {
        std::cerr << "Failed fork" << std::endl;
        return 1;
    }

    if (pid == 0)
    {
        close(p2c[1]);
        close(c2p[0]);
        childLoop(p2c[0], c2p[1]);
    }
    else
    {
        close(p2c[0]);
        close(c2p[1]);
        parentLoop(p2c[1], c2p[0]);
    }

    return 0;
}

