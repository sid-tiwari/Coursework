#import numpy as np
import math

def distance(x, y):
	return math.sqrt((y[1] - x[1]) ** 2 + (y[0] - x[0]) ** 2) 

def avg(x, y):
	return [(x[0] + y[0]) / 2, (x[1] + y[1]) / 2]

def kmeans():
	points = [[2,3], [3,1], [8,7], [9,6], [10,1], [12,2], [2,2], [8,6], [10,2]]
	#k = 3
	means = [[2,3], [12,3], [9,6]]	#initial means

	print("Initial means:" , means)

	clusters = [[], [], []]

	psize = len(points)

	for i in range(0, psize):
		distances = [distance(points[i], means[0]),
					 distance(points[i], means[1]),
					 distance(points[i], means[2])]
		minpos = distances.index(min(distances))

		means[minpos] = avg(means[minpos], points[i])

		clusters[minpos].append(points[i])

	for i in range(3):
		print("Cluster", str(i + 1) + ":", )
		print("Mean", str(i + 1) + ":", means[i])
		print("Cluster elements:" , clusters[i])
		print()		

kmeans()

