#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

// SUMMARY
//
// The file descriptor table is copied during a fork and
// remains (mostly) intact during an exec.
// Between fork and exec, there is the opportunity to 
// modify the file descriptor table.
// For example, we may force file descriptor 1 to refer
// to a file, instead of its original value, before calling
// exec. This is usually seen as a redirection of the
// standard output for the execution of the new program.
// It can be done for any descriptor.

// COMPILE:
//   gcc -o prog06b prog06b.c
//
// RUN:
//   ./prog06b

int main() {
	puts("prog06b running");

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

		// Try different programs
		execlp("echo", "echo", ":: a new process image ::", NULL);
		//execlp("cat", "cat", "prog06a.c", NULL);

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
