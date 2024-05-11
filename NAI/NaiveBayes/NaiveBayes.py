def calc_accuracy(true_positive, true_negative, false_positive, false_negative):
    return (true_positive + true_negative)/(true_positive + true_negative + false_positive + false_negative)

def cals_precision(true_positive, false_positive):
    return true_positive/(true_positive + false_positive)

def calc_recall(true_positive, false_negative):
    return true_positive/(true_positive + false_negative)

def calc_fmeasure(precision, recall):
    return (2*precision*recall)/(precision+recall)
def data_from_train(path):
    #save for each column a dictionary of types as keys and number of its occurencies
    #one dictionaty in data - one column in file
    data = {}
    with open(path) as file:
        for line in file:
            line_data = line.strip().split(',')
            i = 1
            #create all the dictionaries, keys - number of a column
            for element in line_data:
                data[i] = {}
                i += 1
    num_of_lines = 0

    #first-column
    with open(path) as file:
        for line in file:
            num_of_lines += 1
            line_data = line[0]
            if data[1].__contains__(line_data):
                data[1][line_data] += 1
            else:
                data[1][line_data] = 1

    #other columns split by categories
    with open(path) as file:
        for line in file:
            line_data = line.strip().split(',')
            i = 2
            for element in line_data[1:]:
                element = element + line_data[0]
                if data[i].__contains__(element):
                    data[i][element] += 1
                else:
                    data[i][element] = 1
                i+=1
    return data, num_of_lines

def find_type(data, num_of_lines, entry):
    prob_dictionary = {}
    for one_type in data[1].keys():
        prob_type = data[1][one_type]/num_of_lines
        i = 2
        for one_column in entry[1:]:
            one_column += one_type
            try:
                to_multiply = data[i][one_column] / data[1][one_type]
            except KeyError:
                categories_in_column = set()
                for category in data[i]:
                    category = category[0]
                    categories_in_column.add(category)
                to_multiply = 1/(data[1][one_type] + len(categories_in_column))
            prob_type *= to_multiply
            i += 1
        prob_dictionary[one_type] = prob_type

    result = max(prob_dictionary, key=prob_dictionary.get)
    return result


#positive - data[1][0], negative - data[1][1]
def test(path, data, num_of_lines):
    tp = 0
    tn = 0
    fp = 0
    fn = 0
    names_of_types = []
    for key in data[1].keys():
        names_of_types.append(key)

    with open(path) as file:
        for line in file:
            line_data = line.strip().split(',')
            type = find_type(data, num_of_lines, line_data)

            keys = list(data[1].keys())


            if type == keys[0]:
                if line_data[0] == keys[0]:
                    tp += 1
                elif line_data[0] == keys[1]:
                    fp += 1
            elif type == keys[1]:
                if line_data[0] == keys[1]:
                    tn += 1
                elif line_data[0] == keys[0]:
                    fn += 1


    accuracy = calc_accuracy(tp, tn, fp, fn)
    precision = cals_precision(tp, fp)
    recall = calc_recall(tp, fn)
    fmeasure = calc_fmeasure(precision, recall)
    return accuracy, precision, recall, fmeasure





if __name__ == '__main__':
    data, n = data_from_train(r'agaricus-lepiota.data')
    accuracy, precision, recall, fmeasure = test(r'agaricus-lepiota.test.data', data, n)
    print('Accuracy', accuracy)
    print('Precision', precision)
    print('Recall', recall)
    print('Fmeasure', fmeasure)






