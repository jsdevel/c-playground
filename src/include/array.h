#include <stdio.h>
#include <stdlib.h>

#ifndef ARRAY_HEADER_FILE
#define ARRAY_HEADER_FILE
typedef struct array_struct Array;
struct array_struct {
  int size;
  int used;
  void * elements;
  Array * (* forEach)();
  Array * (* push)();
  Array * (* reset)();
  Array * (* unshift)();
};

#define __array_handle_size_increase(type) \
  if (array->elements == NULL) { \
    array->elements = malloc((array->size + 10) * sizeof(type)); \
  } else if (array->used + 1 > array->size) { \
    array->elements = realloc(array->elements, (array->size + 10) * sizeof(type)); \
  } \
  array->size = array->size + 10

#define __array_push_fn(type) \
  __array_handle_size_increase(type); \
  ((type*)array->elements)[array->used] = item; \
  array->used = array->used + 1; \
  return array

#define __array_unshift_fn(type) \
  __array_handle_size_increase(type); \
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

static Array * forEach(Array * array, void (*fn)()) {
  int i;
  for (i = 0;i < array->used;i++) {
    fn(array, i);
  }
  return array;
}

static Array * reset(Array * array) {
  if (array->elements != NULL) {
    free(array->elements);
  }
  return array;
}

static Array * pushInt(Array * array, int item) {
  __array_push_fn(int);
}

static Array * pushString(Array * array, char * item) {
  __array_push_fn(char*);
}

static Array * unshiftInt(Array * array, int item) {
  __array_unshift_fn(int);
}

static Array * unshiftString(Array * array, char * item) {
  __array_unshift_fn(char*);
}

#define __array_constructor(name) \
  Array array = newArray(); \
  array.push = &push##name; \
  array.unshift = &unshift##name; \
  return array

Array newArray() {
  Array array;
  array.size = 0;
  array.used = 0;
  array.elements = NULL;
  array.forEach = &forEach;
  array.reset = &reset;
  return array;
}

Array newIntArray() {
  __array_constructor(Int);
}

Array newStringArray() {
  __array_constructor(String);
}

#undef __array_constructor
#undef __array_handle_size_increase
#undef __array_push_fn
#undef __array_unshift_fn
#endif
