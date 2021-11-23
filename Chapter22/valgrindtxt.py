#!/usr/bin/env python3


# Author: Adrian Weishaupt, Simon Kaemmer

import subprocess
import os


subprocess.call(["valgrind", "--log-file=val", "--tool=lackey", "--trace-mem=yes" , "ls"])

trace = open("./val", "r")
adresslist = open("./addressList.txt", "w")

for line in trace:
    if line.startswith('I'):
        hex = "0x" + line[3:11]
        maskedOffset = int(hex) & 0x00000fff
        maskedPage = hex & 0xfffff000
        pageShift = maskedPage >> 12
        adresslist.write(str(int(pageShift)))

trace.close()
adresslist.close()



