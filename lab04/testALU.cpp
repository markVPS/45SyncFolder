#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "alu.h"
using namespace std;

void assertTrue(bool b, string description) {
  if (b) {
    cout << "PASSED: " << description << endl;
  } else {
    cout << "FAILED: " << description << endl;
  }
}

void testAND(EightBitALU& alu);
void testOR(EightBitALU& alu);
void testADD(EightBitALU& alu);
void testSUB(EightBitALU& alu);

int main() {
  srand(time(0));

  EightBitALU alu;

  testAND(alu);
  testOR(alu);
  testADD(alu);
  testSUB(alu);

  return 0;
}

void binaryStringToBoolArray(string s, bool a[8]) {
  a[7] = s[0] == '1' ? 1 : 0;
  a[6] = s[1] == '1' ? 1 : 0;
  a[5] = s[2] == '1' ? 1 : 0;
  a[4] = s[3] == '1' ? 1 : 0;
  a[3] = s[4] == '1' ? 1 : 0;
  a[2] = s[5] == '1' ? 1 : 0;
  a[1] = s[6] == '1' ? 1 : 0;
  a[0] = s[7] == '1' ? 1 : 0;
}

string boolArrayToBinaryString(bool a[8]) {
  string res = "";

  for (int i = 7; i >= 0; i--)
    res.push_back(a[i] ? '1' : '0');

  return res;
}

