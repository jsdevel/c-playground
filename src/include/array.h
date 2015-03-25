#include <stdio.h>
#include <stdlib.h>

#ifndef ARRAY_HEADER_FILE
#define ARRAY_HEADER_FILE
#define ARRAY_PADDING 10
typedef struct array_struct Array;
struct array_struct {
  int size;
  int used;
  void  * elements;
  Array * (* forEach)();
  Array * (* push)();
  Array * (* reset)();
  Array * (* unshift)();
};

static int handleSizeIncrease(Array * array, size_t bytes) {
  if (array->elements == NULL) {
    array->elements = malloc(ARRAY_PADDING * bytes);
    if (array->elements != NULL) {
      array->size += ARRAY_PADDING;
    }
  } else if ((array->used + 1) > array->size) {
    void *tmp = realloc(array->elements, (array->size + ARRAY_PADDING) * bytes);
    if (tmp == NULL) {
      return 1;
    } else {
      array->size += ARRAY_PADDING;
    }
  }

  if (array->elements == NULL) {
    array->size = 0;
    array->used = 0;
    return 1;
  }
  return 0;
}

#define __array_foreach_fn(type) \
  int i; \
  for (i = 0;i < array->used;i++) { \
    fn(&((type*)array->elements)[i], i, array); \
  } \
  return array \

#define __array_push_fn(type) \
  if (handleSizeIncrease(array, sizeof(type)) == 0) { \
    ((type*)array->elements)[array->used] = item; \
    array->used += 1; \
  } \
  return array

#define __array_unshift_fn(type) \
  if (handleSizeIncrease(array, sizeof(type)) == 0) { \
    int i; \
    if (array->used > 0) { \
      for (i = 0; i <= array->used; i++) { \
        ((type*)array->elements)[array->used - i] = ((type*)array->elements)[array->used - i - 1]; \
      } \
    } \
    ((type*)array->elements)[0] = item; \
    array->used += 1; \
  } \
  return array


static Array * reset(Array * array) {
  if (array->elements != NULL) {
    free(array->elements);
  }
  array->size = 0;
  array->used = 0;
  array->elements = NULL;
  return array;
}

static Array * forEachInt(Array * array, void (*fn)()) {
  __array_foreach_fn(int);
}

static Array * forEachString(Array * array, void (*fn)()) {
  __array_foreach_fn(char*);
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
  array.forEach = &forEach##name; \
  array.push = &push##name; \
  array.unshift = &unshift##name; \
  return array

Array newArray() {
  Array array;
  array.size = 0;
  array.used = 0;
  array.elements = NULL;
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
#undef __array_foreach_fn
#undef __array_push_fn
#undef __array_unshift_fn
#endif
