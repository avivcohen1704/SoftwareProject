import numpy as np
from sklearn.datasets import load_iris
from sklearn.cluster import KMeans
import matplotlib.pyplot as plt
def main():

    dp = load_iris().data
    X = []
    Y = [1,2,3,4,5,6,7,8,9,10]
    centroids = []

    for i in range(10):
        kmeans  = KMeans(n_clusters=i+1, init="k-means++", random_state=0)
        kmeans.fit(dp)
        X.append(kmeans.inertia_)

    plt.plot(Y,X)

    plt.scatter(x=3,y=79,marker="o",color="red")
    plt.scatter(x=2,y=153,marker="o",color="red")
    plt.title('Elbow Method for selection of optimal "k" clusters')
    plt.ylabel("---> inertia")
    plt.xlabel("---> k")
    plt.show()


if __name__ == "__main__":
    main()
