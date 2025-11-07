.global main
.type main, %function
main:
  // FIΧМЕ: open the file in argv[1] and print the first 10 lines of
  // it. You can assume the file exists and will successfully open.
  // Remember that EOF is -1, and that the file might have fewer than
  // 10 lines.
  // 
  // Probably the easiest way to do it is to read a character at a
  // time, use putchar, and check for '\n's.
