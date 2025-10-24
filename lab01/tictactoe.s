.global _start
_start:
  // output prompt
  mov x8, #64
  mov w0, #1
  ldr x1, =prompt
  mov x2, #34
  svc #0

  // get the sub-board
  mov x8, #63
  mov w0, #0
  ldr x1, =board_piece
  mov x2, #4
  svc #0

  // FIΧМЕ: using the input row/column/diagonal (stored in the
  // `board_piece` string), see if there is a winner. If there is one,
  // print the winner followed by a newline. If there is no winner,
  // print a question mark followed by a newline.

  // exit
  mov w0, #0
  mov x8, #93
  svc #0


.data
prompt: .ascii "Enter a row, column, or diagonal:\n"
board_piece: .ascii "???\n"
