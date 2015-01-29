/* -*- C++ -*-
 *
 *   File Name: numarray.h
 *
 * Description:
 *
 *  Created on: Jan 22, 2014
 *      Author: s363792
 */

#ifndef GI_LIBCXX_NUMARRAY_HPP_INCLUDED_
#define GI_LIBCXX_NUMARRAY_HPP_INCLUDED_

#include <complex>
#include <limits>

namespace gi
{

  /*
   * Number array.
   */
  class numarray
  {
    static const size_t SIZE_MASK = 0x1F;
    static const size_t SIGN_MASK = 0x20;
    static const size_t INT_MASK = 0x40;
    //static const size_t FLT_MASK = 0;
    //static const size_t REAL_MASK = 0;
    static const size_t CPLX_MASK = 0x80;
    static const size_t TYPE_MASK = 0xFF;
    static const size_t OWN_MASK = 0x100;

  public:

    /*
     * Element type enum. The size indicates the number of bytes allocated for
     * the basic, fundamental scalar type.
     */
    enum type_t
    {
      VOID = 0,
//      REAL_INT_8  = (SIGN_MASK | REAL_MASK | INT_MASK | 1),
//      REAL_INT_16 = (SIGN_MASK | REAL_MASK | INT_MASK | 2),
//      REAL_INT_32 = (SIGN_MASK | REAL_MASK | INT_MASK | 4),
//      REAL_INT_64 = (SIGN_MASK | REAL_MASK | INT_MASK | 8),
//      REAL_UINT_8  = (REAL_MASK | INT_MASK | 1),
//      REAL_UINT_16 = (REAL_MASK | INT_MASK | 2),
//      REAL_UINT_32 = (REAL_MASK | INT_MASK | 4),
//      REAL_UINT_64 = (REAL_MASK | INT_MASK | 8),
//      CPLX_INT_8  = (SIGN_MASK | CPLX_MASK | INT_MASK | 1),
//      CPLX_INT_16 = (SIGN_MASK | CPLX_MASK | INT_MASK | 2),
//      CPLX_INT_32 = (SIGN_MASK | CPLX_MASK | INT_MASK | 4),
//      CPLX_INT_64 = (SIGN_MASK | CPLX_MASK | INT_MASK | 8),
//      CPLX_UINT_8  = (CPLX_MASK | INT_MASK | 1),
//      CPLX_UINT_16 = (CPLX_MASK | INT_MASK | 2),
//      CPLX_UINT_32 = (CPLX_MASK | INT_MASK | 4),
//      CPLX_UINT_64 = (CPLX_MASK | INT_MASK | 8),
      REAL_FLT_32 = (SIGN_MASK /*| REAL_MASK | FLT_MASK*/ | 4),
      REAL_FLT_64 = (SIGN_MASK /*| REAL_MASK | FLT_MASK*/ | 8),
      CPLX_FLT_32 = (SIGN_MASK | CPLX_MASK /*| FLT_MASK*/ | 4),
      CPLX_FLT_64 = (SIGN_MASK | CPLX_MASK /*| FLT_MASK*/ | 8)
    };

    template< typename T >
    struct traits
    {
      static type_t type = VOID;
    };

    numarray()
      : m_type(0),
        m_size(0),
        m_ptr(0)
    {}

    numarray(type_t type, size_t n)
      : m_type(type | OWN_MASK),
        m_size(n),
        m_ptr(allocate(type, n))
    {}

    ~numarray()
    {
      if (owned())
        deallocate(type(), m_ptr);
    }

    type_t type()      const { return m_type & TYPE_MASK; }
    size_t size()      const { return m_size; }
    void*  data()      const { return m_ptr; }
    bool   owned()     const { return m_type & OWN_MASK; }

    bool   real()      const { return !complex(); }
    bool   complex()   const { return m_type & CPLX_MASK; }

    /*
     * Returns the number of bytes per scalar.
     */
    size_t bps() const { return m_type & SIZE_MASK; }

