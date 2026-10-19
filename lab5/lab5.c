
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next, int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;

  if (current == NULL) {
    return -1;
  }

  while (current->next != NULL) {
    if (current->size >= size) {
      return current->id;
    }
    current = current->next;
  }

  if (current->size >= size) {
    return current->id;
  }

  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;
  int best_fit_id = -1;
  uint64_t best_size = 0;

  if (current == NULL) {
    return -1;
  }

  while (current->next != NULL) {
    if (current->size >= size) {
      if (best_fit_id == -1 || current->size < best_size) {
        best_fit_id = current->id;
        best_size = current->size;
      }
    }
    current = current->next;
  }

  if (current->size >= size) {
    if (best_fit_id == -1 || current->size < best_size) {
      best_fit_id = current->id;
      best_size = current->size;
    }
  }

  return best_fit_id;
}

// Worst Fit: Find the largest block that is big enough
int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;
  int worst_fit_id = -1;
  uint64_t worst_size = 0;

  if (current == NULL) {
    return -1;
  }

  while (current->next != NULL) {
    if (current->size >= size) {
      if (worst_fit_id == -1 || current->size > worst_size) {
        worst_fit_id = current->id;
        worst_size = current->size;
      }
    }
    current = current->next;
  }

  if (current->size >= size) {
    if (worst_fit_id == -1 || current->size > worst_size) {
      worst_fit_id = current->id;
      worst_size = current->size;
    }
  }

  return worst_fit_id;
}

int main(void) {
  struct header *free_block1 = malloc(sizeof(struct header));
  struct header *free_block2 = malloc(sizeof(struct header));
  struct header *free_block3 = malloc(sizeof(struct header));
  struct header *free_block4 = malloc(sizeof(struct header));
  struct header *free_block5 = malloc(sizeof(struct header));

  if (free_block1 == NULL || free_block2 == NULL || free_block3 == NULL || free_block4 == NULL ||
      free_block5 == NULL) {
    free(free_block1);
    free(free_block2);
    free(free_block3);
    free(free_block4);
    free(free_block5);
    return 1;
  }

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);

  return 0;
}
