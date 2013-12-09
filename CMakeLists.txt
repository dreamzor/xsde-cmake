project(xsde)

# preparing config
IF(WIN32) 
	set(XSDE_PLATFORM_POSIX FALSE)
	set(XSDE_PLATFORM_WIN32 TRUE)
ELSE()
	set(XSDE_PLATFORM_POSIX TRUE)
	set(XSDE_PLATFORM_WIN32 FALSE)
ENDIF()
# if(CMAKE_SIZEOF_VOID_P EQUAL 8)
#   set(XSDE_ARCH_WIDTH 64)
# else() 
#   set(XSDE_ARCH_WIDTH 32)
# endif()

include(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN)
if(${IS_BIG_ENDIAN})
	set(XSDE_BYTEORDER 4321)
else()
	set(XSDE_BYTEORDER 1234)
endif()

set(XSDE_ENCODING_UTF8 TRUE)
set(XSDE_ENCODING_ISO8859_1 FALSE)
set(XSDE_STL TRUE)
set(XSDE_STL_ITERATOR TRUE)
set(XSDE_IOSTREAM TRUE)
set(XSDE_EXCEPTIONS TRUE)
set(XSDE_LONGLONG FALSE)
set(XSDE_SNPRINTF TRUE)

set(XSDE_PARSER_VALIDATION TRUE)
set(XSDE_SERIALIZER_VALIDATION FALSE)
set(XSDE_REGEXP TRUE)

set(XSDE_REUSE_STYLE_MIXIN FALSE)
set(XSDE_REUSE_STYLE_TIEIN TRUE)
set(XSDE_REUSE_STYLE_NONE FALSE)

set(XSDE_CUSTOM_ALLOCATOR FALSE)
set(XSDE_DEFAULT_ALLOCATOR TRUE)

set(XSDE_POLYMORPHIC FALSE)

set(XSDE_REGEXP TRUE)

set(XSDE_PARSER_SMAP_BUCKETS 97UL)
set(XSDE_PARSER_IMAP_BUCKETS 97UL)
set(XSDE_SERIALIZER_SMAP_BUCKETS 53UL)
set(XSDE_SERIALIZER_SMAP_BUCKET_BUCKETS 53UL)


# include needed files


set(c_tun
	c/expat/xmlparse.c c/expat/xmlrole.c c/expat/xmltok.c)
set(c_tun ${c_tun} c/genx/genx.c c/genx/char-props.c)

