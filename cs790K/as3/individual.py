import random

import evaluator

class Individual:
	def __init__(self, options, evalr):
		self.options = options
		self.eval = evalr

		self.chromosome = []
		self.chromosomeLength = self.eval.encodedDataLength

		self.fitness = 0
		self.objective = 0

	def SetSeed(self, seed):
		random.seed(seed)

	def init(self):
		self.chromosome = self.eval.getRandomString()

	def evaluate(self):
		self.fitness, self.objective = self.eval.evaluate(self.chromosome)

	def mutate(self, options):
		#print("TODO MAKE MUTATOR")
		for i in range(self.chromosomeLength):
			if random.random() < self.options.pMut:
				self.invert(i, random.randint(0, self.chromosomeLength - 1))
		return

	def swap(self, p1, p2):
		temp = self.chromosome[p1]
		self.chromosome[p1] = self.chromosome[p2]
		self.chromosome[p2] = temp

	def invert(self, p1, p2):
		minp = min(p1, p2)
		maxp = max(p1, p2)
		for i in range(minp, maxp, 1):
			p1 = minp + i
			p2 = maxp - i
			if p1 >= p2:
				break
			temp = self.chromosome[p1]
			self.chromosome[p1] = self.chromosome[p2]
			self.chromosome[p2] = temp

	def myCopy(self, ind):
		self.fitness = ind.fitness
		self.chromosomeLength = ind.chromosomeLength # this should not change!
		self.objective = ind.objective
		for i in range(self.chromosomeLength):
			self.chromosome[i] = ind.chromosome[i]
