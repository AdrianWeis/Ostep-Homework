#!/usr/bin/env python3


# Author: Adrian Weishaupt, Simon Kaemmer

from optparse import OptionParser
from random import randrange

import subprocess
import os

trials = 10
pages = 10
policy = "FIFO"
argument = ""
arrAdressen = []

parser = OptionParser()
parser.add_option('-n', '--numaddrs', default=10, help='Number of Address Trials', action='store', type='int', dest='numtrials')
parser.add_option('-m', '--maxpage', default=10, help='Number of Pages', action='store', type='int', dest='numpages')
parser.add_option('-p', '--policy', default="FIFO", help='Policy Type', action='store', type='string', dest='policyChoice')

(options, args) = parser.parse_args()

trials = options.numtrials
pages = options.numpages
policy = options.policyChoice

for i in range(trials):
    arrAdressen.append(randrange(pages))

argument = ','.join(map(str,arrAdressen))

# Clear whole file to get new values
open('out.txt', 'w').close()

subprocess.call(["./paging-policy.py", "-p " + policy, "-m " + str(pages), "-a " + argument, "-c"])




