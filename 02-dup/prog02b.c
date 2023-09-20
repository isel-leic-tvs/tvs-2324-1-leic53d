#include <stdio.h>
#include <unistd.h>

// SUMMARY
//
// dup2 is a variant of dup where the target index can be specified.
// If the target index is not empty, it gets closed first.

// COMPILE:
//   gcc -o prog02b prog02b.c
//
// RUN:
//   ./prog02b
//   ./prog02b 88> output88.txt

int main() {
	write(1, "prog02b running\n", 16);

	int nfd = dup2(1, 88);

	int res1 = write(nfd, "hello, world\n", 13);
	if (res1 == -1) {
		perror("write to nfd failed");
	} else {
		puts("write to nfd succeeded");
	}

	puts("DONE");
	return 0;
}
