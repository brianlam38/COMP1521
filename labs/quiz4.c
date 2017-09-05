#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	int t1 = 0;
	int t2 = 1;
	int t3 = 10;

	while (t2 < t3) {
		t1 = t1 * t2;
		t2 = t2 + 1;
	}

	printf("%d\n", t1);
	return EXIT_SUCCESS;
}