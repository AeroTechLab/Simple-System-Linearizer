cmake_minimum_required( VERSION 2.8 )
project( System-Linearizer )

set( CMAKE_C_STANDARD 99 )
set( CMAKE_C_STANDARD_REQUIRED ON )

set( LIBRARY_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE PATH "Relative or absolute path to directory where built shared libraries will be placed" )

if( NOT TARGET Matrix )
  include( ${CMAKE_CURRENT_LIST_DIR}/matrix/CMakeLists.txt )
endif()

add_library( SystemLinearizer SHARED ${CMAKE_CURRENT_LIST_DIR}/system_linearizer.c )
set_target_properties( SystemLinearizer PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_DIR} )
target_include_directories( SystemLinearizer PUBLIC ${CMAKE_CURRENT_LIST_DIR} )
target_compile_definitions( SystemLinearizer PUBLIC -DDEBUG )
target_link_libraries( SystemLinearizer Matrix ) 

add_executable( TestLinearizer ${CMAKE_CURRENT_LIST_DIR}/test_linearizer.c )
target_link_libraries( TestLinearizer SystemLinearizer )
