

import evaluator
import random
import utils

from individual import Individual

class Population(object):
	def	__init__(self, options, evaler):
		self.options = options;
		self.eval = evaler

		self.individuals = []
		self.min = -1
		self.max = -1
		self.avg = -1

	def init(self):
		# initialize population with randomly generated Individuals
		for i in range(self.options.populationSize * self.options.chcLambda):
			self.individuals.append(Individual(self.options, self.eval))
			self.individuals[i].init()

	def evaluate(self):
		# evaluates all individuals in population
		for i in range(self.options.populationSize): #ind in self.individuals:
			self.individuals[i].evaluate()
			
	def printPop(self, start, end):
		i = 0
		for i in range(start, end, 1): #self.options.populationSize): #ind in self.individuals:
			print(i, end=": ")
			ind = self.individuals[i]
			print (ind.chromosome, " Fit: ", ind.fitness)
			i = i+1
		self.report("")

	def report(self, gen):
		print (gen, self.min, self.avg, self.max)

	def statistics(self):
		self.sumFitness = 0
		self.min = self.individuals[0].fitness
		self.max = self.individuals[0].fitness
		self.avg = 0
		for i in range(self.options.populationSize): #ind in self.individuals:
			ind = self.individuals[i]
			self.sumFitness += ind.fitness
			if ind.fitness < self.min:
				self.min = ind.fitness
			if ind.fitness > self.max:
				self.max = ind.fitness

		self.avg = self.sumFitness/self.options.populationSize #len(self.individuals)

	def select(self):
		randFraction = self.sumFitness * random.random()
		sum = 0
		i = 0
		for i in range(self.options.populationSize): #ind in self.individuals:
			ind = self.individuals[i]
			sum += ind.fitness
			if randFraction <= sum:
				return (i, ind)
		print("Selection failed")
		return (self.options.populationSize - 1, self.individuals[self.options.populationsSize - 1])

	def generation(self, child):
		for i in range(0, len(self.individuals), 2):
			x, p1 = self.select()
			x, p2 = self.select()
			c1 = child.individuals[i]
			c2 = child.individuals[i + 1]

			self.xover1Pt(p1, p2, c1, c2)			
			c1.mutate(self.options)
			c2.mutate(self.options)

	def CHCGeneration(self, child):
		for i in range(0, self.options.populationSize, 2):
			x, p1 = self.select()
			x, p2 = self.select()
			c1 = self.individuals[self.options.populationSize + i]
			c2 = self.individuals[self.options.populationSize + i + 1]
			self.xover1Pt(p1, p2, c1, c2)
			c1.mutate(self.options);
			c2.mutate(self.options);
		self.halve(child)

	def comparator(self, individual):
		return individual.fitness

	def halve(self, child):
		for	i in range(self.options.populationSize,	self.options.populationSize	* self.options.chcLambda):
			self.individuals[i].evaluate()
		self.individuals.sort (key = self.comparator, reverse = True)
		#self.printPop(0, self.options.populationSize * self.options.chcLambda)
		for i in range(self.options.populationSize):
			child.individuals[i].myCopy(self.individuals[i])
			#			child.individuals[i] = self.individuals[i]

	def xover1Pt(self, p1, p2, c1, c2):
		for i in range(self.eval.encodedDataLength):
			c1.chromosome[i] = p1.chromosome[i]
			c2.chromosome[i] = p2.chromosome[i]
		if utils.flip(self.options.pCross):
			xp = utils.randInt(1, self.eval.encodedDataLength)
			for i in range(xp, self.eval.encodedDataLength):
				c1.chromosome[i] = p2.chromosome[i]
				c2.chromosome[i] = p1.chromosome[i]

	def visualize(self):
		return

