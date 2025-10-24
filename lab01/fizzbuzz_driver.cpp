#include <iostream>
using namespace std;

extern "C" void fizzbuzz(int);

int main() {
  while (true) {
    cout << "Enter a number (-1 to quit):\n";
    int i;
    cin >> i;
    if (i == -1) break;
    fizzbuzz(i);
  }

  return 0;
}
