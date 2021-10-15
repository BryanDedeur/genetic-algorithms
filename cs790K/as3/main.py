import evaluator
from ga import GA
from problem import TSP
from tour import Tour

import os.path
import sys
from os import listdir
from os import path
from os.path import isfile, join

instances = []

# get all files in directory
benchmarkPath = os.getcwd() + "/benchmarks/"

if not path.exists(benchmarkPath):
    print("Cannot find benchmarks path: ", benchmarkPath)
    sys.exit()

for filePath in listdir(benchmarkPath):
    instance = TSP(benchmarkPath + filePath)
    if (instance):
        instances.append(instance)

#for instance in instances:
eval = evaluator.Evaluator(instances[0], True)
ga = GA(eval)
ga.Init()
ga.Run(ga.options.randomSeed)
    
eval.bestTour.Print()
eval.worstTour.Print()
eval.bestTour.Show(False)
eval.worstTour.Show(True)
print('wait')


#print("Best tour: " + str(evaluator.bestTour.totalCost))