import numpy
import math

import matplotlib.pyplot as plt
import numpy as np
import os

from problem import TSP

class Tour:
	def __init__(self, problem, visualize):
		# variables
		self.tsp = problem
		self.totalCost = math.inf
		self.sequence = [] # coordinate id
		self.start = 0
		self.name = ''

		if (visualize == True):
			# only if visualizing
			plt.ion()
			self.figure, self.axes  = plt.subplots(1)
			self.line, = self.axes.plot(np.linspace(0, 0, len(self.sequence)), np.linspace(0, 0, len(self.sequence)), color=(0,0,0,0.25))
			# make scatter plot with coordinates
			x = []
			y = []
			for i in range(len(self.tsp.coordinates)):
				if (i > 0):
					x.append(self.tsp.coordinates[i][0])
					y.append(self.tsp.coordinates[i][1])

			self.axes.scatter(x, y, s=3, color='black')
			self.axes.scatter(self.tsp.coordinates[0][0], self.tsp.coordinates[0][1], marker = "*", color='red')
			self.axes.autoscale_view()
			#self.xValues = np.linspace(0, 0, self.options.maxGen)


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

	def SetName(self, name):
		self.name = name
		self.axes.set_title(name)


	def Visualize(self):

		x = []
		y = []
		for i in range(len(self.sequence)):
			x.append(self.tsp.coordinates[self.sequence[i]][0])
			y.append(self.tsp.coordinates[self.sequence[i]][1])

		self.line.set_data(x, y)

		self.figure.canvas.draw()
		self.figure.canvas.flush_events()
		
		return

	def Show(self, blocking):
		#print("SHOWING")
		self.figure.show()
		return

	def Save(self):
		self.figure.savefig(os.getcwd() + '/results/' + self.name + '.png')




