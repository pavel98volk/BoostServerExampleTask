# BOOST_SERVER_EXAMPLE_TASK
This is a simple example that consists of a simple tcp client & server with one way message transfer using **boost::asio::ip::tcp** socket.

#### how to build
1. If you are on Linux, have g++-9, also [conan package manager](https://docs.conan.io/en/latest/installation.html) and [CMake](https://cgold.readthedocs.io/en/latest/first-step/installation.html), just running ./build.sh script should work.
2. In case you are on Windows, conanprofile.txt can be modified. 
3. If conan is impossible to install, remove conan-related strings from root CMakeLists.txt, make sure boost is accessible by the compiler.
4. If cmake is impossible to install.... well.... tell me to change the project structure?
--------------
**C++ 14 is required**




#### Differences from the task
1. During the sending of the message, client replaces series of consecutive whitespaces with a single whitespace, removes leading and trailing whitespace sequences.
2. command input and information output only works if launched from terminal (It does not create a separate terminal window).
