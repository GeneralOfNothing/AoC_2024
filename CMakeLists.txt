cmake_minimum_required(VERSION 3.20)

project(AoC_2024)

#Targets
add_executable(DayOne src/Day1/main.cpp)
add_executable(DayTwo src/Day2/main.cpp)
add_executable(DayThree src/Day3/main.cpp)
add_executable(DayFour src/Day4/main.cpp)
add_executable(DayFive src/Day5/main.cpp)

#Dummy Target
add_custom_target(BuildAll)

add_dependencies(BuildAll DayOne DayTwo DayThree DayFour DayFive)

#Create a TestData dir in the build location
add_custom_command(TARGET BuildAll
		   PRE_BUILD 
		   COMMAND echo "Creating TestData Dir..."
		   COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/TestData/
		   POST_BUILD
		   COMMAND echo "All targets built sucessfully.")


