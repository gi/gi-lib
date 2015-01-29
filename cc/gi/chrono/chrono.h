/* -*- C++ -*-
 *
 *   File Name: chrono.h
 *
 * Description:
 *
 *  Created on: Mar 28, 2014
 *      Author: S363792
 */

#ifndef GI_LIBCXX_CHRONO_H_
#define GI_LIBCXX_CHRONO_H_

#include <gi/c++config.h>
#include <cmath>

namespace gi
{
  namespace chrono
  {

    class ddunit
    {
    public:

      ddunit(double d) { set(d); }

      ddunit(double seconds, double fractional)
        : m_integral(seconds), m_fractional(fractional)
      {}

      void set(double value)
      {
        m_fractional = std::modf(value, &m_integral);
      }

      ddunit operator+() const { return *this; }
      ddunit operator-() const { return ddunit(-m_integral, -m_fractional); }

      ddunit& operator++()    { ++m_integral; return *this; }
      ddunit  operator++(int) { return ddunit(m_integral++, m_fractional); }

      ddunit& operator--()    { --m_integral; return *this; }
      ddunit  operator--(int) { return ddunit(m_integral--, m_fractional); }

      ddunit& operator+=(const ddunit& rhs)
      {
        m_integral += rhs.m_integral;
        m_fractional += rhs.m_fractional;
        return *this;
      }

      ddunit& operator+=(double rhs)
      {
        m_fractional += std::modf(rhs, &rhs);
        m_integral += rhs;
        return *this;
      }

      ddunit& operator-=(const ddunit& rhs)
      {
        return (*this += -rhs);
      }

      ddunit& operator-=(double rhs)
      {
        return (*this += -rhs);
      }

      ddunit& operator*=(double rhs)
      {
        m_integral *= rhs;
        m_fractional *= rhs;
        return *this;
      }

      ddunit& operator/=(double rhs)
      {
        return *this *= (1 / rhs);
      }

      void normalize()
      {
        double integral;
        m_fractional = std::modf(m_fractional, &integral);
        m_integral += integral;
        if (m_integral > 0 & m_fractional < 0)
        {
          m_integral -= 1;
          m_fractional += 1;
        }
      }

    private:

      double m_integral;
      double m_fractional;
    };

    inline ddunit operator+(const ddunit& lhs, const ddunit& rhs)
    {
      return ddunit(lhs) += rhs;
    }

    inline ddunit operator+(double lhs, const ddunit& rhs)
    {
      return ddunit(lhs) += rhs;
    }

    inline ddunit operator+(const ddunit& lhs, double rhs)
    {
      return ddunit(lhs) += rhs;
    }

    inline ddunit operator-(const ddunit& lhs, const ddunit& rhs)
    {
      return ddunit(lhs) -= rhs;
    }

    inline ddunit operator-(double lhs, const ddunit& rhs)
    {
      return ddunit(lhs) += rhs;
    }

    inline ddunit operator-(const ddunit& lhs, double rhs)
    {
      return ddunit(lhs) -= rhs;
    }

    inline ddunit operator*(const ddunit& lhs, const ddunit& rhs)
    {
      return ddunit(lhs) *= rhs;
    }

    inline ddunit operator*(double lhs, const ddunit& rhs)
    {
      return ddunit(lhs) *= rhs;
    }

    inline ddunit operator*(const ddunit& lhs, double rhs)
    {
      return ddunit(lhs) *= rhs;
    }

    inline ddunit operator/(const ddunit& lhs, const ddunit& rhs)
    {
      return ddunit(lhs) /= rhs;
    }

    inline ddunit operator/(double lhs, const ddunit& rhs)
    {
      return ddunit(lhs) /= rhs;
    }

    inline ddunit operator/(const ddunit& lhs, double rhs)
    {
      return ddunit(lhs) /= rhs;
    }

  } /* namespace chrono */
} /* namespace gi */

#endif /* GI_LIBCXX_CHRONO_H_ */
