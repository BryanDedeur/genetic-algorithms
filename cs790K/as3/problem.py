class TSP:
	def __init__(self, filePath):
		self.name = ""
		self.dimensions = 0
		self.coordinates = []

		# load from file
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
					self.coordinates.append([data[1], data[2]])
					i = i + 1