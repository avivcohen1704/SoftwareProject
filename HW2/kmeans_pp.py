import numpy as np
import pandas as pd
import sys

def main():
    K, iter, eps, file_name_1, file_name_2, s = split_program_args()
    if (s == 0):
        print("An Error Has Occured")
        return
    if (not K.isdigit()):
        print("Invalid number of clusters!")
        return
    if (not iter.isdigit()):
        print("Invalid maximun itertation!")
        return
    if(eps<=0):
        print("An Error Has Occured")
        return

def create_dp(file_name_1, file_name_2):
    dp = []
    file_1 = pd.read_csv(file_name_1, header = None)
    file_2 = pd.read_csv(file_name_2,header = None)
    pandas_dp = pd.merge(left = file_1, right = file_2, left_on =  file_1.columns[0], right_on= file_2.columns[0], how = "inner", sort = True)
    dp = pandas_dp.to_numpy().tolist()
    return dp

def split_program_args():
    if(len(sys.argv)>6 or len(sys.argv)<5):
        return 0,0,0,0,0,0
    argv_len = len(sys.argv)
    K = sys.argv[1]
    iter = sys.argv[2] if argv_len == 6 else "300"
    eps = sys.argv[3]
    file_name_1 = sys.argv[4]
    file_name_2 = sys.argv[5]
    return K, iter, eps, file_name_1, file_name_2, argv_len

def inputValidation(K,iter,N):
    if (K<=1) or (K>=N) or (K%1 != 0):
        print("Invalud number of clusters!")
        return True
    if(iter<=1) or (iter>=1000) or (iter%1 !=0):
        print("Invalid maximum interation!")
        return True
    return False

def output_print(centroids, list_of_indx):
    for i in range(len(list_of_indx)):
        print(list_of_indx[i], ", ")
    for x in centroids:
        line = ''
        for i in range(len(x[0])):
            if i!= 0:
                line += ","
            x[0][i] = "{:.4f}".format(x[0][i])
            line += x[0][i].__str__()
        print(line)

def first_choose (dp):
    np.random.seed(0)
    a = np.random.randint(low=0, high=len(dp))
    return dp[a]

def calc_probability (dp,centroids):
    cnt = 0
    dist=[0 for i in range(len(dp))]
    min_dist= np.inf
    for a in dp:
        for b in centroids:
            curr_dist = euclideanDistance(a,b)
            if curr_dist < min_dist:
                min_dist = curr_dist
        dist[cnt] += min_dist
        cnt +=1
    probability_arr = [dist[i]/sum(dist) for i in range(len(dist))]
    return probability_arr

def create_centroids(dp, K):
    centroids = []
    copy_dp = dp.copy()
    centroids.append(first_choose(copy_dp))
    for i in range(K-1):
        prob_arr = calc_probability(copy_dp, centroids)
        centroids.append(choose_centroid(copy_dp,centroids,prob_arr))
        copy_dp.remove(centroids[len(centroids)-1])

def choose_centroid(dp,centroids,prob_arr):
    return 0

def euclideanDistance(x1,x2):
    d = 0
    for i in range(len(x1)):
        d += (x1[i]-x2[i])**2
    d = d**0.5
    return d


print(np.random.choice(5, 3, p=[0.1, 0, 0.3, 0.6, 0]))

