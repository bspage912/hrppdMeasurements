
PROJECT(TEKTRONIX)

# Should suffice?;
cmake_minimum_required(VERSION 3.0.0)

# Assume ROOTSYS was setup in the environment;
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

# Find ROOT;
FIND_PACKAGE(ROOT 6.0.0 REQUIRED COMPONENTS RIO Tree Hist)

#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

#SET( CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -fPIC -Wno-narrowing" )
#SET( CMAKE_CXX_FLAGS "-g -Wall -std=c++11 -pthread -fPIC -Wno-misleading-indentation" )
include(CheckCXXCompilerFlag)
#SET(CMAKE_CXX_FLAGS "-Wall -std=c++0x -Wno-misleading-indentation")

check_cxx_compiler_flag(-std=c++17 HAVE_FLAG_STD_CXX17)
if(HAVE_FLAG_STD_CXX17)
  # Have -std=c++17, use it;	
  #+SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wno-format-truncation")
else()
  check_cxx_compiler_flag(-std=c++11 HAVE_FLAG_STD_CXX11)
  if(HAVE_FLAG_STD_CXX11)
    # Have -std=c++11, use it;	
    SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  endif()
endif()

include_directories(
  ${PROJECT_SOURCE_DIR}
  )

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

SET(CSV2ROOT_EXE csv2root)
SET(PROCESS_EXE process)

SET( CSV2ROOT_SRC
  source/csv2root_bp.cc
  )

SET( PROCESS_SRC
  source/processElmoScopeTree.cxx
  )

ADD_EXECUTABLE( ${CSV2ROOT_EXE} ${CSV2ROOT_SRC} )
TARGET_LINK_LIBRARIES(${CSV2ROOT_EXE} ${ROOT_LIBRARIES} )

ADD_EXECUTABLE( ${PROCESS_EXE} ${PROCESS_SRC} )
TARGET_LINK_LIBRARIES(${PROCESS_EXE} ${ROOT_LIBRARIES} )

#INSTALL(TARGETS ${CSV2ROOT_EXE} DESTINATION bin)
#INSTALL(TARGETS ${PROCESS_EXE} DESTINATION bin)
