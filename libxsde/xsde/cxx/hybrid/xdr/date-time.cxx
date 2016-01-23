// file      : xsde/cxx/hybrid/xdr/date-time.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/hybrid/xdr/istream.hxx>
#include <xsde/cxx/hybrid/xdr/ostream.hxx>

namespace xsde
{
  namespace cxx
  {
    namespace hybrid
    {
#ifdef XSDE_EXCEPTIONS

      // operator<<
      //

      void
      operator<< (oxdrstream& s, const time_zone& x)
      {
        s << x.zone_hours ();
        s << x.zone_minutes ();
      }

      void
      operator<< (oxdrstream& s, const date& x)
      {
        s << x.year ();
        s << x.month ();
        s << x.day ();
        bool zp = x.zone_present ();
        s << zp;

        if (zp)
        {
          const time_zone& z = x;
          s << z;
        }
      }

      void
      operator<< (oxdrstream& s, const date_time& x)
      {
        s << x.year ();
        s << x.month ();
        s << x.day ();
        s << x.hours ();
        s << x.minutes ();
        s << x.seconds ();
        bool zp = x.zone_present ();
        s << zp;

        if (zp)
        {
          const time_zone& z = x;
          s << z;
        }
      }

      void
      operator<< (oxdrstream& s, const duration& x)
      {
        s << x.negative ();
        s << x.years ();
        s << x.months ();
        s << x.days ();
        s << x.hours ();
        s << x.minutes ();
        s << x.seconds ();
      }

      void
      operator<< (oxdrstream& s, const gday& x)
      {
        s << x.day ();
        bool zp = x.zone_present ();
        s << zp;

        if (zp)
        {
          const time_zone& z = x;
          s << z;
        }
      }

      void
      operator<< (oxdrstream& s, const gmonth& x)
      {
        s << x.month ();
        bool zp = x.zone_present ();
        s << zp;

        if (zp)
        {
          const time_zone& z = x;
          s << z;
        }
      }

      void
      operator<< (oxdrstream& s, const gmonth_day& x)
      {
        s << x.month ();
        s << x.day ();
        bool zp = x.zone_present ();
        s << zp;

        if (zp)
        {
          const time_zone& z = x;
          s << z;
        }
      }

      void
      operator<< (oxdrstream& s, const gyear& x)
      {
        s << x.year ();
        bool zp = x.zone_present ();
        s << zp;

        if (zp)
        {
          const time_zone& z = x;
          s << z;
        }
      }

      void
      operator<< (oxdrstream& s, const gyear_month& x)
      {
        s << x.year ();
        s << x.month ();
        bool zp = x.zone_present ();
        s << zp;

        if (zp)
        {
          const time_zone& z = x;
          s << z;
        }
      }

      void
      operator<< (oxdrstream& s, const time& x)
      {
        s << x.hours ();
        s << x.minutes ();
        s << x.seconds ();
        bool zp = x.zone_present ();
        s << zp;

        if (zp)
        {
          const time_zone& z = x;
          s << z;
        }
      }


      // operator>>
      //

      void
      operator>> (ixdrstream& s, time_zone& x)
      {
        short h, m;
        s >> h;
        s >> m;

        x.zone_hours (h);
        x.zone_minutes (m);
      }

      void
      operator>> (ixdrstream& s, date& x)
      {
        int y;
        unsigned short m, d;
        bool zp;

        s >> y;
        s >> m;
        s >> d;
        s >> zp;

        x.year (y);
        x.month (m);
        x.day (d);

        if (zp)
        {
          time_zone& z = x;
          s >> z;
        }
      }

      void
      operator>> (ixdrstream& s, date_time& x)
      {
        int y;
        unsigned short m, d, h, mi;
        double se;
        bool zp;

        s >> y;
        s >> m;
        s >> d;
        s >> h;
        s >> mi;
        s >> se;
        s >> zp;

        x.year (y);
        x.month (m);
        x.day (d);
        x.hours (h);
        x.minutes (mi);
        x.seconds (se);

        if (zp)
        {
          time_zone& z = x;
          s >> z;
        }
      }

      void
      operator>> (ixdrstream& s, duration& x)
      {
        bool n;
        unsigned int y, m, d, h, mi;
        double se;

        s >> n;
        s >> y;
        s >> m;
        s >> d;
        s >> h;
        s >> mi;
        s >> se;

        x.negative (n);
        x.years (y);
        x.months (m);
        x.days (d);
        x.hours (h);
        x.minutes (mi);
        x.seconds (se);
      }

