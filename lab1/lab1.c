#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *buff = NULL;
  size_t size = 0; // need size_t since the memory always positive

  printf("Please enter some text: ");

  // getline parts
  while (getline(&buff, &size, stdin) != -1) {
    size_t len = strlen(buff);              // it uses to measure the input length
    if (len > 0 && buff[len - 1] == '\n') { // to check whether the last word is \n
      buff[len - 1] = '\0';                 // if yes, use \0 to replace:
    }

    // strtok part
    printf("Tokens:\n");

    char *saveptr = NULL;

    // the first call
    char *token = strtok_r(buff, " ", &saveptr);

    // keep looping
    while (token != NULL) {
      printf("   %s\n", token); // splitting the word

      token = strtok_r(NULL, " ", &saveptr);
    }
    printf("Please enter some text: ");
  }
  free(buff);
  return 0;
}
