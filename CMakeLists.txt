#Specify version
cmake_minimum_required(VERSION 3.30)
#Project name
project(Cavern)

#Add all files that want to be included in the .exe here
add_executable(Test Codebase/Test.cpp Codebase/Pos.cpp)

enable_testing()
#Add the executables to be run as test here?
add_test(NAME RunCavernTests COMMAND Test)