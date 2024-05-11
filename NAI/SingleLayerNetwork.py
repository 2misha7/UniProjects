import string
import random


class Perceptron:
    def __init__(self, language):
        self.language = language
        self.weightsVector = []
        for i in range(26):
            self.weightsVector.append(random.random())
        self.learning_rate = 0.01
        self.iterations = 500
        self.bias = random.random()
        self.Emax = 0.001

    def read_data_for_perceptron(self, path):
        vectors = []
        types = []
        with open(path, encoding='utf-8') as file:
            for line in file:
                data = line.split(',',1)
                if data[0] != self.language:
                    types.append(0)
                else:
                    types.append(1)
                vectors.append(normaliseVector(countLetters(data[1])))
        return vectors, types

    def calculate_output(self, vector):
        net = 0
        for vectorEl, weightsEl in zip(vector, self.weightsVector):
            net += vectorEl * weightsEl
        net -= self.bias
        return net

    def updateBias(self, type, y_i):
        self.bias = self.bias - self.learning_rate * (type - y_i)

    def train(self, vectors, types):
        epoch = 0
        while epoch < self.iterations:
            iteration_error = 0
            for i in range(len(vectors)):
                y_i = self.calculate_output(vectors[i])
                self.weightsVector = self.updateWeights(vectors[i], types[i], y_i)
                self.updateBias(types[i], y_i)
                iteration_error += (types[i] - y_i) ** 2
            iteration_error /= len(vectors)
            if iteration_error <= self.Emax:
                break
            epoch += 1

    def updateWeights(self, vector, type, y_i):
        new_weight_vector = []
        new_input_vector = []  # only for calculations
        i = 0
        while i < len(vector):
            new_input_vector.append(vector[i] * self.learning_rate * (type - y_i))
            i += 1
        i = 0
        while i < len(self.weightsVector):
            new_weight_vector.append(self.weightsVector[i] + new_input_vector[i])
            i += 1
        return new_weight_vector



def returnLanguages(path):
    languages = set()
    with open(path, encoding='utf-8') as file:
        for line in file:
            data = line.split(',')
            languages.add(data[0])
    return languages

def countLetters(line):
    letters = {letter: 0 for letter in string.ascii_lowercase}
    for char in line.lower():
        if char in string.ascii_lowercase:
            letters[char] += 1
    return letters

def normaliseVector(lettersDictionary):
    allLettersSum = sum(lettersDictionary.values())
    normalised = [count / allLettersSum for count in lettersDictionary.values()]
    return normalised



def createPerceptrons(languages):
    perceptrons = []
    for language in languages:
        perceptrons.append(Perceptron(language))
    return perceptrons


def classify_text(text, perceptrons):
    vector = normaliseVector(countLetters(text))
    answers = {}
    for perceptron in perceptrons:
        answers[perceptron] = perceptron.calculate_output(vector)

    max_activated = max(answers, key=answers.get)
    print(max_activated.language)



def test(path, perceptrons):
    #test data
    vectors = []
    types = []
    all_cases = 0
    accurate_cases = 0
    with open(path, encoding='utf-8') as file:
        for line in file:
            data = line.split(',', 1)
            types.append(data[0])
            vectors.append(normaliseVector(countLetters(data[1])))

    for i in range(len(vectors)):
        answers = {}
        for perceptron in perceptrons:
            answers[perceptron] = perceptron.calculate_output(vectors[i])

        max_activated = max(answers, key=answers.get)
        if max_activated.language == types[i]:
            accurate_cases+=1
        all_cases+=1
        print('Output: {}, Desired output: {}'.format(max_activated.language, types[i]))

    print('Accuracy: ', accurate_cases/all_cases)




if __name__ == '__main__':
    train = input('Enter a path to a train file: ')
    testData = input('Enter a path to a test file: ')
    languages = returnLanguages(train)
    perceptrons = createPerceptrons(languages)
    for perceptron in perceptrons:
        print(perceptron.language)
        vectors, types = perceptron.read_data_for_perceptron(train)
        perceptron.train(vectors, types)
    test(testData, perceptrons)
    text = input('Enter text to classify: ')
    classify_text(text, perceptrons)
