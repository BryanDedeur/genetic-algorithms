
import random
import options
import matplotlib.pyplot as plt
import numpy as np
import time

from evaluator import Evaluator
from population import Population

class GA:
	def __init__(self, evaler):
		self.options = options.Options()

		self.minFitness = float('inf')
		self.maxFitness = 0
		self.maxObjective = 0
		self.eval = evaler

		self.parent = Population(self.options, self.eval)
		self.child = Population(self.options, self.eval)

		self.sumFit = []
		self.sumObj = []

		for i in range(3):
			self.sumFit.append([])
			self.sumObj.append([])
			for j in range(self.options.maxGen):
				self.sumFit[i].append(0)
				self.sumObj[i].append(0)


		# only if visualizing
		plt.ion()
		self.figure, self.axes  = plt.subplots(2)

		self.fitLines = []
		self.objLines = []

		xvalues = np.linspace(0, self.options.maxGen, self.options.maxGen)
		tempyvalues = np.linspace(0, 0, self.options.maxGen)

		for i in range(3):
			if i == 0:
				line = 'b-'
			elif i == 1:
				line = 'g-'
			elif i == 2:
				line = 'r-'
			self.fitLines.append(self.axes[0].plot(xvalues, tempyvalues, line)[0])
			self.objLines.append(self.axes[1].plot(xvalues, tempyvalues, line)[0])

		self.axes[0].set_title('GA Ave Data Generation')
		self.axes[0].set_ylabel('Fitness')

		self.axes[1].set_xlabel('Generation')
		self.axes[1].set_ylabel('Objective')

	def Init(self):
		self.parent.init()
		self.child.init()

		self.parent.evaluate()

		self.parent.statistics()
		#self.parent.report(0)

		self.visualizeRunGeneration(0)

		return

	def Run(self, seed):
		random.seed(seed)
		print('GA evolving on seed (' + str(seed) + '): [', end = '')
		for	i in range(self.options.maxGen):
			if (i % int(self.options.maxGen * 0.05) == 0):
				print('.', end = '')
			self.parent.CHCGeneration(self.child)
			self.child.statistics()
			#self.child.report(i)

			self.sumFit[0][i] = self.sumFit[0][i] + self.child.min
			self.sumFit[1][i] = self.sumFit[1][i] + self.child.avg
			self.sumFit[2][i] = self.sumFit[2][i] + self.child.max

			self.sumObj[0][i] = self.sumObj[0][i] + self.child.minO
			self.sumObj[1][i] = self.sumObj[1][i] + self.child.avgO
			self.sumObj[2][i] = self.sumObj[2][i] + self.child.maxO

			self.visualizeRunGeneration(i)
			
			tmp = self.parent
			self.parent = self.child
			self.child = tmp

		print(']')
		return

	def visualizeRunGeneration(self, gen):
		# update data

		for j in range(3):
			y1 = self.sumFit[j]
			y2 = self.sumObj[j]

			for i in range(self.options.maxGen):
				if i <= gen:
					y1[i] = y1[i] / (gen + 1);
					y2[i] = y2[i] / (gen + 1);
				elif gen > 0:
					y1[i] = y1[i] / (gen);
					y2[i] = y2[i] / (gen);

			self.fitLines[j].set_ydata(self.sumFit[j])
			self.objLines[j].set_ydata(self.sumObj[j])
		
		# resize plot
		if (self.sumFit[2][gen] / (gen + 1) > self.maxFitness):
			self.maxFitness = self.sumFit[2][gen] / (gen + 1);
			self.axes[0].set_ylim([0, self.maxFitness * 1.2])

		if (self.sumObj[2][gen] / (gen + 1) > self.maxObjective):
			self.maxObjective = self.sumObj[2][gen] / (gen + 1)
			self.axes[1].set_ylim([0, self.maxObjective * 1.2])

		# update visuals
		self.figure.canvas.draw()
		self.figure.canvas.flush_events()

		return

	def Show(self):
		#print("SHOWING")
		plt.show(block=True)
		return
