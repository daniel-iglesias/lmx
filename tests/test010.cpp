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

#include "LMX/lmx.h"
#include "LMX/lmx_nlsolvers.h"

using namespace lmx;

class MyExternalSystem
{
public:
    MyExternalSystem() {}

    ~MyExternalSystem() {}

    void residuo(lmx::Vector<double>& res_in, lmx::Vector<double>& q_in)
    {
        // x_i^3 = lhs_i
        if ( lhs.size() == 0 )
        {
            temp.resize(res_in.size());
            lhs.resize(res_in.size());
            for (int i=0; i<lhs.size(); ++i)
                lhs.writeElement( std::pow(i+1.,6), i); // lhs_i = i^6
        }
        temp.multElements( q_in, q_in ); //(x_i)^2
        res_in.multElements( temp, q_in ); //(x_i)^3
        res_in -= lhs;
    }

    void jacobiano(lmx::Matrix<double>& jac_in, lmx::Vector<double>& q_in)
    {
        for (int i=0; i<q_in.size() ; ++i)
            jac_in.writeElement( 3.*q_in.readElement(i)*q_in.readElement(i), i, i);
    }

    bool convergence( lmx::Vector<double>& res_in )
    {
        if (res_in.norm1() < 0.001) return 1;
        else return 0;
    }

private:
    lmx::Vector<double> lhs;
    lmx::Vector<double> temp;
};

int main(int argc, char** argv)
{
    std::ofstream fout("test010.out");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(fout.rdbuf()); //redirect std::cout to fout

    setMatrixType(0);
    setVectorType(0);
    setLinSolverType(0);

    Vector<double> b(3);

    b.fillIdentity();

    MyExternalSystem theSystem;
    lmx::NLSolver<MyExternalSystem> theSolver;
    theSolver.setInitialConfiguration( b );

    theSolver.setSystem( theSystem );
    theSolver.setResidue( &MyExternalSystem::residuo );
    theSolver.setJacobian( &MyExternalSystem::jacobiano );
    theSolver.setConvergence( &MyExternalSystem::convergence );
    theSolver.solve( 100 );
    cout << "Result: " << theSolver.getSolution() << endl;

    std::cout.rdbuf(coutbuf); //reset to standard output again
    fout.close();
    std::ifstream fin("test010.out");
    std::string line;

    while(std::getline(fin, line))  //input from the file fin
       {
           std::cout << line << "\n";   //output to stdout
       }

    lmx::CompareDataFiles comparison;
    if (comparison.compareFiles("test010.out", "test010.verified"))
    {
        cout << "\nSUCCESS!!" << endl;
        return 0;
    }
    else
    {
        return 1;
    }
}


