// ======================================================================
//
// Copyright (c) 1999 The CGAL Consortium
//
// This software and related documentation is part of an INTERNAL release
// of the Computational Geometry Algorithms Library (CGAL). It is not
// intended for general use.
//
// ----------------------------------------------------------------------
// 
// release       :
// release_date  :
// 
// file          : include/CGAL/Arithmetic_filter/predicates/sign_of_determinant.h
// package       : Interval_arithmetic
// author(s)     : Sylvain Pion <Sylvain.Pion@sophia.inria.fr>
//
// coordinator   : INRIA Sophia-Antipolis (<Mariette.Yvinec@sophia.inria.fr>)
// ======================================================================

// This file is automatically generated by the script
// examples/Interval_arithmetic/filtered_predicate_converter.

#ifndef CGAL_ARITHMETIC_FILTER_PREDICATES_SIGN_OF_DETERMINANT_H
#define CGAL_ARITHMETIC_FILTER_PREDICATES_SIGN_OF_DETERMINANT_H

CGAL_BEGIN_NAMESPACE

inline
Sign
sign_of_determinant2x2_SAF(
    const Static_filter_error &a00,
    const Static_filter_error &a01,
    const Static_filter_error &a10,
    const Static_filter_error &a11,
    double & epsilon_0)
{
  typedef Static_filter_error FT;
 return static_cast<Sign>(static_cast<int>(CGAL::compare_SAF( a00*a11, a10*a01,
		epsilon_0))); }

inline
Sign
sign_of_determinant2x2_SAF(
    const Restricted_double &a00,
    const Restricted_double &a01,
    const Restricted_double &a10,
    const Restricted_double &a11,
    const double & epsilon_0)
{
  typedef Restricted_double FT;
 return static_cast<Sign>(static_cast<int>(CGAL::compare_SAF( a00*a11, a10*a01,
		epsilon_0))); }

inline
Sign
sign_of_determinant2x2(
    const Static_adaptatif_filter &a00,
    const Static_adaptatif_filter &a01,
    const Static_adaptatif_filter &a10,
    const Static_adaptatif_filter &a11)
{
  bool tried = false;
  static double SAF_bound = -1.0;
  static double SAF_epsilon_0;

letstry:
  try
  {
    // Check the bounds.  All arguments must be <= SAF_bound.
    // The throw mecanism is not useful here, it should be before the try{}.
    if (
	fabs(a00.value()) > SAF_bound ||
	fabs(a01.value()) > SAF_bound ||
	fabs(a10.value()) > SAF_bound ||
	fabs(a11.value()) > SAF_bound)
      throw Restricted_double::unsafe_comparison();
    // Try the epsilon variant of the predicate.
    return sign_of_determinant2x2_SAF(
		Restricted_double(a00.value()),
		Restricted_double(a01.value()),
		Restricted_double(a10.value()),
		Restricted_double(a11.value()),
		SAF_epsilon_0);
  }
  catch (Restricted_double::unsafe_comparison)
  {
    // It failed once, we re-adjust (bound, epsilons).
    if (!tried)
    {
      tried = true;
      // Recompute SAF_bound (tighter or larger).
      SAF_bound = 0;
      SAF_bound = std::max(SAF_bound, fabs(a00.value()));
      SAF_bound = std::max(SAF_bound, fabs(a01.value()));
      SAF_bound = std::max(SAF_bound, fabs(a10.value()));
      SAF_bound = std::max(SAF_bound, fabs(a11.value()));

      // recompute epsilons: "just" call it over Static_filter_error.
      // That's the tricky part that might not work for everything.
      (void) sign_of_determinant2x2_SAF(
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		SAF_epsilon_0);

      // We should verify that all epsilons have really been updated.

      // Try again with the updated (SAF_bound, epsilon)
      goto letstry;
    }
    // This scheme definitely fails => exact computation (filtered_exact<> ?).
    return sign_of_determinant2x2(
		a00.exact(),
		a01.exact(),
		a10.exact(),
		a11.exact());
  }
}

inline
Sign
sign_of_determinant3x3_SAF(
    const Static_filter_error &a00,
    const Static_filter_error &a01,
    const Static_filter_error &a02,
    const Static_filter_error &a10,
    const Static_filter_error &a11,
    const Static_filter_error &a12,
    const Static_filter_error &a20,
    const Static_filter_error &a21,
    const Static_filter_error &a22,
    double & epsilon_0)
{
  typedef Static_filter_error FT;

  return CGAL::sign_SAF(det3x3_by_formula(a00, a01, a02,
                                      a10, a11, a12,
                                      a20, a21, a22),
		epsilon_0);
}

