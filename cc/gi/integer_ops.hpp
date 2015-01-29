/* -*- C++ -*-
 *
 *   File Name: integer_ops.hpp
 *
 * Description: Integer utility algorithms.
 *
 *  Created on: Jun 17, 2014
 *      Author: Zach Gianos
 */

#ifndef GI_LIBCXX_INTEGER_OPS_HPP_INCLUDED_
#define GI_LIBCXX_INTEGER_OPS_HPP_INCLUDED_

#include <climits> // CHAR_BIT
#include <gi/utility/enable_if_int.hpp>

namespace gi
{

  /*!
   * Conditionally negates @c v without branching.
   *
   * @param v
   * @param yes
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer>::type
  negate_if_true(Integer v, bool yes)
  {
    return (v ^ -yes) + yes;
  }

  /*!
   * Conditionally negates @c v without branching.
   *
   * @param v
   * @param no
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer>::type
  negate_if_false(Integer v, bool no)
  {
    return (no ^ (no - 1)) * v;
  }

  /*!
   * Calculates the minimum value without branching.
   *
   * @param x
   * @param y
   * @return
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer>::type
  min(Integer x, Integer y)
  {
    return y ^ ((x ^ y) & -(x < y));
  }

  /*!
   * Calculates the maximum value without branching.
   *
   * @param x
   * @param y
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer>::type
  max(Integer x, Integer y)
  {
    return x ^ ((x ^ y) & -(x < y));
  }

  /*!
   * Return @c true if the integer is a power of two.
   *
   * @param v The value to test
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer, bool>::type
  is_pow2(Integer v)
  {
    return v && !(v & (v - 1));
  }

  /*!
   * Return @c true if the integers have opposite signs.
   *
   * @param x
   * @param y
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline bool is_signopp(Integer x, Integer y)
  {
    return ((x ^ y) < 0);
  }

  /*!
   * Calculates the sign of the value, {0,-1}.
   *
   * @param v
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer>::type
  sign01a(Integer v)
  {
    return -(v < 0);
  }

  /*!
   * Calculates the sign of the value, {0,-1}.
   *
   * @param v
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer>::type
  sign01b(Integer v)
  {
    // avoid branching on CPUs with flag registers (IA32):
    return -(Integer)lrshift(v, (sizeof(Integer) * CHAR_BIT - 1));
  }

  /*!
   * Calculates the sign of the value, {+1,-1}.
   *
   * @param v
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer>::type
  sign3(Integer v)
  {
    return ((Integer)+1) | lrshift(v, (sizeof(Integer) * CHAR_BIT - 1));
  }

  /*!
   * Calculates the sign of the value, {+1,0,-1}.
   *
   * @param v
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer>::type
  sign101a(Integer v)
  {
    return (v > 0) - (v < 0);
  }

  /*!
   * Calculates the sign of the value, {+1,0,-1}.
   *
   * @param v
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer>::type
  sign101b(Integer v)
  {
    return (v != 0) | sign01b(v);
  }

  /*!
   * Returns +1 if v > 0, otherwise 0.
   *
   * @param v
   * @return
   * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
   */
  template <typename Integer>
  inline
  typename enable_if_xint<Integer>::type
  nonnegative(Integer v)
  {
    return 1 ^ lrshift(v, (sizeof(Integer) * CHAR_BIT - 1));
  }

} /* namespace gi */

#endif /* GI_LIBCXX_INTEGER_OPS_HPP_INCLUDED_ */
