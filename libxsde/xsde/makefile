root := ../..

include $(root)/build/config.make
include $(root)/build/c/rules.make
include $(root)/build/cxx/rules.make

EXTRA_CPPFLAGS := -I..

src := c/expat/xmlparse.c c/expat/xmlrole.c c/expat/xmltok.c
src += c/genx/genx.c c/genx/char-props.c

ifneq ($(XSDE_PARSER_VALIDATION)$(XSDE_SERIALIZER_VALIDATION),nn)
ifeq ($(XSDE_REGEXP),y)
src += c/regexp/chvalid.c c/regexp/xmlunicode.c c/regexp/xmlregexp.c
endif
endif

ifeq ($(XSDE_CUSTOM_ALLOCATOR),y)
ifeq ($(XSDE_DEFAULT_ALLOCATOR),y)
src += allocator.c
endif
endif

src += cxx/string.cxx cxx/string-search.cxx cxx/ro-string.cxx cxx/stack.cxx

ifeq ($(XSDE_CUSTOM_ALLOCATOR),y)
ifeq ($(XSDE_EXCEPTIONS),y)
src += cxx/allocator.cxx
endif
endif

ifeq ($(XSDE_ENCODING),iso8859-1)
src += cxx/iso8859-1.cxx
endif

ifeq ($(XSDE_STL),n)
src += cxx/strdupx.cxx
endif

ifeq ($(XSDE_EXCEPTIONS),n)
src += cxx/sys-error.cxx
endif

ifneq ($(XSDE_PARSER_VALIDATION)$(XSDE_SERIALIZER_VALIDATION),nn)
src += cxx/schema-error.cxx
endif

ifeq ($(XSDE_POLYMORPHIC),y)
src += cxx/hashmap.cxx
endif

# Common data types.
#
src += cxx/buffer.cxx cxx/sequence-base.cxx

ifeq ($(XSDE_STL),y)
src += cxx/string-sequence-stl.cxx
else
src += cxx/qname.cxx cxx/string-sequence.cxx
endif


## XML
##
ifneq ($(XSDE_PARSER_VALIDATION)$(XSDE_SERIALIZER_VALIDATION),nn)
src += cxx/xml/char-table.cxx cxx/xml/ncname.cxx
endif


## C++/Hybrid
##
src +=                         \
cxx/hybrid/any-type.cxx        \
cxx/hybrid/any-type-pimpl.cxx  \
cxx/hybrid/any-type-pskel.cxx  \
cxx/hybrid/any-type-simpl.cxx  \
cxx/hybrid/any-type-sskel.cxx  \
cxx/hybrid/sequence.cxx

ifeq ($(XSDE_POLYMORPHIC),y)
src +=                        \
cxx/hybrid/parser-map.cxx     \
cxx/hybrid/serializer-map.cxx
endif

ifeq ($(XSDE_CDR),y)
src +=                             \
cxx/hybrid/cdr/exceptions.cxx      \
cxx/hybrid/cdr/istream.cxx         \
cxx/hybrid/cdr/ostream.cxx         \
cxx/hybrid/cdr/qname.cxx           \
cxx/hybrid/cdr/date-time.cxx       \
cxx/hybrid/cdr/string-sequence.cxx
endif

ifeq ($(XSDE_XDR),y)
src +=                             \
cxx/hybrid/xdr/exceptions.cxx      \
cxx/hybrid/xdr/istream.cxx         \
cxx/hybrid/xdr/ostream.cxx         \
cxx/hybrid/xdr/qname.cxx           \
cxx/hybrid/xdr/date-time.cxx       \
cxx/hybrid/xdr/string-sequence.cxx
endif

## C++/Parser
##
src += cxx/parser/elements.cxx
src += cxx/parser/expat/document.cxx cxx/parser/expat/xml-error.cxx

ifeq ($(XSDE_POLYMORPHIC),y)
src += cxx/parser/map.cxx cxx/parser/substitution-map.cxx
endif

ifeq ($(XSDE_EXCEPTIONS),y)
src += cxx/parser/exceptions.cxx
else
src += cxx/parser/error.cxx
endif

# Parser implementations.
#
ifeq ($(XSDE_PARSER_VALIDATION),y)

src +=                                          \
cxx/parser/validating/parser.cxx                \
cxx/parser/validating/time-zone.cxx             \
cxx/parser/validating/string-common.cxx         \
cxx/parser/validating/xml-schema-pskel.cxx

