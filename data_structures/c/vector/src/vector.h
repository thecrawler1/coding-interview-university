#ifndef VECTOR_H
#define VECTOR_H

#define DEFAULT_CAPACITY 10

struct vector {
  int *arr;
  int size;
  int capacity;
};

struct vector create_vector();

#endif // !VECTOR_H

