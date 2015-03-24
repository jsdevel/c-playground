#include <array.h>
#include <tdd.h>

int printInt(Array * array, int element) {
}

int push_should_increase_elements_size_accordingly() {
  int i;
  Array ints = newIntArray();

  for (i = 0; i < 1000; i++) {
    ints.push(&ints, i);
  }

  ASSERT(ints.used == 1000);
  ASSERT(ints.size == 10000);

  return 0;
}

int elements_should_be_NULL_by_default() {
  ASSERT(newIntArray().elements == NULL);
  ASSERT(newStringArray().elements == NULL);
  return 0;
}

int forEach_should_iterate_over_the_items() {
  int count;
  Array ints = newIntArray();
  ints.push(&ints, 5);
  ints.forEach(&ints, printInt);

  return 0;
}

int creating_an_string_array_should_be_possible() {
  Array chars = newStringArray();
  chars.push(&chars, "asdf");
  chars.push(&chars, "fred");
  chars.unshift(&chars, "boo!");
  chars.push(&chars, "dred");
  chars.unshift(&chars, "zoo!");

  return 0;
}

int reset_should_free_elements_and_reassign_it_a_value_of_NULL() {
  Array ints = newIntArray();
  ASSERT(ints.push(&ints, 5)->reset(&ints)->elements == NULL);
  return 0;
}

#define TDD_SUITE_NAME "Array_"
int main(void) {
  TEST(push_should_increase_elements_size_accordingly);
  TEST(elements_should_be_NULL_by_default);
  TEST(forEach_should_iterate_over_the_items);
  //TEST(reset_should_free_elements_and_reassign_it_a_value_of_NULL);
  TEST(creating_an_string_array_should_be_possible);
}
