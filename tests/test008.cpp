/***************************************************************************
 *   Copyright (C) 2007 by Daniel Iglesias                                 *
 *   daniel@extremo                                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>

#include "LMX/lmx.h"

using namespace std;

int main(int argc, char *argv[])
{
    typedef lmx::Matrix<double> dMatrix;
    typedef lmx::DenseMatrix<double> dDenseMatrix;
    typedef lmx::Vector<double> dVector;

    lmx::setMatrixType(0);

    int size=3;

    dMatrix A(size,size);
    dDenseMatrix B;
    double scalar = 10.5;

    std::ofstream fout("test008.out");

    B.resize(size,size);
    A.fillIdentity(2);
    B.fillIdentity(3);
    B(1,2) = 4.;
    B.writeElement(.5,0,1);

    dMatrix C(A);
    dDenseMatrix D;
    D.resize( C.rows(), C.cols() );

    ///////////////////////////////////////////////////////////////////////////
    // OVERLOADED OPERATORS:
    ///////////////////////////////////////////////////////////////////////////

    // Not efficient overloaded operators between Matrix<T> and DenseMatrix<T>
    cout << "A = " << A << endl;
    fout << "A = " << A << endl;
    cout << "B = " << B << endl;
    fout << "B = " << B << endl;
    cout << "A+B = " << A + B << endl;
    fout << "A+B = " << A + B << endl;
    cout << "A-B = " << A - B << endl;
    fout << "A-B = " << A - B << endl;
    cout << "A*B = " << A * B << endl;
    fout << "A*B = " << A * B << endl;

    cout << "B+A = " << B + A << endl;
    fout << "B+A = " << B + A << endl;
    cout << "B-A = " << B - A << endl;
    fout << "B-A = " << B - A << endl;
    cout << "B*A = " << B * A << endl;
    fout << "B*A = " << B * A << endl;

//   Efficient overloaded operators between Matrix<T> and DenseMatrix<T>
//   with the Matrix<T> C as lvalue
    C=-B;
    cout << "C=-B = " << C << endl;
    fout << "C=-B = " << C << endl;
    C += A + B;
    cout << "C+=A+B = " << C << endl;
    fout << "C+=A+B = " << C << endl;
    C-=B;
    cout << "C-=B = " << C << endl;
    fout << "C-=B = " << C << endl;

//   Efficient overloaded operators between DenseMatrix<T> and Matrix<T>
//   with the DenseMatrix<T> D as lvalue
    D=C;
    cout << "D = " << D << endl;
    fout << "D = " << D << endl;
    A.fillIdentity();
    D += A;
    cout << "D+=A = " << D << endl;
    fout << "D+=A = " << D << endl;
    D-=A;
    cout << "D-=A = " << D << endl;
    fout << "D-=A = " << D << endl;
    cout << "scalar = " << (scalar) << endl;
    fout << "scalar = " << (scalar) << endl;
    D *= scalar;
    cout << "D*=scalar = " << D << endl;
    fout << "D*=scalar = " << D << endl;

    // Nested operators:
    lmx::Vector<double> v(size);
    v.fillIdentity();
    double data=v*(A*B*D*C*v);
    cout << "data=v*(A*B+D*C*v) = " << data << endl;
    fout << "data=v*(A*B+D*C*v) = " << data << endl;

    ///////////////////////////////////////////////////////////////////////////
    // OPERATION SPECIALIZED MEMBER FUNCTIONS:
    ///////////////////////////////////////////////////////////////////////////

    cout << "A = " << A << endl;
    fout << "A = " << A << endl;
    cout << "B = " << B << endl;
    fout << "B = " << B << endl;
    //   Call from a Matrix Object:
    C.add(A,B);
    cout << "C.add(A,B) = " << C << endl;
    fout << "C.add(A,B) = " << C << endl;
    C.add(B,A);
    cout << "C.add(B,A) = " << C << endl;
    fout << "C.add(B,A) = " << C << endl;
    C.subs(A,B);
    cout << "C.subs(A,B) = " << C << endl;
    fout << "C.subs(A,B) = " << C << endl;
    C.subs(B,A);
    cout << "C.subs(B,A) = " << C << endl;
    fout << "C.subs(B,A) = " << C << endl;
    C.mult(A,B);
    cout << "C.mult(A,B) = " << C << endl;
    fout << "C.mult(A,B) = " << C << endl;
    C.mult(B,A);
    cout << "C.mult(B,A) = " << C << endl;
    fout << "C.mult(B,A) = " << C << endl;
    C.mult(B,D);
    cout << "C.mult(B,D) = " << C << endl;
    fout << "C.mult(B,D) = " << C << endl;
    C.multElements(A,B);
    cout << "C.multElements(A,B) = " << C << endl;
    fout << "C.multElements(A,B) = " << C << endl;
    C.multElements(B,A);
    cout << "C.multElements(B,A) = " << C << endl;
    fout << "C.multElements(B,A) = " << C << endl;
    C.multElements(B,D);
    cout << "C.multElements(B,D) = " << C << endl;
    fout << "C.multElements(B,D) = " << C << endl;

//   Call from a DenseMatrix Object:
    cout << "A = " << A << endl;
    fout << "A = " << A << endl;
    cout << "B = " << B << endl;
    fout << "B = " << B << endl;
    D.add(A,B);
    cout << "D.add(A,B) = " << D << endl;
    fout << "D.add(A,B) = " << D << endl;
    D.add(B,A);
    cout << "D.add(B,A) = " << D << endl;
    fout << "D.add(B,A) = " << D << endl;
    D.subs(A,B);
    cout << "D.subs(A,B) = " << D << endl;
    fout << "D.subs(A,B) = " << D << endl;
    D.subs(B,A);
    cout << "D.subs(B,A) = " << D << endl;
    fout << "D.subs(B,A) = " << D << endl;
    D.mult(A,B);
    cout << "D.mult(A,B) = " << D << endl;
    fout << "D.mult(A,B) = " << D << endl;
    D.mult(B,A);
    cout << "D.mult(B,A) = " << D << endl;
    fout << "D.mult(B,A) = " << D << endl;
// This cannot be done!
//  D.mult(B,D);
//  cout << "D.mult(B,D) = " << D << endl;
    D.mult(A,C);
    cout << "D.mult(A,C) = " << D << endl;
    fout << "D.mult(A,C) = " << D << endl;
    D.multElements(A,B);
    cout << "D.multElements(A,B) = " << D << endl;
    fout << "D.multElements(A,B) = " << D << endl;
    D.multElements(B,A);
    cout << "D.multElements(B,A) = " << D << endl;
    fout << "D.multElements(B,A) = " << D << endl;
    D.multElements(B,D);
    cout << "D.multElements(B,D) = " << D << endl;
    fout << "D.multElements(B,D) = " << D << endl;
    D.multElements(A,C);
    cout << "D.multElements(A,C) = " << D << endl;
    fout << "D.multElements(A,C) = " << D << endl;

    fout.close();

    lmx::CompareDataFiles comparison;
    if (comparison.compareFiles("test008.out", "test008.verified"))
    {
        cout << "\nSUCCESS!!" << endl;
        return 0;
    }
    else
    {
        return 1;
    }
}



