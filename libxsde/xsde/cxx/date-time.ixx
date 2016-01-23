// file      : xsde/cxx/date-time.ixx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

namespace xsde
{
  namespace cxx
  {
    // time_zone
    //
    inline time_zone::
    time_zone ()
        : present_ (false)
    {
    }

    inline time_zone::
    time_zone (short h, short m)
        : present_ (true), hours_ (h), minutes_ (m)
    {
    }

    inline bool time_zone::
    zone_present () const
    {
      return present_;
    }

    inline void time_zone::
    zone_reset ()
    {
      present_ = false;
    }

    inline short time_zone::
    zone_hours () const
    {
      return hours_;
    }

    inline void time_zone::
    zone_hours (short h)
    {
      hours_ = h;
      present_ = true;
    }

    inline short time_zone::
    zone_minutes () const
    {
      return minutes_;
    }

    inline void time_zone::
    zone_minutes (short m)
    {
      minutes_ = m;
      present_ = true;
    }

    inline bool
    operator== (const time_zone& x, const time_zone& y)
    {
      return x.zone_present ()
        ? y.zone_present () &&
        x.zone_hours () == y.zone_hours () &&
        x.zone_minutes () == y.zone_minutes ()
        : !y.zone_present ();
    }

    inline bool
    operator!= (const time_zone& x, const time_zone& y)
    {
      return !(x == y);
    }

    // gday
    //
    inline gday::
    gday ()
    {
    }

    inline gday::
    gday (unsigned short day)
        : day_ (day)
    {
    }

    inline gday::
    gday (unsigned short day, short zone_h, short zone_m)
        : time_zone (zone_h, zone_m), day_ (day)
    {
    }

    inline unsigned short gday::
    day () const
    {
      return day_;
    }

    inline void gday::
    day (unsigned short day)
    {
      day_ = day;
    }

    inline bool
    operator== (const gday& x, const gday& y)
    {
      const time_zone& xz = x;
      const time_zone& yz = y;

      return x.day () == y.day () && xz == yz;
    }

    inline bool
    operator!= (const gday& x, const gday& y)
    {
      return !(x == y);
    }

    // gmonth
    //
    inline gmonth::
    gmonth ()
    {
    }

    inline gmonth::
    gmonth (unsigned short month)
        : month_ (month)
    {
    }

    inline gmonth::
    gmonth (unsigned short month, short zone_h, short zone_m)
        : time_zone (zone_h, zone_m), month_ (month)
    {
    }

    inline unsigned short gmonth::
    month () const
    {
      return month_;
    }

    inline void gmonth::
    month (unsigned short month)
    {
      month_ = month;
    }

    inline bool
    operator== (const gmonth& x, const gmonth& y)
    {
      const time_zone& xz = x;
      const time_zone& yz = y;

      return x.month () == y.month () && xz == yz;
    }

    inline bool
    operator!= (const gmonth& x, const gmonth& y)
    {
      return !(x == y);
    }

    // gyear
    //
    inline gyear::
    gyear ()
    {
    }

    inline gyear::
    gyear (int year)
        : year_ (year)
    {
    }

    inline gyear::
    gyear (int year, short zone_h, short zone_m)
        : time_zone (zone_h, zone_m), year_ (year)
    {
    }

    inline int gyear::
    year () const
    {
      return year_;
    }

    inline void gyear::
    year (int year)
    {
      year_ = year;
    }

    inline bool
    operator== (const gyear& x, const gyear& y)
    {
      const time_zone& xz = x;
      const time_zone& yz = y;

      return x.year () == y.year () && xz == yz;
    }

    inline bool
    operator!= (const gyear& x, const gyear& y)
    {
      return !(x == y);
    }

    // gmonth_day
    //
    inline gmonth_day::
    gmonth_day ()
    {
    }

    inline gmonth_day::
    gmonth_day (unsigned short month, unsigned short day)
        : month_ (month), day_ (day)
    {
    }

    inline gmonth_day::
    gmonth_day (unsigned short month, unsigned short day,
                short zone_h, short zone_m)
        : time_zone (zone_h, zone_m), month_ (month), day_ (day)
    {
    }

    inline unsigned short gmonth_day::
    month () const
    {
      return month_;
    }

