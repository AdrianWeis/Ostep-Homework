#!/usr/bin/env python3


# Author: Adrian Weishaupt, Simon Kaemmer

from optparse import OptionParser
from __future__ import print_function
from random import randrange

import subprocess
import os
import matplotlib.pyplot as plt

trials = 10
pages = 10
cache = 5
policy = ["FIFO", "LRU", "RAND", "CLOCK"]
argument = ""
arrAdressen = []

parser = OptionParser()
parser.add_option('-n', '--numaddrs', default=10, help='Number of Address Trials', action='store', type='int', dest='numtrials')
parser.add_option('-m', '--maxpage', default=10, help='Number of Pages', action='store', type='int', dest='numpages')
parser.add_option('-C', '--cachsize', default=10, help='Cachesize', action='store', type='int', dest='cachesize')

(options, args) = parser.parse_args()

trials = options.numtrials
pages = options.numpages
cache = options.cachesize

# Clear whole file to get new values
open('out.txt', 'w').close()

for i in range(trials):
    arrAdressen.append(randrange(pages))

argument = ','.join(map(str,arrAdressen))

for val in policy:
    subprocess.call(["python3 paging-policy.py", "-p " + val, "-m " + str(pages), "-a " + argument, '-C ' + str(cache) , "-c"])
    
# Remove last "," in out.txt
with open('out.txt', 'rb+') as filehandle:
    filehandle.seek(-1, os.SEEK_END)
    filehandle.truncate()





