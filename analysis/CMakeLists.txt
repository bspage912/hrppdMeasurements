
# CMake Stuff
cmake_minimum_required(VERSION 3.20)
project(TEKTRONIX)

# Assume ROOTSYS was setup in the environment;
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Find ROOT;
find_package(ROOT 6.0.0 REQUIRED COMPONENTS RIO Tree Hist)

# Find nlohmann/json (required by waveform_test for JSON config loading)
# Tries CMake package first; falls back to locating the header directly.
find_package(nlohmann_json QUIET)
if(nlohmann_json_FOUND)
    message(STATUS "Found nlohmann_json via CMake package")
else()
    find_path(NLOHMANN_JSON_INCLUDE_DIR nlohmann/json.hpp
              HINTS /usr/include /usr/local/include)
    if(NLOHMANN_JSON_INCLUDE_DIR)
        message(STATUS "Found nlohmann/json.hpp at ${NLOHMANN_JSON_INCLUDE_DIR}")
        include_directories(${NLOHMANN_JSON_INCLUDE_DIR})
    else()
        message(FATAL_ERROR
            "nlohmann/json not found. Install with one of:\n"
            "  RHEL/CentOS: sudo yum install nlohmann-json-devel\n"
            "  Debian/Ubuntu: sudo apt install nlohmann-json3-dev\n"
            "  Or place json.hpp under include/nlohmann/json.hpp")
    endif()
endif()

# Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

# Set C++ Standard
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-std=c++20 HAVE_FLAG_STD_CXX20)
if(HAVE_FLAG_STD_CXX20)
  # Have -std=c++20 then use it;
  set(CMAKE_CXX_STANDARD 20)
  set(CMAKE_CXX_STANDARD_REQUIRED True)
endif()

#check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
#if(HAVE_FLAG_STD_CXX17)
#  # Have -std=c++17 then use it;
#  set(CMAKE_CXX_STANDARD 17)
#  set(CMAKE_CXX_STANDARD_REQUIRED True)
#else()
#  check_cxx_compiler_flag(-std=c++11 HAVE_FLAG_STD_CXX11)
#  if(HAVE_FLAG_STD_CXX11)
#    # Have -std=c++11 then use it
#    set(CMAKE_CXX_STANDARD 11)
#    set(CMAKE_CXX_STANDARD_REQUIRED True)
#  endif()
#endif()

# Move Executables to bin/ and libraries to lib/
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib )

# Set include dir
include_directories( ${PROJECT_SOURCE_DIR}/include )

# Set Executable Names
set( CSV2ROOT_EXE csv2root )
set( PROCESS_EXE process )
#set( PROCESS1_EXE process1 )
#set( PROCESSWF_EXE processWF )
set( WAVEFORM_UTIL_LIB waveformUtil )
set( WAVEFORM_ANALYSIS_UTIL_LIB waveformAnalysisUtil )

# Set Source Directories
set( CSV2ROOT_SRC source/csv2root.cc )
set( PROCESS_SRC source/processTektronixTree.cxx )
#set( PROCESS1_SRC source/processTektronixTree_test1.cxx )
#set( PROCESSWF_SRC source/processWaveforms.cxx )
set( WAVEFORM_UTIL_SRC source/waveformUtil.cxx )
set( WAVEFORM_ANALYSIS_UTIL_SRC source/waveformAnalysisUtil.cxx )

# Build Executables
add_library( ${WAVEFORM_UTIL_LIB} ${WAVEFORM_UTIL_SRC} )
target_link_libraries( ${WAVEFORM_UTIL_LIB} ${ROOT_LIBRARIES} )

add_library( ${WAVEFORM_ANALYSIS_UTIL_LIB} ${WAVEFORM_ANALYSIS_UTIL_SRC} )
if(nlohmann_json_FOUND)
    target_link_libraries( ${WAVEFORM_ANALYSIS_UTIL_LIB} ${ROOT_LIBRARIES} nlohmann_json::nlohmann_json ${WAVEFORM_UTIL_LIB} )
else()
    target_link_libraries( ${WAVEFORM_ANALYSIS_UTIL_LIB} ${ROOT_LIBRARIES} ${WAVEFORM_UTIL_LIB} )
endif()

add_executable( ${CSV2ROOT_EXE} ${CSV2ROOT_SRC} )
target_link_libraries(${CSV2ROOT_EXE} ${ROOT_LIBRARIES} )

add_executable( ${PROCESS_EXE} ${PROCESS_SRC} )
target_link_libraries(${PROCESS_EXE} ${ROOT_LIBRARIES} ${WAVEFORM_ANALYSIS_UTIL_LIB} )

#add_executable( ${PROCESS1_EXE} ${PROCESS1_SRC} )
#target_link_libraries(${PROCESS1_EXE} ${ROOT_LIBRARIES} ${WAVEFORM_TEST_LIB} )

#add_executable( ${PROCESSWF_EXE} ${PROCESSWF_SRC} )
#target_link_libraries(${PROCESSWF_EXE} ${ROOT_LIBRARIES} ${WAVEFORM_UTIL_LIB} )

