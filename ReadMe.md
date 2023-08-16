<h1 align="center">
  <br>
  Spectral Clustering API
  <br>
</h1>

An implementation of a Spectral Clustering algorithm using C to Python API in order to gain efficiency of computations 

<h1 align="left">
Features

### waighted adjacency matrix
for n given data points in d dimentions, it will calculate and return the waighted adjacency matrix by the exponential norm

### Diagonal Degree Matrix
for a given squered matrix size n*n - W, it will calculate and return a diagonal marix D, the (i,i)'th entry in D will be equal to 
sum(j=1,...,n) + M(i,j) and else D will be equal to zero

### Graph Laplacian
given two matrices D, W, it will calculate and return matrix L = D - W

### eigenvectors and eigenvalues
for a given matrix M, it will calculate the eigenvectors and eigenvalues and return them by running Jacobi's algorithm

### SPKmeans
for n given data points in d dimentions, it will calculate an unormalized spectral clustering algorithm by running the waighted adjacency matrix, Diagonal Degree Matrix, Graph Laplacian, eigenvectors and eigenvalues, and run kmeans++ on k eigenvectors that matches k biggest eigenvalues, as columns and returns the converged centroids.
