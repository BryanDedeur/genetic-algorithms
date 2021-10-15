import numpy
import math

import matplotlib.pyplot as plt
import numpy as np

from problem import TSP

class Tour:
	def __init__(self, problem):
		# variables
		self.tsp = problem
		self.totalCost = math.inf
		self.sequence = [] # coordinate id
		self.start = 0

		# only if visualizing

		#plt.show(block=False)

	def Add(self, coordId):
		if len(self.sequence) == 0:
			self.totalCost = 0
		else:
			cost = self.tsp.distances[coordId][self.sequence[len(self.sequence) - 1]]
			self.totalCost = self.totalCost + cost
		self.sequence.append(coordId)

	def Print(self):
		print('Tour: ', end = '')
		print(self.sequence)
		print('Cost: ' + str(self.totalCost))

	def Clear(self):
		self.totalCost = 0
		self.sequence = []
		self.sequence.append(self.start)

	def Visualize(self):
		fig = plt.figure(2)
		fig.tight_layout()
		axes = fig.add_subplot(111)

		x = []
		y = []
		for i in range(len(self.sequence)):
			x.append(self.tsp.coordinates[self.sequence[i]][0])
			y.append(self.tsp.coordinates[self.sequence[i]][1])

		axes.plot(x, y, color=(0,0,0,0.25))

		x = []
		y = []
		for i in range(len(self.tsp.coordinates)):
			if (i > 0):
				x.append(self.tsp.coordinates[i][0])
				y.append(self.tsp.coordinates[i][1])

		axes.scatter(x, y, s=3, color='black')
		axes.scatter(self.tsp.coordinates[0][0], self.tsp.coordinates[0][1], marker = "*", color='red')
		axes.autoscale_view()

		# update visuals
		#plt.plot(self.xValues, self.yValues)
		plt.show(block=True)
		
		return

	def Show(self):
		#print("SHOWING")

		return




