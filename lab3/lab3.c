#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *buff = NULL;
  size_t size = 0;

  char *history[5] = {NULL};
  int count = 0;

  printf("Enter input: ");

  while (getline(&buff, &size, stdin) != -1) {
    size_t len = strlen(buff);

    if (len > 0 && buff[len - 1] == '\n') {
      buff[len - 1] = '\0';
    }

    if (count == 5) {
      free(history[0]);

      for (int i = 0; i < 4; i++) {
        history[i] = history[i + 1];
      }
      count = 4;
    }
    history[count] = strdup(buff);
    count += 1;

    if (strcmp(buff, "print") == 0) {
      for (int i = 0; i < count; i++) {
        printf("%s\n", history[i]);
      }
    }

    printf("Enter input: ");
  }
  free(buff);
  return 0;
}
