#include "tensorflow/lite/micro/ia8201/new_override.h"

#include <cstdlib>
#include <new>

void *kn_malloc(size_t size) {
  // printf("kn_allocate: %d bytes\n",size);
  return (void *)0;  // nullptr;
}

#if 1
void *operator new(size_t size, std::nothrow_t) noexcept {
  return operator new(size);  // Same as regular new
}
#endif
void operator delete(void *p, std::nothrow_t) noexcept {
  operator delete(p);  // Same as regular delete
}

void *operator new[](size_t size, std::nothrow_t) noexcept {
  return operator new(size);  // Same as regular new
}

void operator delete[](void *p, std::nothrow_t) noexcept {
  operator delete(p);  // Same as regular delete
}

void *operator new(size_t size) noexcept { return kn_malloc(size); }

void operator delete(void *p) noexcept {
  // free(p);
}

void *operator new[](size_t size) noexcept {
  return operator new(size);  // Same as regular new
}

void operator delete[](void *p) noexcept {
  operator delete(p);  // Same as regular delete
}