inline
Sign
sign_of_determinant3x3_SAF(
    const Restricted_double &a00,
    const Restricted_double &a01,
    const Restricted_double &a02,
    const Restricted_double &a10,
    const Restricted_double &a11,
    const Restricted_double &a12,
    const Restricted_double &a20,
    const Restricted_double &a21,
    const Restricted_double &a22,
    const double & epsilon_0)
{
  typedef Restricted_double FT;

  return CGAL::sign_SAF(det3x3_by_formula(a00, a01, a02,
                                      a10, a11, a12,
                                      a20, a21, a22),
		epsilon_0);
}

inline
Sign
sign_of_determinant3x3(
    const Static_adaptatif_filter &a00,
    const Static_adaptatif_filter &a01,
    const Static_adaptatif_filter &a02,
    const Static_adaptatif_filter &a10,
    const Static_adaptatif_filter &a11,
    const Static_adaptatif_filter &a12,
    const Static_adaptatif_filter &a20,
    const Static_adaptatif_filter &a21,
    const Static_adaptatif_filter &a22)
{
  bool tried = false;
  static double SAF_bound = -1.0;
  static double SAF_epsilon_0;

letstry:
  try
  {
    // Check the bounds.  All arguments must be <= SAF_bound.
    // The throw mecanism is not useful here, it should be before the try{}.
    if (
	fabs(a00.value()) > SAF_bound ||
	fabs(a01.value()) > SAF_bound ||
	fabs(a02.value()) > SAF_bound ||
	fabs(a10.value()) > SAF_bound ||
	fabs(a11.value()) > SAF_bound ||
	fabs(a12.value()) > SAF_bound ||
	fabs(a20.value()) > SAF_bound ||
	fabs(a21.value()) > SAF_bound ||
	fabs(a22.value()) > SAF_bound)
      throw Restricted_double::unsafe_comparison();
    // Try the epsilon variant of the predicate.
    return sign_of_determinant3x3_SAF(
		Restricted_double(a00.value()),
		Restricted_double(a01.value()),
		Restricted_double(a02.value()),
		Restricted_double(a10.value()),
		Restricted_double(a11.value()),
		Restricted_double(a12.value()),
		Restricted_double(a20.value()),
		Restricted_double(a21.value()),
		Restricted_double(a22.value()),
		SAF_epsilon_0);
  }
  catch (Restricted_double::unsafe_comparison)
  {
    // It failed once, we re-adjust (bound, epsilons).
    if (!tried)
    {
      tried = true;
      // Recompute SAF_bound (tighter or larger).
      SAF_bound = 0;
      SAF_bound = std::max(SAF_bound, fabs(a00.value()));
      SAF_bound = std::max(SAF_bound, fabs(a01.value()));
      SAF_bound = std::max(SAF_bound, fabs(a02.value()));
      SAF_bound = std::max(SAF_bound, fabs(a10.value()));
      SAF_bound = std::max(SAF_bound, fabs(a11.value()));
      SAF_bound = std::max(SAF_bound, fabs(a12.value()));
      SAF_bound = std::max(SAF_bound, fabs(a20.value()));
      SAF_bound = std::max(SAF_bound, fabs(a21.value()));
      SAF_bound = std::max(SAF_bound, fabs(a22.value()));

      // recompute epsilons: "just" call it over Static_filter_error.
      // That's the tricky part that might not work for everything.
      (void) sign_of_determinant3x3_SAF(
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		SAF_epsilon_0);

      // We should verify that all epsilons have really been updated.

      // Try again with the updated (SAF_bound, epsilon)
      goto letstry;
    }
    // This scheme definitely fails => exact computation (filtered_exact<> ?).
    return sign_of_determinant3x3(
		a00.exact(),
		a01.exact(),
		a02.exact(),
		a10.exact(),
		a11.exact(),
		a12.exact(),
		a20.exact(),
		a21.exact(),
		a22.exact());
  }
}

inline
Sign
sign_of_determinant4x4_SAF(
    const Static_filter_error &a00,
    const Static_filter_error &a01,
    const Static_filter_error &a02,
    const Static_filter_error &a03,
    const Static_filter_error &a10,
    const Static_filter_error &a11,
    const Static_filter_error &a12,
    const Static_filter_error &a13,
    const Static_filter_error &a20,
    const Static_filter_error &a21,
    const Static_filter_error &a22,
    const Static_filter_error &a23,
    const Static_filter_error &a30,
    const Static_filter_error &a31,
    const Static_filter_error &a32,
    const Static_filter_error &a33,
    double & epsilon_0)
{
  typedef Static_filter_error FT;

  return CGAL::sign_SAF(det4x4_by_formula(a00, a01, a02, a03,
                                      a10, a11, a12, a13,
                                      a20, a21, a22, a23,
                                      a30, a31, a32, a33),
		epsilon_0);
}

