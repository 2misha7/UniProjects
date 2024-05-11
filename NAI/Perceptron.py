import random

def readData(path):
    vectors = []
    typesDict = {}
    types = []
    typeNameSet = set()
    with open(path) as file:
        for line in file:
            line_data = line.strip().split(",")
            typeNameSet.add(line_data[-1])
        myTypes = list(typeNameSet)
        typesDict[0] = myTypes[0]
        typesDict[1] = myTypes[1]
    with open(path) as file:
        for line in file:
            line_data = line.strip().split(",")
            oneType = line_data[-1]
            if oneType == myTypes[1]:
                types.append(1)
            else:
                types.append(0)
            vector = [float(x) for x in line_data[:-1]]
            vectors.append(vector)
    return typesDict, vectors, types


def classifyVector(typesDict, weights, bias):
    print("Input a vector to classify, all the values must be splitted by a ' ' character")
    inpVector = input()
    vector = [int(x) for x in inpVector.split()]
    output = calculateOutput(vector, weights, bias)
    if output == 0:
        outputName = typesDict[0]
    else:
        outputName = typesDict[1]
    return outputName



def test(path, weights, bias):
    typesDict, testVectors, testTypes = readData(path)
    allAnswers = len(testVectors)
    correctAnswers = 0
    i = 0
    for vector in testVectors:
        output = calculateOutput(vector, weights, bias)
        if output == 0:
            outputName = typesDict[0]
        else:
            outputName = typesDict[1]
        if testTypes[i] == 0:
            desiredName = typesDict[0]
        else:
            desiredName = typesDict[1]
        print("Output: ", outputName, "Desired output: ", desiredName)
        if output == testTypes[i]:
            correctAnswers += 1
        i+=1
    accuracy = correctAnswers/allAnswers
    return accuracy

def generateWeights(vector):
    weightsVector = []
    for element in vector:
        weightsVector.append(random.random())
    return weightsVector

def calculateOutput(vector, weights, bias):
    net = 0
    for vectorEl, weightsEl in zip(vector, weights):
        net += vectorEl * weightsEl
    net -= bias
    output = 0
    if net >= 0:
        output = 1
    return output

def updateWeights(weightsVector, inputVector, learningRate, expectedOutput, output):
    newWeightVector = []
    newInputVector = [] #only for calculations
    i = 0
    while i < len(inputVector):
        newInputVector.append(inputVector[i] * learningRate * (expectedOutput - output))
        i+=1
    i = 0
    while i < len(weightsVector):
        newWeightVector.append(weightsVector[i] + newInputVector[i])
        i+=1
    return newWeightVector


def updateBias(bias, learningRate, expectedOutput, output):
    bias = bias - learningRate * (expectedOutput - output)
    return bias


def trainPerceptron(vectors, types, Emax):
    print("Enter a learning rate: ")
    learning_rate = float(input())
    print("Enter number of iterations: ")
    iterations = int(input())
    weights_vector = generateWeights(vectors[0])
    bias = random.random()
    epoch = 0
    while epoch < iterations:
        iterationError = 0
        for i in range(len(vectors)):
            y_i = calculateOutput(vectors[i], weights_vector, bias)
            weights_vector = updateWeights(weights_vector, vectors[i], learning_rate, types[i], y_i)
            bias = updateBias(bias, learning_rate, types[i], y_i)
            iterationError += (types[i] - y_i) ** 2
        iterationError /= len(vectors)
        print("Epoch:", epoch + 1, "Iteration Error:", iterationError)
        if iterationError <= Emax:
            break
        epoch += 1
    return weights_vector, bias





if __name__ == "__main__":
    trainPath = input("Enter a path to a train file:\n")
    testPath = input("Enter a path to a test file:\n")
    typesDict, vectors, types = readData(trainPath)
    weightVector, bias = trainPerceptron(vectors, types, 0.001)

    accuracy = test(testPath, weightVector, bias)
    print(accuracy)
    print(classifyVector(typesDict, weightVector, bias))