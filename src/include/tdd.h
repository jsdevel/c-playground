#include <colors.h>

#ifndef TDD_HEADER_FILE
#define TDD_HEADER_FILE

#define TEST(name) \
  if (name() != 0) { \
    printf("%sX%s %s\n", CRED, CRESET, TDD_SUITE_NAME#name); \
  } else { \
    printf("%s%s%s %s\n", CGRN, "\xE2\x9C\x93", CRESET, TDD_SUITE_NAME#name); \
  } \
  \

#define ASSERT(expr) \
  if (!(expr)) { \
    printf("'%s' failed!\n", #expr); \
    return 1; \
  } \
  \

#endif
