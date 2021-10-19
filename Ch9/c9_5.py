import matplotlib.pyplot as plt
import numpy as np
from io import StringIO
from contextlib import redirect_stdout
import sys

f = StringIO()
for s in range(16):
    if s != 1:
        continue
    for l in range(1001):
        arg_str = StringIO()
        arg_str.write(" -l")
        arg_str.write(l)
        arg_str.write(":100,")
        arg_str.write(l)
        arg_str.write(":100 -s ")
        arg_str.write(s)
        arg_str.write(" -c")
        sys.argv = [arg_str.getvalue()]
        with redirect_stdout(f):
            with open("./lottery.py") as f:
                exec("./lottery.py")
        s = f.getvalue()
        job0At = s.find("JOB 0 DONE")
        job1At = s.find("JOB 1 DONE")
        job0Done = int(s[job0At+19] + s[job0At+20] +s[job0At+21] + s[job0At+22]) 
        print(job0Done)

# Data for plotting
t = np.arange(0.0, 1.0, 0.1)
s = np.sin(1)

fig, ax = plt.subplots()
ax.plot(t, s)

ax.set(xlabel='time (s)', ylabel='voltage (mV)',
       title='About as simple as it gets, folks')
ax.grid()

fig.savefig("Figur.png")
plt.show()