
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
		self.maxObjective = 0
		self.evaluator = evaluator

		self.parent = Population(self.options, self.evaluator)
		self.child = Population(self.options, self.evaluator)

		# only if visualizing
		plt.ion()
		self.figure, self.axes  = plt.subplots(2)
		#self.figure.tight_layout()
		#self.axes = self.figure.add_subplot(111)
		#self.axes.set_xlabel('generation')
		#self.axes.set_ylabel('fitness')

		# initial plot data
		self.xValues = np.linspace(0, self.options.maxGen, self.options.maxGen)
		self.minGenFitness = np.linspace(0, 0, self.options.maxGen)
		self.maxGenFitness = np.linspace(0, 0, self.options.maxGen)
		self.aveGenFitness = np.linspace(0, 0, self.options.maxGen)
		self.minGenFitnessLine, = self.axes[0].plot(self.xValues, self.minGenFitness, 'b-')
		self.aveGenFitnessLine, = self.axes[0].plot(self.xValues, self.maxGenFitness, 'g-')
		self.maxGenFitnessLine, = self.axes[0].plot(self.xValues, self.aveGenFitness, 'r-') 

		self.minGenObjective = np.linspace(0, 0, self.options.maxGen)
		self.maxGenObjective = np.linspace(0, 0, self.options.maxGen)
		self.aveGenObjective = np.linspace(0, 0, self.options.maxGen)
		self.minGenObjectiveLine, = self.axes[1].plot(self.xValues, self.minGenObjective, 'b-')
		self.aveGenObjectiveLine, = self.axes[1].plot(self.xValues, self.maxGenObjective, 'g-')
		self.maxGenObjectiveLine, = self.axes[1].plot(self.xValues, self.aveGenObjective, 'r-') 


	def Init(self):
		self.parent.init()
		self.child.init()

		self.parent.evaluate()

		self.parent.statistics()
		#self.parent.report(0)

		self.visualizeRunGeneration(0, self.parent.min, self.parent.avg, self.parent.max, self.parent.minO,self.parent.avgO ,self.parent.maxO )

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

			self.visualizeRunGeneration(i, self.child.min, self.child.avg, self.child.max, self.child.minO, self.child.avgO, self.child.maxO)
			
			tmp = self.parent
			self.parent = self.child
			self.child = tmp

		print(']')
		return

	def visualizeRunGeneration(self, gen, min, ave, max, minO, aveO, maxO):
		# update data
		self.minGenFitness[gen] = min
		self.aveGenFitness[gen] = ave
		self.maxGenFitness[gen] = max

		self.minGenFitnessLine.set_ydata(self.minGenFitness)
		self.aveGenFitnessLine.set_ydata(self.aveGenFitness)
		self.maxGenFitnessLine.set_ydata(self.maxGenFitness)

		self.minGenObjective[gen] = minO
		self.aveGenObjective[gen] = aveO
		self.maxGenObjective[gen] = maxO

		self.minGenObjectiveLine.set_ydata(self.minGenObjective)
		self.aveGenObjectiveLine.set_ydata(self.aveGenObjective)
		self.maxGenObjectiveLine.set_ydata(self.maxGenObjective)
		
		# deterime if we should resize plot
		if (max > self.maxFitness):
			self.maxFitness = max;
			self.axes[0].set_ylim([0, self.maxFitness * 1.2])

		if (maxO > self.maxObjective):
			self.maxObjective = maxO
			self.axes[1].set_ylim([0, self.maxObjective * 1.2])


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