ifeq ($(XSDE_POLYMORPHIC),y)
src += cxx/parser/validating/inheritance-map.cxx
endif

src +=                                          \
cxx/parser/validating/boolean.cxx               \
cxx/parser/validating/number.cxx                \
cxx/parser/validating/byte.cxx                  \
cxx/parser/validating/unsigned-byte.cxx         \
cxx/parser/validating/short.cxx                 \
cxx/parser/validating/unsigned-short.cxx        \
cxx/parser/validating/int.cxx                   \
cxx/parser/validating/unsigned-int.cxx          \
cxx/parser/validating/integer.cxx               \
cxx/parser/validating/negative-integer.cxx      \
cxx/parser/validating/non-positive-integer.cxx  \
cxx/parser/validating/positive-integer.cxx      \
cxx/parser/validating/non-negative-integer.cxx  \
cxx/parser/validating/float.cxx                 \
cxx/parser/validating/double.cxx                \
cxx/parser/validating/decimal.cxx

ifeq ($(XSDE_LONGLONG),y)
src +=                                          \
cxx/parser/validating/long-long.cxx             \
cxx/parser/validating/unsigned-long-long.cxx
else
src +=                                          \
cxx/parser/validating/long.cxx                  \
cxx/parser/validating/unsigned-long.cxx
endif

ifeq ($(XSDE_STL),y)

src +=                                          \
cxx/parser/validating/any-simple-type-stl.cxx   \
cxx/parser/validating/string-stl.cxx            \
cxx/parser/validating/normalized-string-stl.cxx \
cxx/parser/validating/token-stl.cxx             \
cxx/parser/validating/name-stl.cxx              \
cxx/parser/validating/nmtoken-stl.cxx           \
cxx/parser/validating/nmtokens-stl.cxx          \
cxx/parser/validating/ncname-stl.cxx            \
cxx/parser/validating/id-stl.cxx                \
cxx/parser/validating/idref-stl.cxx             \
cxx/parser/validating/idrefs-stl.cxx            \
cxx/parser/validating/language-stl.cxx          \
cxx/parser/validating/uri-stl.cxx               \
cxx/parser/validating/qname-stl.cxx

else

src +=                                       \
cxx/parser/validating/any-simple-type.cxx    \
cxx/parser/validating/string.cxx             \
cxx/parser/validating/normalized-string.cxx  \
cxx/parser/validating/token.cxx              \
cxx/parser/validating/name.cxx               \
cxx/parser/validating/nmtoken.cxx            \
cxx/parser/validating/nmtokens.cxx           \
cxx/parser/validating/ncname.cxx             \
cxx/parser/validating/id.cxx                 \
cxx/parser/validating/idref.cxx              \
cxx/parser/validating/idrefs.cxx             \
cxx/parser/validating/language.cxx           \
cxx/parser/validating/uri.cxx                \
cxx/parser/validating/qname.cxx

endif # stl

src +=                                       \
cxx/parser/validating/base64-binary.cxx      \
cxx/parser/validating/hex-binary.cxx         \
cxx/parser/validating/gday.cxx               \
cxx/parser/validating/gmonth.cxx             \
cxx/parser/validating/gyear.cxx              \
cxx/parser/validating/gmonth-day.cxx         \
cxx/parser/validating/gyear-month.cxx        \
cxx/parser/validating/date.cxx               \
cxx/parser/validating/time.cxx               \
cxx/parser/validating/date-time.cxx          \
cxx/parser/validating/duration.cxx

else # validation

src +=                                              \
cxx/parser/non-validating/parser.cxx                \
cxx/parser/non-validating/time-zone.cxx             \
cxx/parser/non-validating/string-common.cxx         \
cxx/parser/non-validating/xml-schema-pskel.cxx

src +=                                              \
cxx/parser/non-validating/boolean.cxx               \
cxx/parser/non-validating/number.cxx                \
cxx/parser/non-validating/byte.cxx                  \
cxx/parser/non-validating/unsigned-byte.cxx         \
cxx/parser/non-validating/short.cxx                 \
cxx/parser/non-validating/unsigned-short.cxx        \
cxx/parser/non-validating/int.cxx                   \
cxx/parser/non-validating/unsigned-int.cxx          \
cxx/parser/non-validating/integer.cxx               \
cxx/parser/non-validating/negative-integer.cxx      \
cxx/parser/non-validating/non-positive-integer.cxx  \
cxx/parser/non-validating/positive-integer.cxx      \
cxx/parser/non-validating/non-negative-integer.cxx  \
cxx/parser/non-validating/float.cxx                 \
cxx/parser/non-validating/double.cxx                \
cxx/parser/non-validating/decimal.cxx

