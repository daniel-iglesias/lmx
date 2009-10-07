/***************************************************************************
 *   Copyright (C) 2007 by Daniel Iglesias   *
 *   daniel@extremo   *
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

// #define HAVE_GMM
// #define HAVE_SUPERLU

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// #include <iostream>
// #include <cstdlib>

#include"LMX/lmx.h"
#include"LMX/lmx_diff_problem_second.h"

using namespace std;

// System: qddot + K*q = f(t)
class MyDiffSystem{
  public:
    MyDiffSystem()
    {
      K.resize(2,2);
      K(0,0) = 2.;
      K(1,1) = 3.;
    }

    ~MyDiffSystem(){}

    void myEvaluation( const lmx::Vector<double>& q,
                       const lmx::Vector<double>& qdot,
                       lmx::Vector<double>& qddot,
                       double time
                     )
    {
      qddot -= K*q;
	  qddot(0) += time;
	  qddot(1) += 2*time;
    }

    void myResidue( lmx::Vector<double>& residue,
                    const lmx::Vector<double>& q,
                    const lmx::Vector<double>& qdot,
                    const lmx::Vector<double>& qddot,
                    double time
                  )
    {
      residue = qddot + K*q;
      residue(0) -= time;
      residue(1) -= 2*time;
    }

    void myTangent( lmx::Matrix<double>& tangent,
                    const lmx::Vector<double>& q,
                    const lmx::Vector<double>& qdot,
                    double partial_qdot,
                    double partial_qddot,
					double time
                  )
    {
      tangent.fillIdentity( partial_qddot );
      tangent += K;
    }

   bool myConvergence( const lmx::Vector<double>& q,
                       const lmx::Vector<double>& qdot,
                       const lmx::Vector<double>& qddot,
                       double time
                     )
  {
    lmx::Vector<double> res(qddot + K*q);
    res(0) -= time;
    res(1) -= 2*time;
    if (res.norm2() < 1e-5) return 1;
    else return 0;
  }


  private:
    lmx::Matrix<double> K;
};

int main(int argc, char** argv)
{

  lmx::setMatrixType( 0 );
  lmx::setVectorType( 0 );
  lmx::setLinSolverType( 0 );

  lmx::DiffProblemSecond< MyDiffSystem > theProblem;
  MyDiffSystem theSystem;
  lmx::Vector<double> q0(2);
  q0(0)=0.2;
  q0(1)=0.0;
  lmx::Vector<double> qdot0(2);
  qdot0(0)=0.0;
  qdot0(1)=0.0;
  
  theProblem.setDiffSystem( theSystem );
  theProblem.setIntegrator( "NEWMARK", .25, .5 );
  theProblem.setInitialConfiguration( q0, qdot0 );
  theProblem.setTimeParameters( 0, 5.0, 0.04 );
//  theProblem.setOutputFile("res.dat", 0);
  theProblem.setEvaluation( &MyDiffSystem::myEvaluation );
  theProblem.setResidue( &MyDiffSystem::myResidue );
  theProblem.setJacobian( &MyDiffSystem::myTangent );
  theProblem.setConvergence( &MyDiffSystem::myConvergence );
  theProblem.solve();
  
  return EXIT_SUCCESS;
}
