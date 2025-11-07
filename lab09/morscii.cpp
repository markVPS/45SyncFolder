#include <signal.h>
#include <termios.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
using namespace std;

struct termios original_termios;
void resetTerminalEchoAtExit() {
  tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
}

// You don't have to use the following two global variables,
// but they're what I used in my solution. Delete them if 
// you're doing things in a different way.
char currentChar = 0;
int currentNumberOfBits = 0;

// FIΧМЕ: add your signal handlers here

int main() {
  // flush every character written to cout immediately
  cout << std::unitbuf;

  // stop the terminal from echoing the characters that you type in
  // (so you don't see ^C^\^C^C... all over the place)
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  original_termios = t;
  t.c_lflag &= ~((tcflag_t)ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
  // Make sure to reset this behavior before the program ends
  atexit(resetTerminalEchoAtExit);
  // If something goes wrong and your program ends abnormally, run the
  // `tput reset` terminal command to set things back to normal.

  // FIΧМЕ: set up two signal handlers here--one for SIGINT and the
  // other for SIGQUIT. SIGINT stands for 0, and SIGQUIT stands for 1.
  // Every 8 interrupts creates an 8-bit number! Interpret that number
  // as a char and print it out. If you ever see 8 SIGINTs in a row
  // (i.e., '\0'), then exit the program instead of printing out the
  // null character.

  while (true) {
    // The unistd.h pause function waits until a signal occurs so that
    // the server doesn't overheat and start a fire
    pause();
  }

  return 0;
}