    inline void gmonth_day::
    month (unsigned short month)
    {
      month_ = month;
    }

    inline unsigned short gmonth_day::
    day () const
    {
      return day_;
    }

    inline void gmonth_day::
    day (unsigned short day)
    {
      day_ = day;
    }

    inline bool
    operator== (const gmonth_day& x, const gmonth_day& y)
    {
      const time_zone& xz = x;
      const time_zone& yz = y;

      return x.month () == y.month () &&
        x.day () == y.day () &&
        xz == yz;
    }

    inline bool
    operator!= (const gmonth_day& x, const gmonth_day& y)
    {
      return !(x == y);
    }

    // gyear_month
    //
    inline gyear_month::
    gyear_month ()
    {
    }

    inline gyear_month::
    gyear_month (int year, unsigned short month)
        : year_ (year), month_ (month)
    {
    }

    inline gyear_month::
    gyear_month (int year, unsigned short month,
                 short zone_h, short zone_m)
        : time_zone (zone_h, zone_m), year_ (year), month_ (month)
    {
    }

    inline int gyear_month::
    year () const
    {
      return year_;
    }

    inline void gyear_month::
    year (int year)
    {
      year_ = year;
    }

    inline unsigned short gyear_month::
    month () const
    {
      return month_;
    }

    inline void gyear_month::
    month (unsigned short month)
    {
      month_ = month;
    }

    inline bool
    operator== (const gyear_month& x, const gyear_month& y)
    {
      const time_zone& xz = x;
      const time_zone& yz = y;

      return x.year () == y.year () &&
        x.month () == y.month () &&
        xz == yz;
    }

    inline bool
    operator!= (const gyear_month& x, const gyear_month& y)
    {
      return !(x == y);
    }

    // date
    //
    inline date::
    date ()
    {
    }

    inline date::
    date (int year, unsigned short month, unsigned short day)
        : year_ (year), month_ (month), day_ (day)
    {
    }

    inline date::
    date (int year, unsigned short month, unsigned short day,
          short zone_h, short zone_m)
        : time_zone (zone_h, zone_m),
          year_ (year), month_ (month), day_ (day)
    {
    }

    inline int date::
    year () const
    {
      return year_;
    }

    inline void date::
    year (int year)
    {
      year_ = year;
    }

    inline unsigned short date::
    month () const
    {
      return month_;
    }

    inline void date::
    month (unsigned short month)
    {
      month_ = month;
    }

    inline unsigned short date::
    day () const
    {
      return day_;
    }

    inline void date::
    day (unsigned short day)
    {
      day_ = day;
    }

    inline bool
    operator== (const date& x, const date& y)
    {
      const time_zone& xz = x;
      const time_zone& yz = y;

      return x.year () == y.year () &&
        x.month () == y.month () &&
        x.day () == y.day () &&
        xz == yz;
    }

    inline bool
    operator!= (const date& x, const date& y)
    {
      return !(x == y);
    }

    // time
    //
    inline time::
    time ()
    {
    }

    inline time::
    time (unsigned short hours, unsigned short minutes, double seconds)
        : hours_ (hours), minutes_ (minutes), seconds_ (seconds)
    {
    }

    inline time::
    time (unsigned short hours, unsigned short minutes, double seconds,
          short zone_h, short zone_m)
        : time_zone (zone_h, zone_m),
          hours_ (hours), minutes_ (minutes), seconds_ (seconds)
    {
    }

    inline unsigned short time::
    hours () const
    {
      return hours_;
    }

    inline void time::
    hours (unsigned short hours)
    {
      hours_ = hours;
    }

    inline unsigned short time::
    minutes () const
    {
      return minutes_;
    }

    inline void time::
    minutes (unsigned short minutes)
    {
      minutes_ = minutes;
    }

    inline double time::
    seconds () const
    {
      return seconds_;
    }

    inline void time::
    seconds (double seconds)
    {
      seconds_ = seconds;
    }

    inline bool
    operator== (const time& x, const time& y)
    {
      const time_zone& xz = x;
      const time_zone& yz = y;

      return x.hours () == y.hours () &&
        x.minutes () == y.minutes () &&
        x.seconds () == y.seconds () &&
        xz == yz;
    }

    inline bool
    operator!= (const time& x, const time& y)
    {
      return !(x == y);
    }

