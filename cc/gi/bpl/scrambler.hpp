/* -*- C++ -*-
 *
 *   File Name: scrambler.hpp
 *
 * Description:
 *
 *  Created on: Jun 25, 2014
 *      Author: Zach Gianos
 */

#ifndef GI_LIBCXX_BPL_SCRAMBLER_HPP_INCLUDED_
#define GI_LIBCXX_BPL_SCRAMBLER_HPP_INCLUDED_

#include <gi/bpl/bitarray.hpp>

namespace gi
{

  template <typename Block, typename Allocator>
  class scrambler
  {
  public:
    typedef bitarray<Block, Allocator> bits_type;

    void scramble(bits_type * bits);
    void descramble(bits_type * bits);
  };
}

#endif /* GI_LIBCXX_BPL_SCRAMBLER_HPP_INCLUDED_ */
