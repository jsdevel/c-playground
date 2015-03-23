#include <stdio.h>
#include <stdlib.h>

typedef struct array_struct Array;
struct array_struct {
  int size;
  int used;
  void * elements;
  Array * (* push)();
  Array * (* forEach)();
};

Array * pushInt(Array * array, int item) {
  if (array->elements == NULL) {
    array->elements = malloc(sizeof(int) * 10);
  } else if (array->used + 1 > array->size) {
    array->elements = realloc(array->elements, sizeof(int) * array->size);
  }

  ((int*)array->elements)[array->used] = item;
  array->size = array->size + 10;
  array->used = array->used + 1;
  return array;
}

Array * pushString(Array * array, char * item) {
  if (array->elements == NULL) {
    array->elements = malloc(sizeof(char*) * 10);
  } else if (array->used + 1 > array->size) {
    array->elements = realloc(array->elements, sizeof(char*) * array->size);
  }

  ((char**)array->elements)[array->used] = item;
  array->size = array->size + 10;
  array->used = array->used + 1;
  return array;
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
  array.forEach = &forEach;
  return array;
}

Array newIntArray() {
  Array array = newArray();
  array.push = &pushInt;
  return array;
}

Array newStringArray() {
  Array array = newArray();
  array.push = &pushString;
  return array;
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

  ints.forEach(&ints, printIntElement);

  Array chars = newStringArray();
  chars.push(&chars, "asdf");
  chars.push(&chars, "fred");
  chars.forEach(&chars, printStringElement);
}
