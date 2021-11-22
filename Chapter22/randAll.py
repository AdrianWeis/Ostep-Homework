#!/usr/bin/env python3


# Author: Adrian Weishaupt, Simon Kaemmer

from optparse import OptionParser
from random import randrange

import subprocess
import os
import matplotlib.pyplot as plt
import re

from subprocess import PIPE, Popen

with open('./paging-policy.py', 'rb+') as f:
    content = f.read()
    f.seek(0)
    f.write(content.replace(b'\r', b''))
    f.truncate()

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
open('vergleich.txt', 'w').close()

for i in range(trials):
    arrAdressen.append(randrange(pages))

argument = ','.join(map(str,arrAdressen))

datei = open('vergleich.txt','r')

pattern = re.compile("FINALSTATS (.*?) hitrate")

for val in policy:
    if val == "CLOCK":
        for bit in range(1,10):
            command = "./paging-policy.py -p " + val + " -b " + str(bit) + " -m " + str(pages) + " -a " + argument + ' -C ' + str(
                cache) + " -c"
            with Popen(command, stdout=PIPE, stderr=None, shell=True) as process:
                output = process.communicate()[0].decode("utf-8")
                datei.write("\r\n" + val + str(bit) + ": " + pattern.findall(output))
    else:
        command = "./paging-policy.py -p " + val + " -m " + str(pages) + " -a " + argument + ' -C ' + str(cache) + " -c"
        with Popen(command, stdout=PIPE, stderr=None, shell=True) as process:
            output = process.communicate()[0].decode("utf-8")
            datei.write("\r\n" + val + ": " + pattern.findall(output))





