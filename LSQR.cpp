#include "stdafx.h"
#include "LSQR.h"


LSQR::LSQR(const Eigen::SparseMatrix<double> &A, const Eigen::VectorXd &b, const Eigen::VectorXd &x_ini, const double &eps)
{
	/******************************
	* Initialize
	******************************/
	x = x_ini;
	Eigen::VectorXd x_old = x_ini;

	double beta = (b - A * x_old).norm();
	Eigen::VectorXd u = (b - A * x_old) / beta;
	Eigen::VectorXd ATu = A.transpose() * u;
	double alpha = ATu.norm();
	Eigen::VectorXd v = ATu/alpha;
	Eigen::VectorXd w = v;
	double phi_bar = beta;
	double rho_bar = alpha;
	
	/***
	* Variables for stopping criteria
	****/
	double z = 0;
	double cs2 = -1;
	double sn2 = 0;
	double ddnorm = 0;
	double bnorm = beta;
	double rnorm = beta;
	double xnorm = 0;
	double xxnorm = 0;
	double Anorm = 0;
	double Acond = 0;

	int itr = 0;
	while (itr < 1000){
		
		/*************************************
		* Continue the bidiagnolization
		**************************************/
		Eigen::VectorXd rhs_beta = A *v - alpha * u;
		beta = rhs_beta.norm();
		u = rhs_beta / beta;

		Eigen::VectorXd rhs_alpha = A.transpose() * u  - beta * v;
		alpha = rhs_alpha.norm();
		v = rhs_alpha / alpha;

		/*************************************
		* Constract and apply next orthogonal transformation
		**************************************/

		double rho = sqrt(rho_bar * rho_bar + beta * beta);
		double c = rho_bar / rho;
		double s = beta / rho;
		double theta = s * alpha;
		rho_bar = -c* alpha;
		double phi = c * phi_bar;
		phi_bar = s*phi_bar;


	

		/*************************************
		* Test for convergence
		**************************************/

		double gambar = -cs2 *rho;
		double rhs = phi - sn2 * rho * z;
		double zbar = rhs / gambar;
		xnorm = sqrt(xxnorm + zbar * zbar);
		double gamma = sqrt(gambar* gambar + theta* theta);
		cs2 = gambar / gamma;
		sn2 = theta / gamma;
		z = rhs / gamma;
		xxnorm += z * z;

		
		Eigen::VectorXd rhow = (1 / rho) * w;
		ddnorm = ddnorm + rhow.norm() * rhow.norm();
		Anorm = sqrt(Anorm * Anorm + alpha * alpha + beta * beta);
		Acond = Anorm + sqrt(ddnorm);
		rnorm = phi_bar;
		double Arnorm = alpha * abs(s * phi);
		double test1 = rnorm / bnorm;
		double test2 = 0;
		double test3 = 0;
		if (Anorm == 0 || rnorm == 0){
			test2 = DBL_MAX;
		}
		else{
			test2 = Arnorm / (Anorm * rnorm);
		}
		if (Acond == 0){
			test3 = DBL_MAX;
		}
		else{
			test3 = 1 / Acond;
		}
		double t1 = test1 / (1 + Anorm*xnorm / bnorm);
		double rtol = eps + eps * Anorm * xnorm / bnorm;

		
		itr++;
		if (test1 <= rtol || test2 <= eps || test3 <= eps){
			break;
		}

		/*************************************
		* Update x, w
		**************************************/
		x = x_old + (phi / rho) * w;
		w = v - (theta / rho) * w;


		// update history of x 
		x_old = x;

	}
}


Eigen::VectorXd LSQR::SolutionX()
{
	return x;
}
