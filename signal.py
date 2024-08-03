#!/usr/bin/python3
import os
import sys

os.kill(os.getpid(), int(sys.argv[1]))
