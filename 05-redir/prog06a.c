#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

// SUMMARY
//
// The file descriptor table is copied during a fork.
// We may force file descriptor 1 in the child process
// to refer to a file, instead of its original value.
// This is usually called a redirection of the standard
// output and it can be done for any descriptor.

// COMPILE:
//   gcc -o prog06a prog06a.c
//
// RUN:
//   ./prog06a

int main() {
	puts("prog06a running");

	printf("PROCESS: pid=%d ; ppid=%d\n", 
		getpid(), getppid()
	);

	pid_t pid = fork();
	if (pid == 0) {
		printf("CHILD: pid=%d ; ppid=%d\n", 
			getpid(), getppid()
		);

		int ofd = open("out.txt", O_CREAT | O_WRONLY, 0640);
		if (ofd == -1) {
			perror("open out.txt failed");
			exit(1);
		}

		dup2(ofd, 1);
		close(ofd);

		puts("CHILD: == REDIRECTED OUTPUT ==");
		puts("CHILD: hello, world!");

	} else {
		printf("PARENT: pid=%d ; ppid=%d\n", 
			getpid(), getppid()
		);
		int res = 0;
		waitpid(pid, &res, 0);
		if (WIFEXITED(res)) {
			printf("PARENT: child returned %d\n", 
				WEXITSTATUS(res)
			);
		} else {
			printf("PARENT: child terminated\n"); 
		}
	}

	puts("THE END");
	return 0;
}
