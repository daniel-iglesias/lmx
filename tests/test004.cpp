// #define HAVE_GMM

#include "LMX/lmx.h"

using namespace lmx;

int main(int argc, char** argv){

  setMatrixType(0);
  setVectorType(0);
  setLinSolverType(0);

  Vector<double> b(3);
  double norma2;
  
  b.writeElement(2.,0);
  b.writeElement(2.,1);
  
  norma2 = b.norm2();
  cout << b << endl << "norma:" << norma2 << endl;
  
  std::ofstream fout("test004.out");
  fout << b << endl << "norma:" << norma2 << endl;
  fout.close();

  if (compareFiles("test004.out", "test004.verified")) {
	  cout << "\nSUCCESS!!" << endl;
	  return 0;
  }
  else {
	  return 1;
  }
}