      void
      operator>> (ixdrstream& s, gday& x)
      {
        unsigned short d;
        bool zp;

        s >> d;
        s >> zp;

        x.day (d);

        if (zp)
        {
          time_zone& z = x;
          s >> z;
        }
      }

      void
      operator>> (ixdrstream& s, gmonth& x)
      {
        unsigned short m;
        bool zp;

        s >> m;
        s >> zp;

        x.month (m);

        if (zp)
        {
          time_zone& z = x;
          s >> z;
        }
      }

      void
      operator>> (ixdrstream& s, gmonth_day& x)
      {
        unsigned short d, m;
        bool zp;

        s >> d;
        s >> m;
        s >> zp;

        x.day (d);
        x.month (m);

        if (zp)
        {
          time_zone& z = x;
          s >> z;
        }
      }

      void
      operator>> (ixdrstream& s, gyear& x)
      {
        int y;
        bool zp;

        s >> y;
        s >> zp;

        x.year (y);

        if (zp)
        {
          time_zone& z = x;
          s >> z;
        }
      }

      void
      operator>> (ixdrstream& s, gyear_month& x)
      {
        int y;
        unsigned short m;
        bool zp;

        s >> y;
        s >> m;
        s >> zp;

        x.year (y);
        x.month (m);

        if (zp)
        {
          time_zone& z = x;
          s >> z;
        }
      }

      void
      operator>> (ixdrstream& s, time& x)
      {
        unsigned short h, m;
        double se;
        bool zp;

        s >> h;
        s >> m;
        s >> se;
        s >> zp;

        x.hours (h);
        x.minutes (m);
        x.seconds (se);

        if (zp)
        {
          time_zone& z = x;
          s >> z;
        }
      }

#else // XSDE_EXCEPTIONS

      // operator<<
      //

      bool
      operator<< (oxdrstream& s, const time_zone& x)
      {
        return s << x.zone_hours () && s << x.zone_minutes ();
      }

      bool
      operator<< (oxdrstream& s, const date& x)
      {
        bool zp = x.zone_present ();

        if (!(s << x.year ())  ||
            !(s << x.month ()) ||
            !(s << x.day ())   ||
            !(s << zp))
          return false;

        if (zp)
        {
          const time_zone& z = x;
          return s << z;
        }

        return true;
      }

      bool
      operator<< (oxdrstream& s, const date_time& x)
      {
        bool zp = x.zone_present ();

        if (!(s << x.year ())    ||
            !(s << x.month ())   ||
            !(s << x.day ())     ||
            !(s << x.hours ())   ||
            !(s << x.minutes ()) ||
            !(s << x.seconds ()) ||
            !(s << zp))
          return false;

        if (zp)
        {
          const time_zone& z = x;
          return s << z;
        }

        return true;
      }

      bool
      operator<< (oxdrstream& s, const duration& x)
      {
        return s << x.negative () &&
          s << x.years () &&
          s << x.months () &&
          s << x.days () &&
          s << x.hours () &&
          s << x.minutes () &&
          s << x.seconds ();
      }

      bool
      operator<< (oxdrstream& s, const gday& x)
      {
        bool zp = x.zone_present ();


        if (!(s << x.day ()) || !(s << zp))
          return false;

        if (zp)
        {
          const time_zone& z = x;
          return s << z;
        }

        return true;
      }

      bool
      operator<< (oxdrstream& s, const gmonth& x)
      {
        bool zp = x.zone_present ();

        if (!(s << x.month ()) || !(s << zp))
          return false;

        if (zp)
        {
          const time_zone& z = x;
          return s << z;
        }

        return true;
      }

      bool
      operator<< (oxdrstream& s, const gmonth_day& x)
      {
        bool zp = x.zone_present ();

        if (!(s << x.month ()) || !(s << x.day ()) || !(s << zp))
          return false;

        if (zp)
        {
          const time_zone& z = x;
          return s << z;
        }

        return true;
      }

      bool
      operator<< (oxdrstream& s, const gyear& x)
      {
        bool zp = x.zone_present ();

        if (!(s << x.year ()) || !(s << zp))
          return false;

        if (zp)
        {
          const time_zone& z = x;
          return s << z;
        }

        return true;
      }

