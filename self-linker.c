#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#define _GNU_SOURCE

int main(int argc, char * argv[])
{
  extern void *_GLOBAL_OFFSET_TABLE_;
  void *handle;
  void *putsFunctionPointer;

  handle = dlopen("libc.so.6", RTLD_LAZY);
  //creates a handler for libc

  //error handling for dlopen
  if (!handle){
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  putsFunctionPointer = dlsym(handle, "puts");
  //finds the function pointer from puts using the handler for libc

  //error handling for dlsym
  if (!putsFunctionPointer){
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  void **GOT_locations = &_GLOBAL_OFFSET_TABLE_;

  GOT_locations[3] = putsFunctionPointer;
  //locates where the entry for puts is in the GOT
  //places the function pointer for puts where it needs to be placed in the GOT

  int closeReturnValue = dlclose (handle);

  //error handling for dlclose
  if (closeReturnValue != 0){
    perror ("Error");
  }

  puts ("hello");
  puts ("world");
}
