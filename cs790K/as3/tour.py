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
		self.figure = plt.figure(2)
		self.figure.tight_layout()
		self.axes = self.figure.add_subplot(111)
		#self.axes.set_xlim([0, 1000])
		#self.axes.set_ylim([0, 1000])

		self.xValues = []
		self.yValues = []
		for i in range(len(self.tsp.coordinates) + 1):
			if not  i == len(self.tsp.coordinates) - 1
				self.xValues.append(self.tsp.coordinates[i][0])
				self.yValues.append(self.tsp.coordinates[i][1])

		self.tourLine, = self.axes.plot(self.xValues, self.yValues, 'b-')

		x = []
		y = []
		for coordinate in self.tsp.coordinates:
			x.append(coordinate[0])
			y.append(coordinate[1])

		self.axes.scatter(x, y)
		self.axes.autoscale_view()
		plt.show(block=False)

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
		# update data
		for i in range(len(self.sequence)):
			coordinateId = self.sequence[i]
			self.xValues[i] = self.tsp.coordinates[coordinateId][0]
			self.yValues[i] = self.tsp.coordinates[coordinateId][1]

		#self.axes.plot(self.xValues, self.yValues, 'b-')
		self.tourLine.set_data(self.xValues, self.yValues)
		#self.axes.relim()
		self.figure.canvas.draw()
		self.figure.canvas.flush_events()

		# update visuals
		#self.figure.canvas.draw()
		#self.figure.canvas.flush_events()
		return