ifeq ($(XSDE_LONGLONG),y)
src +=                                              \
cxx/parser/non-validating/long-long.cxx             \
cxx/parser/non-validating/unsigned-long-long.cxx
else
src +=                                              \
cxx/parser/non-validating/long.cxx                  \
cxx/parser/non-validating/unsigned-long.cxx
endif

ifeq ($(XSDE_STL),y)

src +=                                              \
cxx/parser/non-validating/any-simple-type-stl.cxx   \
cxx/parser/non-validating/string-stl.cxx            \
cxx/parser/non-validating/normalized-string-stl.cxx \
cxx/parser/non-validating/token-stl.cxx             \
cxx/parser/non-validating/name-stl.cxx              \
cxx/parser/non-validating/nmtoken-stl.cxx           \
cxx/parser/non-validating/nmtokens-stl.cxx          \
cxx/parser/non-validating/ncname-stl.cxx            \
cxx/parser/non-validating/id-stl.cxx                \
cxx/parser/non-validating/idref-stl.cxx             \
cxx/parser/non-validating/idrefs-stl.cxx            \
cxx/parser/non-validating/language-stl.cxx          \
cxx/parser/non-validating/uri-stl.cxx               \
cxx/parser/non-validating/qname-stl.cxx

else

src +=                                           \
cxx/parser/non-validating/any-simple-type.cxx    \
cxx/parser/non-validating/string.cxx             \
cxx/parser/non-validating/normalized-string.cxx  \
cxx/parser/non-validating/token.cxx              \
cxx/parser/non-validating/name.cxx               \
cxx/parser/non-validating/nmtoken.cxx            \
cxx/parser/non-validating/nmtokens.cxx           \
cxx/parser/non-validating/ncname.cxx             \
cxx/parser/non-validating/id.cxx                 \
cxx/parser/non-validating/idref.cxx              \
cxx/parser/non-validating/idrefs.cxx             \
cxx/parser/non-validating/language.cxx           \
cxx/parser/non-validating/uri.cxx                \
cxx/parser/non-validating/qname.cxx

endif # stl

src +=                                           \
cxx/parser/non-validating/base64-binary.cxx      \
cxx/parser/non-validating/hex-binary.cxx         \
cxx/parser/non-validating/gday.cxx               \
cxx/parser/non-validating/gmonth.cxx             \
cxx/parser/non-validating/gyear.cxx              \
cxx/parser/non-validating/gmonth-day.cxx         \
cxx/parser/non-validating/gyear-month.cxx        \
cxx/parser/non-validating/date.cxx               \
cxx/parser/non-validating/time.cxx               \
cxx/parser/non-validating/date-time.cxx          \
cxx/parser/non-validating/duration.cxx

endif # validation


## C++/Serializer
##
src += cxx/serializer/elements.cxx cxx/serializer/context.cxx
src += cxx/serializer/genx/document.cxx cxx/serializer/genx/xml-error.cxx

ifeq ($(XSDE_POLYMORPHIC),y)
src += cxx/serializer/map.cxx cxx/serializer/substitution-map.cxx
endif

ifeq ($(XSDE_EXCEPTIONS),y)
src += cxx/serializer/exceptions.cxx
else
src += cxx/serializer/error.cxx
endif

# Serializer implementations.
#
ifeq ($(XSDE_SERIALIZER_VALIDATION),y)

src +=                                              \
cxx/serializer/validating/serializer.cxx            \
cxx/serializer/validating/time-zone.cxx             \
cxx/serializer/validating/string-common.cxx         \
cxx/serializer/validating/xml-schema-sskel.cxx

ifeq ($(XSDE_POLYMORPHIC),y)
src += cxx/serializer/validating/inheritance-map.cxx
endif