    /*
     * Returns the number of bytes per element.
     */
    size_t bpe() const { return bps() * ape(); }

    /*
     * Returns the number of atoms per element.
     */
    size_t ape() const { return (complex() ? 2 : 1); }

    template< typename T >
    T* as()
    {
      return (traits<T>::type == (m_type & TYPE_MASK)) ? static_cast<T*>(m_ptr) : 0;
    }

    template< typename T >
    const T* as() const
    {
      return (traits<T>::type == (m_type & TYPE_MASK)) ? static_cast<const T*>(m_ptr) : 0;
    }

    template< typename T >
    void set(size_t size, T* ptr, bool own = true);

    static void* allocate(type_t type, size_t n);
    static void deallocate(type_t type, void* ptr);

    numarray& own(numarray& rhs)
    {
      if (this != &rhs)
      {
        m_type = rhs.m_type;
        m_size = rhs.m_size;
        m_ptr = rhs.m_ptr;
        rhs.m_type &= ~OWN_MASK;
      }
      return *this;
    }

    numarray& ref(const numarray& rhs)
    {
      if (this != &rhs)
      {
        m_type = rhs.m_type & ~OWN_MASK;
        m_size = rhs.m_size;
        m_ptr = rhs.m_ptr;
      }
      return *this;
    }

    void swap(numarray& rhs)
    {
      std::swap(m_type, rhs.m_type);
      std::swap(m_size, rhs.m_size);
      std::swap(m_ptr, rhs.m_ptr);
    }

  private:

    numarray(const numarray&) /* = delete */;
    numarray& operator=(const numarray&) /* = delete */;

    void set(type_t type, size_t size, void* ptr, bool own = true);

    size_t m_type;
    size_t m_size;
    void*  m_ptr;
  };

  // numarray::traits<T> specializations

  template<>
  struct numarray::traits<float>
  {
    static type_t type = REAL_FLT_32;
  };

  template<>
  struct numarray::traits<double>
  {
    static type_t type = REAL_FLT_64;
  };

  template< typename T >
  struct numarray::traits< std::complex<T> >
  {
    static type_t type = static_cast<type_t>(traits<T>::type | CPLX_MASK);
  };

  template<>
  struct numarray::traits< std::complex<float> >
  {
    static type_t type = CPLX_FLT_32;
  };

  template<>
  struct numarray::traits< std::complex<double> >
  {
    static type_t type = CPLX_FLT_64;
  };

  // numarray inline functions

  template< typename T > inline
  void numarray::set(size_t size, T* ptr, bool own)
  {
    set(traits<T>::type, size, ptr, own);
  }

  inline
  void numarray::set(type_t type, size_t size, void* ptr, bool own)
  {
    if (owned() && (ptr != m_ptr))
      deallocate(this->type(), m_ptr);
    m_type = type;
    m_size = size;
    m_ptr = ptr;
    if (own)
      m_type |= OWN_MASK;
  }

  inline
  void* numarray::allocate(type_t type, size_t n)
  {
    switch (type)
    {
      case traits< float >::type: return new float[n];
      case traits< double >::type: return new double[n];
      case traits< std::complex<float> >::type: return new std::complex<float>[n];
      case traits< std::complex<double> >::type: return new std::complex<double>[n];
    }
    return 0;
  }

  inline
  void numarray::deallocate(type_t type, void* ptr)
  {
    switch (type)
    {
      case traits< float >::type: delete[] ((float*) ptr); break;
      case traits< double >::type: delete[] ((double*) ptr); break;
      case traits< std::complex<float> >::type: delete[] ((std::complex<float>*) ptr); break;
      case traits< std::complex<double> >::type: delete[] ((std::complex<double>*) ptr); break;
    }
  }

} /* namespace gi */

#endif /* GI_LIBCXX_NUMARRAY_HPP_INCLUDED_ */
