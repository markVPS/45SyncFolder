.global main
.type main, %function
main:
  // FIΧМЕ: open the file in argv[1] and print the last 10 lines of
  // it. You can assume the file exists and will successfully open.
  // Remember that EOF is -1, and that the file might have fewer than
  // 10 lines.
  //
  // I definitely recommend doing the head program first!
  // 
  // One possible strategy: read through the file twice. The first
  // time, count the number of '\n's (and don't print anything). Then,
  // `rewind` to the start of the file and throw away the characters
  // until you find the start of the (last - 10 + 1)th line. 
