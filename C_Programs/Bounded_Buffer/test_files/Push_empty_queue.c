#include "queue.h"
#include<stdbool.h> 
#include <unistd.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  // push a 1
  bool x =queue_push(NULL, (void *)1);
  if (x != false) {
    // if not, then we failed
    return 1;
  } 
  return 0;
}
