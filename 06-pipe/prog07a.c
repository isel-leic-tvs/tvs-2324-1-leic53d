#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

// SUMMARY
//
// A pipe is a queue of bytes in (kernel-side) memory, accessed as a file.
// When a process creates a pipe, two entries will be added to its file descriptor
// table. An array (e.g. pipefd) is filled with the descriptor numbers:
//   pipefd[0] : the file descriptor to read bytes from the pipe
//   pipefd[1] : the file descriptor to write bytes to the pipe
// This demo uses a pipe in the simplest (even if likely useless) way. A pipe is
// created, some bytes are written into it, and then they are read back.

// COMPILE:
//   gcc -o prog07a prog07a.c
//
// RUN:
//   ./prog07a

int main() {
	puts("prog07a running");

	int pipefd[2];
	pipe(pipefd);

	write(pipefd[1], "hello, world!", 13);
	
	sleep(5);
	
	char msg[14];
	int n = read(pipefd[0], msg, 13);
	msg[n] = 0;
	
	puts(msg);
}