inline
Sign
sign_of_determinant4x4_SAF(
    const Restricted_double &a00,
    const Restricted_double &a01,
    const Restricted_double &a02,
    const Restricted_double &a03,
    const Restricted_double &a10,
    const Restricted_double &a11,
    const Restricted_double &a12,
    const Restricted_double &a13,
    const Restricted_double &a20,
    const Restricted_double &a21,
    const Restricted_double &a22,
    const Restricted_double &a23,
    const Restricted_double &a30,
    const Restricted_double &a31,
    const Restricted_double &a32,
    const Restricted_double &a33,
    const double & epsilon_0)
{
  typedef Restricted_double FT;

  return CGAL::sign_SAF(det4x4_by_formula(a00, a01, a02, a03,
                                      a10, a11, a12, a13,
                                      a20, a21, a22, a23,
                                      a30, a31, a32, a33),
		epsilon_0);
}

inline
Sign
sign_of_determinant4x4(
    const Static_adaptatif_filter &a00,
    const Static_adaptatif_filter &a01,
    const Static_adaptatif_filter &a02,
    const Static_adaptatif_filter &a03,
    const Static_adaptatif_filter &a10,
    const Static_adaptatif_filter &a11,
    const Static_adaptatif_filter &a12,
    const Static_adaptatif_filter &a13,
    const Static_adaptatif_filter &a20,
    const Static_adaptatif_filter &a21,
    const Static_adaptatif_filter &a22,
    const Static_adaptatif_filter &a23,
    const Static_adaptatif_filter &a30,
    const Static_adaptatif_filter &a31,
    const Static_adaptatif_filter &a32,
    const Static_adaptatif_filter &a33)
{
  bool tried = false;
  static double SAF_bound = -1.0;
  static double SAF_epsilon_0;

letstry:
  try
  {
    // Check the bounds.  All arguments must be <= SAF_bound.
    // The throw mecanism is not useful here, it should be before the try{}.
    if (
	fabs(a00.value()) > SAF_bound ||
	fabs(a01.value()) > SAF_bound ||
	fabs(a02.value()) > SAF_bound ||
	fabs(a03.value()) > SAF_bound ||
	fabs(a10.value()) > SAF_bound ||
	fabs(a11.value()) > SAF_bound ||
	fabs(a12.value()) > SAF_bound ||
	fabs(a13.value()) > SAF_bound ||
	fabs(a20.value()) > SAF_bound ||
	fabs(a21.value()) > SAF_bound ||
	fabs(a22.value()) > SAF_bound ||
	fabs(a23.value()) > SAF_bound ||
	fabs(a30.value()) > SAF_bound ||
	fabs(a31.value()) > SAF_bound ||
	fabs(a32.value()) > SAF_bound ||
	fabs(a33.value()) > SAF_bound)
      throw Restricted_double::unsafe_comparison();
    // Try the epsilon variant of the predicate.
    return sign_of_determinant4x4_SAF(
		Restricted_double(a00.value()),
		Restricted_double(a01.value()),
		Restricted_double(a02.value()),
		Restricted_double(a03.value()),
		Restricted_double(a10.value()),
		Restricted_double(a11.value()),
		Restricted_double(a12.value()),
		Restricted_double(a13.value()),
		Restricted_double(a20.value()),
		Restricted_double(a21.value()),
		Restricted_double(a22.value()),
		Restricted_double(a23.value()),
		Restricted_double(a30.value()),
		Restricted_double(a31.value()),
		Restricted_double(a32.value()),
		Restricted_double(a33.value()),
		SAF_epsilon_0);
  }
  catch (Restricted_double::unsafe_comparison)
  {
    // It failed once, we re-adjust (bound, epsilons).
    if (!tried)
    {
      tried = true;
      // Recompute SAF_bound (tighter or larger).
      SAF_bound = 0;
      SAF_bound = std::max(SAF_bound, fabs(a00.value()));
      SAF_bound = std::max(SAF_bound, fabs(a01.value()));
      SAF_bound = std::max(SAF_bound, fabs(a02.value()));
      SAF_bound = std::max(SAF_bound, fabs(a03.value()));
      SAF_bound = std::max(SAF_bound, fabs(a10.value()));
      SAF_bound = std::max(SAF_bound, fabs(a11.value()));
      SAF_bound = std::max(SAF_bound, fabs(a12.value()));
      SAF_bound = std::max(SAF_bound, fabs(a13.value()));
      SAF_bound = std::max(SAF_bound, fabs(a20.value()));
      SAF_bound = std::max(SAF_bound, fabs(a21.value()));
      SAF_bound = std::max(SAF_bound, fabs(a22.value()));
      SAF_bound = std::max(SAF_bound, fabs(a23.value()));
      SAF_bound = std::max(SAF_bound, fabs(a30.value()));
      SAF_bound = std::max(SAF_bound, fabs(a31.value()));
      SAF_bound = std::max(SAF_bound, fabs(a32.value()));
      SAF_bound = std::max(SAF_bound, fabs(a33.value()));

      // recompute epsilons: "just" call it over Static_filter_error.
      // That's the tricky part that might not work for everything.
      (void) sign_of_determinant4x4_SAF(
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		SAF_epsilon_0);

      // We should verify that all epsilons have really been updated.

      // Try again with the updated (SAF_bound, epsilon)
      goto letstry;
    }
    // This scheme definitely fails => exact computation (filtered_exact<> ?).
    return sign_of_determinant4x4(
		a00.exact(),
		a01.exact(),
		a02.exact(),
		a03.exact(),
		a10.exact(),
		a11.exact(),
		a12.exact(),
		a13.exact(),
		a20.exact(),
		a21.exact(),
		a22.exact(),
		a23.exact(),
		a30.exact(),
		a31.exact(),
		a32.exact(),
		a33.exact());
  }
}

