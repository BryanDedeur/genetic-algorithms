
import random
import options
import matplotlib.pyplot as plt
import numpy as np
import time

from population import Population

class GA:
	def __init__(self):
		self.options = options.Options()
		random.seed(self.options.randomSeed)

		self.minFitness = float('inf')
		self.maxFitness = 0

		# only if visualizing
		plt.ion()
		self.figure = plt.figure()
		self.figure.tight_layout()
		self.axes = self.figure.add_subplot(111)
		self.axes.set_xlabel('generation')
		self.axes.set_ylabel('fitness')

		
		# initial plot data
		x = np.linspace(0, self.options.maxGen, self.options.maxGen)
		self.minGenFitness = np.linspace(0, 0, self.options.maxGen)
		self.maxGenFitness = np.linspace(0, 0, self.options.maxGen)
		self.aveGenFitness = np.linspace(0, 0, self.options.maxGen)
		self.minGenFitnessLine, = self.axes.plot(x, self.minGenFitness, 'b-')
		self.aveGenFitnessLine, = self.axes.plot(x, self.maxGenFitness, 'g-')
		self.maxGenFitnessLine, = self.axes.plot(x, self.aveGenFitness, 'r-') 


	def Init(self):
		self.parent = Population(self.options)
		self.parent.evaluate()
		self.parent.statistics()
		self.parent.report(0)

		self.child = Population(self.options)
		self.visualizeRunGenerationFitness(0, self.child.min, self.child.avg, self.child.max)

		return

	def Run(self):
		for	i in range(1, self.options.maxGen):
			self.parent.CHCGeneration(self.child)
			self.child.statistics()
			self.child.report(i)

			self.visualizeRunGenerationFitness(i, self.child.min, self.child.avg, self.child.max)
			
			tmp = self.parent
			self.parent = self.child
			self.child = tmp

		return

	def visualizeRunGenerationFitness(self, gen, min, ave, max):
		# update data
		self.minGenFitness[gen] = min
		self.aveGenFitness[gen] = ave
		self.maxGenFitness[gen] = max

		self.minGenFitnessLine.set_ydata(self.minGenFitness)
		self.aveGenFitnessLine.set_ydata(self.aveGenFitness)
		self.maxGenFitnessLine.set_ydata(self.maxGenFitness)
		
		# deterime if we should resize plot
		if (max > self.maxFitness):
			self.maxFitness = max;
			self.axes.set_ylim([0, self.maxFitness * 1.2])

		# update visuals
		self.figure.canvas.draw()
		self.figure.canvas.flush_events()

		return

