#define HAVE_GMM
// #define HAVE_SUPERLU

#include <LMX/lmx.h>

int main(int argv, char* argc[]){

typedef lmx::Matrix<double> dMatrix;
typedef lmx::Vector<double> dVector;

if (argv>1){
	int mat_type = atoi(argc[1]);
	lmx::setMatrixType(mat_type);
	if (argv>2){
		int solver_type = atoi(argc[2]);
		lmx::setLinSolverType(solver_type);
	}
}

lmx::Matrix<double> A(1000,1000);
A.fillRandom();
dMatrix B(A);
A += B.transpose();

// A(0,0) = 1 ; A(0,1) = 3 ; A(0,2) = 6 ; A(0,3) = 8 ;
// A(1,0) = 3 ; A(1,1) = 2 ; A(1,2) = 2 ; A(1,3) = 4 ;
// A(2,0) = 6 ; A(2,1) = 2 ; A(2,2) = 2 ; A(2,3) = 4 ;
// A(3,0) = 8 ; A(3,1) = 4 ; A(3,2) = 4 ; A(3,3) = 4 ;

dVector v(1000);
v.fillIdentity();

// v(0) =  1.1 ;
// v(1) =  1.5 ;
// v(2) = -1.9 ;
// v(3) = -1.2 ;

// cout << A ;
// cout << v ;

dVector x(1000);

lmx::LinearSystem<double> lin1(A,x,v);
lin1.setInfo(2) ;
lin1.solveYourself() ;
cout << "Solution: " << endl
<< x(0) << endl;

// std::ofstream fichero("matrix.tex");
// lmx::latexPrint(fichero, "mat", A, 3);

return 1;
}
