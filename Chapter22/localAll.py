#!/usr/bin/env python3


# Author: Adrian Weishaupt, Simon Kaemmer

from optparse import OptionParser
from random import randrange

import subprocess
import os

with open('./paging-policy.py', 'rb+') as f:
    content = f.read()
    f.seek(0)
    f.write(content.replace(b'\r', b''))
    f.truncate()

trials = 10
pages = 10
cache = 5
policy = ["FIFO", "LRU", "LFU", "RAND", "CLOCK"]
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
    if i%5 != 0:
        arrAdressen.append(randrange(0,3))
    else :
        arrAdressen.append(randrange(3,pages))

argument = ','.join(map(str,arrAdressen))

for val in policy:
    if val != "CLOCK":
        subprocess.call(["./paging-policy.py", "-p" + val, "-m" + str(pages), "-a" + argument, '-C' + str(cache) , "-c"])
    else :
        for i in range(1,5):
            subprocess.call(["./paging-policy.py", "-p" + val, "-b" + str(i), "-m" + str(pages), "-a" + argument, '-C' + str(cache) , "-c"])
    