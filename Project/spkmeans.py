import sys
import pandas as pd
import numpy as np
import myspkmeans


def main():
    funcs = ["spk","wam","ddg","gl","jacobi"]
    k, func, fileName = split_program_args()
    if func == 0:
        print("An Error Has Occurred")
        return
    # we need to check valid for k only before kmean++
    if func not in funcs:
        print("An Error Has Occurred")
        return

    df = pd.read_csv(fileName, header=None, sort = True)
    n = len(df)
    df = df.drop(df.columns[0],axis=1)
    dp = df.to_numpy().tolist()
    m = len(dp[0])

    if func == "spk":
        spk(k, dp)
    elif func == "wam":
        myspkmeans.wrap_wam(n,m,dp)
    elif func == "ddg":
        myspkmeans.wrap_ddg(n,m,dp)
    elif func == "gl":
        myspkmeans.wrap_gl(n,m,dp)
    elif func == "jacobi":
        myspkmeans.wrap_jacobi(n,dp)

def spk(k, dp):
    n = len(dp)
    m = len(dp[0])
    M = myspkmeans.warp_spk(n,m,dp)
    V = M[0:n+1]
    l = M[n+1]
    V,l = new_sort(V,l)

    if k == -1:
        k = compute_gap(l)
    
    V = np.array(V)

    final_dp = V[:,:k]

    centroids, list_of_indx = create_centroids(final_dp, k)
    
    final_res = fit(k, 300, 0.00001, final_dp, centroids,len(final_dp[0]), len(final_dp))
    
    output_print_spk(final_res, list_of_indx, k)

def new_sort(V,l):
    Vnp = np.array(V)
    lnp = np.array(l)
    l_sort_indx = np.argsort(l)
    V = Vnp[l_sort_indx]
    l = lnp[l_sort_indx]
    V = V.to_numpy().tolist()
    l = lnp.to_numpy().tolist()
    return V,l

def compute_gap(l):
    k=0
    max = -1
    for i in range(len(l)-1):
        gap = abs(l[i] - l[i+1])
        if gap > max:
            max = gap
            k = i
    if max == -1:
        print("we did a a misstake")
        return
    return k

def create_centroids(dp,k):
    val_of_indx = [i for i in range(len(dp))]
    centroids = []
    list_of_indx = []
    centroids.append(first_choose(dp, list_of_indx))
    for i in range(k-1):
        prob_arr = calc_probability(dp, centroids)
        cen , correct_indx = choose_centroid(dp,centroids,prob_arr, val_of_indx)
        centroids.append(dp[correct_indx])
        list_of_indx.append(cen)
    return centroids, list_of_indx

def choose_centroid(dp,centroids,prob_arr,val_of_indx):
    cen = np.random.choice(val_of_indx, p = prob_arr)
    correct_indx = val_of_indx.index(cen)
    return cen,correct_indx
    
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

def first_choose(dp, list_of_indx):
    a = np.random.choice(range(1,len(dp)))
    list_of_indx.append(a-1)
    return dp[a-1]

def euclideanDistance(x1,x2):
    d = 0
    for i in range(len(x1)):
        d += (x1[i]-x2[i])**2
    d = d**0.5
    return d    

def split_program_args():
    if (len(sys.argv)<2) or (len(sys.argv)>3):
        return 0,0,0
    argv_len = len(sys.argv)
    if argv_len == 4:
        k = sys.argv[1]
        func = sys.argv[2]
        fileName = sys.argv[3]
    else:
        k = -1
        func = sys.argv[1]
        fileName = sys.argv[2]

    k = int(k)
    return k, func, fileName

def output_print_spk(centroids, list_of_indx,size_of_vec):
    indx_str = ""
    for i in range(len(list_of_indx)):
        added = str(list_of_indx[i])
        indx_str += added
        if i==len(list_of_indx)-1:
            break
        indx_str += ","
    print(indx_str)

    for x in centroids:
        line = ''
        for i in range(size_of_vec):
            if i!= 0:
                line += ","
            add = x[i]
            add = "{:.4f}".format(add)
            add = str(add)
            line += add.__str__()
        print(line)
    print()

if __name__ == "__man__":
    main()



