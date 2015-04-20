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

#include <gi/bpl/bitset.hpp>

namespace gi
{

  class scrambler_config
  {
  private:

    std::size_t length;
    std::size_t fill;
  };

  template <typename Block, typename Allocator>
  class dynamic_scrambler
  {
  public:
    typedef dynamic_bitset<Block, Allocator> bits_type;

    void scramble(bits_type * bits);
    void descramble(bits_type * bits);
  };
}

#endif /* GI_LIBCXX_BPL_SCRAMBLER_HPP_INCLUDED_ */
