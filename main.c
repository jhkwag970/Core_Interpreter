#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "parser.h"
#include "executor.h"

int main(int argc, char *argv[]) {  

  scanner(argv[1]);
  executeTree(argv[2]);
  //printTree();

  return 0;
}