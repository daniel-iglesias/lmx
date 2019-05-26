/***************************************************************************
 *   Copyright (C) 2005 by Daniel Iglesias                                 *
 *   https://github.com/daniel-iglesias/lmx                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef LMXDIFF_PROBLEM_DOUBLE_H
#define LMXDIFF_PROBLEM_DOUBLE_H


//////////////////////////////////////////// Doxygen file documentation entry:
    /*!
      \file lmx_diff_problem_double.h

      \brief DiffProblemDouble class implementation

      Describes a virtual class for a partitioned dynamic system with an ODE or DAE description.

      This is the base file of lmx_diff systems' manipulation and solution.

      \author Daniel Iglesias

    */
//////////////////////////////////////////// Doxygen file documentation (end)
#include <map>
#include"lmx_nlsolvers_double.h"
#include "lmx_diff_configuration.h"
#include "lmx_diff_integrator_ab.h"
#include "lmx_diff_integrator_am.h"
#include "lmx_diff_integrator_bdf.h"
#include "lmx_diff_integrator_centraldiff.h"

namespace lmx {

    /**
    \class DiffProblemDouble 
    \brief Template class DiffProblemDouble.
    Implementation for ODE system solvers.
    
    This class implements methods for defining and solving partitioned initial value problems described by a TotalDiff class' derivided object, and initial conditions in the form \f$ \dot{q}(t_o) = \dot{q}_o \f$,  \f$ q(t_o) = q_o \f$.

    @author Daniel Iglesias.
    */
template <typename Sys, typename T=double> class DiffProblemDouble{

  public:

    /** Empty constructor. */
    DiffProblemDouble()
	   : theNLSolver(0)
	   , theConfiguration1(0)
	   , theConfiguration2(0)
	   , theIntegrator1(0)
	   , theIntegrator2(0)
	   , theSystem(0)
	   , p_delta_q1(0)
	   , p_delta_q2(0)
           , b_steptriggered(0)
    {}

    /** Destructor. */
    virtual ~DiffProblemDouble()
    {}

    /**
     * @param system_in Object that defines the differential system equations.
     */
    void setDiffSystem( Sys& system_in )
    { theSystem = &system_in; }

    void setIntegrator1( int type, int opt1=0, int opt2=0 );
    void setIntegrator2( int type, int opt1=0, int opt2=0 );
    void setIntegrator1( const char* type, int opt2=0 );
    void setIntegrator2( const char* type, int opt2=0 );
    void setInitialConfiguration1( lmx::Vector<T>& q_o );
    void setInitialConfiguration2( lmx::Vector<T>& q_o, lmx::Vector<T>& qdot_o );
    void setOutputFile1( const char* filename, int diffOrder );
    void setOutputFile2( const char* filename, int diffOrder );
    void setTimeParameters( double to_in, double tf_in, double step_size_in );
//     void iterationResidue( lmx::Vector<T>& residue, lmx::Vector<T>& q_current );
    void setStepTriggered( void (Sys::* stepTriggered_in)() );
    // needs documentation:
    void setConvergence( double eps_in )
    { epsilon = eps_in; }

    // needs documentation:
    const lmx::Vector<T>& getConfiguration1( int order, int step=0)
    { return theConfiguration1->getConf( order, step ); }

    const lmx::Vector<T>& getConfiguration2( int order, int step=0)
    { return theConfiguration2->getConf( order, step ); }
    
    bool isIntegratorExplicit()
    { if(theIntegrator1 && theIntegrator2) 
      return ( this->theIntegrator1->isExplicit() 
	     * this->theIntegrator2->isExplicit() 
	     ); 
    }

    /**
     * Solve methods to be implemented in derived classes.
     */
    virtual void initialize( )=0;
    virtual void stepSolve( )=0;
    virtual void solve( )=0;

  protected:
    void writeStepFiles();

  private:
    virtual void stepSolveExplicit( ) = 0;
    virtual void stepSolveImplicit( ) = 0;

  protected:
    bool b_steptriggered; ///< 1 if stepTriggered function is set.
    lmx::NLSolverDouble<T>* theNLSolver; ///< Pointer to the NLSolver object, (auto-created).
    lmx::Configuration<T>* theConfiguration1; ///< Pointer to the Configuration object, (auto-created).
    lmx::Configuration<T>* theConfiguration2; ///< Pointer to the Configuration object, (auto-created).
    lmx::IntegratorBase<T>* theIntegrator1; ///< Pointer to the Integrator object, (auto-created).
    lmx::IntegratorBase<T>* theIntegrator2; ///< Pointer to the Integrator object, (auto-created).
    Sys* theSystem; ///< Pointer to object where the differential system is defined.
    lmx::Vector<T>* p_delta_q1; ///< Stores pointer to NLSolver increment.
    lmx::Vector<T>* p_delta_q2; ///< Stores pointer to NLSolver increment.
    double to; ///< Value of the start time stored from input.
    double tf; ///< Value of the finish time stored from input.
    double stepSize; ///< Value of the time step stored from input.
    double epsilon; ///< Value for L2 convergence.
    std::map< int, std::ofstream* > fileOutMap1; ///< collection of output streams for each diff-order requested.
    std::map< int, std::ofstream* > fileOutMap2; ///< collection of output streams for each diff-order requested.
    void (Sys::* stepTriggered)(); ///< function called at the end of each time step
};


/////////////////////////////// Implementation of the methods defined previously

/**
 * Defines the integrator that will be used for configuration advance & actualization.
 * @param type Key of integrator family to use.
 * @param opt1 Optional value for some integrators (usually specifies the order).
 * @param opt2 Optional value for some integrators.
 */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::setIntegrator1( int type, int opt1, int opt2 )
{
  switch (type) {
    case 0 : // integrator == 0 -> Adams-Bashford
      theIntegrator1 = new IntegratorAB<T>( opt1 );
    break;
      
    case 1 : // integrator == 1 -> Adams-Moulton
      theIntegrator1 = new IntegratorAM<T>( opt1 );
    break;
      
    case 2 : // integrator == 2 -> BDF
      theIntegrator1 = new IntegratorBDF<T>( opt1 );
    break;
    
    case 3 : // integrator == 2 -> BDF
      theIntegrator1 = new IntegratorCentralDifference<T>( );
    break;
  }
}

/**
 * Defines the integrator that will be used for configuration advance & actualization.
 * @param type Key of integrator family to use.
 * @param opt1 Optional value for some integrators (usually specifies the order).
 * @param opt2 Optional value for some integrators.
 */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::setIntegrator2( int type, int opt1, int opt2 )
{
  switch (type) {
    case 0 : // integrator == 0 -> Adams-Bashford
      theIntegrator2 = new IntegratorAB<T>( opt1 );
    break;
      
    case 1 : // integrator == 1 -> Adams-Moulton
      theIntegrator2 = new IntegratorAM<T>( opt1 );
    break;
      
    case 2 : // integrator == 2 -> BDF
      theIntegrator2 = new IntegratorBDF<T>( opt1 );
    break;
    
    case 3 : // integrator == 2 -> BDF
      theIntegrator2 = new IntegratorCentralDifference<T>( );
    break;
  }
}

/**
 * Defines the integrator that will be used for configuration advance & actualization.
 * @param type Key of integrator to use.
 * @param opt2 Optional value for some integrators.
 */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::setIntegrator1( const char* type, int opt2 )
{
  if (!strcmp(type, "AB-1")) theIntegrator1 = new IntegratorAB<T>( 1 );
  else if (!strcmp(type, "AB-2")) theIntegrator1 = new IntegratorAB<T>( 2 );
  else if (!strcmp(type, "AB-3")) theIntegrator1 = new IntegratorAB<T>( 3 );
  else if (!strcmp(type, "AB-4")) theIntegrator1 = new IntegratorAB<T>( 4 );
  else if (!strcmp(type, "AB-5")) theIntegrator1 = new IntegratorAB<T>( 5 );
  else if (!strcmp(type, "AM-1")) theIntegrator1 = new IntegratorAM<T>( 1 );
  else if (!strcmp(type, "AM-2")) theIntegrator1 = new IntegratorAM<T>( 2 );
  else if (!strcmp(type, "AM-3")) theIntegrator1 = new IntegratorAM<T>( 3 );
  else if (!strcmp(type, "AM-4")) theIntegrator1 = new IntegratorAM<T>( 4 );
  else if (!strcmp(type, "AM-5")) theIntegrator1 = new IntegratorAM<T>( 5 );
  else if (!strcmp(type, "BDF-1")) theIntegrator1 = new IntegratorBDF<T>( 1 );
  else if (!strcmp(type, "BDF-2")) theIntegrator1 = new IntegratorBDF<T>( 2 );
  else if (!strcmp(type, "BDF-3")) theIntegrator1 = new IntegratorBDF<T>( 3 );
  else if (!strcmp(type, "BDF-4")) theIntegrator1 = new IntegratorBDF<T>( 4 );
  else if (!strcmp(type, "BDF-5")) theIntegrator1 = new IntegratorBDF<T>( 5 );
  else if (!strcmp(type, "CD")) theIntegrator1 = new IntegratorCentralDifference<T>( );
}
/**
 * Defines the integrator that will be used for configuration advance & actualization.
 * @param type Key of integrator to use.
 * @param opt2 Optional value for some integrators.
 */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::setIntegrator2( const char* type, int opt2 )
{
  if (!strcmp(type, "AB-1")) theIntegrator2 = new IntegratorAB<T>( 1 );
  else if (!strcmp(type, "AB-2")) theIntegrator2 = new IntegratorAB<T>( 2 );
  else if (!strcmp(type, "AB-3")) theIntegrator2 = new IntegratorAB<T>( 3 );
  else if (!strcmp(type, "AB-4")) theIntegrator2 = new IntegratorAB<T>( 4 );
  else if (!strcmp(type, "AB-5")) theIntegrator2 = new IntegratorAB<T>( 5 );
  else if (!strcmp(type, "AM-1")) theIntegrator2 = new IntegratorAM<T>( 1 );
  else if (!strcmp(type, "AM-2")) theIntegrator2 = new IntegratorAM<T>( 2 );
  else if (!strcmp(type, "AM-3")) theIntegrator2 = new IntegratorAM<T>( 3 );
  else if (!strcmp(type, "AM-4")) theIntegrator2 = new IntegratorAM<T>( 4 );
  else if (!strcmp(type, "AM-5")) theIntegrator2 = new IntegratorAM<T>( 5 );
  else if (!strcmp(type, "BDF-1")) theIntegrator2 = new IntegratorBDF<T>( 1 );
  else if (!strcmp(type, "BDF-2")) theIntegrator2 = new IntegratorBDF<T>( 2 );
  else if (!strcmp(type, "BDF-3")) theIntegrator2 = new IntegratorBDF<T>( 3 );
  else if (!strcmp(type, "BDF-4")) theIntegrator2 = new IntegratorBDF<T>( 4 );
  else if (!strcmp(type, "BDF-5")) theIntegrator2 = new IntegratorBDF<T>( 5 );
  else if (!strcmp(type, "CD")) theIntegrator2 = new IntegratorCentralDifference<T>( );
}

/**
 * Defines initial conditions for first order diff. problems.
 * @param q_o Zero-order initial configuration.
 */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::setInitialConfiguration1( lmx::Vector<T>& q_o )
{
  if (theConfiguration1==0)
  theConfiguration1 = new Configuration<T>;

  theConfiguration1->setInitialCondition(0, q_o);

}

/**
 * Defines initial conditions for second order diff. problems.
 * @param q_o Zero-order initial configuration.
 * @param qdot_o First-order initial configuration.
 */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::setInitialConfiguration2( lmx::Vector<T>& q_o, lmx::Vector<T>& qdot_o )
{
  if (theConfiguration2==0)
    theConfiguration2 = new Configuration<T>;

  theConfiguration2->setInitialCondition(0, q_o);
  theConfiguration2->setInitialCondition(1, qdot_o);

  theConfiguration2->quiet();
}


/**
  * Defines which variables to store, specifing the file name for each diff-order.
  *
  * @param filename Name of file for storing variables.
  * @param diffOrder 
  */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::setOutputFile1( const char* filename, int diffOrder )
{
  if( !(fileOutMap1[diffOrder] == 0) ){
    cout << "WARNING: Changing opened file for diff order = " << diffOrder << endl;
    cout << "         New name: " << filename << endl;
    fileOutMap1[diffOrder]->open(filename);
  }
  else
    fileOutMap1[diffOrder] = new std::ofstream(filename);
}
  /**
   * Defines which variables to store, specifing the file name for each diff-order.
   *
   * @param filename Name of file for storing variables.
   * @param diffOrder 
   */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::setOutputFile2( const char* filename, int diffOrder )
{
  if( !(fileOutMap2[diffOrder] == 0) ){
    cout << "WARNING: Changing opened file for diff order = " << diffOrder << endl;
    cout << "         New name: " << filename << endl;
    fileOutMap2[diffOrder]->open(filename);
  }
  else
    fileOutMap2[diffOrder] = new std::ofstream(filename);
}



