/* -*- C++ -*-
 *
 *   File Name: bitarray.hpp
 *
 * Description:
 *
 *  Created on: Jun 25, 2014
 *      Author: Zach Gianos
 */

#ifndef GI_LIBCXX_BPL_BITARRAY_HPP_INCLUDED_
#define GI_LIBCXX_BPL_BITARRAY_HPP_INCLUDED_

#include <boost/dynamic_bitset.hpp>

namespace gi
{

  template <typename Block, typename Allocator>
  class bitarray : public ::boost::dynamic_bitset<Block, Allocator>
  {
    typedef ::boost::dynamic_bitset<Block, Allocator> base_type;

  public:
    typedef typename base_type::block_type block_type;
    typedef typename base_type::allocator_type allocator_type;
    typedef typename base_type::size_type size_type;

    bitarray() {}
    ~bitarray() {}
  };

} /* namespace gi */

#endif /* GI_LIBCXX_BPL_BITARRAY_HPP_INCLUDED_ */
