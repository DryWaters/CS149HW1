/*
 * shell_DanielWaters_629.c
 *
 *  Created on: Feb 15, 2018
 *      Author: Daniel Waters
 *      CSUID: 011872692
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 80

int tokenizeStr(char[], char*[]);
void stripNewLine(char[]);

int main(void) {
	char *args[MAXLINE / 2 + 1];
	char *input;				// location to save the input from the user (used by getline)
	size_t bufferSize = MAXLINE;// unsigned int to hold the size of the max buffer size (used by getline)
	int runInBackground = 0;	// Flag to see if user wants to run the process in the background
	int should_run = 1;			// Flag to see if user wants to exit
	int numberOfArgs = 0;		// Keeps track of the number of arguments

	input = (char*)malloc(bufferSize * sizeof(char));	// Define the memory block to hold the line of input

	printf("CS 149 Shell from Daniel Waters\n");
	while (should_run) {
		printf("Daniel-692> ");
		fflush(stdout);

		// Read in a line of characters from stdin.  getline will try and realloc if it exceeds
		// the defined size, so need to check after removing the new line that it does not exceed
		getline(&input, &bufferSize, stdin);
		stripNewLine(input);

		// If the number of characters (after stripping the newline character) are more than MAXLINE then ask again.
		if (strlen(input) > MAXLINE) {
			printf("Maximum number of characters is %d.  Please try again.\n", MAXLINE);
			continue;
		}

		// Tokenize the string and check if user wants to quit.
		numberOfArgs = tokenizeStr(input, args);
		if (!strcmp("exit", args[0])) {
			should_run = 0;
			continue;
		}

		// check if parent process should wait for the child process to end first
		// if run in the background, remove the & from the arguments as it is used
		// by the system and not exec
		if (!strcmp("&", args[numberOfArgs-1])) {
			runInBackground = 1;
			args[numberOfArgs-1] = '\0';
		} else {
			runInBackground = 0;
		}

		// Fork off a child process
		int pid = fork();

		switch (pid) {
		// Error in the forking
		case -1:
			printf("Unable to fork off a new process.  Please try again.\n");
			break;
		// Child process
		case 0:
			// If return value is -1, then unable to start the process with the given name inside args[0]
			if(execvp(args[0], args) == -1) {
				printf("Error executing %s.  Please check name.\n", args[0]);
				return 1;
			}
			return 0;
			break;
		// Parent process
		default:
			// if user does not want to run in the background, then wait for the child to finish
			if(!runInBackground) {
				wait(NULL);
			}
		}
	}

	// clear the input buffer (from malloc)
	free(input);
	return 0;
}

// Method to tokenize a string and returns the number of tokens that were processed.
int tokenizeStr(char str[], char *tokens[]) {
	int index = 0;
	tokens[index] = strtok(str, " ");
	while (tokens[index] != NULL) {
		index++;
		tokens[index] = strtok(NULL, " ");
	}
	return index;
}

// removes the new line character (if present)
void stripNewLine(char str[]) {
	if (str[strlen(str)-1] == '\n') {
		str[strlen(str)-1] = '\0';
	}
}

