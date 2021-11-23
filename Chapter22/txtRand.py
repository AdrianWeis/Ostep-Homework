#!/usr/bin/env python3


# Author: Adrian Weishaupt

from optparse import OptionParser
from __future__ import print_function
from random import randrange

import subprocess
import os
import matplotlib.pyplot as plt

trials = 10
pages = 10
argument = ""
arrAdressen = []

parser = OptionParser()
parser.add_option('-n', '--numaddrs', default=10, help='Number of Address Trials', action='store', type='int', dest='numtrials')
parser.add_option('-m', '--maxpage', default=10, help='Number of Pages', action='store', type='int', dest='numpages')

(options, args) = parser.parse_args()

trials = options.numtrials
pages = options.numpages

# Clear whole file to get new values
open('adrRand.txt', 'w').close()

for i in range(trials):
    arrAdressen.append(randrange(pages))

argument = ','.join(map(str,arrAdressen))

with open("adr.txt", "w") as text_file:
    text_file.write(argument)
