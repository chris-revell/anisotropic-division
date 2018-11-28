import numpy as np
import matplotlib.pyplot as plt
import os

data = np.genfromtxt("output/cellpositions.txt")
ncells = np.genfromtxt("output/cellcount.txt",dtype=int)
xmax=50
drawn = 0
for step in range(ncells.shape[0]):
    print("{:02d}/{:02d}".format((step+1),ncells.shape[0]))
    fig, ax = plt.subplots(figsize=(6,6))
    print("{}:{}".format(drawn,drawn+ncells[step]))

    ax.scatter(data[drawn:drawn+ncells[step],0],data[drawn:drawn+ncells[step],1])
    drawn = drawn+ncells[step]
    ax.set_xlim([-xmax,xmax])
    ax.set_ylim([-xmax,xmax])
    ax.tick_params(axis='x',which='both',bottom=False,top=False,labelbottom=False)
    ax.tick_params(axis='y',which='both',left=False,right=False,labelleft=False)
    fig.savefig("output/test{:05d}".format(step))
    plt.close()
os.system("convert -delay 2 -loop 0 output/*.png output/animated.gif;rm output/*.png")
