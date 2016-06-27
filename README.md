# LSQRwithEigen

## Motivation
LSQR[1] is an algorithm for solving linear system Ax=b in least-square sense. LSQR is similar to, but is more robust on ill-conditioned problems (the condition number of A is large) than Conjugate Gradient method. Although I found several implementaions of LSQR, I want a LSQR library that can deal with matrix A and vector b defined with [Eigen](http://eigen.tuxfamily.org/index.php). 

[1] Christopher C. Paige and Michael A. Saunders. 1982. LSQR: An Algorithm for Sparse Linear Equations and Sparse Least Squares. ACM Trans. Math. Softw. 8, 1 (March 1982), 43-71. DOI=http://dx.doi.org/10.1145/355984.355989


## Requirement
Source code of Eigen 3 
( See the webpage of [Eigen](http://eigen.tuxfamily.org/index.php). )

## How to use it

1. Put the source code of Eigen 3 in the directory where you put these source codes.
2. In order to solve the linear system Ax =b, write the following code (See also *example.cpp*):

  ```
    LSQR lsqr =	LSQR(A, b, x, 1.0e-8);
  ```
  where A, b and x must be SparseMatrix<double>, VectorXd and VectorXd of Eigen.
  
3. We can get the solution by LSQR with:

  ```
    x =	lsqr.Solution();
  ```


