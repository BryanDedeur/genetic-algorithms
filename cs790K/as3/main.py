import evaluator
from ga import GA
from problem import TSP
from tour import Tour

import os.path
import sys
from os import listdir
from os import path
from os.path import isfile, join

# get all benchmark files in directory
instances = {}
benchmarkPath = os.getcwd() + "/benchmarks/"

if not path.exists(benchmarkPath):
    print("Cannot find benchmarks path: ", benchmarkPath)
    sys.exit()

for filePath in listdir(benchmarkPath):
    instance = TSP(benchmarkPath + filePath)
    if (instance):
        fileName = os.path.splitext(os.path.basename(filePath))[0]
        instances[fileName] = instance

# get all optimal solution files in directory
solutions = {}
solutionPath = os.getcwd() + "/solutions/"

if not path.exists(solutionPath):
    print("Cannot find solutions path: ", solutionPath)
    sys.exit()

for filePath in listdir(solutionPath):
    fileName = os.path.basename(filePath).split('.')[0]
    if fileName in instances:
        solution = Tour(instances[fileName], False)
        solution.LoadFromFile(solutionPath + filePath)
        if (solution):
            solutions[fileName] = solution
            #solution.SetName(solution.tsp.name + ' optimal')
            #solution.Visualize()
            #solution.Save()
    else:
        print('Cannot find problem with matching solution name: ' + fileName)

#for instanceName, instance in instances.items():
instanceName = 'eil76'
if instanceName in solutions:
    eval = evaluator.Evaluator(instances[instanceName], True)
    ga = GA(eval, False)
    ga.SetTarget(1/solutions[instanceName].totalCost, solutions[instanceName].totalCost)
    ga.RunAllSeeds()
    ga.Save()
    
    print("Best:")
    eval.bestTour.Print()
    print("Worst:")
    eval.worstTour.Print()

    eval.bestTour.Save()
    eval.worstTour.Save()

#print("Best tour: " + str(evaluator.bestTour.totalCost))