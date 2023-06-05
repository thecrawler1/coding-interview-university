#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "vector.h"

void should_create_vector() {
  struct vector vector = create_vector();

  CU_ASSERT_EQUAL(vector.size, 0);
}

void should_create_vector_with_capacity_16() {
  struct vector vector = create_vector();

  CU_ASSERT_EQUAL(vector.capacity, 16);
}

void should_initialize_empty() {
  struct vector vector = create_vector();

  CU_ASSERT_TRUE(is_empty(&vector));
}

void should_push_element() {
  struct vector vector = create_vector();
  
  push(&vector, 42);

  CU_ASSERT_EQUAL(vector.size, 1);
  CU_ASSERT_FALSE(is_empty(&vector));
}

void _insert_n_elements(struct vector *vector, int n) {
  for (int i = 0; i < n; i++) {
    push(vector, 42);
  }
}

void should_increase_capacity_when_needed() {
  struct vector vector = create_vector();
  
  _insert_n_elements(&vector, DEFAULT_CAPACITY + 1);

  CU_ASSERT_EQUAL(vector.capacity, DEFAULT_CAPACITY * 2);
}

void should_get_element() {
  struct vector vector = create_vector();
  
  push(&vector, 42);
  push(&vector, 82);

  CU_ASSERT_EQUAL(get(&vector, 0), 42);
  CU_ASSERT_EQUAL(get(&vector, 1), 82);
}

void should_pop_element() {
  struct vector vector = create_vector();

  push(&vector, 42);

  CU_ASSERT_EQUAL(pop(&vector), 42);
  CU_ASSERT_TRUE(is_empty(&vector));
}

void should_resize_when_pop_and_size_is_one_quarter_of_capacity() {
  struct vector vector = create_vector();

  _insert_n_elements(&vector, 17);

  int one_quarter = vector.capacity / 4;

  while (vector.size > one_quarter) {
    pop(&vector);
  }

  CU_ASSERT_EQUAL(vector.capacity, DEFAULT_CAPACITY);
}

void should_find_element() {
  struct vector vector = create_vector();

  push(&vector, 1);
  push(&vector, 2);
  push(&vector, 3);
  push(&vector, 4);
  push(&vector, 3);

  CU_ASSERT_EQUAL(find(&vector, 3), 2);
}

void should_not_find_element() {
  struct vector vector = create_vector();

  push(&vector, 1);
  push(&vector, 2);
  push(&vector, 3);
  push(&vector, 4);
  push(&vector, 3);

  CU_ASSERT_EQUAL(find(&vector, 42), -1);
}

void should_insert_an_element_in_the_middle() {
  struct vector vector = create_vector();

  push(&vector, 1);
  push(&vector, 2);
  push(&vector, 3);
  push(&vector, 4);

  insert(&vector, 2, 42);

  CU_ASSERT_EQUAL(get(&vector, 0), 1);
  CU_ASSERT_EQUAL(get(&vector, 1), 2);
  CU_ASSERT_EQUAL(get(&vector, 2), 42);
  CU_ASSERT_EQUAL(get(&vector, 3), 3);
  CU_ASSERT_EQUAL(get(&vector, 4), 4);
}

void should_prepend_an_element() {
  struct vector vector = create_vector();

  push(&vector, 1);
  push(&vector, 2);
  push(&vector, 3);
  push(&vector, 4);

  prepend(&vector, 42);

  CU_ASSERT_EQUAL(get(&vector, 0), 42);
  CU_ASSERT_EQUAL(get(&vector, 1), 1);
  CU_ASSERT_EQUAL(get(&vector, 2), 2);
  CU_ASSERT_EQUAL(get(&vector, 3), 3);
  CU_ASSERT_EQUAL(get(&vector, 4), 4);
}

void should_update_an_element() {
  struct vector vector = create_vector();

  push(&vector, 1);
  push(&vector, 2);
  push(&vector, 3);
  push(&vector, 4);

  update(&vector, 2, 42);

  CU_ASSERT_EQUAL(get(&vector, 0), 1);
  CU_ASSERT_EQUAL(get(&vector, 1), 2);
  CU_ASSERT_EQUAL(get(&vector, 2), 42);
  CU_ASSERT_EQUAL(get(&vector, 3), 4);
}

void should_delete_an_element_by_index() {
  struct vector vector = create_vector();

  push(&vector, 1);
  push(&vector, 2);
  push(&vector, 3);
  push(&vector, 4);

  delete_by_index(&vector, 2);

  CU_ASSERT_EQUAL(get(&vector, 0), 1);
  CU_ASSERT_EQUAL(get(&vector, 1), 2);
  CU_ASSERT_EQUAL(get(&vector, 2), 4);
}

void should_remove_an_element() {
  struct vector vector = create_vector();

  push(&vector, 2);
  push(&vector, 1);
  push(&vector, 2);
  push(&vector, 2);

  delete_by_value(&vector, 2);

  CU_ASSERT_EQUAL(get(&vector, 0), 1);
  CU_ASSERT_EQUAL(vector.size, 1);
}

int init_suite(void) {
  return 0;
}

int clean_suite(void) {
  return 0;
}

void add_test(CU_pSuite suite, const char* name, void (*test_func)(void)) {
  if (CU_add_test(suite, name, test_func) == NULL) {
    CU_cleanup_registry();
    exit(CU_get_error());
  }
}

int main() {
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  CU_pSuite suite = CU_add_suite("Tests suit", init_suite, clean_suite);

  if (NULL == suite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  add_test(suite, "Should create a vector", should_create_vector);
  add_test(suite, "Should initialize with 16 of capacity", should_create_vector);
  add_test(suite, "Should initialize empty", should_initialize_empty);
  add_test(suite, "Should push an element", should_push_element);
  add_test(suite, "Should increase capacity when needed", should_increase_capacity_when_needed);
  add_test(suite, "Should get element", should_get_element);
  add_test(suite, "Should remove last element e return it", should_pop_element);
  add_test(suite, "Should resize when pop and the new size is 1/4 of capacity", should_resize_when_pop_and_size_is_one_quarter_of_capacity);
  add_test(suite, "Should find an element", should_find_element);
  add_test(suite, "Should not find an element", should_not_find_element);
  add_test(suite, "Should insert an element in the middle", should_insert_an_element_in_the_middle);
  add_test(suite, "Should prepend an element", should_prepend_an_element);
  add_test(suite, "Should update an element", should_update_an_element);
  add_test(suite, "Should delete an element", should_delete_an_element_by_index);
  add_test(suite, "Should remove an element", should_remove_an_element);

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return CU_get_error();
}
