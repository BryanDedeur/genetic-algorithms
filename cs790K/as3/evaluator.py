
import individual

def EvaluateOneMax(individual):
	sum = 0
	for i in range(individual.chromosomeLength):
		sum += individual.chromosome[i]

	return sum

min = -5.12
precision = 1/1023

def EvaluateX2(individual):
	x = decode(individual.chromosome, 0, individual.chromosomeLength)
	val = min + precision * x
	return val * val

import math
def decode(chrom, start, end):
	sum = 0
	for i in range(start, end):
		sum += chrom[i] * math.pow(2, i-start)
	return sum