    // date_time
    //
    inline date_time::
    date_time ()
    {
    }

    inline date_time::
    date_time (int year, unsigned short month, unsigned short day,
               unsigned short hours, unsigned short minutes, double seconds)
        : year_ (year), month_ (month), day_ (day),
          hours_ (hours), minutes_ (minutes), seconds_ (seconds)
    {
    }

    inline date_time::
    date_time (int year, unsigned short month, unsigned short day,
               unsigned short hours, unsigned short minutes, double seconds,
               short zone_h, short zone_m)
        : time_zone (zone_h, zone_m),
          year_ (year), month_ (month), day_ (day),
          hours_ (hours), minutes_ (minutes), seconds_ (seconds)
    {
    }

    inline int date_time::
    year () const
    {
      return year_;
    }

    inline void date_time::
    year (int year)
    {
      year_ = year;
    }

    inline unsigned short date_time::
    month () const
    {
      return month_;
    }

    inline void date_time::
    month (unsigned short month)
    {
      month_ = month;
    }

    inline unsigned short date_time::
    day () const
    {
      return day_;
    }

    inline void date_time::
    day (unsigned short day)
    {
      day_ = day;
    }

    inline unsigned short date_time::
    hours () const
    {
      return hours_;
    }

    inline void date_time::
    hours (unsigned short hours)
    {
      hours_ = hours;
    }

    inline unsigned short date_time::
    minutes () const
    {
      return minutes_;
    }

    inline void date_time::
    minutes (unsigned short minutes)
    {
      minutes_ = minutes;
    }

    inline double date_time::
    seconds () const
    {
      return seconds_;
    }

    inline void date_time::
    seconds (double seconds)
    {
      seconds_ = seconds;
    }

    inline bool
    operator== (const date_time& x, const date_time& y)
    {
      const time_zone& xz = x;
      const time_zone& yz = y;

      return x.year () == y.year () &&
        x.month () == y.month () &&
        x.day () == y.day () &&
        x.hours () == y.hours () &&
        x.minutes () == y.minutes () &&
        x.seconds () == y.seconds () &&
        xz == yz;
    }

    inline bool
    operator!= (const date_time& x, const date_time& y)
    {
      return !(x == y);
    }

    // duration
    //
    inline duration::
    duration ()
    {
    }

    inline duration::
    duration (bool negative,
              unsigned int years, unsigned int months, unsigned int days,
              unsigned int hours, unsigned int minutes, double seconds)
        : negative_ (negative),
          years_ (years), months_ (months), days_ (days),
          hours_ (hours), minutes_ (minutes), seconds_ (seconds)
    {
    }

    inline bool duration::
    negative () const
    {
      return negative_;
    }

    inline void duration::
    negative (bool negative)
    {
      negative_ = negative;
    }

    inline unsigned int duration::
    years () const
    {
      return years_;
    }

    inline void duration::
    years (unsigned int years)
    {
      years_ = years;
    }

    inline unsigned int duration::
    months () const
    {
      return months_;
    }

    inline void duration::
    months (unsigned int months)
    {
      months_ = months;
    }

    inline unsigned int duration::
    days () const
    {
      return days_;
    }

    inline void duration::
    days (unsigned int days)
    {
      days_ = days;
    }

    inline unsigned int duration::
    hours () const
    {
      return hours_;
    }

    inline void duration::
    hours (unsigned int hours)
    {
      hours_ = hours;
    }

    inline unsigned int duration::
    minutes () const
    {
      return minutes_;
    }

    inline void duration::
    minutes (unsigned int minutes)
    {
      minutes_ = minutes;
    }

    inline double duration::
    seconds () const
    {
      return seconds_;
    }

    inline void duration::
    seconds (double seconds)
    {
      seconds_ = seconds;
    }

    inline bool
    operator== (const duration& x, const duration& y)
    {
      return x.negative () == y.negative () &&
        x.years () == y.years () &&
        x.months () == y.months () &&
        x.days () == y.days () &&
        x.hours () == y.hours () &&
        x.minutes () == y.minutes () &&
        x.seconds () == y.seconds ();
    }

    inline bool
    operator!= (const duration& x, const duration& y)
    {
      return !(x == y);
    }
  }
}