if(XSDE_PARSER_VALIDATION OR {XSDE_SERIALIZER_VALIDATION)
	if(XSDE_REGEXP)
		set(c_tun ${c_tun} c/regexp/chvalid.c c/regexp/xmlunicode.c c/regexp/xmlregexp.c)
	endif()
endif()

if(XSDE_CUSTOM_ALLOCATOR AND XSDE_DEFAULT_ALLOCATOR)
	set(c_tun ${c_tun} allocator.c)
endif()

set(cxx_tun
	cxx/string.cxx        
	cxx/string-search.cxx 
	cxx/ro-string.cxx     
	cxx/stack.cxx)

if(XSDE_CUSTOM_ALLOCATOR AND XSDE_EXCEPTIONS)
set(cxx_tun ${cxx_tun} cxx/allocator.cxx)
endif()

if(XSDE_ENCODING_ISO8859_1)
	set(cxx_tun ${cxx_tun} cxx/iso8859-1.cxx)
endif()

if(NOT XSDE_STL)
	set(cxx_tun ${cxx_tun} cxx/strdupx.cxx)
endif()

if(NOT XSDE_EXCEPTIONS)
	set(cxx_tun ${cxx_tun} cxx/sys-error.cxx)
endif()

if(XSDE_PARSER_VALIDATION OR XSDE_SERIALIZER_VALIDATION)
	set(cxx_tun ${cxx_tun} cxx/schema-error.cxx)
	if(XSDE_REGEXP)
		set(cxx_tun ${cxx_tun} cxx/schema-error.cxx)
	endif()
endif()

if(XSDE_POLYMORPHIC)
	set(cxx_tun ${cxx_tun} cxx/hashmap.cxx)
endif()

# Common data types.
#
set(cxx_tun ${cxx_tun} cxx/buffer.cxx cxx/sequence-base.cxx)

if(XSDE_STL)
	set(cxx_tun ${cxx_tun} cxx/string-sequence-stl.cxx)
else()
	set(cxx_tun ${cxx_tun} cxx/qname.cxx cxx/string-sequence.cxx)
endif()


## XML
##
if(XSDE_PARSER_VALIDATION OR XSDE_SERIALIZER_VALIDATION)
	set(cxx_tun ${cxx_tun} cxx/xml/char-table.cxx cxx/xml/ncname.cxx)
endif()


# ## C++/Hybrid
# ##
set(cxx_tun ${cxx_tun}                    
cxx/hybrid/any-type.cxx       
cxx/hybrid/any-type-pimpl.cxx 
cxx/hybrid/any-type-pskel.cxx 
cxx/hybrid/any-type-simpl.cxx 
cxx/hybrid/any-type-sskel.cxx 
cxx/hybrid/sequence.cxx)

if(XSDE_POLYMORPHIC)
	set(cxx_tun ${cxx_tun}                     
	cxx/hybrid/parser-map.cxx     
	cxx/hybrid/serializer-map.cxx)
endif()

if(XSDE_CDR)
	set(cxx_tun ${cxx_tun}                          
	cxx/hybrid/cdr/exceptions.cxx      
	cxx/hybrid/cdr/istream.cxx         
	cxx/hybrid/cdr/ostream.cxx         
	cxx/hybrid/cdr/qname.cxx           
	cxx/hybrid/cdr/date-time.cxx       
	cxx/hybrid/cdr/string-sequence.cxx)
endif()

if(XSDE_XDR)
	set(cxx_tun ${cxx_tun}                          
	cxx/hybrid/xdr/exceptions.cxx      
	cxx/hybrid/xdr/istream.cxx         
	cxx/hybrid/xdr/ostream.cxx         
	cxx/hybrid/xdr/qname.cxx           
	cxx/hybrid/xdr/date-time.cxx       
	cxx/hybrid/xdr/string-sequence.cxx)
endif()


## C++/Parser
##
set(cxx_tun ${cxx_tun} cxx/parser/elements.cxx)

if(XSDE_POLYMORPHIC)
	set(cxx_tun ${cxx_tun} cxx/parser/map.cxx cxx/parser/substitution-map.cxx)
endif()

if(XSDE_EXCEPTIONS)
	set(cxx_tun ${cxx_tun} cxx/parser/exceptions.cxx)
else()
	set(cxx_tun ${cxx_tun} cxx/parser/error.cxx)
endif()

set(cxx_tun ${cxx_tun} cxx/parser/expat/document.cxx cxx/parser/expat/xml-error.cxx)


# Parser implementations.
#
if(XSDE_PARSER_VALIDATION)
	set(cxx_tun ${cxx_tun}                                       
	cxx/parser/validating/parser.cxx                
	cxx/parser/validating/time-zone.cxx             
	cxx/parser/validating/string-common.cxx         
	cxx/parser/validating/xml-schema-pskel.cxx)

	if(XSDE_POLYMORPHIC)
		set(cxx_tun ${cxx_tun} cxx/parser/validating/inheritance-map.cxx)
	endif()

	set(cxx_tun ${cxx_tun}                                       
	cxx/parser/validating/boolean.cxx               
	cxx/parser/validating/number.cxx                
	cxx/parser/validating/byte.cxx                  
	cxx/parser/validating/unsigned-byte.cxx         
	cxx/parser/validating/short.cxx                 
	cxx/parser/validating/unsigned-short.cxx        
	cxx/parser/validating/int.cxx                   
	cxx/parser/validating/unsigned-int.cxx          
	cxx/parser/validating/integer.cxx               
	cxx/parser/validating/negative-integer.cxx      
	cxx/parser/validating/non-positive-integer.cxx  
	cxx/parser/validating/positive-integer.cxx      
	cxx/parser/validating/non-negative-integer.cxx  
	cxx/parser/validating/float.cxx                 
	cxx/parser/validating/double.cxx                
	cxx/parser/validating/decimal.cxx)

	if(XSDE_LONGLONG)
		set(cxx_tun ${cxx_tun}                                       
		cxx/parser/validating/long-long.cxx             
		cxx/parser/validating/unsigned-long-long.cxx)
	else()
		set(cxx_tun ${cxx_tun}                                       
		cxx/parser/validating/long.cxx                  
		cxx/parser/validating/unsigned-long.cxx)
	endif()

	if(XSDE_STL)
		set(cxx_tun ${cxx_tun}                                       
		cxx/parser/validating/any-simple-type-stl.cxx   
		cxx/parser/validating/string-stl.cxx            
		cxx/parser/validating/normalized-string-stl.cxx 
		cxx/parser/validating/token-stl.cxx             
		cxx/parser/validating/name-stl.cxx              
		cxx/parser/validating/nmtoken-stl.cxx           
		cxx/parser/validating/nmtokens-stl.cxx          
		cxx/parser/validating/ncname-stl.cxx            
		cxx/parser/validating/id-stl.cxx                
		cxx/parser/validating/idref-stl.cxx             
		cxx/parser/validating/idrefs-stl.cxx            
		cxx/parser/validating/language-stl.cxx          
		cxx/parser/validating/uri-stl.cxx               
		cxx/parser/validating/qname-stl.cxx)
	else()
		set(cxx_tun ${cxx_tun}                                    
		cxx/parser/validating/any-simple-type.cxx    
		cxx/parser/validating/string.cxx             
		cxx/parser/validating/normalized-string.cxx  
		cxx/parser/validating/token.cxx              
		cxx/parser/validating/name.cxx               
		cxx/parser/validating/nmtoken.cxx            
		cxx/parser/validating/nmtokens.cxx           
		cxx/parser/validating/ncname.cxx             
		cxx/parser/validating/id.cxx                 
		cxx/parser/validating/idref.cxx              
		cxx/parser/validating/idrefs.cxx             
		cxx/parser/validating/language.cxx           
		cxx/parser/validating/uri.cxx                
		cxx/parser/validating/qname.cxx)
	endif() # stl

	set(cxx_tun ${cxx_tun}                                   
	cxx/parser/validating/base64-binary.cxx      
	cxx/parser/validating/hex-binary.cxx         
	cxx/parser/validating/gday.cxx               
	cxx/parser/validating/gmonth.cxx             
	cxx/parser/validating/gyear.cxx              
	cxx/parser/validating/gmonth-day.cxx         
	cxx/parser/validating/gyear-month.cxx        
	cxx/parser/validating/date.cxx               
	cxx/parser/validating/time.cxx               
	cxx/parser/validating/date-time.cxx          
	cxx/parser/validating/duration.cxx)

else() # validation

	set(cxx_tun ${cxx_tun}                                           
	cxx/parser/non-validating/parser.cxx                
	cxx/parser/non-validating/time-zone.cxx             
	cxx/parser/non-validating/string-common.cxx         
	cxx/parser/non-validating/xml-schema-pskel.cxx)

	set(cxx_tun ${cxx_tun}                                           
	cxx/parser/non-validating/boolean.cxx               
	cxx/parser/non-validating/number.cxx                
	cxx/parser/non-validating/byte.cxx                  
	cxx/parser/non-validating/unsigned-byte.cxx         
	cxx/parser/non-validating/short.cxx                 
	cxx/parser/non-validating/unsigned-short.cxx        
	cxx/parser/non-validating/int.cxx                   
	cxx/parser/non-validating/unsigned-int.cxx          
	cxx/parser/non-validating/integer.cxx               
	cxx/parser/non-validating/negative-integer.cxx      
	cxx/parser/non-validating/non-positive-integer.cxx  
	cxx/parser/non-validating/positive-integer.cxx      
	cxx/parser/non-validating/non-negative-integer.cxx  
	cxx/parser/non-validating/float.cxx                 
	cxx/parser/non-validating/double.cxx                
	cxx/parser/non-validating/decimal.cxx)

	if(XSDE_LONGLONG)
		set(cxx_tun ${cxx_tun}                                           
		cxx/parser/non-validating/long-long.cxx             
		cxx/parser/non-validating/unsigned-long-long.cxx)
	else()
		set(cxx_tun ${cxx_tun}                                           
		cxx/parser/non-validating/long.cxx                  
		cxx/parser/non-validating/unsigned-long.cxx)
	endif()

	if(XSDE_STL)
		set(cxx_tun ${cxx_tun}                                           
		cxx/parser/non-validating/any-simple-type-stl.cxx   
		cxx/parser/non-validating/string-stl.cxx            
		cxx/parser/non-validating/normalized-string-stl.cxx 
		cxx/parser/non-validating/token-stl.cxx             
		cxx/parser/non-validating/name-stl.cxx              
		cxx/parser/non-validating/nmtoken-stl.cxx           
		cxx/parser/non-validating/nmtokens-stl.cxx          
		cxx/parser/non-validating/ncname-stl.cxx            
		cxx/parser/non-validating/id-stl.cxx                
		cxx/parser/non-validating/idref-stl.cxx             
		cxx/parser/non-validating/idrefs-stl.cxx            
		cxx/parser/non-validating/language-stl.cxx          
		cxx/parser/non-validating/uri-stl.cxx               
		cxx/parser/non-validating/qname-stl.cxx)
	else()
		set(cxx_tun ${cxx_tun}                                        
		cxx/parser/non-validating/any-simple-type.cxx    
		cxx/parser/non-validating/string.cxx             
		cxx/parser/non-validating/normalized-string.cxx  
		cxx/parser/non-validating/token.cxx              
		cxx/parser/non-validating/name.cxx               
		cxx/parser/non-validating/nmtoken.cxx            
		cxx/parser/non-validating/nmtokens.cxx           
		cxx/parser/non-validating/ncname.cxx             
		cxx/parser/non-validating/id.cxx                 
		cxx/parser/non-validating/idref.cxx              
		cxx/parser/non-validating/idrefs.cxx             
		cxx/parser/non-validating/language.cxx           
		cxx/parser/non-validating/uri.cxx                
		cxx/parser/non-validating/qname.cxx)
	endif() # stl

	set(cxx_tun ${cxx_tun}                                        
	cxx/parser/non-validating/base64-binary.cxx      
	cxx/parser/non-validating/hex-binary.cxx         
	cxx/parser/non-validating/gday.cxx               
	cxx/parser/non-validating/gmonth.cxx             
	cxx/parser/non-validating/gyear.cxx              
	cxx/parser/non-validating/gmonth-day.cxx         
	cxx/parser/non-validating/gyear-month.cxx        
	cxx/parser/non-validating/date.cxx               
	cxx/parser/non-validating/time.cxx               
	cxx/parser/non-validating/date-time.cxx          
	cxx/parser/non-validating/duration.cxx)

endif() # validation


# ## C++/Serializer
# ##
set(cxx_tun ${cxx_tun} cxx/serializer/elements.cxx cxx/serializer/context.cxx)

if(XSDE_POLYMORPHIC)
	set(cxx_tun ${cxx_tun} cxx/serializer/map.cxx cxx/serializer/substitution-map.cxx)
endif()

if(XSDE_EXCEPTIONS)
		set(cxx_tun ${cxx_tun}  cxx/serializer/exceptions.cxx)
	else()
		set(cxx_tun ${cxx_tun}  cxx/serializer/error.cxx)
endif()

set(cxx_tun ${cxx_tun}  cxx/serializer/genx/document.cxx cxx/serializer/genx/xml-error.cxx)

# # Serializer implementations.
# #
IF (XSDE_BUILD_SERIALIZER)

	if(XSDE_SERIALIZER_VALIDATION)
		set(cxx_tun ${cxx_tun}                                           
		cxx/serializer/validating/serializer.cxx            
		cxx/serializer/validating/time-zone.cxx             
		cxx/serializer/validating/string-common.cxx         
		cxx/serializer/validating/xml-schema-sskel.cxx)

		if(XSDE_POLYMORPHIC)
			set(cxx_tun ${cxx_tun}  cxx/serializer/validating/inheritance-map.cxx)
		endif()

		set(cxx_tun ${cxx_tun}                                           
		cxx/serializer/validating/boolean.cxx               
		cxx/serializer/validating/byte.cxx                  
		cxx/serializer/validating/unsigned-byte.cxx         
		cxx/serializer/validating/short.cxx                 
		cxx/serializer/validating/unsigned-short.cxx        
		cxx/serializer/validating/int.cxx                   
		cxx/serializer/validating/unsigned-int.cxx          
		cxx/serializer/validating/integer.cxx               
		cxx/serializer/validating/negative-integer.cxx      
		cxx/serializer/validating/non-positive-integer.cxx  
		cxx/serializer/validating/positive-integer.cxx      
		cxx/serializer/validating/non-negative-integer.cxx  
		cxx/serializer/validating/float.cxx                 
		cxx/serializer/validating/double.cxx                
		cxx/serializer/validating/decimal.cxx)

		if(XSDE_LONGLONG)
			set(cxx_tun ${cxx_tun}                                           
			cxx/serializer/validating/long-long.cxx             
			cxx/serializer/validating/unsigned-long-long.cxx)
		else()
			set(cxx_tun ${cxx_tun}                                           
			cxx/serializer/validating/long.cxx                  
			cxx/serializer/validating/unsigned-long.cxx)
		endif()

		if(XSDE_STL)
			set(cxx_tun ${cxx_tun}                                           
			cxx/serializer/validating/any-simple-type-stl.cxx   
			cxx/serializer/validating/string-stl.cxx            
			cxx/serializer/validating/normalized-string-stl.cxx 
			cxx/serializer/validating/token-stl.cxx             
			cxx/serializer/validating/name-stl.cxx              
			cxx/serializer/validating/nmtoken-stl.cxx           
			cxx/serializer/validating/ncname-stl.cxx            
			cxx/serializer/validating/id-stl.cxx                
			cxx/serializer/validating/idref-stl.cxx             
			cxx/serializer/validating/language-stl.cxx          
			cxx/serializer/validating/uri-stl.cxx               
			cxx/serializer/validating/idrefs-stl.cxx            
			cxx/serializer/validating/nmtokens-stl.cxx          
			cxx/serializer/validating/qname-stl.cxx)
		else()
			set(cxx_tun ${cxx_tun}                                        
			cxx/serializer/validating/any-simple-type.cxx    
			cxx/serializer/validating/string.cxx             
			cxx/serializer/validating/normalized-string.cxx  
			cxx/serializer/validating/token.cxx              
			cxx/serializer/validating/name.cxx               
			cxx/serializer/validating/nmtoken.cxx            
			cxx/serializer/validating/ncname.cxx             
			cxx/serializer/validating/id.cxx                 
			cxx/serializer/validating/idref.cxx              
			cxx/serializer/validating/language.cxx           
			cxx/serializer/validating/uri.cxx                
			cxx/serializer/validating/idrefs.cxx             
			cxx/serializer/validating/nmtokens.cxx           
			cxx/serializer/validating/qname.cxx)
		endif() # stl

		set(cxx_tun ${cxx_tun}                                        
		cxx/serializer/validating/base64-binary.cxx      
		cxx/serializer/validating/hex-binary.cxx         
		cxx/serializer/validating/gday.cxx               
		cxx/serializer/validating/gmonth.cxx             
		cxx/serializer/validating/gyear.cxx              
		cxx/serializer/validating/gmonth-day.cxx         
		cxx/serializer/validating/gyear-month.cxx        
		cxx/serializer/validating/date.cxx               
		cxx/serializer/validating/time.cxx               
		cxx/serializer/validating/date-time.cxx          
		cxx/serializer/validating/duration.cxx)

	else() # validation

		set(cxx_tun ${cxx_tun}                                               
		cxx/serializer/non-validating/serializer.cxx            
		cxx/serializer/non-validating/time-zone.cxx             
		cxx/serializer/non-validating/xml-schema-sskel.cxx)

		set(cxx_tun ${cxx_tun}                                               
		cxx/serializer/non-validating/boolean.cxx               
		cxx/serializer/non-validating/byte.cxx                  
		cxx/serializer/non-validating/unsigned-byte.cxx         
		cxx/serializer/non-validating/short.cxx                 
		cxx/serializer/non-validating/unsigned-short.cxx        
		cxx/serializer/non-validating/int.cxx                   
		cxx/serializer/non-validating/unsigned-int.cxx          
		cxx/serializer/non-validating/integer.cxx               
		cxx/serializer/non-validating/negative-integer.cxx      
		cxx/serializer/non-validating/non-positive-integer.cxx  
		cxx/serializer/non-validating/positive-integer.cxx      
		cxx/serializer/non-validating/non-negative-integer.cxx  
		cxx/serializer/non-validating/float.cxx                 
		cxx/serializer/non-validating/double.cxx                
		cxx/serializer/non-validating/decimal.cxx)

		if(XSDE_LONGLONG)
			set(cxx_tun ${cxx_tun}                                               
			cxx/serializer/non-validating/long-long.cxx             
			cxx/serializer/non-validating/unsigned-long-long.cxx)
		else()
			set(cxx_tun ${cxx_tun}                                               
			cxx/serializer/non-validating/long.cxx                  
			cxx/serializer/non-validating/unsigned-long.cxx)
		endif()

		if(XSDE_STL)

			set(cxx_tun ${cxx_tun}                                               
			cxx/serializer/non-validating/any-simple-type-stl.cxx   
			cxx/serializer/non-validating/string-stl.cxx            
			cxx/serializer/non-validating/normalized-string-stl.cxx 
			cxx/serializer/non-validating/token-stl.cxx             
			cxx/serializer/non-validating/name-stl.cxx              
			cxx/serializer/non-validating/nmtoken-stl.cxx           
			cxx/serializer/non-validating/ncname-stl.cxx            
			cxx/serializer/non-validating/id-stl.cxx                
			cxx/serializer/non-validating/idref-stl.cxx             
			cxx/serializer/non-validating/language-stl.cxx          
			cxx/serializer/non-validating/uri-stl.cxx               
			cxx/serializer/non-validating/idrefs-stl.cxx            
			cxx/serializer/non-validating/nmtokens-stl.cxx          
			cxx/serializer/non-validating/qname-stl.cxx)

		else()

			set(cxx_tun ${cxx_tun}                                            
			cxx/serializer/non-validating/any-simple-type.cxx    
			cxx/serializer/non-validating/string.cxx             
			cxx/serializer/non-validating/normalized-string.cxx  
			cxx/serializer/non-validating/token.cxx              
			cxx/serializer/non-validating/name.cxx               
			cxx/serializer/non-validating/nmtoken.cxx            
			cxx/serializer/non-validating/ncname.cxx             
			cxx/serializer/non-validating/id.cxx                 
			cxx/serializer/non-validating/idref.cxx              
			cxx/serializer/non-validating/language.cxx           
			cxx/serializer/non-validating/uri.cxx                
			cxx/serializer/non-validating/idrefs.cxx             
			cxx/serializer/non-validating/nmtokens.cxx           
			cxx/serializer/non-validating/qname.cxx)

		endif() # stl

		set(cxx_tun ${cxx_tun}                                            
		cxx/serializer/non-validating/base64-binary.cxx      
		cxx/serializer/non-validating/hex-binary.cxx         
		cxx/serializer/non-validating/gday.cxx               
		cxx/serializer/non-validating/gmonth.cxx             
		cxx/serializer/non-validating/gyear.cxx              
		cxx/serializer/non-validating/gmonth-day.cxx         
		cxx/serializer/non-validating/gyear-month.cxx        
		cxx/serializer/non-validating/date.cxx               
		cxx/serializer/non-validating/time.cxx               
		cxx/serializer/non-validating/date-time.cxx          
		cxx/serializer/non-validating/duration.cxx)

	endif() # validation

endif() # XSDE_BUILD_SERIALIZER


configure_file("${PROJECT_SOURCE_DIR}/config.h.in"
			   "${PROJECT_BINARY_DIR}/include/xsde/config.h")
include_directories("${PROJECT_BINARY_DIR}/include/")

set(XSDE_FILES ${c_tun} ${cxx_tun})
add_library(xsde STATIC ${XSDE_FILES})

install(TARGETS xsde 
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)



# add_executable(xsde_hello 
# 	examples/hybrid-hello/driver.cxx 
# 	examples/hybrid-hello/hello.cxx
# 	examples/hybrid-hello/hello-pskel.cxx
# 	examples/hybrid-hello/hello-pimpl.cxx
# )
# target_link_libraries(xsde_hello xsde)
# add_dependencies(xsde_hello xsde)


# c_o   := $(addprefix $(out_base)/,$(c_tun:.c=.o))
# c_d   := $(c_o:.o=.o.d)

# cxx_o := $(addprefix $(out_base)/,$(cxx_tun:.cxx=.o))
# cxx_d := $(cxx_o:.o=.o.d)

# xsde.l             := $(out_base)/xsde.l
# xsde.l.cpp-options := $(out_base)/xsde.l.cpp-options

# dist     := $(out_base)/.dist
# dist-win := $(out_base)/.dist-win
# clean    := $(out_base)/.clean

# Import.
#

# ifeq ($(xsde_cdr),y)
# $(call import,
#   $(scf_root)/import/libace/stub.make,
#   l: ace.l,cpp-options: ace.l.cpp-options)
# endif

# Build.
#
# $(xsde.l): $(c_o) $(cxx_o)
# $(c_o) $(cxx_o) $(c_d) $(cxx_d): $(xsde.l.cpp-options) $(out_base)/config.h


# ifeq ($(xsde_exceptions),y)
# $(c_o): c_exceptions := y
# endif

# ifeq ($(xsde_cdr),y)
# $(xsde.l): $(ace.l)
# $(cxx_o) $(cxx_d): $(ace.l.cpp-options)
# $(xsde.l.cpp-options): $(ace.l.cpp-options)
# endif

# $(xsde.l.cpp-options): prefix := xsde/ $(out_root)/libxsde/
# $(xsde.l.cpp-options): value := -I$(out_root)/libxsde -I$(src_root)/libxsde

# $(call include-dep,$(c_d) $(cxx_d))

# config.h
#
	# $(out_base)/config.h: $(dcf_root)/configuration-dynamic.make
	# 	@echo '// file      : xsde/config.h'                             >$@
	# 	@echo '// author    : automatically generated'                  >>$@
	# 	@echo ''                                                        >>$@
	# 	@echo '#ifndef XSDE_CONFIG_H'                                   >>$@
	# 	@echo '#define XSDE_CONFIG_H'                                   >>$@
	# 	@echo ''                                                        >>$@
	# 	@echo '#define XSDE_PLATFORM_POSIX'                             >>$@
	# 	@echo '#define XSDE_ARCH_WIDTH $(xsde_arch_width)'              >>$@
	# ifeq ($(xsde_byteorder),l)
	# 	@echo '#define XSDE_BYTEORDER 1234'                             >>$@
	# else
	# 	@echo '#define XSDE_BYTEORDER 4321'                             >>$@
	# endif
	# ifeq ($(xsde_encoding),utf8)
	# 	@echo '#define XSDE_ENCODING_UTF8'                              >>$@
	# else
	# 	@echo '#undef XSDE_ENCODING_UTF8'                               >>$@
	# endif
	# ifeq ($(xsde_encoding),iso8859-1)
	# 	@echo '#define XSDE_ENCODING_ISO8859_1'                         >>$@
	# else
	# 	@echo '#undef XSDE_ENCODING_ISO8859_1'                          >>$@
	# endif
	# ifeq ($(xsde_stl),y)
	# 	@echo '#define XSDE_STL'                                        >>$@
	# else
	# 	@echo '#undef XSDE_STL'                                         >>$@
	# endif
	# ifeq ($(xsde_stl_iterator),y)
	# 	@echo '#define XSDE_STL_ITERATOR'                               >>$@
	# else
	# 	@echo '#undef XSDE_STL_ITERATOR'                                >>$@
	# endif
	# ifeq ($(xsde_iostream),y)
	# 	@echo '#define XSDE_IOSTREAM'                                   >>$@
	# else
	# 	@echo '#undef XSDE_IOSTREAM'                                    >>$@
	# endif
	# ifeq ($(xsde_exceptions),y)
	# 	@echo '#define XSDE_EXCEPTIONS'                                 >>$@
	# else
	# 	@echo '#undef XSDE_EXCEPTIONS'                                  >>$@
	# endif
	# ifeq ($(xsde_longlong),y)
	# 	@echo '#define XSDE_LONGLONG'                                   >>$@
	# else
	# 	@echo '#undef XSDE_LONGLONG'                                    >>$@
	# endif
	# ifeq ($(xsde_snprintf),y)
	# 	@echo '#define XSDE_SNPRINTF'                                   >>$@
	# else
	# 	@echo '#undef XSDE_SNPRINTF'                                    >>$@
	# endif
	# ifeq ($(xsde_parser_validation),y)
	# 	@echo '#define XSDE_PARSER_VALIDATION'                          >>$@
	# else
	# 	@echo '#undef XSDE_PARSER_VALIDATION'                           >>$@
	# endif
	# ifeq ($(xsde_serializer_validation),y)
	# 	@echo '#define XSDE_SERIALIZER_VALIDATION'                      >>$@
	# else
	# 	@echo '#undef XSDE_SERIALIZER_VALIDATION'                       >>$@
	# endif
	# ifeq ($(xsde_regexp),y)
	# 	@echo '#define XSDE_REGEXP'                      		>>$@
	# else
	# 	@echo '#undef XSDE_REGEXP'                                      >>$@
	# endif
	# ifeq ($(xsde_reuse_style),mixin)
	# 	@echo '#define XSDE_REUSE_STYLE_MIXIN'                          >>$@
	# else
	# 	@echo '#undef XSDE_REUSE_STYLE_MIXIN'                           >>$@
	# endif
	# ifeq ($(xsde_reuse_style),tiein)
	# 	@echo '#define XSDE_REUSE_STYLE_TIEIN'                          >>$@
	# else
	# 	@echo '#undef XSDE_REUSE_STYLE_TIEIN'                           >>$@
	# endif
	# ifeq ($(xsde_reuse_style),none)
	# 	@echo '#define XSDE_REUSE_STYLE_NONE'                           >>$@
	# else
	# 	@echo '#undef XSDE_REUSE_STYLE_NONE'                            >>$@
	# endif
	# ifeq ($(xsde_custom_allocator),y)
	# 	@echo '#define XSDE_CUSTOM_ALLOCATOR'                      	>>$@
	# else
	# 	@echo '#undef XSDE_CUSTOM_ALLOCATOR'                       	>>$@
	# endif
	# ifeq ($(xsde_default_allocator),y)
	# 	@echo '#define XSDE_DEFAULT_ALLOCATOR'                      	>>$@
	# else
	# 	@echo '#undef XSDE_DEFAULT_ALLOCATOR'                       	>>$@
	# endif
	# ifeq ($(xsde_polymorphic),y)
	# 	@echo '#define XSDE_POLYMORPHIC'                                >>$@
	# 	@echo '#define XSDE_PARSER_SMAP_BUCKETS $(xsde_parser_smap_buckets)UL' >>$@
	# ifeq ($(xsde_parser_validation),y)
	# 	@echo '#define XSDE_PARSER_IMAP_BUCKETS $(xsde_parser_imap_buckets)UL' >>$@
	# endif
	# 	@echo '#define XSDE_SERIALIZER_SMAP_BUCKETS $(xsde_serializer_smap_buckets)UL' >>$@
	# 	@echo '#define XSDE_SERIALIZER_SMAP_BUCKET_BUCKETS $(xsde_serializer_smap_bucket_buckets)UL' >>$@
	# ifeq ($(xsde_serializer_validation),y)
	# 	@echo '#define XSDE_SERIALIZER_IMAP_BUCKETS $(xsde_serializer_imap_buckets)UL' >>$@
	# endif
	# else
	# 	@echo '#undef XSDE_POLYMORPHIC'                                 >>$@
	# endif
	# 	@echo ''                                                        >>$@
	# 	@echo '#endif // XSDE_CONFIG_H'                                 >>$@


# # Convenience alias for default target.
# #
# $(out_base)/: $(xsde.l)


# # Dist.
# #
# $(dist):
# 	$(call install-data,$(src_base)/allocator.h,$(dist_prefix)/libxsde/xsde/allocator.h)
# 	$(call install-data,$(src_base)/allocator.c,$(dist_prefix)/libxsde/xsde/allocator.c)
# 	$(call install-dir,$(src_base)/c,$(dist_prefix)/libxsde/xsde/c,\( -name '*.h' -o -name '*.c' -o -name COPYING \))
# 	$(call install-dir,$(src_base)/cxx,$(dist_prefix)/libxsde/xsde/cxx,-name '*.?xx')

# $(dist-win): $(dist)

# # Clean.
# #
# $(clean): $(xsde.l).o.clean            
#   $(xsde.l.cpp-options).clean          
#   $(addsuffix .c.clean,$(c_o))         \
#   $(addsuffix .c.clean,$(c_d))         \
#   $(addsuffix .cxx.clean,$(cxx_o))     \
#   $(addsuffix .cxx.clean,$(cxx_d))
# 	$(call message,rm $$1,rm -f $$1,$(out_base)/config.h)


# # Generated .gitignore.
# #
# ifeq ($(out_base),$(src_base))
# $(out_base)/config.h: | $(out_base)/.gitignore

# $(out_base)/.gitignore: files := config.h
# $(clean): $(out_base)/.gitignore.clean

# $(call include,$(bld_root)/git/gitignore.make)
# endif


# # How to.
# #
# $(call include,$(bld_root)/c/c-o.make)
# $(call include,$(bld_root)/c/c-d.make)
# $(call include,$(bld_root)/cxx/cxx-o.make)
# $(call include,$(bld_root)/cxx/cxx-d.make)
# $(call include,$(bld_root)/cxx/o-l.make)
# $(call include,$(bld_root)/install.make)
