#include <iostream>
using namespace std;

int main() {
  int x = 42;
  int y = 43;
  
  int a[] = {4, 5, 6};

  // TODO: set a breakpoint on the next non-comment line
  
  // TODO: look at the register values. What do you see?

  // TODO: Follow any of the registers that look like address values
  // (i.e., they hold huge (positive or negative) numbers). Go to
  // those addresses and inspect the first 10 integer values in memory
  // there. Do you find anything interesting?

  cout << "This should print once you continue the program.\n";

  for (int i = 1; i <= 10; i++) {
    // TODO: set a breakpoint on the next line
    cout << i << endl;
    // TODO: use `step` to go through each line one at a time until
    // the loop is over. Then you can use `continue` to finish off the
    // program.
  }

  return 0;
}