src +=                                              \
cxx/serializer/validating/boolean.cxx               \
cxx/serializer/validating/byte.cxx                  \
cxx/serializer/validating/unsigned-byte.cxx         \
cxx/serializer/validating/short.cxx                 \
cxx/serializer/validating/unsigned-short.cxx        \
cxx/serializer/validating/int.cxx                   \
cxx/serializer/validating/unsigned-int.cxx          \
cxx/serializer/validating/integer.cxx               \
cxx/serializer/validating/negative-integer.cxx      \
cxx/serializer/validating/non-positive-integer.cxx  \
cxx/serializer/validating/positive-integer.cxx      \
cxx/serializer/validating/non-negative-integer.cxx  \
cxx/serializer/validating/float.cxx                 \
cxx/serializer/validating/double.cxx                \
cxx/serializer/validating/decimal.cxx

ifeq ($(XSDE_LONGLONG),y)
src +=                                              \
cxx/serializer/validating/long-long.cxx             \
cxx/serializer/validating/unsigned-long-long.cxx
else
src +=                                              \
cxx/serializer/validating/long.cxx                  \
cxx/serializer/validating/unsigned-long.cxx
endif

ifeq ($(XSDE_STL),y)

src +=                                              \
cxx/serializer/validating/any-simple-type-stl.cxx   \
cxx/serializer/validating/string-stl.cxx            \
cxx/serializer/validating/normalized-string-stl.cxx \
cxx/serializer/validating/token-stl.cxx             \
cxx/serializer/validating/name-stl.cxx              \
cxx/serializer/validating/nmtoken-stl.cxx           \
cxx/serializer/validating/ncname-stl.cxx            \
cxx/serializer/validating/id-stl.cxx                \
cxx/serializer/validating/idref-stl.cxx             \
cxx/serializer/validating/language-stl.cxx          \
cxx/serializer/validating/uri-stl.cxx               \
cxx/serializer/validating/idrefs-stl.cxx            \
cxx/serializer/validating/nmtokens-stl.cxx          \
cxx/serializer/validating/qname-stl.cxx

else

src +=                                           \
cxx/serializer/validating/any-simple-type.cxx    \
cxx/serializer/validating/string.cxx             \
cxx/serializer/validating/normalized-string.cxx  \
cxx/serializer/validating/token.cxx              \
cxx/serializer/validating/name.cxx               \
cxx/serializer/validating/nmtoken.cxx            \
cxx/serializer/validating/ncname.cxx             \
cxx/serializer/validating/id.cxx                 \
cxx/serializer/validating/idref.cxx              \
cxx/serializer/validating/language.cxx           \
cxx/serializer/validating/uri.cxx                \
cxx/serializer/validating/idrefs.cxx             \
cxx/serializer/validating/nmtokens.cxx           \
cxx/serializer/validating/qname.cxx

endif # stl

src +=                                           \
cxx/serializer/validating/base64-binary.cxx      \
cxx/serializer/validating/hex-binary.cxx         \
cxx/serializer/validating/gday.cxx               \
cxx/serializer/validating/gmonth.cxx             \
cxx/serializer/validating/gyear.cxx              \
cxx/serializer/validating/gmonth-day.cxx         \
cxx/serializer/validating/gyear-month.cxx        \
cxx/serializer/validating/date.cxx               \
cxx/serializer/validating/time.cxx               \
cxx/serializer/validating/date-time.cxx          \
cxx/serializer/validating/duration.cxx

else # validation

src +=                                                  \
cxx/serializer/non-validating/serializer.cxx            \
cxx/serializer/non-validating/time-zone.cxx             \
cxx/serializer/non-validating/xml-schema-sskel.cxx

src +=                                                  \
cxx/serializer/non-validating/boolean.cxx               \
cxx/serializer/non-validating/byte.cxx                  \
cxx/serializer/non-validating/unsigned-byte.cxx         \
cxx/serializer/non-validating/short.cxx                 \
cxx/serializer/non-validating/unsigned-short.cxx        \
cxx/serializer/non-validating/int.cxx                   \
cxx/serializer/non-validating/unsigned-int.cxx          \
cxx/serializer/non-validating/integer.cxx               \
cxx/serializer/non-validating/negative-integer.cxx      \
cxx/serializer/non-validating/non-positive-integer.cxx  \
cxx/serializer/non-validating/positive-integer.cxx      \
cxx/serializer/non-validating/non-negative-integer.cxx  \
cxx/serializer/non-validating/float.cxx                 \
cxx/serializer/non-validating/double.cxx                \
cxx/serializer/non-validating/decimal.cxx

ifeq ($(XSDE_LONGLONG),y)
src +=                                                  \
cxx/serializer/non-validating/long-long.cxx             \
cxx/serializer/non-validating/unsigned-long-long.cxx
else
src +=                                                  \
cxx/serializer/non-validating/long.cxx                  \
cxx/serializer/non-validating/unsigned-long.cxx
endif

