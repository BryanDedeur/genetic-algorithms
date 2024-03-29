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
			lines[i] = lines[i].lower()
			if lines[i].find('name: ') != -1:
				self.name = lines[i].replace('name: ', '').replace('\n', '')
			elif lines[i].find('dimension: ') != -1:
				self.dimensions = int(lines[i].replace('dimension: ', ''))
			elif lines[i].find('node_coord_section') != -1:
				i = i + 1
				while lines[i].lower().find('eof') == -1:
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

