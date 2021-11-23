#!/usr/bin/env python3


# Author: Adrian Weishaupt

import subprocess
import os

open("./val", "w").close()
open("./addressList.txt", "w").close()

subprocess.call(["valgrind", "--log-file=val", "--tool=lackey", "--trace-mem=yes" , "ls"])

trace = open("./val", "r")
adresslist = open("./addressList.txt", "w")

for line in trace:
    if line.startswith('I'):
        hex = "0x" + line[3:11]
        maskedPage = int(hex,16) & 0xfffff000
        pageShift = maskedPage >> 12
        adresslist.write("\r\n" + str(int(pageShift)))
    if line[1] == 'L':
        hex = "0x" + line[3:11]
        maskedPage = int(hex,16) & 0xfffff000
        pageShift = maskedPage >> 12
        adresslist.write("\r\n" + str(int(pageShift)))
    if line[1] == 'S':
        if line[12] != ',':
            hex = "0x" + line[3:11]
            maskedPage = int(hex,16) & 0xfffff000
            pageShift = maskedPage >> 12
            adresslist.write("\r\n" + str(int(pageShift)))
        else :
            #keine Ahnung auf einmal 40 bit

trace.close()
adresslist.close()

os.system("sort addressList.txt | uniq -c | sort -nr")

