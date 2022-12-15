import sys

e = 0.001
convergenceCnt = 0
iterCnt = 0

def main():
    K, iter, file_name,s = split_program_args()
    if s == 0:
        print("An Error Has Occurred")
        return
    if(not K.isdigit()):
        print("Invalid number of clusters!")
        return
    if(not iter.isdigit()):
        print("Invalid maximun itertation!")
        return
    kmeans(int(K), int(iter), file_name)


def split_program_args():
    argv_len = len(sys.argv)
    if (argv_len > 4) or (argv_len < 3):
        return 0,0,0,0
    K = sys.argv[1]
    iter = sys.argv[2] if argv_len == 4 else "200"
    file_name = sys.argv[argv_len - 1]
    return K, iter, file_name, argv_len

def kmeans(K, iter=200, inputData=None):
    convergenceCnt = 0
    iterCnt = 0

    '''Sets up all the parameters'''



    '''gets all the data points from the file'''
    X = getDataPoints(inputData)

    ''' check the input'''
    N = len(X)
    if inputValidation(K,iter,N):
        return


    '''initialize centroids'''
    centroids = getCentroids(X,K)
    clusters = [[] for x in range(K)]

    
    '''the repeat loop'''
    while iterCnt < iter or convergenceCnt < K:

        #initialize empty clusters
        clusters = [[] for x in range(K)]

        for x in X: #for every data point
            min = [0,-1] #left means the number of the cluster, right -> the closest distance

            for i in range(len(centroids)): # for every centroid
                d = euclideanDistance(x,centroids[i][0]) # calcs the distances between the datapoint & the centroid
                if min[1] == -1: # the insert after the first calc
                    min = [i,d]
                elif min[1] >= d: #if we found a closer distance, we update the min
                    min[0] = i
                    min[1] = d
            clusters[min[0]].append(x) # we add x to the closest cluster

        A = updateCen(clusters,centroids,convergenceCnt) # updates centroids & check for convergence
        centroids = A[0]
        convergenceCnt = A[1]
        iterCnt += 1

    # prints the final centroids as wished
    for x in centroids:
        line = ''
        for i in range(len(x[0])):
            if i!= 0:
                line += ","
            x[0][i] = "{:.4f}".format(x[0][i])
            line += x[0][i].__str__()
        print(line)


def updateCen(clusters,centroids,convergenceCnt):    #### there is a problame here!!!!!!!!!
    oldCen = centroids
    for i in range(len(centroids)): # for every centroid
        centroids[i][0] = [0 for x in range(len(centroids[i][0]))]
        for x in clusters[i]: # for every datapoint in cluster[i]
            for j in range(len(x)):
                centroids[i][0][j] = (centroids[i][0][j] + x[j])
        centroids[i][0] = [x /len(clusters[i]) for x in centroids[i][0]]
        if euclideanDistance(centroids[i][0],oldCen[i][0]) < e and centroids[i][1] == False:
            convergenceCnt += 1
            centroids[i][1] == True
    return [centroids,convergenceCnt]

def getCentroids(X, K):
    centroids = []
    for i in range(K):
        centroids.append([X[i], False])
    return centroids

def getDataPoints(inputData):
    X = []
    f = open(inputData,"r")

    for line in f:
        line = line.strip()
        line = line.split(",")
        x = [float(y) for y in line]
        X.append(x)
    return(X)

def euclideanDistance(x1,x2):

    d = 0
    for i in range(len(x1)):
        d += (x1[i]-x2[i])**2
    d = d**0.5
    return d

def inputValidation(K,iter,N):
    if (K<=1) or (K>=N) or (K%1 != 0):
        print("Invalud number of clusters!")
        return True
    if(iter<=1) or (iter>=1000) or (iter%1 !=0):
        print("Invalid maximum interation!")
        return True
    return False

if __name__ == "__main__":
    main()
