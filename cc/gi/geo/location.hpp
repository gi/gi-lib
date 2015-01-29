/*
 * location.hpp
 *
 *  Created on: Nov 13, 2014
 *      Author: s363792
 */

#ifndef GI_LIBCXX_GEO_LOCATION_HPP_
#define GI_LIBCXX_GEO_LOCATION_HPP_

namespace gi
{
  namespace geo
  {
    namespace cs
    {

      template< typename T1, typename T2 = T1, typename T3 = T2 >
      class vector3
      {
      public:

	const T1& get1() const { return m_1; }
	const T1& get2() const { return m_2; }
	const T1& get3() const { return m_3; }

      private:

	T1 m_1;
	T2 m_2;
	T3 m_3;
      };

      template< typename Angle, typename Height >
      class geodetic : public vector3<Angle,Angle,Height>
      {
      public:

	const Angle& lat() const { return get1(); }
	const Angle& lon() const { return get2(); }
	const Angle& alt() const { return get3(); }
      };

      template< typename T >
      class ecef : public vector3<T>
      {
      public:

	const T& x() const { return get1(); }
	const T& y() const { return get2(); }
	const T& z() const { return get3(); }
      };

    } /* namespace cs */
  } /* namespace geo */
} /* namespace gi */

#endif /* GI_LIBCXX_GEO_LOCATION_HPP_ */