void testAND(EightBitALU& alu) {
  bool operand1[8];
  bool operand2[8];
  bool res[8];
  bool selector[] = {0, 0};

  // 01001010 & 11100011 = 01000010
  // N Z C V: 0 0 0 0
  binaryStringToBoolArray("01001010", operand1);
  binaryStringToBoolArray("11100011", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "01000010" && alu.getN() == 0 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testAND 1");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 01010101 & 01000100 = 01000100
  // N Z C V: 0 0 0 0
  binaryStringToBoolArray("01010101", operand1);
  binaryStringToBoolArray("01000100", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "01000100" && alu.getN() == 0 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testAND 2");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 01000110 & 00111000 = 00000000
  // N Z C V: 0 1 0 0
  binaryStringToBoolArray("01000110", operand1);
  binaryStringToBoolArray("00111000", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "00000000" && alu.getN() == 0 && alu.getZ() == 1 && alu.getC() == 0 && alu.getV() == 0, "testAND 3");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 11101100 & 01101011 = 01101000
  // N Z C V: 0 0 0 0
  binaryStringToBoolArray("11101100", operand1);
  binaryStringToBoolArray("01101011", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "01101000" && alu.getN() == 0 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testAND 4");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 00011011 & 00000001 = 00000001
  // N Z C V: 0 0 0 0
  binaryStringToBoolArray("00011011", operand1);
  binaryStringToBoolArray("00000001", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "00000001" && alu.getN() == 0 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testAND 5");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;
}

void testOR(EightBitALU& alu) {
  bool operand1[8];
  bool operand2[8];
  bool res[8];
  bool selector[] = {1, 0};

  // 10000110 | 01011100 = 11011110
  // N Z C V: 1 0 0 0
  binaryStringToBoolArray("10000110", operand1);
  binaryStringToBoolArray("01011100", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "11011110" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testOR 1");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 11001101 | 10110010 = 11111111
  // N Z C V: 1 0 0 0
  binaryStringToBoolArray("11001101", operand1);
  binaryStringToBoolArray("10110010", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "11111111" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testOR 2");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 11101110 | 01011110 = 11111110
  // N Z C V: 1 0 0 0
  binaryStringToBoolArray("11101110", operand1);
  binaryStringToBoolArray("01011110", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "11111110" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testOR 3");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 00101011 | 00001111 = 00101111
  // N Z C V: 0 0 0 0
  binaryStringToBoolArray("00101011", operand1);
  binaryStringToBoolArray("00001111", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "00101111" && alu.getN() == 0 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testOR 4");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 11001000 | 11011000 = 11011000
  // N Z C V: 1 0 0 0
  binaryStringToBoolArray("11001000", operand1);
  binaryStringToBoolArray("11011000", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "11011000" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testOR 5");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 00000000 | 00000000 = 00000000
  // N Z C V: 0 1 0 0
  binaryStringToBoolArray("00000000", operand1);
  binaryStringToBoolArray("00000000", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "00000000" && alu.getN() == 0 && alu.getZ() == 1 && alu.getC() == 0 && alu.getV() == 0, "testOR 6");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

}

void testADD(EightBitALU& alu) {
  bool operand1[8];
  bool operand2[8];
  bool res[8];
  bool selector[] = {0, 1};

  // 01001011 + 01001110 = 10011001
  // N Z C V: 1 0 0 1
  binaryStringToBoolArray("01001011", operand1);
  binaryStringToBoolArray("01001110", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "10011001" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 1, "testADD 1");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 00110000 + 10000000 = 10110000
  // N Z C V: 1 0 0 0
  binaryStringToBoolArray("00110000", operand1);
  binaryStringToBoolArray("10000000", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "10110000" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testADD 2");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 00010101 + 10100011 = 10111000
  // N Z C V: 1 0 0 0
  binaryStringToBoolArray("00010101", operand1);
  binaryStringToBoolArray("10100011", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "10111000" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testADD 3");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 11100000 + 10111010 = 10011010
  // N Z C V: 1 0 1 0
  binaryStringToBoolArray("11100000", operand1);
  binaryStringToBoolArray("10111010", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "10011010" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 1 && alu.getV() == 0, "testADD 4");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // N Z C V: 1 0 0 1
  binaryStringToBoolArray("01100101", operand1);
  binaryStringToBoolArray("00101110", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "10010011" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 1, "testADD 5");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 10000000 + 10000000 = 00000000
  // N Z C V: 0 1 1 1
  binaryStringToBoolArray("10000000", operand1);
  binaryStringToBoolArray("10000000", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "00000000" && alu.getN() == 0 && alu.getZ() == 1 && alu.getC() == 1 && alu.getV() == 1, "testADD 6");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;
}

void testSUB(EightBitALU& alu) {
  bool operand1[8];
  bool operand2[8];
  bool res[8];
  bool selector[] = {1, 1};

  // 10100001 - 10101111 = 11110010
  // N Z C V: 1 0 0 0
  binaryStringToBoolArray("10100001", operand1);
  binaryStringToBoolArray("10101111", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "11110010" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testSUB 1");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 00010001 - 11110110 = 00011011
  // N Z C V: 0 0 0 0
  binaryStringToBoolArray("00010001", operand1);
  binaryStringToBoolArray("11110110", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "00011011" && alu.getN() == 0 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 0, "testSUB 2");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 11110011 - 01010111 = 10011100
  // N Z C V: 1 0 1 0
  binaryStringToBoolArray("11110011", operand1);
  binaryStringToBoolArray("01010111", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "10011100" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 1 && alu.getV() == 0, "testSUB 3");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 01101110 - 11100000 = 10001110
  // N Z C V: 1 0 0 1
  binaryStringToBoolArray("01101110", operand1);
  binaryStringToBoolArray("11100000", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "10001110" && alu.getN() == 1 && alu.getZ() == 0 && alu.getC() == 0 && alu.getV() == 1, "testSUB 4");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 11000010 - 10001001 = 00111001
  // N Z C V: 0 0 1 0
  binaryStringToBoolArray("11000010", operand1);
  binaryStringToBoolArray("10001001", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "00111001" && alu.getN() == 0 && alu.getZ() == 0 && alu.getC() == 1 && alu.getV() == 0, "testSUB 5");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;

  // 11000010 - 11000010 = 00000000
  // N Z C V: 0 1 1 0
  binaryStringToBoolArray("11000010", operand1);
  binaryStringToBoolArray("11000010", operand2);
  alu.loadOperand1(operand1);
  alu.loadOperand2(operand2);
  alu.compute(selector, res);
  assertTrue(boolArrayToBinaryString(res) == "00000000" && alu.getN() == 0 && alu.getZ() == 1 && alu.getC() == 1 && alu.getV() == 0, "testSUB 6");
  cout << " (Your answer, N, Z, C, V): " << boolArrayToBinaryString(res) << ", " << alu.getN() << ", " << alu.getZ() << ", " << alu.getC() << ", " << alu.getV() << endl;
}