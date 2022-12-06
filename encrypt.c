#include <stdio.h> // printf scanf
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "union.h"
#include "func.h"
	       	

int main(int argc, char* argv[])
{
	if (argc <= 1) {
		fprintf(stderr, "%s", "\e[0;31m You should specify file name as argument!\n \e[0m");
		return 1;
	}

	union U u1;
	int size = sizeof(u1);
	unsigned char (*pencrypt)(unsigned char) = &encrypt; // pointer to function
	unsigned char *res = malloc(size); // dynamic memory

	printf("\e[0;35m Let's Encrypt:\n \e[0m"); // Hello

	// User input
	scanf("%s", u1.Area.title);
	scanf("%f %f", &u1.Area.x, &u1.Area.y);

	// File handling
	FILE *write_ptr;
	/* Test Presentation */
	write_ptr = fopen("plaintext", "wb");
	fwrite(u1.bytearr, size, sizeof(char), write_ptr);
	process(u1.bytearr, res, size, pencrypt);

	const char* fname = argv[1];
	write_ptr = fopen(fname, "wb");
	if (write_ptr == NULL) {
		fprintf(stderr, "Value of errno: %d\nError opening file\n", errno);
		free(res);
		exit(EXIT_FAILURE);
	}

	// if (access(fname, W_OK) == 0) {
	// 	write_ptr = fopen(fname, "wb");
	// }
	// else { // Can't access to the file
	// 	fprintf(stderr, "%s", "\e[0;31m File doesn't exist.\n \e[0m");
	// 	free(res);
	// 	exit(EXIT_FAILURE);
	// }

	fwrite(res, size, sizeof(char), write_ptr); // Write into file
	if (feof(write_ptr)) {
		fprintf(stderr, "Error reading %s: unexpected end of file\nValue of errno: %d\n", fname, errno);
		free(res);
		fclose(write_ptr);
		exit(EXIT_FAILURE);
	}
	else if (ferror(write_ptr)) {
		fprintf(stderr, "Error reading file\nValue of errno: %d\n", errno);
		free(res);
		fclose(write_ptr);
		exit(EXIT_FAILURE);
	}

	// printf("%s\t%f\t%f\n", u1.Area.title, u1.Area.x, u1.Area.y);

	// print plaintext as bytes
	for (int i = 0; i < size; i++) {
		printf("%x ", u1.bytearr[i]);
	}
	free(res);
	fclose(write_ptr);
	return 0;
}
