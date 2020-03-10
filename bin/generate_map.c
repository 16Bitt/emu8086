#define _GNU_SOURCE

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

// Helper functions
bool is_grp(char *str);
void handle_line(int args_read, char* arg0, char* arg1, char* arg2, char *arg3);

int main(int argc, char **argv) {
  char *line = NULL;
  size_t len;
  int bytes_read;
  char targets[4][16];
  
  puts("#include \"emu8086.h\"\n");
  puts("void handle_decode(uint8_t op) {");
  puts("  switch(op) {");

  while((bytes_read = getline(&line, &len, stdin)) != -1) {
    int args_read = sscanf(line, "%s\t%s\t%s\t%s", targets[0], targets[1], targets[2], targets[3]);
    handle_line(args_read, targets[0], targets[1], targets[2], targets[3]);
    free(line);
    line = NULL;
  }
  
  puts("  default:");
  puts("  }");
  puts("}");

  return 0;
}

bool is_grp(char *op) {
  return strstr(op, "GRP") != NULL;
}

void handle_line(int args_read, char* arg0, char* arg1, char* arg2, char *arg3) {
  switch(args_read) {
    case 2:
      if(strstr(arg1, "--") != NULL || strstr(arg1, ":") != NULL) {
        printf("/* Unknown opcode %s */\n", arg0);
        break;
      }
      if(is_grp(arg0)) {
        printf("/* Ignore GRP */\n");
        break;
      }

      printf("  case 0x%s:\n", arg0);
      printf("    op_%s();\n", arg1);
      printf("    break;\n");
      
      break;
    case 4:
      if(is_grp(arg0)) {
        printf("/* Ignore GRP */\n");
        break;
      }
      printf("  case 0x%s:\n", arg0);
      printf("    op_%s(args_%s_%s);\n", arg1, arg2, arg3);
      printf("    break;\n");
      break;
    case 0:
    case 1:
    default:
      break;
  }
}

