#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "parser.h"
#include "executor.h"

int main(int argc, char *argv[]) {  

  scanner("Correct/test.code");
  executeTree();
  //printTree();

  return 0;
}