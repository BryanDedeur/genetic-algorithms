import individual
import random
import tour
import copy

from problem import TSP

class Evaluator:
	def __init__(self, problem, visualize):
		# variables
		self.problem = problem
		self.tour = tour.Tour(problem, False)

		if visualize:
			self.bestTour = tour.Tour(problem, True)
			self.bestTour.SetName(self.problem.name + ' best')
			self.worstTour = tour.Tour(problem, True)
			self.worstTour.SetName(self.problem.name + ' worst')
			self.worstTour.totalCost = 0
		self.encodedDataLength = len(self.problem.coordinates) - 1 # we skip the first

	def SetSeed(self, seed):
		random.seed(seed)
	
	def getRandomString(self):
		# make array using base 0 indicies not size of actual data
		temp = []
		for i in range(self.encodedDataLength):
			temp.append(i)
		# randomly shuffle data around
		for i in range(len(temp)):
			i2 = random.randint(0, len(temp) - 1)
			tempVal = temp[i]
			temp[i] = temp[i2]
			temp[i2] = tempVal
		return temp

	def evaluate(self, encodedData):
		if not self.validEncoding(encodedData):
			print("Encoded data is invalid:" + encodedData)
			quit()

		# construct tour
		self.tour.Clear()
		for i in range(len(encodedData)):
			self.tour.Add(encodedData[i] + 1)
		self.tour.Add(0)

		# track best tour
		if self.bestTour.totalCost > self.tour.totalCost:
			self.bestTour.sequence = self.tour.sequence
			self.bestTour.totalCost = self.tour.totalCost
			self.bestTour.Visualize()

		# track worst tour
		if self.worstTour.totalCost < self.tour.totalCost:
			self.worstTour.sequence = self.tour.sequence
			self.worstTour.totalCost = self.tour.totalCost
			self.worstTour.Visualize()

		return 1/self.tour.totalCost, self.tour.totalCost

	# tests if encoded data is valid
	def validEncoding(self, data):
		# valid if all items are different
		return True

	# tests if decoded data is valid
	def validDecoding(self, data):
		return True

