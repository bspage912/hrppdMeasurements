
# CMake Stuff
cmake_minimum_required(VERSION 3.25)
project(TEKTRONIX)

# Assume ROOTSYS was setup in the environment;
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Find ROOT;
find_package(ROOT 6.0.0 REQUIRED COMPONENTS RIO Tree Hist)

# Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

# Set C++ Standard
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
if(HAVE_FLAG_STD_CXX17)
  # Have -std=c++17 then use it;
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
else()
  check_cxx_compiler_flag(-std=c++11 HAVE_FLAG_STD_CXX11)
  if(HAVE_FLAG_STD_CXX11)
    # Have -std=c++11 then use it
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
  endif()
endif()

# Move Executables to bin/ and libraries to lib/
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib )

# Set include dir
include_directories( ${PROJECT_SOURCE_DIR}/include )

# Set Executable Names
set( CSV2ROOT_EXE csv2root )
set( PROCESS_EXE process )
set( PROCESSWF_EXE processWF )
set( WAVEFORM_LIB waveform )

# Set Source Directories
set( CSV2ROOT_SRC source/csv2root.cc )
set( PROCESS_SRC source/processTektronixTree.cxx )
set( PROCESSWF_SRC source/processWaveforms.cxx )
set( WAVEFORM_SRC source/waveform.cxx )

# Build Executables
add_library( ${WAVEFORM_LIB} ${WAVEFORM_SRC} )
target_link_libraries( ${WAVEFORM_LIB} ${ROOT_LIBRARIES} )

add_executable( ${CSV2ROOT_EXE} ${CSV2ROOT_SRC} )
target_link_libraries(${CSV2ROOT_EXE} ${ROOT_LIBRARIES} )

add_executable( ${PROCESS_EXE} ${PROCESS_SRC} )
target_link_libraries(${PROCESS_EXE} ${ROOT_LIBRARIES} ${WAVEFORM_LIB} )

add_executable( ${PROCESSWF_EXE} ${PROCESSWF_SRC} )
target_link_libraries(${PROCESSWF_EXE} ${ROOT_LIBRARIES} ${WAVEFORM_LIB} )

