

import evaluator
import random

from individual import Individual

class Population(object):
	def	__init__(self, options, evaler):
		self.options = options;
		self.eval = evaler

		self.individuals = [] 

		self.fitStats = [] # 0 = min, 1 = ave, 2 = max, 3 = sum
		self.objStats = [] # 0 = min, 1 = ave, 2 = max, 3 = sum

		for i in range(4):
			self.fitStats.append(0)
			self.objStats.append(0)

	def init(self):
		self.individuals = [] 

		# initialize population with randomly generated Individuals
		for i in range(self.options.populationSize * self.options.chcLambda):
			self.individuals.append(Individual(self.options, self.eval))
			self.individuals[i].init()

	def SetSeed(self, seed):
		random.seed(seed)
		for i in range(self.options.populationSize):
			self.individuals[i].SetSeed(seed)

	def evaluate(self, evalEachInd):
		# reset stats
		self.resetStatistics()

		# evaluates all individuals in population
		for i in range(self.options.populationSize):
			if evalEachInd:
				self.individuals[i].evaluate()
			# increment the statistics
			self.computeMinMaxSum(self.individuals[i])

		#self.ScalePop()

		# compute averages
		self.fitStats[1] = self.fitStats[3] / self.options.populationSize
		self.objStats[1] = self.objStats[3] / self.options.populationSize

	def ScalePop(self):
		# linearly scale the population
		scaleA, scaleB = self.FindCoeffs();

		scaledSumFitness = 0.0;
		for i in range(self.options.populationSize	* self.options.chcLambda):
			ind = self.individuals[i]
			ind.scaledFitness = scaleA * ind.fitness + scaleB
			scaledSumFitness += ind.scaledFitness

	def FindCoeffs(self):
		# find coeffs scale_constA and scale_constB for linear scaling according to f_scaled = scale_constA * f_raw + scale_constB */  

		#d = 0;
		min = self.fitStats[0]
		avg = self.fitStats[1]
		max = self.fitStats[2]

		scaleFactor = 10

		if (min > (scaleFactor * avg - max)/(scaleFactor - 1.0)):
			d = max - avg
			scaleConstA = (scaleFactor - 1.0) * avg / d
			scaleConstB = avg * (max - (scaleFactor * avg))/d
		else:  
			d = avg - min;
			scaleConstA = avg/d
			scaleConstB = -min * avg/d
		
		if (d < 0.00001 and d > -0.00001):
			scaleConstA = 1.0
			scaleConstB = 0.0
		
		return scaleConstA, scaleConstB
	

	def resetStatistics(self):
		# reset min
		self.fitStats[0] = float('inf')
		self.objStats[0] = float('inf')

		# reset ave
		self.fitStats[1] = 0
		self.objStats[1] = 0

		# reset max
		self.fitStats[2] = 0
		self.objStats[2] = 0

		# reset sums
		self.fitStats[3] = 0
		self.objStats[3] = 0

	def computeMinMaxSum(self, ind):
		# min max fitness
		if ind.fitness < self.fitStats[0]:
			self.fitStats[0] = ind.fitness
		if ind.fitness > self.fitStats[2]:
			self.fitStats[2] = ind.fitness

		# min max objective
		if ind.objective < self.objStats[0]:
			self.objStats[0] = ind.objective
		if ind.objective > self.objStats[2]:
			self.objStats[2] = ind.objective

		# sums
		self.fitStats[3] += ind.fitness
		self.objStats[3] += ind.objective

	def select(self):
		randFraction = self.fitStats[3] * random.random()
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

			self.xoverPMX(p1, p2, c1, c2)			
			c1.mutate(self.options)
			c2.mutate(self.options)

	def CHCGeneration(self, child):
		for i in range(0, self.options.populationSize, 2):
			x, p1 = self.select()
			x, p2 = self.select()
			c1 = self.individuals[self.options.populationSize + i]
			c2 = self.individuals[self.options.populationSize + i + 1]
			self.xoverPMX(p1, p2, c1, c2)
			c1.mutate(self.options);
			c2.mutate(self.options);
		self.halve(child)

	def comparator(self, individual):
		return individual.fitness

	def halve(self, child):
		# reset stats
		self.resetStatistics()
		for i in range(self.options.populationSize):
			# increment the statistics
			self.computeMinMaxSum(self.individuals[i])

		# evaluate new children
		for	i in range(self.options.populationSize,	self.options.populationSize	* self.options.chcLambda):
			self.individuals[i].evaluate()
			self.computeMinMaxSum(self.individuals[i])

		# compute averages
		self.fitStats[1] = self.fitStats[3] / self.options.populationSize
		self.objStats[1] = self.objStats[3] / self.options.populationSize

		# scale population
		#self.ScalePop()

		# sort the population by fitness
		self.individuals.sort (key = self.comparator, reverse = True)

		# set population to right batch size
		for i in range(self.options.populationSize):
			child.individuals[i].myCopy(self.individuals[i])

		# gather statistics
		self.evaluate(False)

	def xover1Pt(self, p1, p2, c1, c2):
		for i in range(self.eval.encodedDataLength):
			c1.chromosome[i] = p1.chromosome[i]
			c2.chromosome[i] = p2.chromosome[i]
		if random.random() < self.options.pCross:
			xp = random.randint(1, self.eval.encodedDataLength)
			for i in range(xp, self.eval.encodedDataLength):
				c1.chromosome[i] = p2.chromosome[i]
				c2.chromosome[i] = p1.chromosome[i]

	def xoverPMX(self, p1, p2, c1, c2):
		# set children to parent data
		for i in range(self.eval.encodedDataLength):
			c1.chromosome[i] = p1.chromosome[i]
			c2.chromosome[i] = p2.chromosome[i]

		# determine if crossover should happen
		if random.random() < self.options.pCross:
			# determine two points
			x1 = random.randint(1, self.eval.encodedDataLength)
			x2 = random.randint(1, self.eval.encodedDataLength)
			minX = min(x1, x2)
			maxX = max(x1, x2)

			# exchange that data inbetween points
			for i in range(minX, maxX, 1):
				c2.chromosome[i] = p1.chromosome[i]
				c1.chromosome[i] = p2.chromosome[i]

			# exchange disrupted data
			for i in range(minX, maxX, 1):
				for j in range(self.eval.encodedDataLength):
					if (j < minX or j >= maxX):
						if c1.chromosome[i] == c1.chromosome[j]:
							c1.chromosome[j] = c2.chromosome[i]
						if c2.chromosome[i] == c2.chromosome[j]:
							c2.chromosome[j] = c1.chromosome[i]

			# repair c1
			# get counts of things
			needsRemoved = []
			needsAdded = []
			for i in range(self.eval.encodedDataLength):
				counter = 0
				for j in range(self.eval.encodedDataLength):
					if c1.chromosome[j] == i:
						counter = counter + 1
				if counter > 1:
					needsRemoved.append(i)
				if counter == 0:
					needsAdded.append(i)
			
			# repair odd counts of items
			if needsRemoved != 0:
				for i in range(self.eval.encodedDataLength):
					for j in range(len(needsRemoved)):
						if c1.chromosome[i] == needsRemoved[j]:
							c1.chromosome[i] = needsAdded[j]
							needsAdded.remove(needsAdded[j])
							needsRemoved.remove(needsRemoved[j])
							break
			
			# repair c2
			# get counts of things
			needsRemoved = []
			needsAdded = []
			for i in range(self.eval.encodedDataLength):
				counter = 0
				for j in range(self.eval.encodedDataLength):
					if c2.chromosome[j] == i:
						counter = counter + 1
				if counter > 1:
					needsRemoved.append(i)
				if counter == 0:
					needsAdded.append(i)

			if needsRemoved != 0:
				# repair odd counts of items
				for i in range(self.eval.encodedDataLength):
					for j in range(len(needsRemoved)):
						if c2.chromosome[i] == needsRemoved[j]:
							c2.chromosome[i] = needsAdded[j]
							needsAdded.remove(needsAdded[j])
							needsRemoved.remove(needsRemoved[j])
							break

		return c1, c2

	def visualize(self):
		return

