/*
 * hw1.2.c
 *
 *  Created on: Feb 15, 2018
 *      Author: daniel
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINE 5

void tokenizeStr(char[], char*[]);

int main(void) {
	char *args[MAXLINE / 2 + 1];
	size_t input;
	char *buffer;
	size_t maxsize = MAXLINE;

	buffer = (char*)malloc(maxsize * sizeof(char));
	int should_run = 1;
	printf("CS 149 Shell from Daniel Waters\n");
	while (should_run) {
		printf("Daniel-692> ");
		fflush(stdout);

		input = getline(&buffer, &maxsize, stdin);
		printf("read in %lu characters\n", input);
		tokenizeStr(buffer, args);
		if (!strcmp("exit", args[0])) {
			should_run = 0;
			continue;
		}

		int index = 0;
		while(args[index] != NULL) {
			printf("The token strings are: %s\n", args[index]);
			index++;
		}
		printf("index size is %d\n", index);


	}
	free(buffer);
	return 0;
}

void tokenizeStr(char str[], char *tokens[]) {
	int index = 0;
	tokens[index] = strtok(str, " ");
	while (tokens[index] != NULL) {
		index++;
		tokens[index] = strtok(NULL, " ");
	}
}

