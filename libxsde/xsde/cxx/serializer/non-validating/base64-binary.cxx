// file      : xsde/cxx/serializer/non-validating/base64-binary.cxx
// author    : Boris Kolpackov <boris@codesynthesis.com>
// copyright : Copyright (c) 2005-2011 Code Synthesis Tools CC
// license   : GNU GPL v2 + exceptions; see accompanying LICENSE file

#include <xsde/cxx/serializer/non-validating/base64-binary.hxx>

#ifdef XSDE_CUSTOM_ALLOCATOR
#  include <xsde/cxx/allocator.hxx>
#endif

namespace xsde
{
  namespace cxx
  {
    namespace serializer
    {
      namespace non_validating
      {
        base64_binary_simpl::
        ~base64_binary_simpl ()
        {
          if (free_ && value_)
          {
            buffer* v = const_cast<buffer*> (value_);
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete v;
#else
            v->~buffer ();
            cxx::free (v);
#endif
          }
        }

        void base64_binary_simpl::
        pre (const buffer* value)
        {
          value_ = value;
        }

        static const char base64_tab[] = {
          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
          'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
          'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
          'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
          'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x',
          'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
          '8', '9', '+', '/', '\0'
        };

        inline void
        split_1 (char b, unsigned char& b1, unsigned char& b2)
        {
          unsigned char ub = static_cast<unsigned char> (b);
          b1 = ub >> 2;
          b2 = (ub & 0x3) << 4;
        }

        inline void
        split_2 (char b, unsigned char& b2, unsigned char& b3)
        {
          unsigned char ub = static_cast<unsigned char> (b);
          b2 |= ub >> 4;
          b3 = (ub & 0x0F) << 2;
        }

        inline void
        split_3 (char b, unsigned char& b3, unsigned char& b4)
        {
          unsigned char ub = static_cast<unsigned char> (b);
          b3 |= ub >> 6;
          b4 = ( ub & 0x3F );
        }

        void base64_binary_simpl::
        _serialize_content ()
        {
          // Maximum 76 characters per line, 76/4 = 19
          //
          const size_t quads_per_line = 19;
          char buf[quads_per_line * 4 + 1];

          if (size_t size = value_->size ())
          {
            const char* data = value_->data ();
            size_t quads = (size + 2) / 3;

            // Process all quadruplets except the last, one line at a time.
            //
            size_t i = 0;
            size_t j = 0;
            unsigned char b1, b2, b3, b4;

            for (; j < (quads - 1);)
            {
              for (; i < quads_per_line && j < (quads - 1); ++i, ++j)
              {
                split_1 (*data++, b1, b2);
                split_2 (*data++, b2, b3);
                split_3 (*data++, b3, b4);

                buf[i * 4] = base64_tab[b1];
                buf[i * 4 + 1] = base64_tab[b2];
                buf[i * 4 + 2] = base64_tab[b3];
                buf[i * 4 + 3] = base64_tab[b4];
              }

              if (i == quads_per_line)
              {
                buf[i * 4] = '\n';

#ifdef XSDE_EXCEPTIONS
                _characters (buf, i * 4 + 1);
#else
                if (!_characters (buf, i * 4 + 1))
                  break;
#endif
                i = 0;
              }
            }

#ifndef XSDE_EXCEPTIONS
            if (j == (quads - 1))
            {
#endif
            // Process last quadruplet. The first byte is always present.
            //
            split_1 (*data++, b1, b2);
            buf[i * 4] = base64_tab[b1];

            if (data != value_->end ())
            {
              // Second byte is present.
              //
              split_2 (*data++, b2, b3);
              buf[i * 4 + 1] = base64_tab[b2];

              if(data != value_->end ())
              {
                // Third byte is present.
                //
                split_3 (*data++, b3, b4);
                buf[i * 4 + 2] = base64_tab[b3];
                buf[i * 4 + 3] = base64_tab[b4];
              }
              else
              {
                buf[i * 4 + 2] = base64_tab[b3];
                buf[i * 4 + 3] = '=';
              }
            }
            else
            {
              buf[i * 4 + 1] = base64_tab[b2];
              buf[i * 4 + 2] = '=';
              buf[i * 4 + 3] = '=';
            }

            i++;

            buf[i * 4] = '\n';
            _characters (buf, i * 4 + 1);

#ifndef XSDE_EXCEPTIONS
            }
#endif
          }

          if (free_)
          {
            buffer* v = const_cast<buffer*> (value_);
#ifndef XSDE_CUSTOM_ALLOCATOR
            delete v;
#else
            v->~buffer ();
            cxx::free (v);
#endif
            value_ = 0;
          }
        }
      }
    }
  }
}
