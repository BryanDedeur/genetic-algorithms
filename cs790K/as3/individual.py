import random
import utils

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
			if utils.flip(options.pMut):
				otherP = random.randint(0,self.chromosomeLength - 1)
				temp = self.chromosome[i]
				self.chromosome[i] = self.chromosome[otherP]
				self.chromosome[otherP] = temp
		return

	def myCopy(self, ind):
		self.fitness = ind.fitness
		self.chromosomeLength = ind.chromosomeLength # this should not change!
		self.objective = ind.objective
		for i in range(self.chromosomeLength):
			self.chromosome[i] = ind.chromosome[i]