ifeq ($(XSDE_STL),y)

src +=                                                  \
cxx/serializer/non-validating/any-simple-type-stl.cxx   \
cxx/serializer/non-validating/string-stl.cxx            \
cxx/serializer/non-validating/normalized-string-stl.cxx \
cxx/serializer/non-validating/token-stl.cxx             \
cxx/serializer/non-validating/name-stl.cxx              \
cxx/serializer/non-validating/nmtoken-stl.cxx           \
cxx/serializer/non-validating/ncname-stl.cxx            \
cxx/serializer/non-validating/id-stl.cxx                \
cxx/serializer/non-validating/idref-stl.cxx             \
cxx/serializer/non-validating/language-stl.cxx          \
cxx/serializer/non-validating/uri-stl.cxx               \
cxx/serializer/non-validating/idrefs-stl.cxx            \
cxx/serializer/non-validating/nmtokens-stl.cxx          \
cxx/serializer/non-validating/qname-stl.cxx

else

src +=                                               \
cxx/serializer/non-validating/any-simple-type.cxx    \
cxx/serializer/non-validating/string.cxx             \
cxx/serializer/non-validating/normalized-string.cxx  \
cxx/serializer/non-validating/token.cxx              \
cxx/serializer/non-validating/name.cxx               \
cxx/serializer/non-validating/nmtoken.cxx            \
cxx/serializer/non-validating/ncname.cxx             \
cxx/serializer/non-validating/id.cxx                 \
cxx/serializer/non-validating/idref.cxx              \
cxx/serializer/non-validating/language.cxx           \
cxx/serializer/non-validating/uri.cxx                \
cxx/serializer/non-validating/idrefs.cxx             \
cxx/serializer/non-validating/nmtokens.cxx           \
cxx/serializer/non-validating/qname.cxx

endif # stl

src +=                                               \
cxx/serializer/non-validating/base64-binary.cxx      \
cxx/serializer/non-validating/hex-binary.cxx         \
cxx/serializer/non-validating/gday.cxx               \
cxx/serializer/non-validating/gmonth.cxx             \
cxx/serializer/non-validating/gyear.cxx              \
cxx/serializer/non-validating/gmonth-day.cxx         \
cxx/serializer/non-validating/gyear-month.cxx        \
cxx/serializer/non-validating/date.cxx               \
cxx/serializer/non-validating/time.cxx               \
cxx/serializer/non-validating/date-time.cxx          \
cxx/serializer/non-validating/duration.cxx

endif # validation

#
#
obj := $(src:.c=.o)
obj := $(obj:.cxx=.o)

# Build.
#
libxsde.a: $(obj)
	$(AR) $(ARFLAGS) $@ $^
ifneq ($(RANLIB),)
	$(RANLIB) $@
endif

# It is tricky to output # with both POSIX and Windows shells.
#
ifeq ($(shell echo %PATH%),%PATH%)
h := \\\#
shell_type := posix
else
h := \#
shell_type := windows
endif

$(obj): config.h

config.h: $(root)/config/config.make
	@echo generating config.h
ifeq ($(shell_type),windows)
	@echo /* Generated - do not edit. */      >$@
else
	@echo "/* Generated - do not edit. */"    >$@
endif
	@echo $(h)ifndef XSDE_CONFIG_H              >>$@
	@echo $(h)define XSDE_CONFIG_H              >>$@
ifeq ($(XSDE_PLATFORM),wince)
	@echo $(h)define XSDE_PLATFORM_WINCE        >>$@
endif
ifeq ($(XSDE_PLATFORM),win32)
	@echo $(h)define XSDE_PLATFORM_WIN32        >>$@
endif
ifeq ($(XSDE_PLATFORM),posix)
	@echo $(h)define XSDE_PLATFORM_POSIX        >>$@
endif
	@echo $(h)define XSDE_ARCH_WIDTH $(XSDE_ARCH_WIDTH) >>$@
ifeq ($(XSDE_BYTEORDER),l)
	@echo $(h)define XSDE_BYTEORDER 1234        >>$@
endif
ifeq ($(XSDE_BYTEORDER),b)
	@echo $(h)define XSDE_BYTEORDER 4321        >>$@
endif
ifeq ($(XSDE_ENCODING),utf8)
	@echo $(h)define XSDE_ENCODING_UTF8         >>$@
