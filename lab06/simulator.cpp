#include <iostream>
#include <fstream>
using namespace std;

#include "cpu.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Please supply a program file to run.\n";
    cerr << "Example: " << argv[0] << " prog1\n";
    return 1;
  }

  vector<unsigned int> instructions;

  // Open the file in argv[1] in binary mode, and read an unsigned int
  // at a time. Copy every unsigned int we read into the instructions
  // vector.
  ifstream ifs(argv[1], ios::binary);
  unsigned int nextInstruction;

  while (ifs.read(reinterpret_cast<char*>(&nextInstruction), 4)) {
    instructions.push_back(nextInstruction);
  }

  CPU cpu;
  cpu.loadProgram(instructions);
  cpu.runProgram();

  return 0;
}
