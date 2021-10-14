import individual
import random

from problem import TSP
from tour import Tour

class Evaluator:
	def __init__(self, problem):
		# variables
		self.problem = problem
		self.tour = Tour(problem)
		self.bestTour = Tour(problem)
		self.encodedDataLength = len(self.problem.coordinates) - 1 # we skip the first
	
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
		if (self.tour.totalCost < self.bestTour.totalCost):
			self.bestTour = self.tour

		return 1/self.tour.totalCost, self.tour.totalCost

	# tests if encoded data is valid
	def validEncoding(self, data):
		return True

	# tests if decoded data is valid
	def validDecoding(self, data):
		return True

