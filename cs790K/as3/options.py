

class Options:
	def __init__(self):
		self.populationSize = 500
		self.maxGen = 750
		self.pCross = 0.99
		self.pMut = 0.05

		self.selectionType = 'chc'
		self.crossType = 'pmx'
		self.mutType = 'invert'

		self.chcLambda = 2
		#self.seeds = {8115}
		self.seeds = {3520, 8115, 8647, 9420, 3116, 6377, 6207, 4187, 3641, 8591, 3580, 8524, 2650, 2811, 9963, 7537, 3472, 3714, 8158, 7284, 6948, 6119, 5253, 5134, 7350, 2652, 9968, 3914, 6899, 4715}

		self.resultsFile = 'results.txt'
		self.resultsDir = '/results/'