      bool
      operator<< (oxdrstream& s, const gyear_month& x)
      {
        bool zp = x.zone_present ();

        if (!(s << x.year ()) || !(s << x.month ()) || !(s << zp))
          return false;

        if (zp)
        {
          const time_zone& z = x;
          return s << z;
        }

        return true;
      }

      bool
      operator<< (oxdrstream& s, const time& x)
      {
        bool zp = x.zone_present ();

        if (!(s << x.hours ())   ||
            !(s << x.minutes ()) ||
            !(s << x.seconds ()) ||
            !(s << zp))
          return false;

        if (zp)
        {
          const time_zone& z = x;
          return s << z;
        }

        return true;
      }


      // operator>>
      //

      bool
      operator>> (ixdrstream& s, time_zone& x)
      {
        short h, m;

        if (!(s >> h) || !(s >> m))
          return false;

        x.zone_hours (h);
        x.zone_minutes (m);

        return true;
      }

      bool
      operator>> (ixdrstream& s, date& x)
      {
        int y;
        unsigned short m, d;
        bool zp;

        if (!(s >> y) || !(s >> m) || !(s >> d) || !(s >> zp))
          return false;

        x.year (y);
        x.month (m);
        x.day (d);

        if (zp)
        {
          time_zone& z = x;
          return s >> z;
        }

        return true;
      }

      bool
      operator>> (ixdrstream& s, date_time& x)
      {
        int y;
        unsigned short m, d, h, mi;
        double se;
        bool zp;

        if (!(s >> y) || !(s >> m) || !(s >> d) ||
            !(s >> h) || !(s >> mi) || !(s >> se) || !(s >> zp))
          return false;

        x.year (y);
        x.month (m);
        x.day (d);
        x.hours (h);
        x.minutes (mi);
        x.seconds (se);

        if (zp)
        {
          time_zone& z = x;
          return s >> z;
        }

        return true;
      }

      bool
      operator>> (ixdrstream& s, duration& x)
      {
        bool n;
        unsigned int y, m, d, h, mi;
        double se;

        if (!(s >> n) || !(s >> y) || !(s >> m) || !(s >> d) ||
            !(s >> h) || !(s >> mi) || !(s >> se))
          return false;

        x.negative (n);
        x.years (y);
        x.months (m);
        x.days (d);
        x.hours (h);
        x.minutes (mi);
        x.seconds (se);

        return true;
      }

      bool
      operator>> (ixdrstream& s, gday& x)
      {
        unsigned short d;
        bool zp;

        if (!(s >> d) || !(s >> zp))
          return false;

        x.day (d);

        if (zp)
        {
          time_zone& z = x;
          return s >> z;
        }

        return true;
      }

      bool
      operator>> (ixdrstream& s, gmonth& x)
      {
        unsigned short m;
        bool zp;

        if (!(s >> m) || !(s >> zp))
          return false;

        x.month (m);

        if (zp)
        {
          time_zone& z = x;
          return s >> z;
        }

        return true;
      }

      bool
      operator>> (ixdrstream& s, gmonth_day& x)
      {
        unsigned short d, m;
        bool zp;

        if (!(s >> d) || !(s >> m) || !(s >> zp))
          return false;

        x.day (d);
        x.month (m);

        if (zp)
        {
          time_zone& z = x;
          return s >> z;
        }

        return true;
      }

      bool
      operator>> (ixdrstream& s, gyear& x)
      {
        int y;
        bool zp;

        if (!(s >> y) || !(s >> zp))
          return false;

        x.year (y);

        if (zp)
        {
          time_zone& z = x;
          return s >> z;
        }

        return true;
      }

      bool
      operator>> (ixdrstream& s, gyear_month& x)
      {
        int y;
        unsigned short m;
        bool zp;

        if (!(s >> y) || !(s >> m) || !(s >> zp))
          return false;

        x.year (y);
        x.month (m);

        if (zp)
        {
          time_zone& z = x;
          return s >> z;
        }

        return true;
      }

      bool
      operator>> (ixdrstream& s, time& x)
      {
        unsigned short h, m;
        double se;
        bool zp;

        if (!(s >> h) || !(s >> m) || !(s >> se) || !(s >> zp))
          return false;

        x.hours (h);
        x.minutes (m);
        x.seconds (se);

        if (zp)
        {
          time_zone& z = x;
          return s >> z;
        }

        return true;
      }

#endif // XSDE_EXCEPTIONS
    }
  }
}
