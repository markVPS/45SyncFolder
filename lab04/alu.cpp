#include "alu.h"

#include <algorithm>
#include <iostream>
using namespace std;

EightBitALU::EightBitALU() {
  // zero out operands
  for (int i = 0; i < 8; i++) {
    operand1[i] = operand2[i] = false;
  }

  // zero out flags too
  N = Z = C = V = false;
}

bool EightBitALU::getN() const { return N; }
bool EightBitALU::getZ() const { return Z; }
bool EightBitALU::getC() const { return C; }
bool EightBitALU::getV() const { return V; }

void EightBitALU::loadOperand1(const bool x[8]) {
  // Copy x into operand1
  for (int i = 0; i < 8; i++) {
    operand1[i] = x[i];
  }
}

void EightBitALU::loadOperand2(const bool y[8]) {
  // Copy y into operand2
  for (int i = 0; i < 8; i++) {
    operand2[i] = y[i];
  }
}

void EightBitALU::AND(bool res[8]) {
  // Perform AND on operand1 and operand2
  for (int i = 0; i < 8; i++) {
    res[i] = operand1[i] && operand2[i];
  }
  
  // Store the result into res
  // Set flags to their appropriate values
  N = res[7]; // Negative flag (MSB)
  
  // Zero flag - check if all bits are 0
  Z = true;
  for (int i = 0; i < 8; i++) {
    if (res[i]) {
      Z = false;
      break;
    }
  }
  
  C = false; // No carry for logical operations
  V = false; // No overflow for logical operations
}

void EightBitALU::OR(bool res[8]) {
  // Perform OR on operand1 and operand2
  for (int i = 0; i < 8; i++) {
    res[i] = operand1[i] || operand2[i];
  }
  
  // Store the result into res
  // Set flags to their appropriate values
  N = res[7]; // Negative flag (MSB)
  
  // Zero flag - check if all bits are 0
  Z = true;
  for (int i = 0; i < 8; i++) {
    if (res[i]) {
      Z = false;
      break;
    }
  }
  
  C = false; // No carry for logical operations
  V = false; // No overflow for logical operations
}

void EightBitALU::ADD(bool res[8]) {
  // Perform ADD on operand1 and operand2
  bool carry = false;
  bool carry_in_msb = false;
  bool carry_out_msb = false;
  
  for (int i = 0; i < 8; i++) {
    // Full adder logic: sum = a XOR b XOR carry
    bool sum = (operand1[i] != operand2[i]) != carry;
    
    // Full adder logic: carry = (a AND b) OR (carry AND (a XOR b))
    bool new_carry = (operand1[i] && operand2[i]) || (carry && (operand1[i] != operand2[i]));
    
    // Track carry for MSB (bit 7) for overflow calculation
    if (i == 6) { // This is the carry into bit 7 (MSB)
      carry_in_msb = new_carry;
    }
    
    carry = new_carry;
    res[i] = sum;
  }
  
  carry_out_msb = carry; // Final carry is carry out of MSB
  
  // Store the result into res
  // Set flags to their appropriate values
  N = res[7]; // Negative flag (MSB)
  
  // Zero flag - check if all bits are 0
  Z = true;
  for (int i = 0; i < 8; i++) {
    if (res[i]) {
      Z = false;
      break;
    }
  }
  
  C = carry_out_msb; // Carry flag is carry out of MSB
  
  // Overflow is when carry in != carry out at the MSB
  V = (carry_in_msb != carry_out_msb);
}

void EightBitALU::twosComplementOperand2() {
  // Overwrite operand2 with its two's complement (negate operand2 in place)
  
  // Step 1: Invert all bits (one's complement)
  for (int i = 0; i < 8; i++) {
    operand2[i] = !operand2[i];
  }
  
  // Step 2: Add 1 to get two's complement
  bool carry = true; // Start with carry=1 to add 1
  for (int i = 0; i < 8; i++) {
    bool sum = operand2[i] != false != carry; // operand2[i] XOR 0 XOR carry
    bool new_carry = operand2[i] && carry; // Since we're adding 0, only need to check these two
    operand2[i] = sum;
    carry = new_carry;
    
    if (!carry) break; // No more carry propagation needed
  }
}

void EightBitALU::compute(const bool selector[2], bool res[8]) {
  // Perform the appropriate operation on operand1 and operand2
  if (selector[0] == false && selector[1] == false) {
    // 00: operand1 AND operand2
    AND(res);
  } else if (selector[0] == true && selector[1] == false) {
    // 01: operand1 OR operand2
    OR(res);
  } else if (selector[0] == false && selector[1] == true) {
    // 10: operand1 ADD operand2
    ADD(res);
  } else if (selector[0] == true && selector[1] == true) {
    // 11: operand1 SUB operand2
    // Use twosComplementOperand2 and ADD to implement SUB
    
    // Save original operand2
    bool original_operand2[8];
    for (int i = 0; i < 8; i++) {
      original_operand2[i] = operand2[i];
    }
    
    // Negate operand2 using two's complement
    twosComplementOperand2();
    
    // Perform addition: operand1 + (-operand2)
    ADD(res);
    
    // Restore original operand2
    for (int i = 0; i < 8; i++) {
      operand2[i] = original_operand2[i];
    }
  }
}
