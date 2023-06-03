#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

struct vector create_vector() {
  struct vector new_vector;

  new_vector.arr = (int *) malloc(DEFAULT_CAPACITY * sizeof(int));
  new_vector.size = 0;
  new_vector.capacity = DEFAULT_CAPACITY;

  return new_vector;
}
