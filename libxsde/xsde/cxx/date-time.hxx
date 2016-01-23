// file      : xsde/cxx/date-time.hxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#ifndef XSDE_CXX_DATE_TIME_HXX
#define XSDE_CXX_DATE_TIME_HXX

namespace xsde
{
  namespace cxx
  {
    //
    //
    class time_zone
    {
    public:
      time_zone ();
      time_zone (short hours, short minutes);

      // Returns true if time zone is specified.
      //
      bool
      zone_present () const;

      // Resets the time zone to the 'not specified' state.
      //
      void
      zone_reset ();

      short
      zone_hours () const;

      void
      zone_hours (short);

      short
      zone_minutes () const;

      void
      zone_minutes (short);

    private:
      bool present_;
      short hours_;
      short minutes_;
    };

    bool
    operator== (const time_zone&, const time_zone&);

    bool
    operator!= (const time_zone&, const time_zone&);

    //
    //
    class gday: public time_zone
    {
    public:
      gday ();
      explicit
      gday (unsigned short day);
      gday (unsigned short day, short zone_hours, short zone_minutes);

      unsigned short
      day () const;

      void
      day (unsigned short);

    private:
      unsigned short day_;
    };

    bool
    operator== (const gday&, const gday&);

    bool
    operator!= (const gday&, const gday&);

    //
    //
    class gmonth: public time_zone
    {
    public:
      gmonth ();
      explicit
      gmonth (unsigned short month);
      gmonth (unsigned short month, short zone_hours, short zone_minutes);

      unsigned short
      month () const;

      void
      month (unsigned short);

    private:
      unsigned short month_;
    };

    bool
    operator== (const gmonth&, const gmonth&);

    bool
    operator!= (const gmonth&, const gmonth&);

    //
    //
    class gyear: public time_zone
    {
    public:
      gyear ();
      explicit
      gyear (int year);
      gyear (int year, short zone_hours, short zone_minutes);

      int
      year () const;

      void
      year (int);

    private:
      int year_;
    };

    bool
    operator== (const gyear&, const gyear&);

    bool
    operator!= (const gyear&, const gyear&);

    //
    //
    class gmonth_day: public time_zone
    {
    public:
      gmonth_day ();
      gmonth_day (unsigned short month, unsigned short day);
      gmonth_day (unsigned short month, unsigned short day,
                  short zone_hours, short zone_minutes);

      unsigned short
      month () const;

      void
      month (unsigned short);

      unsigned short
      day () const;

      void
      day (unsigned short);

    private:
      unsigned short month_;
      unsigned short day_;
    };

    bool
    operator== (const gmonth_day&, const gmonth_day&);

    bool
    operator!= (const gmonth_day&, const gmonth_day&);

    //
    //
    class gyear_month: public time_zone
    {
    public:
      gyear_month ();
      gyear_month (int year, unsigned short month);
      gyear_month (int year, unsigned short month,
                   short zone_hours, short zone_minutes);

      int
      year () const;

      void
      year (int);

      unsigned short
      month () const;

      void
      month (unsigned short);

    private:
      int year_;
      unsigned short month_;
    };

    bool
    operator== (const gyear_month&, const gyear_month&);

    bool
    operator!= (const gyear_month&, const gyear_month&);

    //
    //
    class date: public time_zone
    {
    public:
      date ();
      date (int year, unsigned short month, unsigned short day);
      date (int year, unsigned short month, unsigned short day,
            short zone_hours, short zone_minutes);

      int
      year () const;

      void
      year (int);

      unsigned short
      month () const;

      void
      month (unsigned short);

      unsigned short
      day () const;

      void
      day (unsigned short);

    private:
      int year_;
      unsigned short month_;
      unsigned short day_;
    };

    bool
    operator== (const date&, const date&);

    bool
    operator!= (const date&, const date&);

    //
    //
    class time: public time_zone
    {
    public:
      time ();
      time (unsigned short hours, unsigned short minutes, double seconds);
      time (unsigned short hours, unsigned short minutes, double seconds,
            short zone_hours, short zone_minutes);

      unsigned short
      hours () const;

      void
      hours (unsigned short);

      unsigned short
      minutes () const;

      void
      minutes (unsigned short);

      double
      seconds () const;

      void
      seconds (double);

    private:
      unsigned short hours_;
      unsigned short minutes_;
      double seconds_;
    };

    bool
    operator== (const time&, const time&);

    bool
    operator!= (const time&, const time&);

    //
    //
    class date_time: public time_zone
    {
    public:
      date_time ();
      date_time (int year, unsigned short month, unsigned short day,
                 unsigned short hours, unsigned short minutes, double seconds);

      date_time (int year, unsigned short month, unsigned short day,
                 unsigned short hours, unsigned short minutes, double seconds,
                 short zone_hours, short zone_minutes);

      int
      year () const;

      void
      year (int);

      unsigned short
      month () const;

      void
      month (unsigned short);

      unsigned short
      day () const;

      void
      day (unsigned short);

      unsigned short
      hours () const;

      void
      hours (unsigned short);

      unsigned short
      minutes () const;

      void
      minutes (unsigned short);

      double
      seconds () const;

      void
      seconds (double);

    private:
      int year_;
      unsigned short month_;
      unsigned short day_;
      unsigned short hours_;
      unsigned short minutes_;
      double seconds_;
    };

    bool
    operator== (const date_time&, const date_time&);

    bool
    operator!= (const date_time&, const date_time&);

    //
    //
    class duration
    {
    public:
      duration ();
      duration (bool negative,
                unsigned int years, unsigned int months, unsigned int days,
                unsigned int hours, unsigned int minutes, double seconds);

      bool
      negative () const;

      void
      negative (bool);

      unsigned int
      years () const;

      void
      years (unsigned int);

      unsigned int
      months () const;

      void
      months (unsigned int);

      unsigned int
      days () const;

      void
      days (unsigned int);

      unsigned int
      hours () const;

      void
      hours (unsigned int);

      unsigned int
      minutes () const;

      void
      minutes (unsigned int);

      double
      seconds () const;

      void
      seconds (double);

    private:
      bool negative_;
      unsigned int years_;
      unsigned int months_;
      unsigned int days_;
      unsigned int hours_;
      unsigned int minutes_;
      double seconds_;
    };

    bool
    operator== (const duration&, const duration&);

    bool
    operator!= (const duration&, const duration&);
  }
}

#include <xsde/cxx/date-time.ixx>

#endif  // XSDE_CXX_DATE_TIME_HXX
