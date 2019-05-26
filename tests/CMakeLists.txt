IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Release CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

set(BOOST_ROOT "C:/Users/Daniel/Libraries/boost_1_66_0") # either set it here or from the command line 
find_package(Boost)

include_directories (
  ${LMX_SOURCE_DIR}/src/
  ${Boost_INCLUDE_DIRS}
)

set(Inputs 001 002 003 004 005 006 007 008 009 010 011 012 013 014)
foreach(Input ${Inputs})
  add_executable (test${Input} test${Input}.cpp)
  add_test(NAME Test${Input} COMMAND test${Input})
endforeach()