inline
Sign
sign_of_determinant5x5_SAF(
    const Static_filter_error &a00,
    const Static_filter_error &a01,
    const Static_filter_error &a02,
    const Static_filter_error &a03,
    const Static_filter_error &a04,
    const Static_filter_error &a10,
    const Static_filter_error &a11,
    const Static_filter_error &a12,
    const Static_filter_error &a13,
    const Static_filter_error &a14,
    const Static_filter_error &a20,
    const Static_filter_error &a21,
    const Static_filter_error &a22,
    const Static_filter_error &a23,
    const Static_filter_error &a24,
    const Static_filter_error &a30,
    const Static_filter_error &a31,
    const Static_filter_error &a32,
    const Static_filter_error &a33,
    const Static_filter_error &a34,
    const Static_filter_error &a40,
    const Static_filter_error &a41,
    const Static_filter_error &a42,
    const Static_filter_error &a43,
    const Static_filter_error &a44,
    double & epsilon_0)
{
  typedef Static_filter_error FT;

  return CGAL::sign_SAF(det5x5_by_formula(a00, a01, a02, a03, a04,
                                      a10, a11, a12, a13, a14,
                                      a20, a21, a22, a23, a24,
                                      a30, a31, a32, a33, a34,
                                      a40, a41, a42, a43, a44),
		epsilon_0);
}

inline
Sign
sign_of_determinant5x5_SAF(
    const Restricted_double &a00,
    const Restricted_double &a01,
    const Restricted_double &a02,
    const Restricted_double &a03,
    const Restricted_double &a04,
    const Restricted_double &a10,
    const Restricted_double &a11,
    const Restricted_double &a12,
    const Restricted_double &a13,
    const Restricted_double &a14,
    const Restricted_double &a20,
    const Restricted_double &a21,
    const Restricted_double &a22,
    const Restricted_double &a23,
    const Restricted_double &a24,
    const Restricted_double &a30,
    const Restricted_double &a31,
    const Restricted_double &a32,
    const Restricted_double &a33,
    const Restricted_double &a34,
    const Restricted_double &a40,
    const Restricted_double &a41,
    const Restricted_double &a42,
    const Restricted_double &a43,
    const Restricted_double &a44,
    const double & epsilon_0)
{
  typedef Restricted_double FT;

  return CGAL::sign_SAF(det5x5_by_formula(a00, a01, a02, a03, a04,
                                      a10, a11, a12, a13, a14,
                                      a20, a21, a22, a23, a24,
                                      a30, a31, a32, a33, a34,
                                      a40, a41, a42, a43, a44),
		epsilon_0);
}

