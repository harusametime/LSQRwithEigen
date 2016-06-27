#include "stdafx.h"
#include "./Eigen/Eigen/Dense"
#include "./Eigen/Eigen/Sparse"
#include <iostream>
#include "LSQR.h"

#define _CRT_SECURE_NO_WARNINGS

int _tmain(int argc, _TCHAR* argv[])
{
	//Matrix size m x n
	int m = 200;
	int n = 100;

	// Determine A randomly
	Eigen::MatrixXd A = Eigen::MatrixXd::Random(m, n);
	
	Eigen::SparseMatrix<double> Asp = A.sparseView();

	// Determine true minimizer x randomly
	Eigen::VectorXd x_t = Eigen::VectorXd::Random(n);

	// Determine b (= A x_t)
	Eigen::VectorXd b = Asp * x_t;
	
	// Minimizer x
	Eigen::VectorXd x(n);
	x.setZero();

	//Run LSQR
	LSQR lsqr = LSQR(Asp, b, x, 1.0e-8);

	x = lsqr.SolutionX();


	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "Solution obtained by LSQR" << std::endl;
	std::cout << "--------------------------------------------" << std::endl;

	for (int i = 0; i < x.rows(); i++){
		std::cout << x(i) << std::endl;
	}

	std::cout << "--------------------------------------------" << std::endl;
	std::cout << "Ground Truth" << std::endl;
	std::cout <<"--------------------------------------------" << std::endl;

	for (int i = 0; i < x.rows(); i++){
		std::cout << x_t(i) << std::endl;
	}

}
