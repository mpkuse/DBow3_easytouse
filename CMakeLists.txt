cmake_minimum_required(VERSION 2.8.3)
project(nap)

set( CMAKE_CXX_STANDARD 11 )
find_package(Threads)
find_package(OpenCV 3 REQUIRED)


SET (SRCS
    dbow3_core/BowVector.cpp
    dbow3_core/Database.cpp
    dbow3_core/DescManip.cpp
    dbow3_core/FeatureVector.cpp
    dbow3_core/QueryResults.cpp
    dbow3_core/quicklz.c
    dbow3_core/ScoringObject.cpp
    dbow3_core/Vocabulary.cpp
    )


INCLUDE_DIRECTORIES( dbow3_core )

# This is rather crude to link all the .o with the executables.
# I will accept a PR (pull-request) if you change this bit to
# make a static-linked library (.a) for the core files.

# Usage
add_executable( demo_general demo_general.cpp ${SRCS} )
add_executable( dbow3_test dbow3_test.cpp ${SRCS} )

# Vocabulary Construction
add_executable( create_voc_step0 create_voc_step0.cpp ${SRCS} )
add_executable( create_voc_step1 create_voc_step1.cpp ${SRCS} )


target_link_libraries( demo_general  ${OpenCV_LIBRARIES} )
target_link_libraries( dbow3_test  ${OpenCV_LIBRARIES} )


target_link_libraries( create_voc_step0  ${OpenCV_LIBRARIES} )
target_link_libraries( create_voc_step1  ${OpenCV_LIBRARIES} )
