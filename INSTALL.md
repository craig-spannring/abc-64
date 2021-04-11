*Currently this will only run properly when compiled for a 32 bit system.*

This project follows the standard CMake conventions for building.

   $ mkdir build          # This may be located anywhere.
   $ cd build
   $ cmake {FLAGS} ../.   # Path to this directory

For a native build FLAGS might be something like 

   `-DCMAKE_BUILD_TYPE=Release  ../.`

or

   `-DCMAKE_BUILD_TYPE=Release  ../.`
   
# Compiling for 32bit from a 64-bit machine

You must first setup a 32-bit development environment which is in
general beyond the scope of this document.  For recent versions of
Unbuntu it might be as simple as
  `sudo apt install g++-multilib`

To build your FLAGS should be something like 

   `-DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=linux-gcc32.toolchain  ../.`
   
or 

   `-DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=linux-gcc32.toolchain  ../.`


