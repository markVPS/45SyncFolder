#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

extern "C" int string_to_integer(const char* s);

int main() {
  srand(time(0));

  // make a random string of digits
  string s = "";
  for (int i = 0; i < 4 + rand() % 6; i++) {
    s.push_back('0' + rand() % 10);
  }

  int i = string_to_integer(s.c_str());
  int answer = stoi(s);

  cout << s << endl;
  cout << i << " " << answer << endl;
  cout << endl;

  if (i == answer) {
    cout << "PASSED: string_to_integer" << endl;
  } else {
    cout << "FAILED: string_to_integer" << endl;
  }

  return 0;
}
