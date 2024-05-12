import random
from collections import Counter


def read_data(path):
    data = {}
    with open(path) as file:
        i = 0
        for line in file:
            line_data = line.split(',')
            data[i] = [line_data[-1].strip(), [float(x) for x in line_data[:-1]]]
            i += 1
    return data


def pick_centroids(k, data):
    vectors = [value[-1] for value in data.values()]
    centroids = []
    for i in range(k):
        centroid = []
        for j in range(len(vectors[0])):
            random_index = random.randint(0, len(vectors) - 1)
            vector = vectors[random_index]
            centroid.append(vector[j])
        centroids.append(centroid)
    return centroids


def find_distance(centroid, vector):
    distance = 0
    for i in range(len(centroid)):
        distance += (vector[i] - centroid[i]) ** 2
    return distance


def find_average_of_vectors(vectors):
    # Initialize an accumulator for the sum of vectors
    sum_vector = [0] * len(vectors[0])
    for vector in vectors:
        sum_vector = [sum(x) for x in zip(sum_vector, vector)]
    avg_vector = [x / len(vectors) for x in sum_vector]
    return avg_vector

def k_means(k, data, centroids):
    # initial centroids
    new_centroids = []
    # initialize clusters
    clusters = [[] for _ in range(k)]


    # repeat until no example changes cluster
    repeat = True
    previous_clusters_with_id = [[] for _ in range(k)]
    it_id = 1
    while repeat:
        iteration_distance = 0
        clusters_with_id = [[] for _ in range(k)]
        # assign every entry to a cluster
        for key, value in data.items():
            distances = []
            # example vector
            vector = value[1]
            # calc dist for each centroid
            for i in range(len(centroids)):
                # calc dist from each centroid
                distance = find_distance(centroids[i], vector)
                distances.append(distance)

            ind_vector = [key, value]
            min_value = min(distances)
            min_index = distances.index(min_value)
            clusters[min_index].append(value)  # Append the value to the corresponding cluster
            clusters_with_id[min_index].append(ind_vector)
            iteration_distance += min_value

        # New centroids
        new_centroids = []
        for i in range(len(clusters)):
            # Iterate over the cluster directly
            all_entries = [entry[-1] for entry in clusters[i]]
            # Check if all_entries is not empty
            if len(all_entries) > 0:
                new_centroid = find_average_of_vectors(all_entries)
            else:
                # Keep the same centroid if no points in the cluster
                new_centroid = centroids[i]
            new_centroids.append(new_centroid)


        not_repeat = True
        # checking if vectors are in the same cluster as in previous iteration
        for i in range(len(previous_clusters_with_id)):
            id_elements_in_prev_cluster = [vector[0] for vector in previous_clusters_with_id[i]]
            id_elements_in_current_cluster = [vector[0] for vector in clusters_with_id[i]]
            prev = sorted(id_elements_in_prev_cluster)
            current = sorted(id_elements_in_current_cluster)
            if prev != current:
                not_repeat = False

        previous_clusters_with_id = clusters_with_id
        if not_repeat:
            repeat = False
        else:
            centroids = new_centroids
        print("Iteration ", it_id, ": ", iteration_distance)
        it_id += 1

    return clusters, centroids


if __name__ == '__main__':
    data = read_data(r'C:\Users\Misha\Desktop\Kmeans\iris.data')

    clusters, centroids = k_means(3, data, pick_centroids(3, data))
    id = 1
    print()
    for cluster in clusters:
        print("Cluster ", id, ":")
        all_entries = [entry[0] for entry in cluster]
        entries_counts = Counter(all_entries)
        total_entries = len(all_entries)
        entry_percentages = {entry: count / total_entries * 100 for entry, count in entries_counts.items()}
        print(entry_percentages)
        id+=1
