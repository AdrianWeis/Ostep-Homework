#!/usr/bin/env python3


# Author: Adrian Weishaupt, Simon Kaemmer

import subprocess

subprocess.call(["valgrind --log-file=val --tool=lackey --trace-mem=yes ls"])
