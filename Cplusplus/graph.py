import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

fig = plt.figure()
fig.suptitle('Array in random order', fontsize=14, fontweight='bold')

xs = [100, 1000, 10000, 100000, 1000000, 5000000, 10000000]

ys1 =  [0.0, 0.0, 1.0, 7.0, 67.3, 319.3, 740.2]
ys2 =  [0.0, 0.0, 4.5, 36.9, 379.2, 2066.5, 4523.2]
ys3 =  [0.0, 0.0, 0.0, 6.0, 68.5, 315.4, 772.8]
ys4 =  [0.0, 0.0, 2.1, 32.6, 420.7, 2198.2, 5040.3]

plt.plot(xs, ys1, 'red')
plt.plot(xs, ys2, 'blue')
plt.plot(xs, ys3, 'orange')
plt.plot(xs, ys4, 'purple')
plt.axis([0, 10000000, 0, 10000])

red_patch = mpatches.Patch(color='red')
blue_patch = mpatches.Patch(color='blue')
orange_patch = mpatches.Patch(color='orange')
purple_patch = mpatches.Patch(color='purple')
plt.legend([red_patch, orange_patch, blue_patch, purple_patch],
           ["introsort", "introsort (same V)", "std::sort", "std::sort (same V)"])

plt.xlabel("(N, V)")
plt.ylabel("Average time (in milliseconds)")
plt.show()
