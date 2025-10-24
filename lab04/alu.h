#ifndef ALU_H
#define ALU_H

class EightBitALU {
 public:
  EightBitALU();
  void loadOperand1(const bool x[8]);
  void loadOperand2(const bool y[8]);
  void compute(const bool selector[2], bool res[8]);

  bool getN() const;
  bool getZ() const;
  bool getC() const;
  bool getV() const;

 private:
  void AND(bool res[8]);
  void OR(bool res[8]);
  void ADD(bool res[8]);
  void twosComplementOperand2();

  bool operand1[8];
  bool operand2[8];
  bool N;
  bool Z;
  bool C;
  bool V;
};

#endif /* end of include guard: ALU_H */
