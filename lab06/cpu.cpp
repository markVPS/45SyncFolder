#include "cpu.h"

#include <algorithm>
#include <iostream>
using namespace std;

CPU::CPU() {
  // set all the registers to 0
  R0 = R1 = R2 = R3 = 0;
  // set the data_memory to all 0s
  std::fill(data_memory, data_memory + 256, 0);
  // set the instruction_memory to all HALTs
  std::fill(instruction_memory, instruction_memory + 256, 0x0F000000);
}

void CPU::loadProgram(std::vector<unsigned int> instructions) {
  // copy the instructions into instruction_memory, starting at
  // address 0
  std::copy(instructions.begin(), instructions.end(), instruction_memory);
}

unsigned int CPU::fetch(unsigned char address) const {
  return instruction_memory[address];
}

Opcode CPU::decodeOpcode(unsigned char encoded_opcode) const {
  unsigned char code = encoded_opcode & 0x0F;
  return static_cast<Opcode>(code);
}

Register CPU::decodeRegister(unsigned char encoded_register) const {
  unsigned char r = encoded_register & 0x03;
  return static_cast<Register>(r);
}

Instruction CPU::decode(unsigned int encoded_instruction) const {
  Instruction i;
  unsigned char encoded_opcode = (encoded_instruction >> 24) & 0xFF;
  unsigned char encoded_dest   = (encoded_instruction >> 16) & 0xFF;
  unsigned char encoded_op1    = (encoded_instruction >> 8) & 0xFF;
  unsigned char encoded_low    = (encoded_instruction) & 0xFF;

  i.opcode   = decodeOpcode(encoded_opcode);
  i.dest     = decodeRegister(encoded_dest);
  i.operand1 = decodeRegister(encoded_op1);
  i.operand2 = decodeRegister(encoded_low);
  i.immediate = static_cast<unsigned char>(encoded_low);
  return i;
}

int& CPU::getRegister(Register whichRegister) {
  // return the requested register value stored in the CPU
  switch (whichRegister) {
    case Reg0:
      return R0;
    case Reg1:
      return R1;
    case Reg2:
      return R2;
    case Reg3:
      return R3;
  }

  // the compiler isn't smart enough to know that the switch statement
  // covers all the possibilities, so this line is to appease it:
  return R0; // we'll never get here
}

void CPU::runProgram() {
  PC = 0;
  // FIΧМЕ: set PC to 0--that's where the program starts

  // keep track of the number of cycles that it takes to run the
  // program--you can use this to help you debug
  unsigned long long cycles = 0;

  while (true) {
    // Step 1: Fetch
        unsigned int encoded = fetch(PC);

        PC = static_cast<unsigned char>(PC + 1);

    // (Remember our addresses are just indices, so +1 is all you need here)

    // increment cycles, since we're about to execute another instruction
    cycles += 1;

    // Step 2: Decode
    // FIΧМЕ: Figure out what kind of instruction it is
    Instruction instruction = decode(encoded);

    // Steps 3, 4, and 5: Execute, Memory, and Write Back
    // Based on the opcode, execute the instruction to completion.
    // If the instruction is HALT, stop the loop (thus ending the
    // program's execution).
    if (instruction.opcode == LOAD) {
      int& dest = getRegister(instruction.dest);
      dest = data_memory[instruction.immediate];
    } else if (instruction.opcode == STORE) {
      int val = getRegister(instruction.operand1);
      data_memory[instruction.immediate] = val;
    } else if (instruction.opcode == MOVREG) {
      int val = getRegister(instruction.operand1);
      int& dest = getRegister(instruction.dest);
      dest = val;
    } else if (instruction.opcode == MOVIMM) {
      int& dest = getRegister(instruction.dest);
      dest = instruction.immediate;
    } else if (instruction.opcode == ADDREG) {
      // ADDREG uses .dest, .operand1, and .operand2
      // .dest register = .operand1 register + .operand2 register
      int& dest = getRegister(instruction.dest);
      int op1 = getRegister(instruction.operand1);
      int op2 = getRegister(instruction.operand2);
      dest = op1 + op2;
    } else if (instruction.opcode == ADDREGIMM) {
      int& dest = getRegister(instruction.dest);
      int op1 = getRegister(instruction.operand1);
      dest = op1 + instruction.immediate;
    } else if (instruction.opcode == SUBREG) {
      int& dest = getRegister(instruction.dest);
      int op1 = getRegister(instruction.operand1);
      int op2 = getRegister(instruction.operand2);
      dest = op1 - op2;
    } else if (instruction.opcode == SUBREGIMM) {
      int& dest = getRegister(instruction.dest);
      int op1 = getRegister(instruction.operand1);
      dest = op1 - instruction.immediate;
    } else if (instruction.opcode == MULREG) {
      int& dest = getRegister(instruction.dest);
      int op1 = getRegister(instruction.operand1);
      int op2 = getRegister(instruction.operand2);
      dest = op1 * op2;
    } else if (instruction.opcode == MULREGIMM) {
      int& dest = getRegister(instruction.dest);
      int op1 = getRegister(instruction.operand1);
      dest = op1 * instruction.immediate;
    } else if (instruction.opcode == CMP) {
      int op1 = getRegister(instruction.operand1);
      int op2 = getRegister(instruction.operand2);
      LE = (op1 <= op2);
    } else if (instruction.opcode == BLE) {
      if (LE) {
        PC = instruction.immediate;
      }
    } else if (instruction.opcode == BAL) {
      PC = instruction.immediate;
    } else if (instruction.opcode == PRINTINT) {
      // PRINTINT uses .operand1
      // get the value out of the specified register and print it
      // (do not include a newline or anything extra)
      int val = getRegister(instruction.operand1);
      cout << val;
    } else if (instruction.opcode == PRINTCHAR) {
      int val = getRegister(instruction.operand1);
      cout << static_cast<char>(val);
    } else if (instruction.opcode == HALT) {
      // HALT uses no other fields
      // stop the program
      break;
    }
  }
}

