#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

// SUMMARY
//
// As the file descriptor table is cloned during fork, any new child process will
// have access to the same pipe file descriptors as its parent at fork-time.
// This enables a more useful scenario, where two (hierarchical related) processes
// communicate over one or more pipes.
//
// As pipes are a single byte queue, they are adequate for unidirectional communication.
// The parent and child process will close the pipe file descriptors that they won't be
// using (e.g. the "writer" child closes its own input descriptor for the pipe, while
// the "reader" parent closes its own output descriptor for that same pipe).
//
// Reading from the pipe will block waiting for more data if it finds the pipe empty, 
// unless all output descriptors for that pipe have already been closed by all processes,
// in which case read returns 0.  If some output descriptor is left open by mistake, read
// might get blocked indefinitely.

// COMPILE:
//   gcc -o prog07b prog07b.c
//
// RUN:
//   ./prog07b

int main() {
	puts("prog07b running");

	int pipefd[2];
	pipe(pipefd);

	pid_t pid = fork();
	if (pid == 0) {
		close(pipefd[0]);

		write(pipefd[1], "hello, world!\n", 14);
		sleep(3);
		write(pipefd[1], "hello, isel!\n", 13);
		sleep(3);
		write(pipefd[1], "hello, leic51d!\n", 16);

		close(pipefd[1]);
	} else {
		close(pipefd[1]);  // What happens if this line is deleted/commented? Why?

		for (;;) {
			char msg[256];
			int n = read(pipefd[0], msg, 255);
			if (n == 0) break;
			
			msg[n] = 0;
			printf("[msg] %s\n", msg); 
		}

		close(pipefd[0]);
	}
}
