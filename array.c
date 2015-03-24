#include <stdio.h>
#include <stdlib.h>

typedef struct array_struct Array;
struct array_struct {
  int size;
  int used;
  void * elements;
  Array * (* forEach)();
  Array * (* push)();
  Array * (* unshift)();
};

#define __array_handle_size(type) \
  if (array->elements == NULL) { \
    array->elements = malloc(sizeof(type) * 10); \
  } else if (array->used + 1 > array->size) { \
    array->elements = realloc(array->elements, sizeof(type) * array->size); \
  } \
  array->size = array->size + 10

#define __array_push_fn(type) \
  __array_handle_size(type); \
  ((type*)array->elements)[array->used] = item; \
  array->used = array->used + 1; \
  return array


Array * pushInt(Array * array, int item) {
  __array_push_fn(int);
}

Array * pushString(Array * array, char * item) {
  __array_push_fn(char*);
}

#define __array_unshift_fn(type) \
  __array_handle_size(type); \
  int i; \
  if (array->used > 0) { \
    for (i = 0; i <= array->used; i++) { \
      ((type*)array->elements)[array->used - i] = ((type*)array->elements)[array->used - i - 1]; \
    } \
  } \
  ((type*)array->elements)[0] = item; \
  array->size = array->size + 10; \
  array->used = array->used + 1; \
  return array

Array * unshiftInt(Array * array, int item) {
  __array_unshift_fn(int);
}

Array * unshiftString(Array * array, char * item) {
  __array_unshift_fn(char*);
}

Array * forEach(Array * array, void (*fn)()) {
  int i;
  for (i = 0;i < array->used;i++) {
    fn(array, i);
  }
  return array;
}

Array newArray() {
  Array array;
  array.size = 0;
  array.used = 0;
  array.elements = NULL;
  array.forEach = &forEach;
  return array;
}

#define __array_constructor(name) \
  Array array = newArray(); \
  array.push = &push##name; \
  array.unshift = &unshift##name; \
  return array

Array newIntArray() {
  __array_constructor(Int);
}

Array newStringArray() {
  __array_constructor(String);
}

void printIntElement(Array * array, int index) {
  printf("Index: %i, Element: %i\n", index, ((int*)array->elements)[index]);
}

void printStringElement(Array * array, int index) {
  printf("Index: %i, Element: %s\n", index, ((char**)array->elements)[index]);
}

int main() {
  int i;
  Array ints = newIntArray();

  for (i = 0; i < 1000; i++) {
    ints.push(&ints, i);
  }

  //ints.forEach(&ints, printIntElement);

  Array chars = newStringArray();
  chars.push(&chars, "asdf");
  chars.push(&chars, "fred");
  chars.unshift(&chars, "boo!");
  chars.push(&chars, "dred");
  chars.unshift(&chars, "zoo!");
  chars.forEach(&chars, printStringElement);
}

#undef __array_constructor
#undef __array_handle_size
#undef __array_push_fn
#undef __array_unshift_fn
