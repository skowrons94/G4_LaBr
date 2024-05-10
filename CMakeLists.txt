#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(G4_LaBr)
set(CMAKE_CXX_STANDARD 14)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(ROOT REQUIRED COMPONENTS RIO Net)
include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc ${PROJECT_SOURCE_DIR}/src/geometry/*.cc ${PROJECT_SOURCE_DIR}/src/generator/PositronGun/*.cc ${PROJECT_SOURCE_DIR}/src/generator/NuclideGen/*.cc ${PROJECT_SOURCE_DIR}/src/generator/IsotropicGun/*.cc ${PROJECT_SOURCE_DIR}/src/generator/GammaDecayScheme/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh ${PROJECT_SOURCE_DIR}/include/geometry/*.hh ${PROJECT_SOURCE_DIR}/include/generator/GammaDecayScheme/*.hh ${PROJECT_SOURCE_DIR}/include/generator/IsotropicGun/*.hh ${PROJECT_SOURCE_DIR}/include/generator/PositronGun/*.hh ${PROJECT_SOURCE_DIR}/include/generator/NuclideGen/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(G4_LaBr ${sources} ${headers})
target_link_libraries(G4_LaBr ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})

#----------------------------------------------------------------------------
# Creates the data directory
#
#file(MAKE_DIRECTORY ${PROJECT_BINARY_DIR}/data)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory
#
file(COPY ${PROJECT_SOURCE_DIR}/mac DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/mesh DESTINATION ${PROJECT_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/Run.py DESTINATION ${PROJECT_BINARY_DIR})

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS G4_LaBr DESTINATION bin)