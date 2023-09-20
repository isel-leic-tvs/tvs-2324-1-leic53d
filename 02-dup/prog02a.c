#include <stdio.h>
#include <unistd.h>

// SUMMARY
//
// dup duplicates an entry of the file descriptor table.
// It takes the index of the entry to be duplicated and returns the index of the duplicate.
// The available entry with the lowest number is used.

// COMPILE:
//   gcc -o prog02a prog02a.c
//
// RUN:
//   ./prog02a
//   ./prog02a 3> output3.txt

int main() {
	write(1, "prog02a running\n", 16);

	int nfd = dup(1);  // what's the value of nfd for command lines with different redirects?

	int res1 = write(nfd, "hello, world\n", 13);
	if (res1 == -1) {
		perror("write to nfd failed");
	} else {
		puts("write to nfd succeeded");
	}

	int res2 = write(3, "hello, world\n", 13);
	if (res2 == -1) {
		perror("write to 3 failed");
	} else {
		puts("write to 3 succeeded");
	}

	puts("DONE");
	return 0;
}
