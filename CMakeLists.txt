cmake_minimum_required(VERSION 3.5)

project(fluid-gonzalo)

###################
## CONFIGURATION ##
###################

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON )
set(CMAKE_CXX_EXTENSIONS OFF)

# Set additional CXX flags
string(APPEND CMAKE_CXX_FLAGS " \
    -std=c++11 \
    -Wall \
")

###################
##    LIBRARY    ##
###################

set(ENCODER_HEADERS
  ${PROJECT_SOURCE_DIR}/include/CircularBuffer.h
  ${PROJECT_SOURCE_DIR}/include/EncoderReader.h
)
add_library(encoderFluid INTERFACE ${ENCODER_HEADERS})
target_include_directories(encoderFluid INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/encoderFluid>
)

install(TARGETS encoderFluid EXPORT encoderFluidExport)
install(EXPORT encoderFluidExport
  DESTINATION lib/cmake/encoderFluid
)
install(FILES ${ENCODER_HEADERS}
  DESTINATION include/encoderFluid
)

###################
##     TESTS    ##
###################

enable_testing()
add_subdirectory(tests)

