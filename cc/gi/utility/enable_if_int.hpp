/* -*- C++ -*-
 *
 *   File Name: enable_if_int.hpp
 *
 * Description:
 *
 *  Created on: Jun 25, 2014
 *      Author: Zach Gianos
 */

#ifndef GI_LIBCXX_ENABLE_IF_INT_HPP_INCLUDED_
#define GI_LIBCXX_ENABLE_IF_INT_HPP_INCLUDED_

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/utility/enable_if.hpp>

namespace gi
{

  template <typename T, typename R = T>
  struct enable_if_xint : public ::boost::enable_if<::boost::is_integral<T>::type, R> {};

  template <typename T, typename R = T>
  struct enable_if_sint : public ::boost::enable_if<::boost::is_signed<T>::type, R> {};

  template <typename T, typename R = T>
  struct enable_if_uint : public ::boost::enable_if<::boost::is_unsigned<T>::type, R> {};

} /* namespace gi */

#endif /* GI_LIBCXX_ENABLE_IF_INT_HPP_INCLUDED_ */
