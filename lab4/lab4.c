#define _DEFAULT_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[100];

  int len = snprintf(buf, 100, format,
                     data_size == sizeof(uint64_t) ? *(uint64_t *)data : *(void **)data);

  if (len > 0 && len < 100) {
    write(1, buf, len);
  }
}

int main() {
  char *heap = sbrk(256);

  if (heap == NULL) {
    return 1;
  }

  struct header *first = (struct header *)heap;
  struct header *second = (struct header *)(heap + 128);

  first->size = 128;
  first->next = NULL;

  second->size = 128;
  second->next = first;

  char *data1 = (char *)(first + 1);
  char *data2 = (char *)(second + 1);

  int size = 128 - sizeof(struct header);

  for (int i = 0; i < size; i++) {
    data1[i] = 0;
    data2[i] = 1;
  }

  print_out("first block: %p\n", &first, 8);
  print_out("second block: %p\n", &second, 8);

  print_out("first block size: %lu\n", &first->size, 8);
  print_out("first block next: %p\n", &first->next, 8);

  print_out("second block size: %lu\n", &second->size, 8);
  print_out("second block next: %p\n", &second->next, 8);

  for (int i = 0; i < size; i++) {
    uint64_t num = data1[i];
    print_out("%lu\n", &num, 8);
  }

  for (int i = 0; i < size; i++) {
    uint64_t num = data2[i];
    print_out("%lu\n", &num, 8);
  }

  return 0;
}
