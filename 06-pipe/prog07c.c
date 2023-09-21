#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

// SUMMARY
//
// As pipes are used as files, they can also get their descriptors duplicated with
// dup2 into other indices, such as stdin or stdout.  This allows a familiar scenario
// where process A writes data to standard output and process B reads that same data
// from its own standard input.  That's in fact what happens, when the shell (command
// line interpreter) executes a command line like:
//    cat lusiadas.txt | grep Portugal
// The shell will create a pipe (because of "|"), then it will fork twice, with the
// first child setting its standard output to the pipe's output descriptor, and the
// second child setting its standard input to the pipe's input descriptor, and finally
// each child calling exec, the first one for "cat lusiadas.txt" and the second one for
// "grep Portugal". 
//
// The demo below is simpler, as only one child is created that will write back to its
// parent over the pipe, and the parent transforming itself into "grep" through a call 
// to exec.

// COMPILE:
//   gcc -o prog07c prog07c.c
//
// RUN:
//   ./prog07c

int main() {
	puts("prog07c running");

	int pipefd[2];
	pipe(pipefd);

	pid_t pid = fork();
	if (pid == 0) {
		close(pipefd[0]);

		dup2(pipefd[1], 1);
		close(pipefd[1]);

		puts("hello, world!");
		sleep(3);
		puts("hello, isel!");
		sleep(3);
		puts("hello, leic51d!");

	} else {
		close(pipefd[1]);

		dup2(pipefd[0], 0);
		close(pipefd[0]);
		
		execlp("grep", "grep", "i", NULL);
	}
}
