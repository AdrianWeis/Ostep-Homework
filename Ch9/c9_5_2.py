import matplotlib.pyplot as plt
import numpy as np

# Data for plotting
t = np.arange(0.0, 1.0, 0.1)
s = np.arange(0.0, 1000.0, 1.0)

fig, ax = plt.subplots()
ax.plot(t, s)

ax.set(xlabel='length of Jobs', ylabel='fairness',
       title='Test')
ax.grid()


fig.savefig("Figur.png")
plt.show()