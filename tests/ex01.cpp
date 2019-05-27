// #define HAVE_GMM
// #define HAVE_SUPERLU

#include <LMX/lmx.h>

int main()
{

    typedef lmx::Matrix<double> dMatrix;
    typedef lmx::Vector<double> dVector;

    lmx::setMatrixType(0);
    lmx::setLinSolverType(0);

    lmx::Matrix<double> A(4,4); // igual a dMatrix A(4,4);
    dMatrix B( A.rows(), A.cols() );
    dVector v(4);

    A.fillRandom(10.);
    B.fillIdentity();
    v.fillIdentity();

    dMatrix C( A );

    cout << A*B*C << endl ;
    cout << A+B-C << endl ;
    cout << A*v << endl ;

    dVector x(4);

    lmx::solveLinear(A,x,v);
    cout << "Solution: " << endl
         << x << endl;

    std::ofstream fichero("matrix.tex");
    lmx::latexPrint(fichero, "mat", A, 3);

    return 1;
}
