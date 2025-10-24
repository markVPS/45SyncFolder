.global fizzbuzz
.type fizzbuzz, %function
fizzbuzz:
  sub sp, sp, #16
  str lr, [sp]
  // ===================================
  // DON'T TOUCH ANYTHING ABOVE THE LINE

  // FIΧМЕ: a nonnegative number has been placed in w0. Print:
  //   "fizz\n" if the number is divisible by 3
  //   "buzz\n" if the number is divisible by 5
  //   "fizzbuzz\n" if the number is divisible by 3 *and* 5
  // If none of the above apply, just do nothing.

  // There is no modulus (%) instruction in ARM assembly! How can you
  // get it using division, multiplication, and subtraction?

  // Don't call the exit syscall--let the program continue executing below

  // DON'T ADD ANY MORE CODE AFTER THIS LINE
  // (You'll still need to add .data)
  // =======================================
  ldr lr, [sp]
  add sp, sp, #16
  ret

.data
// FIΧМЕ: include your strings to print here.
// Make sure not to use a label called `fizzbuzz`, since we already
// used that above.
