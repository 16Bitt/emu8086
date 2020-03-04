#include "emu8086.h"
#include "stdlib.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "string.h"
#include "errno.h"

// fileno isn't defined in 

uint8_t* load_binary(char *path) {
  FILE *f = fopen(path, "rb");
  if(f == NULL) {
    printf("failed to call fopen(): %s\n", strerror(errno));
    return NULL;
  }

  struct stat info;
  int err = fstat(fileno(f), &info);
  if(err != 0) {
    printf("failed to call fstat(): %s\n", strerror(errno));

    // TODO: handle errno
    fclose(f);
    return NULL;
  }
  
  uint8_t *buffer = (uint8_t *) malloc(info.st_size);
  fread(buffer, sizeof(uint8_t), info.st_size, f);

  return buffer;
}
