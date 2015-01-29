/* -*- C++ -*-
 *
 *   File Name: bitops.hpp
 *
 * Description: Common operations on binary values.
 *
 *  Created on: Jun 20, 2014
 *      Author: Zach Gianos
 */

#ifndef GI_LIBCXX_BITOPS_HPP_INCLUDED_
#define GI_LIBCXX_BITOPS_HPP_INCLUDED_

#include <climits> // CHAR_BIT
#include <gi/unsigned_cast.hpp>
#include <gi/utility/enable_if_int.hpp>

namespace gi
{

  namespace bitops
  {

    /*!
     * Logically right-shift the value.
     *
     * The built-in right-shift operator ">>" is implementation-defined for
     * signed integral types whose value is less than zero. Since, in two's
     * complement representation, the most-significant bit is a 1 for negative
     * numbers, there are two possible implementations for a right-shift
     * operation:
     * - logical shift:
     *   A 0 bit replaces the most-significant bits. This is equivalent to
     *   applying the operation on the associated unsigned value.
     * - arithmetic shift:
     *   A 1 bit replaces the most-significant bits. This is equivalent to
     *   integer division by 2.
     *
     * This function simply casts the value to the unsigned type before applying
     * the built-in right-shift operation.
     *
     * @param v
     * @param n
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lrshift(Integer v, std::size_t n)
    {
      return reinterpret_cast<Integer>(unsigned_cast(v) >> n);
    }

    /*
     * Note:
     * For some integral type T:
     * (T)~(T)0/15     = 0x1111...
     * (T)~(T)0/255    = 0x0101...
     * (T)~(T)0/5      = 0x3333...
     * (T)~(T)0/3      = 0x5555...
     * (T)~(T)0/17     = 0x0f0f...
     */

    /*!
     * Compute the Hamming weight/population count/sideways sum of @c v.
     *
     * @param v The integer target
     * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
     */
    template <typename UnsignedInteger>
    inline
    typename enable_if_uint<UnsignedInteger, unsigned int>::type
    pop(UnsignedInteger v)
    {
      typedef UnsignedInteger T;
      v = v - ((v >> 1) & (T)~(T)0/3);
      v = (v & (T)~(T)0/5) + ((v >> 2) & (T)~(T)0/5);
      v = (v + (v >> 4)) & (T)~(T)0/17;
      v = (v * ((T)~(T)0/255)) >> ((sizeof(T) - 1) * CHAR_BIT);
      return v;
    }

    /*!
     * Compute the Hamming weight/population count/sideways sum of @c v.
     *
     * @param v The integer target
     * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
     */
    template <typename Integer>
    inline
    typename enable_if_sint<Integer, unsigned int>::type
    pop(Integer v)
    {
      return pop(unsigned_cast(v));
    }

