// Copyright (c) 1997-2001  ETH Zurich (Switzerland).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
// 
//
// Author(s)     : Sven Schoenherr <sven@inf.fu-berlin.de>
//                 Bernd Gaertner <gaertner@inf.ethz.ch>
//                 Franz Wessendorp <fransw@inf.ethz.ch>
//                 Kaspar Fischer <fischerk@inf.ethz.ch>

#ifndef CGAL_QP_PRICING_STRATEGY_H
#define CGAL_QP_PRICING_STRATEGY_H

// includes
#include <CGAL/QP_solver.h>
#include <CGAL/IO/Verbose_ostream.h>

#include <string>

CGAL_BEGIN_NAMESPACE

// ==================
// class declarations
// ==================
template < class Rep_ >
class QP_pricing_strategy;

template < class Rep_ >
class QP_solver;

// ===============
// class interface
// ===============
template < class Rep_ >
class QP_pricing_strategy {

  public:

    // self
    typedef  Rep_                       Rep;
    typedef  QP_pricing_strategy<Rep>  Self;

    // types
    typedef  typename Rep::ET           ET;
    typedef  CGAL::QP_solver<Rep>      QP_solver;
    typedef  CGAL::Verbose_ostream      Verbose_ostream;
    typedef  typename Rep::Is_in_standard_form
                                        Is_in_standard_form;
    typedef  typename Rep::Is_linear    Is_linear;
    typedef typename QP_solver::Bound_index Bound_index;

  public:

    // initialization
    void  set ( const QP_solver& solver, Verbose_ostream& vout);
    void  init( int dummy);

    // operations
    virtual  int   pricing(int& direction ) = 0;

    virtual  void  leaving_basis( int i) { }
    virtual  void  transition( ) { }
    
  protected:
    
    // construction & destruction
    QP_pricing_strategy( const std::string& strategy_name);
public:
    virtual ~QP_pricing_strategy( ) { }
protected:
    QP_pricing_strategy( );            // detects error in virtual inheritance
        
    // initialization (of derived classes)
    virtual  void  set ( ) { }
    virtual  void  init( ) { }
    
    // operations
    ET  mu_j( int j) const;

    // access
    const QP_solver&  solver( ) const { return *solverP; }
    Verbose_ostream&  vout  ( ) const { return *voutP;   }

    // constants (protected)
    const ET  et0;

    // used during pricing loop; finds out whether j is a
    // new best candidate for the entering variable w.r.t.
    // Dantzig's pivot rule (reduced cost pricing); the
    // return value is true iff j is the new best candidate
    template <typename NT>
    bool price_dantzig (int j, const NT& mu, const NT& nt0,
		     int& min_j, NT& min_mu, int& direction);

    // returns whether j satisfying mu_j = mu is a candidate
    // for the entering variable
    template <typename NT>
    bool is_improving (int j, const NT& mu, const NT& nt0) const;

  private:

    // data members
    const QP_solver*  solverP;          // the ambient QP solver
    Verbose_ostream*  voutP;            // used for verbose output
    std::string       name;             // derived strategy's name
};

// ----------------------------------------------------------------------------

// =============================
// class implementation (inline)
// =============================

// construction
template < class Rep_ >  inline
QP_pricing_strategy<Rep_>::
QP_pricing_strategy( const std::string& strategy_name)
    : et0( 0), name( strategy_name)
{ }

// detects error in virtual inheritance
template < class Rep_ >  inline
QP_pricing_strategy<Rep_>::
QP_pricing_strategy( )
  : et0(0)
{
    CGAL_qpe_assertion_msg( false, "call to 'QP_pricing_strategy<Rep>::\n'" \
	"QP_pricing_strategy( const std::string&  strategy_name)'\n" \
	"is missing in most derived pricing class!");
}

// initialization
template < class Rep_ >  inline
void  QP_pricing_strategy<Rep_>::
set( const QP_solver&  solver, Verbose_ostream&  vout)
{
    solverP = &solver;
    voutP   = &vout;
    set();
}

template < class Rep_ >  inline
void  QP_pricing_strategy<Rep_>::
init( int)
{
    CGAL_qpe_debug {
	vout() << "pricing: " << name << std::endl;
    }
    init();
}