inline
Sign
sign_of_determinant5x5(
    const Static_adaptatif_filter &a00,
    const Static_adaptatif_filter &a01,
    const Static_adaptatif_filter &a02,
    const Static_adaptatif_filter &a03,
    const Static_adaptatif_filter &a04,
    const Static_adaptatif_filter &a10,
    const Static_adaptatif_filter &a11,
    const Static_adaptatif_filter &a12,
    const Static_adaptatif_filter &a13,
    const Static_adaptatif_filter &a14,
    const Static_adaptatif_filter &a20,
    const Static_adaptatif_filter &a21,
    const Static_adaptatif_filter &a22,
    const Static_adaptatif_filter &a23,
    const Static_adaptatif_filter &a24,
    const Static_adaptatif_filter &a30,
    const Static_adaptatif_filter &a31,
    const Static_adaptatif_filter &a32,
    const Static_adaptatif_filter &a33,
    const Static_adaptatif_filter &a34,
    const Static_adaptatif_filter &a40,
    const Static_adaptatif_filter &a41,
    const Static_adaptatif_filter &a42,
    const Static_adaptatif_filter &a43,
    const Static_adaptatif_filter &a44)
{
  bool tried = false;
  static double SAF_bound = -1.0;
  static double SAF_epsilon_0;

letstry:
  try
  {
    // Check the bounds.  All arguments must be <= SAF_bound.
    // The throw mecanism is not useful here, it should be before the try{}.
    if (
	fabs(a00.value()) > SAF_bound ||
	fabs(a01.value()) > SAF_bound ||
	fabs(a02.value()) > SAF_bound ||
	fabs(a03.value()) > SAF_bound ||
	fabs(a04.value()) > SAF_bound ||
	fabs(a10.value()) > SAF_bound ||
	fabs(a11.value()) > SAF_bound ||
	fabs(a12.value()) > SAF_bound ||
	fabs(a13.value()) > SAF_bound ||
	fabs(a14.value()) > SAF_bound ||
	fabs(a20.value()) > SAF_bound ||
	fabs(a21.value()) > SAF_bound ||
	fabs(a22.value()) > SAF_bound ||
	fabs(a23.value()) > SAF_bound ||
	fabs(a24.value()) > SAF_bound ||
	fabs(a30.value()) > SAF_bound ||
	fabs(a31.value()) > SAF_bound ||
	fabs(a32.value()) > SAF_bound ||
	fabs(a33.value()) > SAF_bound ||
	fabs(a34.value()) > SAF_bound ||
	fabs(a40.value()) > SAF_bound ||
	fabs(a41.value()) > SAF_bound ||
	fabs(a42.value()) > SAF_bound ||
	fabs(a43.value()) > SAF_bound ||
	fabs(a44.value()) > SAF_bound)
      throw Restricted_double::unsafe_comparison();
    // Try the epsilon variant of the predicate.
    return sign_of_determinant5x5_SAF(
		Restricted_double(a00.value()),
		Restricted_double(a01.value()),
		Restricted_double(a02.value()),
		Restricted_double(a03.value()),
		Restricted_double(a04.value()),
		Restricted_double(a10.value()),
		Restricted_double(a11.value()),
		Restricted_double(a12.value()),
		Restricted_double(a13.value()),
		Restricted_double(a14.value()),
		Restricted_double(a20.value()),
		Restricted_double(a21.value()),
		Restricted_double(a22.value()),
		Restricted_double(a23.value()),
		Restricted_double(a24.value()),
		Restricted_double(a30.value()),
		Restricted_double(a31.value()),
		Restricted_double(a32.value()),
		Restricted_double(a33.value()),
		Restricted_double(a34.value()),
		Restricted_double(a40.value()),
		Restricted_double(a41.value()),
		Restricted_double(a42.value()),
		Restricted_double(a43.value()),
		Restricted_double(a44.value()),
		SAF_epsilon_0);
  }
  catch (Restricted_double::unsafe_comparison)
  {
    // It failed once, we re-adjust (bound, epsilons).
    if (!tried)
    {
      tried = true;
      // Recompute SAF_bound (tighter or larger).
      SAF_bound = 0;
      SAF_bound = std::max(SAF_bound, fabs(a00.value()));
      SAF_bound = std::max(SAF_bound, fabs(a01.value()));
      SAF_bound = std::max(SAF_bound, fabs(a02.value()));
      SAF_bound = std::max(SAF_bound, fabs(a03.value()));
      SAF_bound = std::max(SAF_bound, fabs(a04.value()));
      SAF_bound = std::max(SAF_bound, fabs(a10.value()));
      SAF_bound = std::max(SAF_bound, fabs(a11.value()));
      SAF_bound = std::max(SAF_bound, fabs(a12.value()));
      SAF_bound = std::max(SAF_bound, fabs(a13.value()));
      SAF_bound = std::max(SAF_bound, fabs(a14.value()));
      SAF_bound = std::max(SAF_bound, fabs(a20.value()));
      SAF_bound = std::max(SAF_bound, fabs(a21.value()));
      SAF_bound = std::max(SAF_bound, fabs(a22.value()));
      SAF_bound = std::max(SAF_bound, fabs(a23.value()));
      SAF_bound = std::max(SAF_bound, fabs(a24.value()));
      SAF_bound = std::max(SAF_bound, fabs(a30.value()));
      SAF_bound = std::max(SAF_bound, fabs(a31.value()));
      SAF_bound = std::max(SAF_bound, fabs(a32.value()));
      SAF_bound = std::max(SAF_bound, fabs(a33.value()));
      SAF_bound = std::max(SAF_bound, fabs(a34.value()));
      SAF_bound = std::max(SAF_bound, fabs(a40.value()));
      SAF_bound = std::max(SAF_bound, fabs(a41.value()));
      SAF_bound = std::max(SAF_bound, fabs(a42.value()));
      SAF_bound = std::max(SAF_bound, fabs(a43.value()));
      SAF_bound = std::max(SAF_bound, fabs(a44.value()));

      // recompute epsilons: "just" call it over Static_filter_error.
      // That's the tricky part that might not work for everything.
      (void) sign_of_determinant5x5_SAF(
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		SAF_epsilon_0);

      // We should verify that all epsilons have really been updated.

      // Try again with the updated (SAF_bound, epsilon)
      goto letstry;
    }
    // This scheme definitely fails => exact computation (filtered_exact<> ?).
    return sign_of_determinant5x5(
		a00.exact(),
		a01.exact(),
		a02.exact(),
		a03.exact(),
		a04.exact(),
		a10.exact(),
		a11.exact(),
		a12.exact(),
		a13.exact(),
		a14.exact(),
		a20.exact(),
		a21.exact(),
		a22.exact(),
		a23.exact(),
		a24.exact(),
		a30.exact(),
		a31.exact(),
		a32.exact(),
		a33.exact(),
		a34.exact(),
		a40.exact(),
		a41.exact(),
		a42.exact(),
		a43.exact(),
		a44.exact());
  }
}

