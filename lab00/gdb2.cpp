#include <iostream>
using namespace std;

int main() {
  int x = 42;
  int* p = &x;

  p = (int*)((long long)p ^ (long long)p);
  cout << *p << endl;

  // TODO: what did the weird line above do to p? What is p's value
  // now? Why did the program crash?

  return 0;
}
