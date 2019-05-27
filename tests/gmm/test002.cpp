
#include "LMX/lmx.h"

using namespace lmx;

class SolveTest
{
public:
    SolveTest()
    {}
    ~SolveTest()
    {}
    void solve( int dim )
    {
        A.resize(0,0);
        A.resize(dim,dim);
        cout << "Solving system of " << dim << " equations... ";
        cout.flush();
        b.resize(dim);

        b.fillIdentity();
        A.fillRandom();

        LinearSystem<double> x(A,b);
        x.setInfo(0);

        {
            ExactStopwatch sw;
            sw.setQuiet();
            x.solveYourself();
            cout << sw.getTime() << endl;
        }

    }

private:
    Matrix<double> A;
    Vector<double> b;
};

int main(int argc, char* argv)
{

    setMatrixType(3);
    setVectorType(0);

    cout << "Testing Matrix type = 3 (gmm sparse)" << endl;
    int i;
    SolveTest tester;

    setLinSolverType(0);
    cout << "\n\t Solver type = 0 (direct)" << endl;
    for(i=10; i<=300; i=3*i)
    {
        tester.solve( i );
    }

    setLinSolverType(3);
    cout << "\n\t Solver type = 3 (iterative, gmres)" << endl;
    for(i=10; i<=300; i=3*i)
    {
        tester.solve( i );
    }

    return 1;
}
