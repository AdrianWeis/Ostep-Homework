#!/usr/bin/env python3

# Author: Adrian Weishaupt

import matplotlib.pyplot as plt

dataFIFO = [50.41, 79.67, 91.89, 96.32, 97.88, 99.39]
dataLRU = [50.41, 85.58, 93.72, 97.14, 98.31, 99.65]
dataRAND = [50.41, 79.41, 91.30, 95.92, 97.90, 99.42]
dataCLOCK = [50.41, 80.07, 92.11, 96.48, 98.17, 99.54]
dataOPT = [50.41, 85.88, 95.44, 97.99, 99.09, 99.83]
cacheSize = [1,2,4,8,16,32]

axxis = plt.subplot()
axxis.set_xscale("symlog", base=2)
axxis.set_xlabel("Number of Cache-Page")
axxis.set_ylabel("Hitrate in %")
axxis.plot(cacheSize, dataFIFO, "y",label="FIFO")
axxis.plot(cacheSize, dataLRU, "b", label="LRU")
axxis.plot(cacheSize, dataRAND, "g", label="RAND")
axxis.plot(cacheSize, dataCLOCK, "r", label="CLOCK")
axxis.plot(cacheSize, dataOPT, "k" ,label="OPT")
axxis.legend()

plt.show()
plt.savefig("plots.png")