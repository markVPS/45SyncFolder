#include <iostream>
using namespace std;

int main() {
  // TODO: set a breakpoint at the start of the main function
  // TODO: use the `disassemble` command to show the assembly code
  // TODO: use stepi and keep printing out the registers. Can you see
  // how x, y, and z are getting set/changed/used?

  int x = 42;
  // TODO: what is the assembly for the following line? What is the
  // hex value of the instruction?
  x++; 
  int y = x + 7;

  int z = 4 * 2;
  x--;

  return 0;
}
