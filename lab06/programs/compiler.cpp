// This program is a compiler that takes our pretend CPU's assembly
// instructions and turns them into our pretend binary format.

#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

void fix(string& line) {
  // remove whitespace, comments, replace ','s with ' 's, and
  // uppercase everything
  
  string fixed = "";

  // find starting index
  int i = 0;
  while (i < line.size() && isspace(line.at(i))) {
    i++;
  }

  // find ending index
  int j = line.size() - 1;
  while (j >= 0 && isspace(line.at(j))) {
    j--;
  }
  // end early if there are comments
  for (int k = i; k <= j; k++) {
    if (line.at(k) == '@') {
      j = k - 1;
      break;
    }
  }
  // there might be extra spaces before the comment
  while (j >= 0 && isspace(line.at(j))) {
    j--;
  }

  // replace ','s with ' 's for ease of stringstream-ing
  for (int k = i; k <= j; k++) {
    char c = toupper(line.at(k));
    if (c == ',') c = ' ';
    fixed += c;
  }

  line = fixed;
}

unsigned char randomByte() { return rand() % 256; }

unsigned char parseRegister(stringstream& ss) {
  string reg;
  ss >> reg;

  // code can be anything as long as the last two bits have the right
  // register code
  unsigned char code = (rand() % 256) & 0b11111100;

  if (reg == "R0")
    code |= 0b00;
  else if (reg == "R1")
    code |= 0b01;
  else if (reg == "R2")
    code |= 0b10;
  else if (reg == "R3")
    code |= 0b11;
  else
    throw runtime_error("Unknown register: " + reg);

  return code;
}

unsigned char parseImmediate(stringstream& ss) {
  int imm;
  ss >> imm;

  if (imm < 0 || imm > 255) {
    throw runtime_error("Immediate can only be between 0 and 255: " +
                        to_string(imm));
  }

  // code can be anything as long as the last two bits have the right
  // register code
  unsigned char immediate = static_cast<unsigned char>(imm);

  return immediate;
}

unsigned char operationToOpcode(const string& op) {
  // opcode can be anything as long as the last four bits have the
  // right value
  unsigned char code = (rand() % 256) & 0b11110000;

  if (op == "LOAD") {
    return code | 0;
  } else if (op == "STORE") {
    return code | 1;
  } else if (op == "MOVREG") {
    return code | 2;
  } else if (op == "MOVIMM") {
    return code | 3;
  } else if (op == "ADDREG") {
    return code | 4;
  } else if (op == "ADDREGIMM") {
    return code | 5;
  } else if (op == "SUBREG") {
    return code | 6;
  } else if (op == "SUBREGIMM") {
    return code | 7;
  } else if (op == "MULREG") {
    return code | 8;
  } else if (op == "MULREGIMM") {
    return code | 9;
  } else if (op == "CMP") {
    return code | 10;
  } else if (op == "BLE") {
    return code | 11;
  } else if (op == "BAL") {
    return code | 12;
  } else if (op == "PRINTINT") {
    return code | 13;
  } else if (op == "PRINTCHAR") {
    return code | 14;
  } else if (op == "HALT") {
    return code | 15;
  } else {
    throw runtime_error("Invalid operation: " + op);
  }
}

unsigned int makeInstruction(unsigned char opcode, unsigned char x,
                             unsigned char y, unsigned char z) {
  return (opcode << 24) | (x << 16) | (y << 8) | z;
}

unsigned int parse(const string& line) {
  stringstream ss(line);
  string op;
  ss >> op;

  unsigned char opcode = operationToOpcode(op);

  if (op == "LOAD" || op == "MOVIMM") {
    unsigned char destCode = parseRegister(ss);
    unsigned char immediate = parseImmediate(ss);

    // fill the rest with randomness
    unsigned char operand1Code = randomByte();

    // make instruction
    return makeInstruction(opcode, destCode, operand1Code, immediate);
  } else if (op == "STORE") {
    unsigned char operand1Code = parseRegister(ss);
    unsigned char immediate = parseImmediate(ss);
    unsigned char destCode = randomByte();
    return makeInstruction(opcode, destCode, operand1Code, immediate);
  } else if (op == "MOVREG") {
    unsigned char destCode = parseRegister(ss);
    unsigned char operand1Code = parseRegister(ss);
    unsigned char operand2Code = randomByte();
    return makeInstruction(opcode, destCode, operand1Code, operand2Code);
  } else if (op == "ADDREG" || op == "SUBREG" || op == "MULREG") {
    unsigned char destCode = parseRegister(ss);
    unsigned char operand1Code = parseRegister(ss);
    unsigned char operand2Code = parseRegister(ss);
    return makeInstruction(opcode, destCode, operand1Code, operand2Code);
  } else if (op == "ADDREGIMM" || op == "SUBREGIMM" || op == "MULREGIMM") {
    unsigned char destCode = parseRegister(ss);
    unsigned char operand1Code = parseRegister(ss);
    unsigned char immediate = parseImmediate(ss);
    return makeInstruction(opcode, destCode, operand1Code, immediate);
  } else if (op == "CMP") {
    unsigned char operand1Code = parseRegister(ss);
    unsigned char operand2Code = parseRegister(ss);
    unsigned char destCode = randomByte();
    return makeInstruction(opcode, destCode, operand1Code, operand2Code);
  } else if (op == "BAL" || op == "BLE") {
    unsigned char immediate = parseImmediate(ss);
    unsigned char destCode = randomByte();
    unsigned char operand1Code = randomByte();
    return makeInstruction(opcode, destCode, operand1Code, immediate);
  } else if (op == "PRINTINT" || op == "PRINTCHAR") {
    unsigned char operand1Code = parseRegister(ss);
    unsigned char destCode = randomByte();
    unsigned char operand2Code = randomByte();
    return makeInstruction(opcode, destCode, operand1Code, operand2Code);
  } else if (op == "HALT") {
    unsigned char destCode = randomByte();
    unsigned char operand1Code = randomByte();
    unsigned char operand2Code = randomByte();
    return makeInstruction(opcode, destCode, operand1Code, operand2Code);
  } else {
    throw runtime_error("Unknown operation: " + op);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Please supply a text file to compile (and redirect the output to "
            "a file).\n";
    cerr << "Example: " << argv[0] << " prog1.c45.s > prog1.c45\n";
    return 1;
  }

  srand(time(0));

  ifstream ifs(argv[1]);
  string line;

  while (getline(ifs, line)) {
    fix(line);
    if (line == "") continue;

    unsigned int instruction = parse(line);
    cout.write(reinterpret_cast<char*>(&instruction), 4);
  }

  return 0;
}
