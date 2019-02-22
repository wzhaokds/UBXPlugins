# UBXPlugins
Sample codes to demonstrate how to integrate C++ applications into our UBX platform for slice-n-dice on POD service, at http://www.kdsglobal.com

The library could be built on a Linux host, running devtoolset-7, https://www.softwarecollections.org/en/scls/rhscl/devtoolset-7/,
or earlier versions, up to devtoolset-4.

You can also develop and test your codes in MacOS with gmake and g++ and Windows with Ubuntu installed (https://docs.microsoft.com/en-us/windows/wsl/install-win10)

You can download the package with

git clone https://github.com/wzhaokds/UBXPlugins.git

Then in the UBXPlugins folder, run

make

which will build the library and a test program. To run the test program, you can run it with and see the following output:

./UBXPf0113_0853 FN30 201901 5 350 10

ok, executing

UBXpf0113_0853.fCalc() = 7.10773

In the "make" process, a static library libUBXPf0113_0853.a is also produced. This library and the corresponding header file, UBXPf0113_0853.hpp, are the only two files needed for integrating with our UBX system.

