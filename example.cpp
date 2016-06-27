#include "stdafx.h"

#define _CRT_SECURE_NO_WARNINGS

int _tmain(int argc, _TCHAR* argv[])
{
	//Matrix size m x n
	int m = 1000;
	int n = 800;

	// Determine A randomly
	Mat A = Mat::Random(m, n);
	SpMat Asp = A.sparseView();

  // Determine true x randomly
	Vec x_t = Vec::Random(n);
	
	// Determine b (= A x_t)
	Vec b = Asp * x_t;         

  

}
