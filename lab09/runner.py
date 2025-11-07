import atexit
import signal
import subprocess
import sys
import time

def cleanup(subproc):
    subproc.terminate()


if len(sys.argv) != 2:
    print('Usage: {} inputFile.txt'.format(sys.argv[0]))
    quit()

subproc = subprocess.Popen(['./morscii'])

atexit.register(cleanup, subproc)

time.sleep(0.5)

with open(sys.argv[1]) as f:
    fileString = f.read()

for c in fileString:
    if c == '0':
        subproc.send_signal(signal.SIGINT)
    elif c == '1':
        subproc.send_signal(signal.SIGQUIT)
    time.sleep(0.1)

time.sleep(0.5)