  /**
   * Defines basic time parameters.
   * 
   * @param to_in Initial time.
   * @param tf_in End time
   * @param step_size_in Prefered time step.
   */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::setTimeParameters( double to_in, double tf_in, double step_size_in )
{
  this->to = to_in;
  this->tf = tf_in;
  this->stepSize = step_size_in;
}

/**
 * When the configuration advances, this method is invoked for writing the requested diff-order values.
 */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::writeStepFiles()
{
  std::map< int, std::ofstream* >::iterator it;
  for( it = fileOutMap1.begin(); it != fileOutMap1.end(); ++it){
    it->second->setf(std::ios::scientific, std::ios::floatfield);
    it->second->precision(6);
    *(it->second) << theConfiguration1->getTime()<< "\t";
    for (unsigned int i=0; i < theConfiguration1->getConf(it->first,0).size(); ++i){
      *(it->second) << theConfiguration1->getConf(it->first,0).readElement(i) << "\t";
    }
    *(it->second) << endl;
  }
  for( it = fileOutMap2.begin(); it != fileOutMap2.end(); ++it){
    it->second->setf(std::ios::scientific, std::ios::floatfield);
    it->second->precision(6);
    *(it->second) << theConfiguration2->getTime()<< "\t";
    for (unsigned int i=0; i < theConfiguration2->getConf(it->first,0).size(); ++i){
      *(it->second) << theConfiguration2->getConf(it->first,0).readElement(i) << "\t";
    }
    *(it->second) << endl;
  }
}

  /**
   * Defines a function call between time steps.
   *
   */
template <typename Sys, typename T>
    void DiffProblemDouble<Sys,T>::setStepTriggered( void (Sys::* stepTriggered_in)() )
{
  this->stepTriggered = stepTriggered_in;
  b_steptriggered = 1;
}


}; // namespace lmx


#endif