    /*!
     * Compute the number of bits that are set from the most-significant bit
     * down to the bit at the given position.
     *
     * @param v The integer target
     * @param pos The bit position upto which bits are counted
     * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer, unsigned int>::type
    rank(Integer v, unsigned int pos)
    {
      // Shift out bits after given position.
      v = lrshift(v, (sizeof(Integer) * CHAR_BIT - pos));
      return pop(v);
    }

    /*!
     * Conditionally set or clear bits without branching.
     *
     * @param w The word to modify
     * @param m The bit mask
     * @param f The conditional flag
     * @return
     * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    set_if_a(Integer w, Integer m, bool f)
    {
      return w ^ ((-f ^ w) & m);
    }

    /*!
     * Conditionally set or clear bits without branching.
     *
     * @param w The word to modify
     * @param m The bit mask
     * @param f The conditional flag
     * @return
     * @copyright Sean Eron Anderson http://graphics.stanford.edu/~seander/bithacks.html
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    set_if_b(Integer w, Integer m, bool f)
    {
      return (w & ~m) | (-f & m);
    }

    /*!
     * Extracts the bit field.
     *
     * @param w The target word
     * @param p The starting bit position
     * @param n The number of bits to extract
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    extract(Integer w, unsigned int p, unsigned int n)
    {
      return lrshift(w, p) & ((1 << n) - 1);
    }

    /*!
     * Lowest cleared fill: clear all trailing ones.
     *
     * Ex) 01011 => 01000
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lcfill(Integer w)
    {
      // 01011: 01011 & 01100 = 01000
      return w & (w + 1);
    }

    /*!
     * Isolate the lowest-order cleared bit.
     *
     * Ex) 01011 => 11011
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lcisolate(Integer w)
    {
      // 01011: 01011 | 10011 = 11011
      return w | ~(w + 1);
    }

    /*!
     * Complement of the isolated lowest-order cleared bit
     *
     * Ex) 01011 => 00100
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lcisolatec(Integer w)
    {
      // ex) 01011: 10100 & 01100 = 00100
      return ~w & (w + 1);
    }

    /*!
     * Lowest cleared mask: a mask up to the lowest-order cleared bit.
     *
     * Ex) 01011 => 00111
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lcmask(Integer w)
    {
      // ex) 01011: 01011 ^ 01100 = 00111
      return w ^ (w + 1);
    }

    /*!
     * Set the lowest cleared bit.
     *
     * Ex) 01011 => 01111
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lcset(Integer w)
    {
      // ex) 01011: 01011 | 01100 = 01111
      return w | (w + 1);
    }

    /*!
     * Lowest set fill: set trailing zeros.
     *
     * Ex) 01100 => 01111
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lsfill(Integer w)
    {
      // 01100: 01100 | 01011 = 01111
      return w | (w - 1);
    }

    /*!
     * The isolated lowest-order set bit.
     *
     * Ex) 01100 => 00100
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lsisolate(Integer w)
    {
      // 01100: 01100 & 10100 = 00100
      return w & -w;
    }

    /*!
     * Complement of the mask selecting the lowest-order set bit.
     *
     * Ex) 01100 => 11011
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lsisolatec(Integer w)
    {
      // 01100: 10011 | 01011 = 11011
      return ~w | (w - 1);
    }

    /*!
     * Lowest set mask: a mask up to the lowest-order set bit.
     *
     * Ex) 01100 => 00111
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lsmask(Integer w)
    {
      // ex) 01100: 01100 ^ 01011 = 00111
      return w ^ (w - 1);
    }

    /*!
     * Clear the lowest-order set bit.
     *
     * Ex) 01100 => 01000
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    lsclear(Integer w)
    {
      // 01100: 01100 & 01011 = 01000
      return w & (w - 1);
    }

    /*!
     * Mask from trailing zeros.
     *
     * Ex) 01100 => 00011
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    t0mask(Integer w)
    {
      // 01100: 10011 & 01011 = 00011
      return ~w & (w - 1);
    }

    /*!
     * Complement mask from trailing ones.
     *
     * Ex) 01011 => 11100
     *
     * @param w
     * @return
     */
    template <typename Integer>
    inline
    typename enable_if_xint<Integer>::type
    t1maskc(Integer w)
    {
      // 01011: 10100 | 01100 = 11100
      return ~w | (w + 1);
    }

    /*
     * "first" = lowest-order/least-significant/right-most
     * "last" = highest-order/most-significant/left-most
     * "leading" = left-most
     * "trailing" = right-most
     *
     * ff1 (find first one)
     *     ff0(~x)
     *     pos: pop(x ^ (~(-x)))
     *     pos: sizeof(x)*CHAR_BIT - cl0(x & (-x))
     *     mask: x & (-x)
     * fl1 (find last one):
     *     fl0(~x)
     *     pos: log2<int>(x)
     *     pos: sizeof(x)*CHAR_BIT - 1 - cl0(x)
     * cl1 (count leading ones) / nl1 (number of leading ones):
     *     cl0(~x)
     * ct1 (count trailing ones) / nt1 (number of trailing ones):
     *     ct0(~x)
     *     (x==0) ? 0 : pop(x ^ (x + 1)) - 1
     * ff0 (find first zero):
     *     ff1(~x)
     *     mask: ~x & (x+1)
     * fl0 (find last zero):
     *     fl1(~x)
     * cl0 (count leading zeros) / nl0 (number of leading zeros):
     *     cl1(~x)
     *     sizeof(x)*CHAR_BIT - 1 - log2<int>(x)
     * ct0 (count trailing zeros) / nt0 (number of trailing zeros):
     *     ct1(~x)
     *     log2<int>(x & (-x))
     *     pop((x & (-x)) - 1)
     *     (x==0) ? sizeof(x)*CHAR_BIT : ff1<pos>(x) - 1
     *
     * ex) 1111110000001000
     * ff1 fl1 cl1 ct1 ff0 fl0 cl0 ct0
     *   4  32   6   0   1  10   0   3
     *
     * ex) 0000001111110111
     * ff1 fl1 cl1 ct1 ff0 fl0 cl0 ct0
     *   1  10   0   3   4  32   6   0
     */

  } /* namespace bitops */

} /* namespace gi */

#endif /* GI_LIBCXX_BITOPS_HPP_INCLUDED_ */
