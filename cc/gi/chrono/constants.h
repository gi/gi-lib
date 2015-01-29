/* -*- C++ -*-
 *
 *   File Name: constants.h
 *
 * Description:
 *
 *  Created on: Apr 3, 2014
 *      Author: S363792
 */

#ifndef GI_LIBCXX_CONSTANTS_H_
#define GI_LIBCXX_CONSTANTS_H_

namespace gi
{
  namespace calendar
  {
    namespace days
    {
      enum id {sunday, monday, tuesday, wednesday, thursday, friday, saturday};

      template< id D > static inline const char* name()            { return "error"; }
      template< /**/ > static inline const char* name<sunday>()    { return "Sunday"; }
      template< /**/ > static inline const char* name<monday>()    { return "Monday"; }
      template< /**/ > static inline const char* name<tuesday>()   { return "Tuesday"; }
      template< /**/ > static inline const char* name<wednesday>() { return "Wednesday"; }
      template< /**/ > static inline const char* name<thursday>()  { return "Thursday"; }
      template< /**/ > static inline const char* name<friday>()    { return "Friday"; }
      template< /**/ > static inline const char* name<saturday>()  { return "Saturday"; }
    } /* namespace days */

    namespace months
    {
      enum id
      {
        january,
        february,
        march,
        april,
        may,
        june,
        july,
        august,
        september,
        october,
        november,
        december
      };

      template< id M > static inline const char* name()            { return "error"; }
      template< /**/ > static inline const char* name<january>()   { return "January"; }
      template< /**/ > static inline const char* name<february>()  { return "February"; }
      template< /**/ > static inline const char* name<march>()     { return "March"; }
      template< /**/ > static inline const char* name<april>()     { return "April"; }
      template< /**/ > static inline const char* name<may>()       { return "May"; }
      template< /**/ > static inline const char* name<june>()      { return "June"; }
      template< /**/ > static inline const char* name<july>()      { return "July"; }
      template< /**/ > static inline const char* name<august>()    { return "August"; }
      template< /**/ > static inline const char* name<september>() { return "September"; }
      template< /**/ > static inline const char* name<october>()   { return "October"; }
      template< /**/ > static inline const char* name<november>()  { return "November"; }
      template< /**/ > static inline const char* name<december>()  { return "December"; }
    } /* namespace months */

    template< months::id M, bool leap = false > struct days_in_month { static const int value = 0; };
    template<> struct days_in_month<months::january>         { static const int value = 31; };
    template<> struct days_in_month<months::february,false>  { static const int value = 28; };
    template<> struct days_in_month<months::february,true>   { static const int value = 29; };
    template<> struct days_in_month<months::march>           { static const int value = 31; };
    template<> struct days_in_month<months::april>           { static const int value = 30; };
    template<> struct days_in_month<months::may>             { static const int value = 31; };
    template<> struct days_in_month<months::june>            { static const int value = 30; };
    template<> struct days_in_month<months::july>            { static const int value = 31; };
    template<> struct days_in_month<months::august>          { static const int value = 31; };
    template<> struct days_in_month<months::september>       { static const int value = 30; };
    template<> struct days_in_month<months::october>         { static const int value = 31; };
    template<> struct days_in_month<months::november>        { static const int value = 30; };
    template<> struct days_in_month<months::december>        { static const int value = 31; };

    template< int year >
    struct is_leap_year
    {
      static const bool value = (!(year % 4) && (year % 100)) || !(year % 400);
    };

    template< bool leap  > struct days_in_year_base       { static const int value = 365; };
    template< /* true */ > struct days_in_year_base<true> { static const int value = 366; };

    template< int year > struct days_in_year : days_in_year_base<is_leap_year<year>::value> {};

    template< int Y, months::id M, int D >
    struct day_of_year
    {
      static const int value =
          D + days_in_month< (M-1), is_leap_year<Y>::value >::value
          + day_of_year< Y, (M-1), 0 >::value;
    };

    /* partial specialization for January */
    template< int Y, int D >
    struct day_of_year<Y, months::january, D>
    {
      static const int value = D;
    };

    template< int Y, months::id M, int D >
    struct days_left_in_year
    {
      static const int value =
          days_in_year<Y>::value - day_of_year<Y,M,D>::value;
    };

    template< int Y, months::id M = months::january, int D = 0 >
    struct epoch {};

    template< int I1, int I2 >
    struct min
    {
      static const int value = (I1 < I2 ? I1 : I2);
    };

    template< int I1, int I2 >
    struct max
    {
      static const int value = (I1 > I2 ? I1 : I2);
    };

    template< typename T1, typename T2 >
    struct difference
    {
      static const int value = 0;
    };

    template< int Y >
    struct difference< epoch<Y>, epoch<Y> >
    {
      static const int value = 0;
    };

    template< int Y, months::id M1, int D1, months::id M2, int D2 >
    struct difference< epoch<Y,M1,D1>, epoch<Y,M2,D2> >
    {
      static const int value = day_of_year<Y,M2,D2>::value - day_of_year<Y,M1,D1>::value;
    };

    template< int Y1, int Y2 >
    struct difference< epoch<Y1>, epoch<Y2> >
    {
      static const int value =
          signum<int,(Y2-Y1)>::value
          * (days_in_year<min<Y1,Y2>::value>::value
              + difference< epoch<min<Y1,Y2>::value+1>, epoch<max<Y1,Y2>::value> >::value);
    };

    template< bool P, bool N > struct signum_base { static const int value = 0; };
    template<> struct signum_base<true,false>     { static const int value = 1; };
    template<> struct signum_base<false,true>     { static const int value = -1; };
    template<> struct signum_base<true,true>      { /* error */ };
    template< typename T, T X > struct signum : signum_base<(X>0),(X<0)> {};

    template< int Y1, months::id M1, int D1, int Y2, months::id M2, int D2 >
    struct difference< epoch<Y1,M1,D1>, epoch<Y2,M2,D2> >
    {
      static const int value =
          day_of_year<Y2,M2,D2>::value + days_left_in_year<Y1,M1,D1>::value
          + difference< epoch<(Y1+1)>, epoch<Y2> >::value;
    };

    template< int y1, months::id m1, int d1, int y2, months::id m2, int d2 >
    inline int delta_days(epoch<y1,m1,d1> e1, epoch<y2,m2,d2> e2)
    {
      int days;
      int delta = y1 - y2;

      if (delta > 0)
      {
        days = days_left_in_year<y2,m2,d2>::value + day_of_year<y1,m1,d1>::value;
        for (delta--; delta > 0; delta--)
          days += days_in_year<y2+delta>::value;
      }
      else
      {
        days = days_left_in_year<y1,m1,d1>::value + day_of_year<y2,m2,d2>::value;
        for (delta++; delta < 0; delta++)
          days += days_in_year<y2+delta>::value;
      }
      return days;
    }

  }
}

#endif /* GI_LIBCXX_CONSTANTS_H_ */
