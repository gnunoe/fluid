###################
##  GTEST FETCH  ##
###################

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(BUILD_GTEST ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

###############
##   TESTS   ##
###############

# CircularBuffer Test
add_executable (utest-CircularBuffer
    ${PROJECT_SOURCE_DIR}/tests/test_CircularBuffer.cpp
)

target_link_libraries(utest-CircularBuffer
    gtest_main
    encoderFluid
)

# EncoderReader Test
add_executable (utest-EncoderReader
    ${PROJECT_SOURCE_DIR}/tests/test_EncoderReader.cpp
)

target_link_libraries(utest-EncoderReader
    gtest_main
    encoderFluid
)
