import numpy
import math

from problem import TSP

class Tour:
	def __init__(self, problem):
		# variables
		self.tsp = problem
		self.totalCost = math.inf
		self.sequence = [] # coordinate id
		self.start = 0

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