inline
Sign
sign_of_determinant6x6_SAF(
    const Static_filter_error &a00,
    const Static_filter_error &a01,
    const Static_filter_error &a02,
    const Static_filter_error &a03,
    const Static_filter_error &a04,
    const Static_filter_error &a05,
    const Static_filter_error &a10,
    const Static_filter_error &a11,
    const Static_filter_error &a12,
    const Static_filter_error &a13,
    const Static_filter_error &a14,
    const Static_filter_error &a15,
    const Static_filter_error &a20,
    const Static_filter_error &a21,
    const Static_filter_error &a22,
    const Static_filter_error &a23,
    const Static_filter_error &a24,
    const Static_filter_error &a25,
    const Static_filter_error &a30,
    const Static_filter_error &a31,
    const Static_filter_error &a32,
    const Static_filter_error &a33,
    const Static_filter_error &a34,
    const Static_filter_error &a35,
    const Static_filter_error &a40,
    const Static_filter_error &a41,
    const Static_filter_error &a42,
    const Static_filter_error &a43,
    const Static_filter_error &a44,
    const Static_filter_error &a45,
    const Static_filter_error &a50,
    const Static_filter_error &a51,
    const Static_filter_error &a52,
    const Static_filter_error &a53,
    const Static_filter_error &a54,
    const Static_filter_error &a55,
    double & epsilon_0)
{
  typedef Static_filter_error FT;

  return CGAL::sign_SAF(det6x6_by_formula(a00, a01, a02, a03, a04, a05,
                                      a10, a11, a12, a13, a14, a15,
                                      a20, a21, a22, a23, a24, a25,
                                      a30, a31, a32, a33, a34, a35,
                                      a40, a41, a42, a43, a44, a45,
                                      a50, a51, a52, a53, a54, a55),
		epsilon_0);
}

inline
Sign
sign_of_determinant6x6_SAF(
    const Restricted_double &a00,
    const Restricted_double &a01,
    const Restricted_double &a02,
    const Restricted_double &a03,
    const Restricted_double &a04,
    const Restricted_double &a05,
    const Restricted_double &a10,
    const Restricted_double &a11,
    const Restricted_double &a12,
    const Restricted_double &a13,
    const Restricted_double &a14,
    const Restricted_double &a15,
    const Restricted_double &a20,
    const Restricted_double &a21,
    const Restricted_double &a22,
    const Restricted_double &a23,
    const Restricted_double &a24,
    const Restricted_double &a25,
    const Restricted_double &a30,
    const Restricted_double &a31,
    const Restricted_double &a32,
    const Restricted_double &a33,
    const Restricted_double &a34,
    const Restricted_double &a35,
    const Restricted_double &a40,
    const Restricted_double &a41,
    const Restricted_double &a42,
    const Restricted_double &a43,
    const Restricted_double &a44,
    const Restricted_double &a45,
    const Restricted_double &a50,
    const Restricted_double &a51,
    const Restricted_double &a52,
    const Restricted_double &a53,
    const Restricted_double &a54,
    const Restricted_double &a55,
    const double & epsilon_0)
{
  typedef Restricted_double FT;

  return CGAL::sign_SAF(det6x6_by_formula(a00, a01, a02, a03, a04, a05,
                                      a10, a11, a12, a13, a14, a15,
                                      a20, a21, a22, a23, a24, a25,
                                      a30, a31, a32, a33, a34, a35,
                                      a40, a41, a42, a43, a44, a45,
                                      a50, a51, a52, a53, a54, a55),
		epsilon_0);
}

