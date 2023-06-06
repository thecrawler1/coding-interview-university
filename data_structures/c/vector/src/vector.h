#ifndef VECTOR_H
#define VECTOR_H

#define DEFAULT_CAPACITY 16

typedef struct {
  int *arr;
  int size;
  int capacity;
} vector;

vector create_vector();
int is_empty(vector *);
void push(vector *, int);
int get(vector *, int);
int pop(vector *);
int find(vector *, int);
void insert(vector *, int, int);
void prepend(vector *, int);
void update(vector *, int, int);
void delete_by_index(vector *, int);
void delete_by_value(vector *, int);

#endif // !VECTOR_H

