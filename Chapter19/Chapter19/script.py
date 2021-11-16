#!/usr/bin/env python3


# Author: Adrian Weishaupt, Simon Kaemmer

from __future__ import print_function
from optparse import OptionParser

import subprocess
import os
import matplotlib.pyplot as plt

arrNumpages = [1, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048]
trials = 1000000

parser = OptionParser()
parser.add_option('-n', '--numtrials', default=1000000, help='Number of Trials - use > 10k to get more accurate', action='store', type='int', dest='numtrials')

(options, args) = parser.parse_args()

trials = options.numtrials
# Clear whole file to get new values
open('out.txt', 'w').close()

# Print data to out.txt
for val in arrNumpages:
    subprocess.call(["./tlb", "-n " + str(val), "-l " + str(trials)])

# Remove last "," in out.txt
with open('out.txt', 'rb+') as filehandle:
    filehandle.seek(-1, os.SEEK_END)
    filehandle.truncate()

# Reading out.txt and bring values into array
file = open("out.txt", "r")

data = str(file.read()).split(",")
data = list(map(int, data))


# Plotting data

axes = plt.subplot()
axes.set_xscale("symlog", base=2)
axes.set_xlabel("Number of Pages")
axes.set_ylabel("Time Per Acces (ms)")
axes.set_title("TLB Size Measurement")
axes.plot(arrNumpages, data)
plt.show()




