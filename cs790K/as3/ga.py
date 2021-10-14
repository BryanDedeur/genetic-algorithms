
import random
import options
import matplotlib.pyplot as plt
import numpy as np
import time

from evaluator import Evaluator
from population import Population

class GA:
	def __init__(self, evaluator):
		self.options = options.Options()

		self.minFitness = float('inf')
		self.maxFitness = 0
		self.evaluator = evaluator

		self.parent = Population(self.options, self.evaluator)
		self.child = Population(self.options, self.evaluator)

		# only if visualizing
		plt.ion()
		self.figure = plt.figure(1)
		self.figure.tight_layout()
		self.axes = self.figure.add_subplot(111)
		self.axes.set_xlabel('generation')
		self.axes.set_ylabel('fitness')

		# initial plot data
		self.xValues = np.linspace(0, self.options.maxGen, self.options.maxGen)
		self.minGenFitness = np.linspace(0, 0, self.options.maxGen)
		self.maxGenFitness = np.linspace(0, 0, self.options.maxGen)
		self.aveGenFitness = np.linspace(0, 0, self.options.maxGen)
		self.minGenFitnessLine, = self.axes.plot(self.xValues, self.minGenFitness, 'b-')
		self.aveGenFitnessLine, = self.axes.plot(self.xValues, self.maxGenFitness, 'g-')
		self.maxGenFitnessLine, = self.axes.plot(self.xValues, self.aveGenFitness, 'r-') 


	def Init(self):
		self.parent.init()
		self.child.init()

		self.parent.evaluate()

		self.parent.statistics()
		#self.parent.report(0)

		self.visualizeRunGenerationFitness(0, self.child.min, self.child.avg, self.child.max)

		return

	def Run(self, seed):
		random.seed(seed)
		print('GA evolving on seed (' + str(seed) + '): [', end = '')
		for	i in range(1, self.options.maxGen):
			if (i % int(self.options.maxGen * 0.05) == 0):
				print('.', end = '')
			self.parent.CHCGeneration(self.child)
			self.child.statistics()
			#self.child.report(i)

			self.visualizeRunGenerationFitness(i, self.child.min, self.child.avg, self.child.max)
			
			tmp = self.parent
			self.parent = self.child
			self.child = tmp

		print(']')
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

		self.evaluator.bestTour.Visualize(self.evaluator.bestTour.sequence)

		# update visuals
		self.figure.canvas.draw()
		self.figure.canvas.flush_events()


		#plt.plot(self.xValues, self.minGenFitness)
		#plt.draw()
		#plt.pause(0.001)

		return

	def Show(self):
		#print("SHOWING")
		plt.show(block=True)
		return
