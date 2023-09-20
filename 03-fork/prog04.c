#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// SUMMARY
//
// As fork creates a different process, with a different address space,
// global variables are duplicated in memory, and will have independent
// values. Even if they have the same virtual address, they will end up
// in different physical memory addresses.

// COMPILE:
//   gcc -o prog04 prog04.c
//
// RUN:
//   ./prog04

int value = 88;

int main() {
	puts("prog04 running");

	printf("PROCESS: pid=%d ; ppid=%d\n", 
		getpid(), getppid()
	);

	pid_t pid = fork();
	if (pid == 0) {
		printf("CHILD: pid=%d ; ppid=%d\n", 
			getpid(), getppid()
		);
		value += 1000;
	} else {
		printf("PARENT: pid=%d ; ppid=%d\n", 
			getpid(), getppid()
		);
	}

	puts(":: using value ::");

	for (int i = 0; i < 10; ++i) {
		printf("[%d] value at %p is %d\n", getpid(), &value, value);
		value += 1;
		sleep(1);
	}

	if (pid != 0) {
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
