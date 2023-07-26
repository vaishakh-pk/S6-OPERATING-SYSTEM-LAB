//VAISHAKH.P.K
//20220103  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include<sys/wait.h>
int main() {
  int pipefd[2];
  char string[100];
  char isPalindrome;

  // Create a pipe.
  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(1);
  }

  // Fork a child process.
  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(1);
  }

  // Parent process.
  if (pid > 0) {
    // Close the read end of the pipe.
    close(pipefd[0]);

    // Prompt the user for a string.
    printf("Enter a string: ");
    fgets(string, sizeof(string), stdin);

    // Write the string to the pipe.
    write(pipefd[1], string, strlen(string));

    // Wait for the child process to finish.
    wait(NULL);

    // Read the result from the pipe.
    read(pipefd[1], &isPalindrome, sizeof(isPalindrome));

    // Print the result.
    if (isPalindrome) {
      printf("The string is a palindrome.\n");
    } else {
      printf("The string is not a palindrome.\n");
    }
  }

  // Child process.
  else {
    // Close the write end of the pipe.
    close(pipefd[1]);

    // Read the string from the pipe.
    read(pipefd[0], string, sizeof(string));

    // Check if the string is a palindrome.
    isPalindrome = 1;
    for (int i = 0, j = strlen(string) - 1; i < j; i++, j--) {
      if (string[i] != string[j]) {
        isPalindrome = 0;
        break;
      }
    }

    // Write the result to the pipe.
    write(pipefd[1], &isPalindrome, sizeof(isPalindrome));
  }

  return 0;
}

//output

/*
Enter a string: aba
The string is a palindrome.

Enter a string: abasjg
The string is not palindrome.
*/
