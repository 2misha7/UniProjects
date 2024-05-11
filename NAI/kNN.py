# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.


import math
import matplotlib.pyplot as plt
from collections import Counter

import numpy as np


def kNNClassifier(k, trainSet, testSet):
    trainData = readFromFile(trainSet)
    testData = readFromFile(testSet)
    allCases = 0
    correctCases = 0
    for testKey, testInstance in testData.items():
        for oneTestCase in testInstance:
            distances = []
            for trainKey, trainInstance in trainData.items():
                for oneTrainCase in trainInstance:
                    resultPair = [findDistance(oneTrainCase, oneTestCase), trainKey]
                    distances.append(resultPair)
            distances.sort()
            kClosest = [pair[1] for pair in distances[:k]]
            most_frequent= max(set(kClosest), key=kClosest.count)
            if most_frequent == testKey:
                 correctCases += 1
            allCases += 1
    accuracy = correctCases / allCases
    return accuracy


def classifyVector(k, trainSet, vector):
    trainData = readFromFile(trainSet)
    distances = []
    for trainKey, trainInstance in trainData.items():
        for oneTrainCase in trainInstance:
            resultPair = [trainKey, findDistance(oneTrainCase, vector)]
            distances.append(resultPair)
    distances.sort(key=lambda x: x[1])
    kClosest = [pair[0] for pair in distances[:k]]
    most_frequent = Counter(kClosest).most_common(1)[0][0]
    print(most_frequent)

def findDistance(vector1, vector2):
    sum_squares = 0
    for i in range(len(vector1)):
        sum_squares += (float(vector1[i]) - float(vector2[i])) ** 2
    dist = math.sqrt(sum_squares)
    return dist

def readFromFile(path):
    data = {}
    with open(path) as file:
        for line in file:
            lineData = line.strip().split(",")
            key = lineData[-1]
            if key not in data:
                data[key] = []
            data[key].append(lineData[:-1])
    return data

def drawGraph(trainSet, testSet):

    k = []
    accuracy = []

    with open(trainSet, 'r') as file:
        line_count = sum(1 for line in file)
    k = np.arange(1, line_count + 1)
    i = 0
    for kValue in k:
        acc = kNNClassifier(kValue,trainSet, testSet)
        print(acc)
        accuracy.append(acc)
        i+=1

    plt.plot(k, accuracy)
    plt.xlabel('k')
    plt.ylabel('Test Accuracy')
    plt.show()



if __name__ == '__main__':
    print("Type 1 if you want to find an accuracy\n"
          "Type 2 if you want to classify a vector\n")
    choice = input()
    if int(choice) == 1:
        print("Input a path to a file with a train set")
        trainSet = input()
        print("Input a path to a file with a test set")
        testSet = input()
        print("Input a value of k")
        k = int(input())
        print(kNNClassifier(k, trainSet, testSet))
    elif int(choice) == 2:
        print("Input a path to a file with a train set")
        trainSet = input()
        print("Input a vector to classify, all the values must be splitted by a ' ' character")
        inpVector = input()
        vector = [int(x) for x in inpVector.split()]
        print("Input a value of k")
        k = int(input())
        classifyVector(k, trainSet, vector)
    else:
        print("Goodbye")