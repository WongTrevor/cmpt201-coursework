#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
  char *buff = NULL;
  size_t size = 0;

  printf("Please enter some program to run. \n");
  printf(" > ");

  // getline part
  while (getline(&buff, &size, stdin) != -1) {

    // remove \n
    size_t len = strlen(buff);
    if (len > 0 && buff[len - 1] == '\n') {
      buff[len - 1] = '\0';
    }

    // create te=he child process
    pid_t pid = fork();

    if (pid < 0) {
      printf("Fork Fail\n");
    } else if (pid == 0) {
      execlp(buff, buff, NULL);
      printf("Exec fail\n");
      exit(1);
    } else {
      if (waitpid(pid, NULL, 0) == -1) {
        printf("Wait fail\n");
      }
    }

    printf("Please enter some program to run. \n");
    printf(" > ");
  }
  free(buff);
  return 0;
}
