#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "parser.h"
#include "printer.h"

int main(int argc, char *argv[]) {  

  scanner(argv[1]);
  //printTree();

  return 0;
}