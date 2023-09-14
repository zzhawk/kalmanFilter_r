import matplotlib.pyplot as plt
import numpy as np

f = open("ans.csv", "r")
x_raw = []
y_raw = []
x_meas = []
y_meas = []
x_filt = []
y_filt = []

for line in f:
    item = line.split(',')
    x_raw.append(float(item[0]))
    y_raw.append(float(item[1]))
    x_meas.append(float(item[2]))
    y_meas.append(float(item[3]))
    x_filt.append(float(item[4]))
    y_filt.append(float(item[5]))


plt.scatter(np.asarray(x_raw), np.asarray(y_raw), label="raw")
plt.scatter(np.asarray(x_meas), np.asarray(y_meas), label="measured")
plt.scatter(np.asarray(x_filt), np.asarray(y_filt), label="filtered")

plt.plot(np.asarray(x_raw), np.asarray(y_raw))
plt.plot(np.asarray(x_meas), np.asarray(y_meas))
plt.plot(np.asarray(x_filt), np.asarray(y_filt))

plt.legend()

plt.show()

pass