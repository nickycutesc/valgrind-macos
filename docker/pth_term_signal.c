#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <assert.h>

#include <sys/wait.h>

void *
slavethread(void *arg)
{
    sigset_t sigmask;

    // if (sigfillset(&sigmask))
    // {
    //     fprintf(stderr, "Error line %u\n", __LINE__);
    //     _exit(255);
    // }

    // if (pthread_sigmask(SIG_UNBLOCK, &sigmask, 0))
    // {
    //     fprintf(stderr, "Error line %u\n", __LINE__);
    //     _exit(255);
    // }

    while (1)
        sleep(1);
}

void csighandler(int sig) {
  fprintf(stderr, "Child signal %d\n", sig);
}

void
childprocess()
{
    // signal(SIGINT, csighandler);
    // signal(SIGTERM, csighandler);

    // pthread_t slave;

    // if (pthread_create(&slave, 0, &slavethread, 0))
    // {
    //     fprintf(stderr, "Error line %u\n", __LINE__);
    //     _exit(255);
    // }

    while (1)
        sleep(1);
}

void sighandler(int sig) {
  fprintf(stderr, "Parent signal %d\n", sig);
  exit(1);
}

int main(int argc, char **argv)
{
    // signal(SIGINT, sighandler);

    sigset_t sigmask;

    // if (sigfillset(&sigmask))
    // {
    //     fprintf(stderr, "Error line %u\n", __LINE__);
    //     return 255;
    // }

    // if (pthread_sigmask(SIG_BLOCK, &sigmask, 0))
    // {
    //     fprintf(stderr, "Error line %u\n", __LINE__);
    //     return 255;
    // }

    int childpid = fork();

    if (-1 == childpid)
    {
        fprintf(stderr, "Error line %u\n", __LINE__);
        return 255;
    }

    if ( ! childpid)
        childprocess();

    sleep(3);

    if (kill(childpid, SIGTERM))
    {
        fprintf(stderr, "Error line %u\n", __LINE__);
        return 255;
    }

    int status;
    if (childpid != waitpid(childpid, &status, 0))
    {
        fprintf(stderr, "Error line %u\n", __LINE__);
        return 255;
    }

    assert(WIFSIGNALED(status));

    fprintf(stderr, "Signal %d\n", WTERMSIG(status));
    assert(WTERMSIG(status) == SIGTERM);

    return 0;
}
