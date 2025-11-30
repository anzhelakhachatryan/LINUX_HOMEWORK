#include <iostream>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>
#include <ucontext.h>
#include <cstring>

void print_sender_info(siginfo_t* info)
{
    pid_t spid = info->si_pid;
    uid_t suid = info->si_uid;
    passwd* pw = getpwuid(suid);
    const char* uname = pw ? pw->pw_name : "unknown";

    std::cout << "Received SIGUSR1 from process "
              << spid << " executed by "
              << suid << " (" << uname << ")" << std::endl;
}

void print_context_registers(void* context)
{
#if defined(__x86_64__)
    ucontext_t *uc = static_cast<ucontext_t*>(context);
    unsigned long rip = uc->uc_mcontext.gregs[REG_RIP];
    unsigned long rax = uc->uc_mcontext.gregs[REG_RAX];
    unsigned long rbx = uc->uc_mcontext.gregs[REG_RBX];

    std::cout << "State of context: EIP = 0x"
              << std::hex << (unsigned int)rip
              << ", EAX = 0x" << (unsigned int)rax
              << ", EBX = 0x" << (unsigned int)rbx
              << std::dec << std::endl;

#elif defined(__i386__)
    ucontext_t *uc = static_cast<ucontext_t*>(context);
    unsigned long eip = uc->uc_mcontext.gregs[REG_EIP];
    unsigned long eax = uc->uc_mcontext.gregs[REG_EAX];
    unsigned long ebx = uc->uc_mcontext.gregs[REG_EBX];

    std::cout << "State of context: EIP = 0x"
              << std::hex << eip
              << ", EAX = 0x" << eax
              << ", EBX = 0x" << ebx
              << std::dec << std::endl;
#else
    std::cout << "State of context: unsupported architecture." << std::endl;
#endif
}

void handler(int, siginfo_t *info, void *context)
{
    print_sender_info(info);
    print_context_registers(context);
}

void setup_signal()
{
    struct sigaction sa;
    std::memset(&sa, 0, sizeof(sa));

    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;

    sigaction(SIGUSR1, &sa, nullptr);
}

int main()
{
    std::cout << "PID: " << getpid() << "\n";
    setup_signal();

    while (true)
        sleep(10);
}

