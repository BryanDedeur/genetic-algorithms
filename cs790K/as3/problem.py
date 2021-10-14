import numpy

class TSP:
	def __init__(self, filePath):
		# variables
		self.name = ""
		self.dimensions = 0
		self.coordinates = []
		self.distances = [] # 2d euclidian distances point to all other points

		# setup
		self.loadFromFile(filePath)
		self.compute2DEucDists()

	# load from file
	def loadFromFile(self, filePath):
		print("Loading problem: " + filePath)
		file = open(filePath, 'r')
		lines = file.readlines()
		file.close()

		for i in range(len(lines)):
			if lines[i].find('NAME: ') != -1:
				self.name = lines[i].replace('NAME: ', '').replace('\n', '')
			elif lines[i].find('DIMENSION: ') != -1:
				self.dimensions = int(lines[i].replace('DIMENSION: ', ''))
			elif lines[i].find('NODE_COORD_SECTION') != -1:
				i = i + 1
				while lines[i].find('EOF') == -1:
					data = []
					for subStr in lines[i].split():
						try:
							float(subStr)
						except ValueError:
							continue
						data.append(float(subStr))
					self.coordinates.append(numpy.array((data[1], data[2])))
					i = i + 1
		return

	def compute2DEucDists(self):
		#print("Computing 2D euclidian distances for " + self.name + "...")
		for i in range(len(self.coordinates)):
			eucdists = []
			for j in range(len(self.coordinates)):
				# calculate the euclidian distance
				eucdists.append(int(numpy.linalg.norm(self.coordinates[i] - self.coordinates[j])))
			self.distances.append(eucdists)
		return

