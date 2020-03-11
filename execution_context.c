#include "emu8086.h"

struct ExecutionContext * mk_context() {
  struct ExecutionContext *ec = (struct ExecutionContext *) malloc(sizeof(struct ExecutionContext));
  ec->fetch_addr = 0;

  return ec;
}

void execute_step(struct ExecutionContext *ec) {

}
