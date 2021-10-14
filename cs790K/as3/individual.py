import random
import utils

import evaluator

class Individual:
	def __init__(self, options, eval):
		self.options = options
		self.evaluator = eval

		self.chromosome = []
		self.chromosomeLength = eval.encodedDataLength

		self.fitness = -1
		self.objective = -1

	def init(self):
		self.chromosome = self.evaluator.getRandomString()

	def evaluate(self):
		self.fitness, self.objective = self.evaluator.evaluate(self.chromosome)







	def mutate(self, options):
		#print("TODO MAKE MUTATOR")
		#for i in range(self.chromosomeLength):
		#	if utils.flip(options.pMut):
		#			self.chromosome[i] = 1 - self.chromosome[i]
		return

	def myCopy(self, ind):
		self.fitness = ind.fitness
		self.chromosomeLength = ind.chromosomeLength # this should not change!
		self.objective = ind.objective
		for i in range(self.chromosomeLength):
			self.chromosome[i] = ind.chromosome[i]
