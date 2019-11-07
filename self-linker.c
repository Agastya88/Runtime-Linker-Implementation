#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE

int main(int argc, char * argv[])
{
  extern void *_GLOBAL_OFFSET_TABLE_;
  printf("The first entry of the global offset table is %p\n", _GLOBAL_OFFSET_TABLE_);
  printf("The GOT starts at address %p\n", (void *) &_GLOBAL_OFFSET_TABLE_);

  void *handle;
  void *putsFunctionPointer;

  handle = dlopen("libc.so.6", RTLD_LAZY);

  if (!handle)
  {
      fprintf(stderr, "%s\n", dlerror());
      exit(EXIT_FAILURE);
  }

  putsFunctionPointer = dlsym(handle, "puts");

  printf("The entry with the addition of the offset is: %p\n",
  (void*) (&_GLOBAL_OFFSET_TABLE_ + 0x18));

  void **a = (void*)(&_GLOBAL_OFFSET_TABLE_ + 0x18);

  *a = putsFunctionPointer;

  printf ("Function pointer for puts: %p\n", putsFunctionPointer);

  int closeReturnValue = dlclose (handle);
  if (closeReturnValue != 0)
  {
    perror ("Error");
  }

}