// operations
template < class Rep_ >  inline
typename Rep_::ET  QP_pricing_strategy<Rep_>::
mu_j( int j) const
{
  return this->solver().mu_j(j);
}

template < class Rep_ >
template <typename NT> 
bool  QP_pricing_strategy<Rep_>::
is_improving (int j, const NT& mu, const NT& nt0 ) const
{  
  CGAL_qpe_precondition(!this->solver().is_basic(j));
  CGAL_qpe_precondition(!this->solver().is_artificial(j));
  if (this->solver().is_original(j)) {
    const Bound_index bnd_ind =
      this->solver().nonbasic_original_variable_bound_index(j);
    switch (bnd_ind) {
    case QP_solver::LOWER:
      return mu < nt0;
    case QP_solver::UPPER:
      return mu > nt0;
    case QP_solver::ZERO:	
      const int where =
	  this->solver().state_of_zero_nonbasic_variable(j);
      return (where >= 0 && mu > nt0 || where <= 0 && mu < nt0);
    case QP_solver::FIXED:
      return false;
    case QP_solver::BASIC:
    default:
      CGAL_qpe_assertion(false);
      return false;
    }
  } else {
    // artficial variable
    return mu < nt0;
  }
}

template < class Rep_ >
template <typename NT> 
bool QP_pricing_strategy<Rep_>::
price_dantzig (int j, const NT& mu, const NT& nt0,
	 int& min_j, NT& min_mu, int& direction) {
  CGAL_qpe_precondition(!this->solver().is_basic(j));
  CGAL_qpe_precondition(!this->solver().is_artificial(j));
  if (this->solver().is_original(j)) {
    // original variable
    const Bound_index bnd_ind =
      this->solver().nonbasic_original_variable_bound_index(j);
    switch (bnd_ind) {
    case QP_solver::LOWER:
      {
	CGAL_qpe_debug { 
	  this->vout() << "mu_" << j << ": " << mu
		       << " LOWER" << std::endl;
	}
	    
	if (mu < nt0) {
	  // new minimum?
	  if (mu < min_mu) {
	    min_j = j; min_mu = mu;
	    direction = 1;
	  }
	}
	break;
      }
    case QP_solver::ZERO:
      {
	// determine whether the variable is on lower or upper bound, or
	// somewhere it the middle:
	//
	// Note: it cannot be both on the lower and upper bound (as it is
	// not FIXED).
	const int where =
	  this->solver().state_of_zero_nonbasic_variable(j);
	    
	CGAL_qpe_debug { 
	  this->vout() << "mu_" << j << ": " << mu
		       << " ZERO " 
		       << (where == -1? "(LOWER)" : 
			   (where == 0? "(MIDDLE)" : "(UPPER)"))
		       << std::endl;
	}
	    
	if (where >= 0 &&       // middle or on upper bound?
	    mu > nt0) {
	  // new minimum?
	  if (-mu < min_mu) {
	    min_j = j; min_mu = -mu;
	    direction = -1;
	  }                                                    
	}
	if (where <= 0 &&       // middle or on lower bound?
	    mu < nt0) {
	  // new minimum?
	  if (mu < min_mu) {
	    min_j = j; min_mu = mu;
	    direction = 1;
	  }                            
	}
	break;
      }
    case QP_solver::UPPER:
      {
	CGAL_qpe_debug { 
	  this->vout() << "mu_" << j << ": " << mu
		       << " UPPER" << std::endl;
	}
	    
	if (mu > nt0) {
	  // new minimum?
	  if (-mu < min_mu) {
	    min_j = j; min_mu = -mu;
	    direction = -1;
	  }
	}                    
	break;
      }
    case QP_solver::FIXED:
      CGAL_qpe_debug {
	this->vout() << "Fixed variable " << j << std::endl;
      }
      break;
    case QP_solver::BASIC:
      CGAL_qpe_assertion(false);
      break;
    } 
  } else {                                    
    // slack variable
    CGAL_qpe_debug {
      this->vout() << "mu_" << j << ": " << mu 
		   << " LOWER (slack)" << std::endl;
    }

    // new minimum?
    if (mu < min_mu) {
      min_j = j; min_mu = mu;
      direction = 1;
    }
  }
  return (min_j == j);
}



CGAL_END_NAMESPACE

#endif // CGAL_QP_PRICING_STRATEGY_H

// ===== EOF ==================================================================
