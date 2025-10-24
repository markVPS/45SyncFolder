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
  // FIΧМЕ: go into the instruction memory and fetch the binary form
  // of the instruction at the given address
}

Opcode CPU::decodeOpcode(unsigned char encoded_opcode) const {
  // FIΧМЕ: decode the binary opcode and return which Opcode it was:
  //    0 -> LOAD
  //    1 -> STORE
  //    2 -> MOVREG
  //    3 -> MOVIMM
  //    4 -> ADDREG
  //    5 -> ADDREGIMM
  //    6 -> SUBREG
  //    7 -> SUBREGIMM
  //    8 -> MULREG
  //    9 -> MULREGIMM
  //   10 -> CMP
  //   11 -> BLE
  //   12 -> BAL
  //   13 -> PRINTINT
  //   14 -> PRINTCHAR
  //   15 -> HALT
  // Only consider the number represented by the last four bits of the
  // encoding--the other bits don't matter.
}

Register CPU::decodeRegister(unsigned char encoded_register) const {
  // FIΧМЕ: decode the binary register and return which Register it was:
  //   0 -> Reg0
  //   1 -> Reg1
  //   2 -> Reg2
  //   3 -> Reg3
  // Only consider the number represented by the last two bits of the
  // encoding--the other bits don't matter
}

Instruction CPU::decode(unsigned int encoded_instruction) const {
  Instruction i;

  // FIΧМЕ: extract the opcode bits from encoded_instruction, decode
  // them, and put the Opcode in i

  // FIΧМЕ: extract the dest bits from encoded_instruction, decode
  // them, and put the Register in i

  // FIΧМЕ: extract the operand1 bits from encoded_instruction, decode
  // them, and put the Register in i

  // FIΧМЕ: extract the operand2 bits from encoded_instruction, decode
  // them, and put the Register in i

  // FIΧМЕ: extract the immediate bits from encoded_instruction, and
  // put the unsigned char in i

  // Remember that an instruction can't have both an operand2 and an
  // immediate, and that many instructions don't use all of the above
  // parts. That's not a problem--fill in every field here just in
  // case.

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
  // FIΧМЕ: set PC to 0--that's where the program starts

  // keep track of the number of cycles that it takes to run the
  // program--you can use this to help you debug
  unsigned long long cycles = 0;

  while (true) {
    // Step 1: Fetch
    // FIΧМЕ: Get the current encoded instruction out of PC

    // FIΧМЕ: Increment PC to point to the next instruction
    // (Remember our addresses are just indices, so +1 is all you need here)

    // increment cycles, since we're about to execute another instruction
    cycles += 1;

    // Step 2: Decode
    // FIΧМЕ: Figure out what kind of instruction it is
    Instruction instruction = ???;

    // Steps 3, 4, and 5: Execute, Memory, and Write Back
    // Based on the opcode, execute the instruction to completion.
    // If the instruction is HALT, stop the loop (thus ending the
    // program's execution).
    if (instruction.opcode == LOAD) {
      // FIΧМЕ: execute this instruction to completion
      // LOAD uses .dest and .immediate
      // .immediate is the data memory address to load the value from
      // .dest is the register to load the memory value into
    } else if (instruction.opcode == STORE) {
      // FIΧМЕ: execute this instruction to completion
      // STORE uses .operand1 and .immediate
      // .operand1 is the register holding the value to store
      // .immediate is the data memory address to store the value at
    } else if (instruction.opcode == MOVREG) {
      // FIΧМЕ: execute this instruction to completion
      // MOVREG uses .dest and .operand1
      // .operand1 is the register holding the value to store into the
      // .dest register
    } else if (instruction.opcode == MOVIMM) {
      // FIΧМЕ: execute this instruction to completion
      // MOVIMM uses .dest and .immediate
      // .immediate is the value to store into the .dest register
    } else if (instruction.opcode == ADDREG) {
      // ADDREG uses .dest, .operand1, and .operand2
      // .dest register = .operand1 register + .operand2 register
      int& dest = getRegister(instruction.dest);
      int op1 = getRegister(instruction.operand1);
      int op2 = getRegister(instruction.operand2);
      dest = op1 + op2;
    } else if (instruction.opcode == ADDREGIMM) {
      // FIΧМЕ: execute this instruction to completion
      // ADDREGIMM uses .dest, .operand1, and .immediate
      // .dest register = .operand1 register + .immediate
    } else if (instruction.opcode == SUBREG) {
      // FIΧМЕ: execute this instruction to completion
      // SUBREG uses .dest, .operand1, and .operand2
      // .dest register = .operand1 register - .operand2 register
    } else if (instruction.opcode == SUBREGIMM) {
      // FIΧМЕ: execute this instruction to completion
      // SUBREGIMM uses .dest, .operand1, and .immediate
      // .dest register = .operand1 register - .immediate
    } else if (instruction.opcode == MULREG) {
      // FIΧМЕ: execute this instruction to completion
      // MULREG uses .dest, .operand1, and .operand2
      // .dest register = .operand1 register * .operand2 register
    } else if (instruction.opcode == MULREGIMM) {
      // FIΧМЕ: execute this instruction to completion
      // MULREGIMM uses .dest, .operand1, and .immediate
      // .dest register = .operand1 register * .immediate
    } else if (instruction.opcode == CMP) {
      // FIΧМЕ: execute this instruction to completion
      // CMP uses .operand1 and .operand2
      // set the LE flag to true if the operand1 register is less then
      // or equal to the operand2 register, and false otherwise
    } else if (instruction.opcode == BLE) {
      // FIΧМЕ: execute this instruction to completion
      // BLE uses .immediate
      // If the LE flag is set, set PC to the instruction address
      // provided in .immediate. Otherwise do nothing (since we'll
      // automatically continue to the next instruction).
    } else if (instruction.opcode == BAL) {
      // FIΧМЕ: execute this instruction to completion
      // BAL uses .immediate
      // Set PC to the instruction address provided in .immediate.
    } else if (instruction.opcode == PRINTINT) {
      // PRINTINT uses .operand1
      // get the value out of the specified register and print it
      // (do not include a newline or anything extra)
      int val = getRegister(instruction.operand1);
      cout << val;
    } else if (instruction.opcode == PRINTCHAR) {
      // FIΧМЕ: execute this instruction to completion
      // PRINTCHAR uses .operand1
      // get the value out of the specified register, convert to a
      // char, and print it
      // (do not include a newline or anything extra)
    } else if (instruction.opcode == HALT) {
      // HALT uses no other fields
      // stop the program
      break;
    }
  }
}
