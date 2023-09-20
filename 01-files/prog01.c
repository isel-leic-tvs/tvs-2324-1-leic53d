#include <stdio.h>
#include <unistd.h>

// SUMMARY
//
// Every process has its own file descriptor table (in kernel space).
// File descriptors are positive integer values, that are indices to this table.
// Entries 0, 1, 2 refer to standard input, standard output, and standard error, respectively.
// Using the shell, more entries can be pre-filled using redirects.

// COMPILE:
//   gcc -o prog01 prog01.c
//
// RUN:
//   ./prog01
//   ./prog01 3> output3.txt

int main() {

	write(1, "prog01 running\n", 15);

	int res = write(3, "hello, world\n", 13);
	if (res == -1) {
		perror("write to 3 failed");
	} else {
		puts("write succeeded");
	}

	puts("DONE");
	return 0;
}

