from sklearn import datasets
from sklearn.model_selection import train_test_split
import numpy as np
import random

def distance(a, b):
	#euclidean distance
	return np.sqrt(np.sum(np.power(b - a, 2)))

def find_k_neighbours(point, data, k):
	distances = np.zeros(data.shape[0])
	for i in range(len(distances)):
		distances[i] = distance(point, data[i])

	return np.argsort(distances)[:k]

def winner(votes):
	vote_count = {}
	for vote in votes:
		if vote in vote_count:
			vote_count[vote] += 1
		else:
			vote_count[vote] = 1

	candidates = []
	max_votes = max(vote_count.values())
	for vote, count in vote_count.items():
		if count == max_votes:
			candidates.append(vote)
	return random.choice(candidates)

def knn(k):
	iris = datasets.load_iris();
	x, y = iris.data, iris.target
	x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.33)

	predictions = []
	for point in x_test:
		#print("Point", str(point))
		indices = find_k_neighbours(point, x_train, k)
		#print("K-neighbours indices:", str(indices))
		#print("K-neighbours votes: ", str(y_train[indices]))
		winning_vote = winner(y_train[indices])
		#print("Winning vote:", str(winning_vote))
		predictions.append(winning_vote)

	correct = 0
	for i in range(y_test.shape[0]):
		if predictions[i] == y_test[i]:
			correct += 1

	accuracy = correct / y_test.shape[0] * 100
	print("Accuracy:", accuracy)

k = int(input("k: "))
knn(k)


