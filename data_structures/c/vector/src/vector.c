#include <stdlib.h>
#include <stdio.h>

#include "vector.h"

int * _create_arr(int size) {
  return (int *) malloc(size * sizeof(int));
}

vector create_vector() {
  vector new_vector;

  new_vector.arr = _create_arr(DEFAULT_CAPACITY);
  new_vector.capacity = DEFAULT_CAPACITY;
  new_vector.size = 0;

  return new_vector;
}

void _copy_array(int * old_arr, int * new_arr, int size) {
  for (int i = 0; i < size; i++) {
    *(old_arr + i) = *(new_arr + i);
  }
}

int _min(int a, int b) {
  return a < b ? a : b;
}

void _resize(vector *vector, int new_capacity) {
  int * new_arr = _create_arr(new_capacity);

  _copy_array(vector->arr, new_arr, _min(vector->size, new_capacity));
  free(vector->arr);

  vector->arr = new_arr;
  vector->capacity = new_capacity;
}

int is_empty(vector * vector) {
  return vector->size == 0;
}

void _validate_array_index_bounds(vector *vector, int index) {
  if (index < 0 || index >= vector->size) {
    fprintf(stderr, "Array index out of bounds.\n");
    exit(1);
  }
}

int get(vector * vector, int pos) {
  _validate_array_index_bounds(vector, pos);

  return *(vector->arr + pos);
}

void _increase_capacity_if_needed(vector *vector) {
  if (vector->size == vector->capacity) {
    _resize(vector, vector->capacity * 2);
  }
}

void _decrease_capacity_if_needed(vector *vector) {
  if (vector->capacity > DEFAULT_CAPACITY && vector->size * 4 <= vector->capacity) {
    _resize(vector, vector->capacity / 2);
  }
}

void update(vector *vector, int index, int value) {
  _validate_array_index_bounds(vector, index);

  *(vector->arr + index) = value;
}

void push(vector *vector, int value) {
  _increase_capacity_if_needed(vector);

  vector->size++;
  update(vector, vector->size - 1, value);
}

int pop(vector *vector) {
  if (is_empty(vector)) {
    return -1;
  }

  int element = get(vector, vector->size - 1);
  vector->size--;

  _decrease_capacity_if_needed(vector);

  return element;
}

int find(vector *vector, int element) {
  for (int i = 0; i < vector->size; i++) {
    if (get(vector, i) == element) {
       return i;
    }
  }
  return -1;
}

void insert(vector *vector, int index, int value) {
  _validate_array_index_bounds(vector, index);
  _increase_capacity_if_needed(vector);

  vector->size++;

  for (int i = vector->size - 1; i > index; i--) {
    update(vector, i, get(vector, i - 1));
  }

  *(vector->arr + index) = value;
}

void prepend(vector *vector, int value) {
  insert(vector, 0, value);
}

void delete_by_index(vector *vector, int index) {
  _validate_array_index_bounds(vector, index);

  for (int i = index; i < vector->size - 1; i++) {
    update(vector, i, get(vector, i + 1));
  }

  vector->size--;

  _decrease_capacity_if_needed(vector);
}

void delete_by_value(vector *vector, int value) {
  while (1) {
    int index = find(vector, value);

    if (index != -1) delete_by_index(vector, index);
    else break;
  };
}
