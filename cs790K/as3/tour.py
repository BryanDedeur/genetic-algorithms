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
		plt.ion()
		self.fig = plt.figure(2)
		self.fig.tight_layout()
		self.axes = self.fig.add_subplot(111)

		self.xValues = np.linspace(0, 0, len(self.tsp.coordinates) + 1)
		self.yValues = np.linspace(0, 0, len(self.tsp.coordinates) + 1)

		self.tourLine, = self.axes.plot(self.xValues, self.yValues, 'b-')

		x = []
		y = []
		for i in range(len(self.tsp.coordinates)):
			if (i > 0):
				x.append(self.tsp.coordinates[i][0])
				y.append(self.tsp.coordinates[i][1])

		self.axes.scatter(x, y, s=1.25)
		self.axes.scatter(self.tsp.coordinates[0][0], self.tsp.coordinates[0][1], marker = "*")
		self.axes.autoscale_view()
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

	def Visualize(self, sequence):
		# update data
		for i in range(len(sequence)):
			coordinateId = sequence[i]
			self.xValues[i] = self.tsp.coordinates[coordinateId][0]
			self.yValues[i] = self.tsp.coordinates[coordinateId][1]

		#self.axes.plot(self.xValues, self.yValues, 'b-')
		self.tourLine.set_data(self.xValues, self.yValues)
		self.tourLine.set_ydata(self.yValues)

		# update visuals
		self.fig.canvas.draw()
		self.fig.canvas.flush_events()
		
		return

	def Show(self):
		#print("SHOWING")
		plt.plot(self.xValues, self.yValues)
		plt.show(block=True)
		return




