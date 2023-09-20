#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// SUMMARY
//
// fork creates a copy of the current process.
//
// It does create a new thread of execution, albeit in it's own process,
// as the original Unix didn't have multiple threads per process.
//
// fork is called once, but returns twice, as the new process starts its
// execution by returning 0 from fork. In the original process, fork will
// return the pid of the new process.
//
// A process that creates other processes MUST wait for their termination,
// or else those child processes remain in a "zombie" state.

// COMPILE:
//   gcc -o prog03a prog03a.c
//
// RUN:
//   ./prog03a

int main() {
	puts("prog03a running");

	printf("PROCESS: pid=%d ; ppid=%d\n", 
		getpid(), getppid()
	);

	pid_t pid = fork();
	if (pid == 0) {
		printf("CHILD: pid=%d ; ppid=%d\n", 
			getpid(), getppid()
		);
	} else {
		printf("PARENT: pid=%d ; ppid=%d\n", 
			getpid(), getppid()
		);
		wait(NULL);
	}

	puts("THE END");
	return 0;
}
