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
  //creates a handler for libc

  if (!handle)
  {
      fprintf(stderr, "%s\n", dlerror());
      exit(EXIT_FAILURE);
  }

  putsFunctionPointer = dlsym(handle, "puts");
  //finds the function pointer from puts using the handler for libc

  void **putsGOT_location = (void*)(&_GLOBAL_OFFSET_TABLE_ + 0x18);
  //locates where the entry for puts is in the GOT
  //I found this by running GDB on the program hello-world

  *putsGOT_location = putsFunctionPointer;
  //places the function pointer for puts where it needs to be placed in the GOT

  puts ("hello");
  puts ("world");

  int closeReturnValue = dlclose (handle);
  if (closeReturnValue != 0)
  {
    perror ("Error");
  }
}
