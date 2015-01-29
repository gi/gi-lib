/* -*- C++ -*-
 *
 *   File Name: unsigned_cast.hpp
 *
 * Description:
 *
 *  Created on: Jun 20, 2014
 *      Author: Zach Gianos
 */

#ifndef GI_LIBCXX_UNSIGNED_CAST_HPP_INCLUDED_
#define GI_LIBCXX_UNSIGNED_CAST_HPP_INCLUDED_

#include <boost/type_traits/make_unsigned.hpp>

namespace gi
{

  template <typename T>
  inline
  typename ::boost::make_unsigned<T>::type
  unsigned_cast(T v)
  {
    return v; // implicit conversion
  }

} /* namespace gi */

#endif /* GI_LIBCXX_UNSIGNED_CAST_HPP_INCLUDED_ */
