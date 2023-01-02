import numpy as np
import pandas as pd
import sys
import kmeans_capi
np.random.seed(0)

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
    if (eps<=0):
        print("An Error Has Occured")
        return
    
    K = int(K)
    iter = int(iter)

    dp = create_dp(file_name_1, file_name_2)

    if inputValidation(K,iter,len(dp)) == True:
        return

    centroids, list_of_indx = create_centroids(dp, K)
    
    last_centroids = kmeans_capi.kmeans_wrap(K, iter, eps, dp, centroids, len(dp[0]), len(dp))
    
    output_print(last_centroids, list_of_indx)

    return





def create_dp(file_name_1, file_name_2):
    dp = []
    file_1 = pd.read_csv(file_name_1, header = None)
    file_2 = pd.read_csv(file_name_2,header = None)
    pandas_dp = pd.merge(left = file_1, right = file_2, left_on =  file_1.columns[0], right_on= file_2.columns[0], how = "inner", sort = True)
    pandas_dp = pandas_dp.drop(pandas_dp.columns[0],axis=1)
    dp = pandas_dp.to_numpy().tolist()
    return dp

def split_program_args():
    if(len(sys.argv)>6 or len(sys.argv)<5):
        return 0,0,0,0,0,0
    argv_len = len(sys.argv)
    if argv_len == 5:
        K = sys.argv[1]
        iter = "300"
        eps = sys.argv[2]
        file_name_1 = sys.argv[3]
        file_name_2 = sys.argv[4]
    else:
        K = sys.argv[1]
        iter = sys.argv[2] if argv_len == 6 else "300"
        eps = sys.argv[3]
        file_name_1 = sys.argv[4]
        file_name_2 = sys.argv[5]

    eps = float(eps)

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
    indx_str = ""
    for i in range(len(list_of_indx)):
        indx_str += list_of_indx[i]
        if i==len(list_of_indx)-1:
            break
        indx_str += ","
    print(indx_str)

    for x in centroids:
        line = ''
        for i in range(len(x[0])):
            if i!= 0:
                line += ","
            x[0][i] = "{:.4f}".format(x[0][i])
            line += x[0][i].__str__()
        print(line)

def first_choose (dp, list_of_indx):
    a = np.random.choice(range(1,len(dp)))
    list_of_indx.append(a-1)
    return dp[a-1]

def calc_probability (dp,centroids):
    cnt = 0
    dist=[0 for i in range(len(dp))]
    for a in dp:
        min_dist = np.inf
        for b in centroids:
            curr_dist = euclideanDistance(a,b)
            if curr_dist < min_dist:
                min_dist = curr_dist
        dist[cnt] = min_dist
        cnt +=1
    total = sum(dist)
    probability_arr = [dist[i]/total for i in range(len(dist))]
    return probability_arr

def create_centroids(dp, K):
    centroids = []
    list_of_indx = []
    centroids.append(first_choose(dp, list_of_indx))
    for i in range(K-1):
        prob_arr = calc_probability(dp, centroids)
        cen = choose_centroid(dp,centroids,prob_arr)
        centroids.append(dp[cen])
        list_of_indx.append(cen)
    return centroids, list_of_indx

def choose_centroid(dp,centroids,prob_arr):
    indx = [i for i in range(len(prob_arr))]
    cen = np.random.choice(indx, p = prob_arr)
    return cen

def euclideanDistance(x1,x2):
    d = 0
    for i in range(len(x1)):
        d += (x1[i]-x2[i])**2
    d = d**0.5
    return d

if __name__ == "__main__":
    main()
