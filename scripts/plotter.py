import numpy as np
import matplotlib.pyplot as plt
import os

# Read cell positions from file
data = np.genfromtxt("output/cellpositions.txt")
# Read the number of cells at each time interval from file.
# This tells the script how many of the values in the data array to plot for each time point
ncells = np.genfromtxt("output/cellcount.txt",dtype=int)


xmax=50   # Size of plots
drawn = 0 # Counter for how many lines of data have been plotted so far
for step in range(ncells.shape[0]):
    print("{:02d}/{:02d}".format((step+1),ncells.shape[0]))
    # Create new figure for each time point.
    fig, ax = plt.subplots(figsize=(6,6))
    # Plot cell positions corresponding to this time step
    ax.scatter(data[drawn:drawn+ncells[step],0],data[drawn:drawn+ncells[step],1])
    drawn = drawn+ncells[step]
    # Set plot parameters
    ax.set_xlim([-xmax,xmax])
    ax.set_ylim([-xmax,xmax])
    ax.tick_params(axis='x',which='both',bottom=False,top=False,labelbottom=False)
    ax.tick_params(axis='y',which='both',left=False,right=False,labelleft=False)
    # Save plot
    fig.savefig("output/test{:05d}".format(step))
    plt.close()
# Save plots as animated gif and remove static images.
os.system("convert -delay 10 -loop 0 output/*.png output/animated.gif;rm output/*.png")
