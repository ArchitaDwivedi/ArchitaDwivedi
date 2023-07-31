#include "queue.h"
#include<stdbool.h> 
#include <unistd.h>

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;

  void* q2;
  q2 = NULL;

  // push a 1
  bool x = queue_pop(NULL, &q2);
  if (x != false) {
    // if not, then we failed
    return 1;
  } 
  return 0;
}
 