inline
Sign
sign_of_determinant6x6(
    const Static_adaptatif_filter &a00,
    const Static_adaptatif_filter &a01,
    const Static_adaptatif_filter &a02,
    const Static_adaptatif_filter &a03,
    const Static_adaptatif_filter &a04,
    const Static_adaptatif_filter &a05,
    const Static_adaptatif_filter &a10,
    const Static_adaptatif_filter &a11,
    const Static_adaptatif_filter &a12,
    const Static_adaptatif_filter &a13,
    const Static_adaptatif_filter &a14,
    const Static_adaptatif_filter &a15,
    const Static_adaptatif_filter &a20,
    const Static_adaptatif_filter &a21,
    const Static_adaptatif_filter &a22,
    const Static_adaptatif_filter &a23,
    const Static_adaptatif_filter &a24,
    const Static_adaptatif_filter &a25,
    const Static_adaptatif_filter &a30,
    const Static_adaptatif_filter &a31,
    const Static_adaptatif_filter &a32,
    const Static_adaptatif_filter &a33,
    const Static_adaptatif_filter &a34,
    const Static_adaptatif_filter &a35,
    const Static_adaptatif_filter &a40,
    const Static_adaptatif_filter &a41,
    const Static_adaptatif_filter &a42,
    const Static_adaptatif_filter &a43,
    const Static_adaptatif_filter &a44,
    const Static_adaptatif_filter &a45,
    const Static_adaptatif_filter &a50,
    const Static_adaptatif_filter &a51,
    const Static_adaptatif_filter &a52,
    const Static_adaptatif_filter &a53,
    const Static_adaptatif_filter &a54,
    const Static_adaptatif_filter &a55)
{
  bool tried = false;
  static double SAF_bound = -1.0;
  static double SAF_epsilon_0;

letstry:
  try
  {
    // Check the bounds.  All arguments must be <= SAF_bound.
    // The throw mecanism is not useful here, it should be before the try{}.
    if (
	fabs(a00.value()) > SAF_bound ||
	fabs(a01.value()) > SAF_bound ||
	fabs(a02.value()) > SAF_bound ||
	fabs(a03.value()) > SAF_bound ||
	fabs(a04.value()) > SAF_bound ||
	fabs(a05.value()) > SAF_bound ||
	fabs(a10.value()) > SAF_bound ||
	fabs(a11.value()) > SAF_bound ||
	fabs(a12.value()) > SAF_bound ||
	fabs(a13.value()) > SAF_bound ||
	fabs(a14.value()) > SAF_bound ||
	fabs(a15.value()) > SAF_bound ||
	fabs(a20.value()) > SAF_bound ||
	fabs(a21.value()) > SAF_bound ||
	fabs(a22.value()) > SAF_bound ||
	fabs(a23.value()) > SAF_bound ||
	fabs(a24.value()) > SAF_bound ||
	fabs(a25.value()) > SAF_bound ||
	fabs(a30.value()) > SAF_bound ||
	fabs(a31.value()) > SAF_bound ||
	fabs(a32.value()) > SAF_bound ||
	fabs(a33.value()) > SAF_bound ||
	fabs(a34.value()) > SAF_bound ||
	fabs(a35.value()) > SAF_bound ||
	fabs(a40.value()) > SAF_bound ||
	fabs(a41.value()) > SAF_bound ||
	fabs(a42.value()) > SAF_bound ||
	fabs(a43.value()) > SAF_bound ||
	fabs(a44.value()) > SAF_bound ||
	fabs(a45.value()) > SAF_bound ||
	fabs(a50.value()) > SAF_bound ||
	fabs(a51.value()) > SAF_bound ||
	fabs(a52.value()) > SAF_bound ||
	fabs(a53.value()) > SAF_bound ||
	fabs(a54.value()) > SAF_bound ||
	fabs(a55.value()) > SAF_bound)
      throw Restricted_double::unsafe_comparison();
    // Try the epsilon variant of the predicate.
    return sign_of_determinant6x6_SAF(
		Restricted_double(a00.value()),
		Restricted_double(a01.value()),
		Restricted_double(a02.value()),
		Restricted_double(a03.value()),
		Restricted_double(a04.value()),
		Restricted_double(a05.value()),
		Restricted_double(a10.value()),
		Restricted_double(a11.value()),
		Restricted_double(a12.value()),
		Restricted_double(a13.value()),
		Restricted_double(a14.value()),
		Restricted_double(a15.value()),
		Restricted_double(a20.value()),
		Restricted_double(a21.value()),
		Restricted_double(a22.value()),
		Restricted_double(a23.value()),
		Restricted_double(a24.value()),
		Restricted_double(a25.value()),
		Restricted_double(a30.value()),
		Restricted_double(a31.value()),
		Restricted_double(a32.value()),
		Restricted_double(a33.value()),
		Restricted_double(a34.value()),
		Restricted_double(a35.value()),
		Restricted_double(a40.value()),
		Restricted_double(a41.value()),
		Restricted_double(a42.value()),
		Restricted_double(a43.value()),
		Restricted_double(a44.value()),
		Restricted_double(a45.value()),
		Restricted_double(a50.value()),
		Restricted_double(a51.value()),
		Restricted_double(a52.value()),
		Restricted_double(a53.value()),
		Restricted_double(a54.value()),
		Restricted_double(a55.value()),
		SAF_epsilon_0);
  }
  catch (Restricted_double::unsafe_comparison)
  {
    // It failed once, we re-adjust (bound, epsilons).
    if (!tried)
    {
      tried = true;
      // Recompute SAF_bound (tighter or larger).
      SAF_bound = 0;
      SAF_bound = std::max(SAF_bound, fabs(a00.value()));
      SAF_bound = std::max(SAF_bound, fabs(a01.value()));
      SAF_bound = std::max(SAF_bound, fabs(a02.value()));
      SAF_bound = std::max(SAF_bound, fabs(a03.value()));
      SAF_bound = std::max(SAF_bound, fabs(a04.value()));
      SAF_bound = std::max(SAF_bound, fabs(a05.value()));
      SAF_bound = std::max(SAF_bound, fabs(a10.value()));
      SAF_bound = std::max(SAF_bound, fabs(a11.value()));
      SAF_bound = std::max(SAF_bound, fabs(a12.value()));
      SAF_bound = std::max(SAF_bound, fabs(a13.value()));
      SAF_bound = std::max(SAF_bound, fabs(a14.value()));
      SAF_bound = std::max(SAF_bound, fabs(a15.value()));
      SAF_bound = std::max(SAF_bound, fabs(a20.value()));
      SAF_bound = std::max(SAF_bound, fabs(a21.value()));
      SAF_bound = std::max(SAF_bound, fabs(a22.value()));
      SAF_bound = std::max(SAF_bound, fabs(a23.value()));
      SAF_bound = std::max(SAF_bound, fabs(a24.value()));
      SAF_bound = std::max(SAF_bound, fabs(a25.value()));
      SAF_bound = std::max(SAF_bound, fabs(a30.value()));
      SAF_bound = std::max(SAF_bound, fabs(a31.value()));
      SAF_bound = std::max(SAF_bound, fabs(a32.value()));
      SAF_bound = std::max(SAF_bound, fabs(a33.value()));
      SAF_bound = std::max(SAF_bound, fabs(a34.value()));
      SAF_bound = std::max(SAF_bound, fabs(a35.value()));
      SAF_bound = std::max(SAF_bound, fabs(a40.value()));
      SAF_bound = std::max(SAF_bound, fabs(a41.value()));
      SAF_bound = std::max(SAF_bound, fabs(a42.value()));
      SAF_bound = std::max(SAF_bound, fabs(a43.value()));
      SAF_bound = std::max(SAF_bound, fabs(a44.value()));
      SAF_bound = std::max(SAF_bound, fabs(a45.value()));
      SAF_bound = std::max(SAF_bound, fabs(a50.value()));
      SAF_bound = std::max(SAF_bound, fabs(a51.value()));
      SAF_bound = std::max(SAF_bound, fabs(a52.value()));
      SAF_bound = std::max(SAF_bound, fabs(a53.value()));
      SAF_bound = std::max(SAF_bound, fabs(a54.value()));
      SAF_bound = std::max(SAF_bound, fabs(a55.value()));

      // recompute epsilons: "just" call it over Static_filter_error.
      // That's the tricky part that might not work for everything.
      (void) sign_of_determinant6x6_SAF(
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		Static_filter_error(SAF_bound,0,1),
		SAF_epsilon_0);

      // We should verify that all epsilons have really been updated.

      // Try again with the updated (SAF_bound, epsilon)
      goto letstry;
    }
    // This scheme definitely fails => exact computation (filtered_exact<> ?).
    return sign_of_determinant6x6(
		a00.exact(),
		a01.exact(),
		a02.exact(),
		a03.exact(),
		a04.exact(),
		a05.exact(),
		a10.exact(),
		a11.exact(),
		a12.exact(),
		a13.exact(),
		a14.exact(),
		a15.exact(),
		a20.exact(),
		a21.exact(),
		a22.exact(),
		a23.exact(),
		a24.exact(),
		a25.exact(),
		a30.exact(),
		a31.exact(),
		a32.exact(),
		a33.exact(),
		a34.exact(),
		a35.exact(),
		a40.exact(),
		a41.exact(),
		a42.exact(),
		a43.exact(),
		a44.exact(),
		a45.exact(),
		a50.exact(),
		a51.exact(),
		a52.exact(),
		a53.exact(),
		a54.exact(),
		a55.exact());
  }
}

CGAL_END_NAMESPACE

#endif // CGAL_ARITHMETIC_FILTER_PREDICATES_SIGN_OF_DETERMINANT_H
