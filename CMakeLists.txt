# We will always try to use a version > 3.1 if avaliable
cmake_minimum_required(VERSION 3.20)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()
# Name of the project
project(HelloBulletProject)
# Set to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Find Bullet Physics
find_package(Bullet CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)


add_executable(BulletBoilerPlate)
target_sources(BulletBoilerPlate PRIVATE main.cpp )
target_link_libraries(BulletBoilerPlate PRIVATE fmt::fmt )
# Note this order is important
target_link_libraries(BulletBoilerPlate PRIVATE LinearMath Bullet3Common BulletDynamics  BulletCollision  BulletSoftBody)

#################################################################################
# Testing code
#################################################################################

find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
enable_testing()
add_executable(ParticleTests)
target_sources(ParticleTests PRIVATE tests/ParticleTests.cpp  src/Emitter.cpp src/Vec3.cpp include/Emitter.h include/Particle.h include/Vec3.h)
target_link_libraries(ParticleTests PRIVATE GTest::gtest GTest::gtest_main )
gtest_discover_tests(ParticleTests)