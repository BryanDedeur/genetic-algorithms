import os.path
import sys

from ga import GA
from os import listdir
from os import path
from os.path import isfile, join
from problem import TSP

instances = []

# get all files in directory
benchmarkPath = os.getcwd() + "/cs790K/as3/benchmarks/"

if not path.exists(benchmarkPath):
    print("Cannot find benchmarks path: ", benchmarkPath)
    sys.exit()

for filePath in listdir(benchmarkPath):
    instance = TSP(benchmarkPath + filePath)
    if (instance):
        instances.append(instance)

ga = GA()
ga.Init()
ga.Run()