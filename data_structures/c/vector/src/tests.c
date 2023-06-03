#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "vector.h"

void should_create_vector() {
  struct vector my_vector = create_vector();

  CU_ASSERT_EQUAL(my_vector.size, 0);
}

void should_create_vector_with_capacity_10() {
  struct vector my_vector = create_vector();

  CU_ASSERT_EQUAL(my_vector.capacity, 10);
}

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
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

  if (NULL == CU_add_test(suite, "Should create vector", should_create_vector)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (NULL == CU_add_test(suite, "Should create vector with 10 of capacity", should_create_vector)) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();

  return CU_get_error();
}
