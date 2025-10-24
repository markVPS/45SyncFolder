#ifndef CPU_H
#define CPU_H

#include <vector>

enum Opcode {
  LOAD,
  STORE,
  MOVREG,
  MOVIMM,
  ADDREG,
  ADDREGIMM,
  SUBREG,
  SUBREGIMM,
  MULREG,
  MULREGIMM,
  CMP,
  BLE,
  BAL,
  PRINTINT,
  PRINTCHAR,
  HALT
};

enum Register {
  Reg0,
  Reg1,
  Reg2,
  Reg3
};

struct Instruction {
  // All Instructions must have an opcode
  Opcode opcode;

  // The rest of the fields always get set, but they can't all be
  // used. It depends on the instruction. For example, the PRINTINT
  // instruction only uses operand1, so the CPU shouldn't touch any
  // of the other fields while it executing PRINTINT.
  Register dest;
  Register operand1;
  Register operand2;
  unsigned char immediate;
};

class CPU {
 public:
  CPU();
  void loadProgram(std::vector<unsigned int> instructions);
  void runProgram();

 private:
  unsigned int fetch(unsigned char address) const;
  Instruction decode(unsigned int encoded_instruction) const;
  Opcode decodeOpcode(unsigned char encoded_opcode) const;
  Register decodeRegister(unsigned char encoded_register) const;
  int& getRegister(Register whichRegister);

  // registers & flags
  unsigned char PC;
  int R0;
  int R1;
  int R2;
  int R3;
  bool LE;

  // memory
  int data_memory[256];
  unsigned int instruction_memory[256];
};

#endif /* end of include guard: CPU_H */
