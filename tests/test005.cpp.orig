// #define HAVE_GMM

#include "LMX/lmx.h"

using namespace lmx;

int main(int argc, char** argv){

  setMatrixType(0);
  setVectorType(0);
  setLinSolverType(0);

  Vector<double> a(3);
  Vector<double> b(3);
  Vector<double> c(3);
  double norm;

  std::ofstream fout("test005.out");

  a.writeElement(1.,0);
  a.writeElement(2.,0);
  b.writeElement(3.5,1);
  
  cout << "a = " << a << std::endl;
  cout << "b = " << b << std::endl;
  fout << "a = " << a << std::endl;
  fout << "b = " << b << std::endl;

  c.add(a,b);
  cout << "a+b = " << c << std::endl;
  cout << "a+b = " << a+b << std::endl;
  fout << "a+b = " << c << std::endl;
  fout << "a+b = " << a + b << std::endl;

  c.subs(a,b);
  cout << "a-b = " << c << std::endl;
  cout << "a-b = " << a-b << std::endl;
  fout << "a-b = " << c << std::endl;
  fout << "a-b = " << a - b << std::endl;

  c.multElements(a,b);
  cout << "a(i)*b(i) = " << c << std::endl;
  cout << "a*b = " << a*b << std::endl;
  fout << "a(i)*b(i) = " << c << std::endl;
  fout << "a*b = " << a * b << std::endl;

  norm = a.norm1();
  cout << a << endl << "norm(a) = " << norm << endl;
  fout << a << endl << "norm(a) = " << norm << endl;

  fout.close();

  CompareDataFiles comparison;
  if (comparison.compareFiles("test005.out", "test005.verified")) {
	  cout << "\nSUCCESS!!" << endl;
	  return 0;
  }
  else {
	  return 1;
  }
}
