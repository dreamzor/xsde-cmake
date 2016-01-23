cmake_minimum_required(VERSION 2.8)

project(example-hybrid-hello)

add_executable(xsde_hello 
  driver.cxx 
  hello.cxx
  hello-pskel.hxx
  hello-pskel.cxx
  hello-pimpl.hxx
  hello-pimpl.cxx
)
target_link_libraries(xsde_hello xsde)
add_dependencies(xsde_hello xsde)