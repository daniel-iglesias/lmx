// #define HAVE_GMM

#include "LMX/lmx.h"

using namespace lmx;

int main(int argc, char** argv){

  setMatrixType(0);
  setVectorType(0);
  setLinSolverType(0);

  Matrix<double> A(3,3);
  Vector<double> b(3);
  
  b.fillIdentity();
//  A.fillRandom();
  for (int i=0; i<3; ++i){
    for (int j=0; j<=i; ++j){
      A.writeElement(4.5+i-20./(j+1), i, j);
      A.writeElement(A(i,j), j, i);
    }
  } 
  
  LinearSystem<double> x(A,b);
  x.solveYourself();
  
  cout << A << endl << b << endl;
  cout << x.getSolution();
  
  std::ofstream fout("test002.out");
  fout << A << endl << b << endl;
  fout << x.getSolution();
  fout.close();

  if (compareFiles("test002.out", "test002.verified")) {
	  cout << "\nSUCCESS!!" << endl;
	  return 0;
  }
  else {
	  return 1;
  }
}
