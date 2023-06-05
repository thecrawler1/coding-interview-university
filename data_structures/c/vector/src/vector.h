#ifndef VECTOR_H
#define VECTOR_H

#define DEFAULT_CAPACITY 16

struct vector {
  int *arr;
  int size;
  int capacity;
};

struct vector create_vector();
int is_empty(struct vector *);
void push(struct vector *, int);
int get(struct vector *, int);
int pop(struct vector *);
int find(struct vector *, int);
void insert(struct vector *, int, int);
void prepend(struct vector *, int);
void update(struct vector *, int, int);
void delete_by_index(struct vector *, int);
void delete_by_value(struct vector *, int);

#endif // !VECTOR_H

