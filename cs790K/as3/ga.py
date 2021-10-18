
import random
import options
import matplotlib.pyplot as plt
import numpy as np
import time

import os

from evaluator import Evaluator
from population import Population

class GA:
	def __init__(self, evaler, visualize):
		self.version = 1
		self.options = options.Options()

		self.minFitness = float('inf')
		self.maxFitness = 0
		self.maxObjective = 0
		self.eval = evaler

		self.qualityTolerance = -5
		self.runCount = 0
		self.runsNearOptimum = 0

		self.parents = Population(self.options, self.eval)
		self.children = Population(self.options, self.eval)

		self.sumQuality = 0 # percentage distance from optimum
		self.reliability = 0 # percentage of runs within quality
		self.sumSpeed = 0 # average number of evaluations needed to get within quality

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
		self.visualize = visualize
		self.CreateVisuals()
		if visualize:
			plt.ion()

	def CreateVisuals(self):
		self.figure, self.axes  = plt.subplots(2)

		self.fitLines = []
		self.objLines = []

		xvalues = np.linspace(0, self.options.maxGen, self.options.maxGen)

		for i in range(3):
			if i == 0:
				style = 'b-'
				label = 'min'
			elif i == 1:
				style = 'g-'
				label = 'ave'
			elif i == 2:
				style = 'r-'
				label = 'max'
			self.fitLines.append(self.axes[0].plot(xvalues, self.aveFit[i], style)[0])
			self.objLines.append(self.axes[1].plot(xvalues, self.aveObj[i], style)[0])
		
		self.axes[0].set_title('GA ave generation ave seed results ' + self.eval.problem.name)
		self.axes[0].set_ylabel('Fitness')

		self.axes[1].set_xlabel('Generation')
		self.axes[1].set_ylabel('Objective')

	def Init(self):
		self.parents.init()
		self.children.init()

		self.parents.evaluate(True)
		#self.children.evaluate(True)


		self.statistics(self.parents, 0)
		self.visualizeRunGeneration(0)

		return

	def SetTarget(self, fit, obj):
		self.targetFitness = fit
		self.axes[0].plot(np.linspace(0, self.options.maxGen, 2), np.linspace(fit, fit, 2), 'c-', label='optimum')
		#self.axes[0].legend()

		self.targetObjective = obj
		self.axes[1].plot(np.linspace(0, self.options.maxGen, 2), np.linspace(obj, obj, 2), 'c-', label='optimum')
		#self.axes[1].legend()


	def statistics(self, population, gen):
		#statistics
		for j in range(3):
			self.sumFit[j][gen] = self.sumFit[j][gen] + population.fitStats[j]
			self.sumObj[j][gen] = self.sumObj[j][gen] + population.objStats[j]
			self.aveFit[j][gen] = self.sumFit[j][gen] / (self.runCount + 1)
			self.aveObj[j][gen] = self.sumObj[j][gen] / (self.runCount + 1)

	def RunAllSeeds(self):
		self.Init()
		for seed in self.options.seeds:
			self.Run(seed)

	def Run(self, seed):
		random.seed(seed)
		self.parents.SetSeed(seed)
		self.children.SetSeed(seed)

		bestObjInRun = float('inf')
		self.eval.ResetCounter()
		qualityReached = False

		print(str(self.runCount + 1) + '. GA evolving on seed (' + str(seed) + '): [', end = '')
		for	g in range(self.options.maxGen):
			self.parents.CHCGeneration(self.children)

			self.statistics(self.children, g)

			# update visuals less frequently
			if (g % int(self.options.maxGen * 0.05) == 0):
				print('.', end = '')
				self.visualizeRunGeneration(g)
			
			# compute qualtiy stuff and speed stuff
			minObj = self.parents.objStats[0]
			if (minObj < bestObjInRun):
				bestObjInRun = minObj
				quality = 100 * ((self.targetObjective - bestObjInRun) / ((self.targetObjective + bestObjInRun)/2))

			if quality >= self.qualityTolerance:
				if not qualityReached:
					qualityReached = True
					self.sumSpeed += self.eval.counter

			tmp = self.parents
			self.parents = self.children
			self.children = tmp
		print(']')

		if not qualityReached:
			self.sumSpeed += self.eval.counter

		self.visualizeRunGeneration(g)

		self.sumQuality += quality # percentage distance from optimum
		
		if quality >= self.qualityTolerance:
			self.runsNearOptimum += 1

		self.runCount += 1

		if (self.runsNearOptimum > 0):
			self.reliability = self.runCount / self.runsNearOptimum # percentage of runs within quality

		return

	def plotData(self):
		# plot the data
		for j in range(3):
			self.fitLines[j].set_ydata(self.aveFit[j])
			self.objLines[j].set_ydata(self.aveObj[j])
		
		# resize plot
		scaler = 0.1
		maxF = max(self.aveFit[2])
		maxF = max(maxF, self.targetFitness)
		minF = min(self.aveFit[0])

		maxO = max(self.aveObj[2])
		minO = min(self.aveObj[0])
		minO = max(minO, self.targetObjective)

		self.axes[0].set_ylim(minF - ((maxF-minF) * scaler), maxF + ((maxF-minF) * scaler))
		self.axes[1].set_ylim(minO - ((maxO-minO) * scaler), maxO + ((maxO-minO) * scaler))

	def visualizeRunGeneration(self, gen):
		self.plotData()

		# update visuals
		self.figure.canvas.draw()
		self.figure.canvas.flush_events()

		# update eval visuals
		self.eval.bestTour.Visualize()
		self.eval.worstTour.Visualize()

		return

	def getHeaderString(self, delim, ending):
		return (
			 'ga version' + delim +
			 'problem' + delim +
			 'pop size' + delim +
			 'num gens' + delim +
			 'selection' + delim +
			 'cross' + delim +
			 'p-cross' + delim +
			 'mutate' + delim +
			 'p-mutate' + delim +
			 'runs' + delim + 
			 'quality' + delim +
			 'reliability' + delim +
			 'speed' + ending
		 )

	def getParamsString(self, delim, ending):
		return (
			 str(self.version) + delim +
			 str(self.eval.problem.name) + delim +
			 str(self.options.populationSize) + delim +
			 str(self.options.maxGen) + delim +
			 self.options.selectionType + delim +
			 self.options.crossType + delim +
			 str(self.options.pCross) + delim +
			 self.options.mutType + delim +
			 str(self.options.pMut) + delim +
			 str(self.runCount) + delim +
			 str(self.sumQuality / self.runCount) + delim +
			 str(self.reliability) + delim +
			 str(self.sumSpeed / self.runCount) + ending
		 )

	def Save(self):
		# results
		resultsPath = os.getcwd() + self.options.resultsDir + self.options.resultsFile
		print("Saving results to: " + resultsPath)

		resultsFile = open(resultsPath, "a") 
		# if empty
		if os.path.exists(resultsPath) and os.stat(resultsPath).st_size == 0:
			resultsFile.write(self.getHeaderString('\t', '\n'))
		resultsFile.write(self.getParamsString('\t', '\n'))
		resultsFile.close()

		# visuals
		self.plotData()
		visualsPath = os.getcwd() + self.options.resultsDir + self.eval.problem.name + '.png'
		self.figure.savefig(visualsPath)

	def Show(self):
		#print("SHOWING")
		plt.show()
		return