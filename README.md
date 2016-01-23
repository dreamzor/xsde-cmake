xsde-cmake
==========

CMakeLists.txt for building CodeSynthesis XSD/e runtime


You can only download binaries/makefiles at XSD/e download page (http://www.codesynthesis.com/products/xsde/download.xhtml), so it becomes a mess if your project uses CMake: use different binaries for different platforms is pain. It's much more convenient to compile everything from sources. 

This is a mostly draft, but working CMakeLists.txt for CodeSynthresis XSD/e 3.2.0, rewritten from one of makefiles. Right now cxx-parser and cxx-hybrid are tested. 

The source code in `libxsde` and example folder is open source and downloaded from 

http://www.codesynthesis.com/download/xsde/3.2/ 

File `config.h.in` is added there and used to generate `config.h` file during CMake building process.

### Building the library and example

    cd build
    cmake ..
    make -j 4
    
### Running the compiled example
    ./build/example-hybrid-hello/xsde_hello example-hybrid-hello/hello.xml
    
### Compiling object model, parser skeletons and implementations from .xsd file
   1. Download CodeSynthesis xsd/e binary file (called `xsde`, usually located under `bin` directory)
   2. Run it on your .xsd file with parameters `cxx-hybrid  --generate-parser --generate-aggregate --no-long-long`
   
   You may also want to use other parameters (see the xsd/e docs), such as:
     * `--include-with-brackets`
     * `--include-prefix <your prefix>`
     * `--guard-prefix xsde_generated`
     * `--output-dir <your_dir>`
  
This is how to compile the .xsd file included as example:
   
    cd example-hybrid-hello
    /somewhere/xsde-3.2.0-x86_64-linux-gnu/bin/xsde cxx-hybrid --generate-parser --generate-aggregate --no-long-long hello.xsd

which will generate:

* `hello.hxx, hello.cxx` - object model files
* `hello-pskel.hxx, hello-pskel.cxx` - parser skeletons files
* `hello-pimpl.hxx, hello-pimpl.cxx` - parser implementation files
    

Any help in development is highly appreciated.
    
