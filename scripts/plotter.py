import numpy as np
import matplotlib.pyplot as plt
import os
from scipy.spatial import Voronoi, voronoi_plot_2d
from matplotlib.patches import Polygon
from math import sqrt

# Read cell positions from file
data = np.genfromtxt("output/cellpositions.txt")
# Read the number of cells at each time interval from file.
# This tells the script how many of the values in the data array to plot for each time point
ncells = np.genfromtxt("output/cellcount.txt",dtype=int)


def voronoi_finite_polygons_2d(vor, radius=None):
    """
    Function from https://stackoverflow.com/questions/20515554/colorize-voronoi-diagram/20678647#20678647

    Reconstruct infinite voronoi regions in a 2D diagram to finite
    regions.

    Parameters
    ----------
    vor : Voronoi
        Input diagram
    radius : float, optional
        Distance to 'points at infinity'.

    Returns
    -------
    regions : list of tuples
        Indices of vertices in each revised Voronoi regions.
    vertices : list of tuples
        Coordinates for revised Voronoi vertices. Same as coordinates
        of input vertices, with 'points at infinity' appended to the
        end.

    """

    if vor.points.shape[1] != 2:
        raise ValueError("Requires 2D input")

    new_regions = []
    new_vertices = vor.vertices.tolist()

    center = vor.points.mean(axis=0)
    if radius is None:
        radius = vor.points.ptp().max()

    # Construct a map containing all ridges for a given point
    all_ridges = {}
    for (p1, p2), (v1, v2) in zip(vor.ridge_points, vor.ridge_vertices):
        all_ridges.setdefault(p1, []).append((p2, v1, v2))
        all_ridges.setdefault(p2, []).append((p1, v1, v2))

    # Reconstruct infinite regions
    for p1, region in enumerate(vor.point_region):
        vertices = vor.regions[region]

        if all(v >= 0 for v in vertices):
            # finite region
            new_regions.append(vertices)
            continue

        # reconstruct a non-finite region
        ridges = all_ridges[p1]
        new_region = [v for v in vertices if v >= 0]

        for p2, v1, v2 in ridges:
            if v2 < 0:
                v1, v2 = v2, v1
            if v1 >= 0:
                # finite ridge: already in the region
                continue

            # Compute the missing endpoint of an infinite ridge

            t = vor.points[p2] - vor.points[p1] # tangent
            t /= np.linalg.norm(t)
            n = np.array([-t[1], t[0]])  # normal

            midpoint = vor.points[[p1, p2]].mean(axis=0)
            direction = np.sign(np.dot(midpoint - center, n)) * n
            far_point = vor.vertices[v2] + direction * radius

            new_region.append(len(new_vertices))
            new_vertices.append(far_point.tolist())

        # sort region counterclockwise
        vs = np.asarray([new_vertices[v] for v in new_region])
        c = vs.mean(axis=0)
        angles = np.arctan2(vs[:,1] - c[1], vs[:,0] - c[0])
        new_region = np.array(new_region)[np.argsort(angles)]

        # finish
        new_regions.append(new_region.tolist())

    return new_regions, np.asarray(new_vertices)




xmax=35   # Size of plots
drawn = 0 # Counter for how many lines of data have been plotted so far
for step in range(ncells.shape[0]):
    stepdata = data[drawn:drawn+ncells[step],:]
    print("{:02d}/{:02d}".format((step+1),ncells.shape[0]))
    vor = Voronoi(stepdata[:,:2])

    drawn = drawn+ncells[step]

    # plot
    regions, vertices = voronoi_finite_polygons_2d(vor,2)
    # colorize
    for j,region in enumerate(regions):
        polygon = vertices[region]
        indices = []
        for i in range(np.shape(polygon)[0]):
            vec = polygon[i,:2]-stepdata[j,:2]
            vec_mag = sqrt(np.dot(vec,vec))
            if vec_mag > 2:
                #if not (np.min(stepdata[:,0]) < polygon[i,0] < np.max(stepdata[:,0])) or not (np.min(stepdata[:,1]) < polygon[i,1] < np.max(stepdata[:,1])):
                #indices.append(i)
                polygon[i,:2] = stepdata[j,:2] + 2*vec/vec_mag
        #polygon = np.delete(polygon,np.array(indices),0)
        if stepdata[j,2]==60:
            plt.fill(*zip(*polygon),color="blue")
        plt.plot(*zip(*polygon),color='black',lw=0.5)
    plt.plot(data[drawn:drawn+ncells[step],0], data[drawn:drawn+ncells[step],1], 'ko',ms=1)
    #plt.xlim(vor.min_bound[0] - 0.1, vor.max_bound[0] + 0.1)
    #plt.ylim(vor.min_bound[1] - 0.1, vor.max_bound[1] + 0.1)
    plt.xlim([-xmax,xmax])
    plt.ylim([-xmax,xmax])
    plt.tick_params(axis='x',which='both',bottom=False,top=False,labelbottom=False)
    plt.tick_params(axis='y',which='both',left=False,right=False,labelleft=False)
    plt.savefig("output/test{:05d}".format(step),bbox_inches='tight',padding_inches=0,dpi=500)
    plt.close()
# Save plots as animated gif and remove static images.
os.system("convert -delay 10 -loop 0 output/*.png output/animated.gif;rm output/*.png")
