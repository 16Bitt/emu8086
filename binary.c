#include "emu8086.h"
#include "stdio.h"

void binary_print(uint8_t byte) {
  int mask = 0x80;
  for(int i = 0; i < 8; i++) {
    int bit = byte & (mask >> i);
    if(bit) {
      printf("1");
    } else {
      printf("0");
    }
  }
}
