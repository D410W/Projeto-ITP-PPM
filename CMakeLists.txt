# CMakeLists.txt

# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Define your project name and the languages it uses
project(ProjetoItpPPM LANGUAGES CXX)

# (Optional but recommended) Set the C++ standard
# This ensures consistency across different compilers.
set(CMAKE_CXX_STANDARD 17) # For C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # CMake will error if C++17 is not available

# Add an executable target
# 'my_executable' is the name of your executable
# 'main.cpp', 'src/foo.cpp', 'src/bar.cpp' are your source files
add_executable(my_executable src/main.cpp 
                             src/includes/Paleta/paleta.cpp 
                             src/includes/ImageP2/imagep2.cpp 
                             src/includes/ImageP3/imagep3.cpp)

# (Optional) Link libraries if your executable needs them
# For example, if you were using an external library like Boost, you'd link it here.
# target_link_libraries(my_executable PRIVATE Boost::program_options)

# (Optional) If you have headers in a separate 'include' directory, tell CMake where to find them.
# This assumes your headers are in a directory named 'include' at the project root.
# target_include_directories(my_executable PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
