
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

		self.runCount = 0

		self.parents = Population(self.options, self.eval)
		self.children = Population(self.options, self.eval)

		self.sumFit = []
		self.sumObj = []

		# for running averages to display
		self.aveFit = []
		self.aveObj = []

		for i in range(3):
			self.sumFit.append([])
			self.sumObj.append([])
			self.aveFit.append([])
			self.aveObj.append([])
			for j in range(self.options.maxGen):
				self.sumFit[i].append(0)
				self.sumObj[i].append(0)
				self.aveFit[i].append(0)
				self.aveObj[i].append(0)


		# only if visualizing
		plt.ion()
		self.figure, self.axes  = plt.subplots(2)

		self.fitLines = []
		self.objLines = []

		xvalues = np.linspace(0, self.options.maxGen, self.options.maxGen)

		for i in range(3):
			if i == 0:
				line = 'b-'
			elif i == 1:
				line = 'g-'
			elif i == 2:
				line = 'r-'
			self.fitLines.append(self.axes[0].plot(xvalues, self.aveFit[i], line)[0])
			self.objLines.append(self.axes[1].plot(xvalues, self.aveObj[i], line)[0])

		self.axes[0].set_title('GA Ave Data Generation')
		self.axes[0].set_ylabel('Fitness')

		self.axes[1].set_xlabel('Generation')
		self.axes[1].set_ylabel('Objective')

	def Init(self):
		self.parents.init()
		self.children.init()

		self.parents.evaluate(True)

		self.statistics(self.parents, 0)
		self.visualizeRunGeneration(0)

		return

	def statistics(self, population, gen):
		#statistics
		for j in range(3):
			self.sumFit[j][gen] = self.sumFit[j][gen] + population.fitStats[j]
			self.sumObj[j][gen] = self.sumObj[j][gen] + population.objStats[j]
			self.aveFit[j][gen] = self.sumFit[j][gen] / (self.runCount + 1)
			self.aveObj[j][gen] = self.sumObj[j][gen] / (self.runCount + 1)

	def RunAllSeeds(self):
		for seed in self.options.seeds:
			self.Run(seed)

	def Run(self, seed):
		random.seed(seed)
		print(str(self.runCount + 1) + '. GA evolving on seed (' + str(seed) + '): [', end = '')
		for	g in range(self.options.maxGen):
			self.parents.CHCGeneration(self.children)

			self.statistics(self.children, g)

			# update visuals less frequently
			if (g % int(self.options.maxGen * 0.05) == 0):
				print('.', end = '')
				self.visualizeRunGeneration(g)
			
			tmp = self.parents
			self.parents = self.children
			self.children = tmp
		print(']')

		self.runCount = self.runCount + 1
		return

	def visualizeRunGeneration(self, gen):
		# plot the data
		for j in range(3):
			self.fitLines[j].set_ydata(self.aveFit[j])
			self.objLines[j].set_ydata(self.aveObj[j])
		
		# resize plot
		scaler = 0.01
		maxF = max(self.aveFit[2])
		minF = min(self.aveFit[1])

		maxO = max(self.aveObj[2])
		minO = min(self.aveObj[1])

		self.axes[0].set_ylim(minF - (minF * scaler), maxF + (maxF * scaler))
		self.axes[1].set_ylim(minO - (minO * scaler), maxO + (maxO * scaler))

		# update visuals
		self.figure.canvas.draw()
		self.figure.canvas.flush_events()

		return

	def Show(self):
		#print("SHOWING")
		plt.show(block=True)
		return

	def Save(self):
		path = os.getcwd() + '/results/' + self.name + '.png'
		print("Saving to: " + path)
		self.figure.savefig(path)