else
ifeq ($(XSDE_ENCODING),)
	@echo $(h)define XSDE_ENCODING_UTF8         >>$@
else
	@echo $(h)undef XSDE_ENCODING_UTF8          >>$@
endif
endif
ifeq ($(XSDE_ENCODING),iso8859-1)
	@echo $(h)define XSDE_ENCODING_ISO8859_1    >>$@
else
	@echo $(h)undef XSDE_ENCODING_ISO8859_1     >>$@
endif
ifeq ($(XSDE_STL),y)
	@echo $(h)define XSDE_STL                   >>$@
endif
ifeq ($(XSDE_STL_ITERATOR),y)
	@echo $(h)define XSDE_STL_ITERATOR          >>$@
endif
ifeq ($(XSDE_IOSTREAM),y)
	@echo $(h)define XSDE_IOSTREAM              >>$@
endif
ifeq ($(XSDE_EXCEPTIONS),y)
	@echo $(h)define XSDE_EXCEPTIONS            >>$@
endif
ifeq ($(XSDE_LONGLONG),y)
	@echo $(h)define XSDE_LONGLONG              >>$@
endif
ifeq ($(XSDE_SNPRINTF),y)
	@echo $(h)define XSDE_SNPRINTF              >>$@
endif
ifeq ($(XSDE_PARSER_VALIDATION),y)
	@echo $(h)define XSDE_PARSER_VALIDATION     >>$@
endif
ifeq ($(XSDE_SERIALIZER_VALIDATION),y)
	@echo $(h)define XSDE_SERIALIZER_VALIDATION >>$@
endif
ifeq ($(XSDE_REGEXP),y)
	@echo $(h)define XSDE_REGEXP                >>$@
endif
ifeq ($(XSDE_REUSE_STYLE),mixin)
	@echo $(h)define XSDE_REUSE_STYLE_MIXIN     >>$@
else
	@echo $(h)undef XSDE_REUSE_STYLE_MIXIN      >>$@
endif
ifeq ($(XSDE_REUSE_STYLE),tiein)
	@echo $(h)define XSDE_REUSE_STYLE_TIEIN     >>$@
else
	@echo $(h)undef XSDE_REUSE_STYLE_TIEIN      >>$@
endif
ifeq ($(XSDE_REUSE_STYLE),none)
	@echo $(h)define XSDE_REUSE_STYLE_NONE      >>$@
else
	@echo $(h)undef XSDE_REUSE_STYLE_NONE       >>$@
endif
ifeq ($(XSDE_CUSTOM_ALLOCATOR),y)
	@echo $(h)define XSDE_CUSTOM_ALLOCATOR      >>$@
endif
ifeq ($(XSDE_DEFAULT_ALLOCATOR),y)
	@echo $(h)define XSDE_DEFAULT_ALLOCATOR     >>$@
endif
ifeq ($(XSDE_POLYMORPHIC),y)
	@echo $(h)define XSDE_POLYMORPHIC           >>$@
	@echo $(h)define XSDE_PARSER_SMAP_BUCKETS $(XSDE_PARSER_SMAP_BUCKETS)UL >>$@
ifeq ($(XSDE_PARSER_VALIDATION),y)
	@echo $(h)define XSDE_PARSER_IMAP_BUCKETS $(XSDE_PARSER_IMAP_BUCKETS)UL >>$@
endif
	@echo $(h)define XSDE_SERIALIZER_SMAP_BUCKETS $(XSDE_SERIALIZER_SMAP_BUCKETS)UL >>$@
	@echo $(h)define XSDE_SERIALIZER_SMAP_BUCKET_BUCKETS $(XSDE_SERIALIZER_SMAP_BUCKET_BUCKETS)UL >>$@
ifeq ($(XSDE_SERIALIZER_VALIDATION),y)
	@echo $(h)define XSDE_SERIALIZER_IMAP_BUCKETS $(XSDE_SERIALIZER_IMAP_BUCKETS)UL >>$@
endif
else
	@echo $(h)undef XSDE_POLYMORPHIC            >>$@
endif
	@echo $(h)endif                             >>$@


# Generated.
#
.PHONY: gen
gen:


# Test.
#
.PHONY: test
test: libxsde.a
	@:

# Clean.
#
.PHONY: clean cleanobj
cleanobj:
	rm -f libxsde.a $(obj) config.h

clean: cleanobj
