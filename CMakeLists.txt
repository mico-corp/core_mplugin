##---------------------------------------------------------------------------------------------------------------------
##  MICO TEMPLATE plugin
##---------------------------------------------------------------------------------------------------------------------
##  Copyright 2020 Pablo Ramon Soria (a.k.a. Bardo91) pabramsor@gmail.com & Ricardo Lopez Lopez (a.k.a Ric92) & Marco Montes Grova (a.k.a mgrova)
##---------------------------------------------------------------------------------------------------------------------
##  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
##  and associated documentation files (the "Software"), to deal in the Software without restriction,
##  including without limitation the rights to use, copy, modify, merge, publish, distribute,
##  sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
##  furnished to do so, subject to the following conditions:
##
##  The above copyright notice and this permission notice shall be included in all copies or substantial
##  portions of the Software.
##
##  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
##  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
##  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
##  OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
##  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
##---------------------------------------------------------------------------------------------------------------------

cmake_minimum_required (VERSION 3.12 FATAL_ERROR)
project(mico VERSION 1.0 LANGUAGES C CXX)
set(PLUGIN_NAME ${PROJECT_NAME}-core)

##################################################
######    Configure project               ########
##################################################

##################################################
######    Loading 3rd party libraries.    ########
##################################################

set(MICO_CORE_INCLUDES "")
set(MICO_CORE_LIBRARIES "")
set(MICO_CORE_COMPILE_DEFS "")

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING
       "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
       FORCE )
endif()

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/" ${CMAKE_MODULE_PATH})

if(NOT ${BUNDLE_COMPILATION})
  find_package(flow REQUIRED)
  if(${flow_FOUND})
    set(MICO_CORE_LIBRARIES "${MICO_CORE_LIBRARIES} flow::flow")
    set(MICO_CORE_COMPILE_DEFS "${MICO_CORE_COMPILE_DEFS} HAS_FLOW")
  endif()
else()
  set(flow_FOUND TRUE)
    set(MICO_CORE_LIBRARIES "${MICO_CORE_LIBRARIES} flow")
    set(MICO_CORE_COMPILE_DEFS "${MICO_CORE_COMPILE_DEFS} HAS_FLOW")
endif()

find_package(PCL QUIET REQUIRED)
if(${PCL_FOUND})
    set(MICO_CORE_INCLUDES "${MICO_CORE_INCLUDES} ${PCL_INCLUDE_DIRS}")
    set(MICO_CORE_LIBRARIES "${MICO_CORE_LIBRARIES} ${PCL_LIBRARIES}")
    set(MICO_CORE_COMPILE_DEFS "${MICO_CORE_COMPILE_DEFS} ENABLE_PCL DISABLE_PCAP DISABLE_PNG DISABLE_LIBUSB_1_0")
endif()

find_package(OpenCV REQUIRED COMPONENTS core)
if(${OpenCV_FOUND})
    set(MICO_CORE_INCLUDES "${MICO_CORE_INCLUDES} ${OpenCV_INCLUDE_DIRS}")
    set(MICO_CORE_LIBRARIES "${MICO_CORE_LIBRARIES} ${OpenCV_LIBS}")
    set(MICO_CORE_COMPILE_DEFS "${MICO_CORE_COMPILE_DEFS} HAS_OPENCV")
endif()


##################################################
###### Create project and configure ALIAS ########
##################################################

file(GLOB_RECURSE MICO_CORE_SOURCE_FILES "src/*.cpp" "src/*.c")
file(GLOB_RECURSE MICO_CORE_HEADER_FILES "include/*.h" "include/*.inl")
 
SET(MICO_MODULES ${MICO_MODULES} core PARENT_SCOPE)
add_library(${PLUGIN_NAME}  ${LIBRARY_MODE} ${MICO_CORE_HEADER_FILES} ${MICO_CORE_SOURCE_FILES})
target_compile_features(${PLUGIN_NAME} PUBLIC cxx_std_17)
target_include_directories(${PLUGIN_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

#target_compile_options(${PLUGIN_NAME} PUBLIC "-Wall")

add_library(${PROJECT_NAME}::${PLUGIN_NAME} ALIAS ${PLUGIN_NAME})

target_include_directories(${PLUGIN_NAME} PUBLIC ${MICO_CORE_INCLUDES})
target_link_libraries(${PLUGIN_NAME} LINK_PUBLIC ${MICO_CORE_LIBRARIES})
target_compile_definitions(${PLUGIN_NAME} PUBLIC ${MICO_CORE_COMPILE_DEFS})

##################################################
######    Documentation.                  ########
##################################################
find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(	doc_CORE
						${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
						WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
						COMMENT "Generating API documentation with Doxygen" VERBATIM )
endif(DOXYGEN_FOUND)

##################################################
######    Installation.                   ########
##################################################
# FLOW INSTALL target 
if(WIN32)
    set(EXPORTED_PLUGIN_NAME ${PLUGIN_NAME}_mplugin)
    add_library(${EXPORTED_PLUGIN_NAME} SHARED ${MICO_CORE_HEADER_FILES} ${MICO_CORE_SOURCE_FILES})
    target_include_directories(${EXPORTED_PLUGIN_NAME} PUBLIC ${MICO_CORE_INCLUDES})
    target_link_libraries(${EXPORTED_PLUGIN_NAME} LINK_PUBLIC ${MICO_CORE_LIBRARIES})
    target_compile_definitions(${EXPORTED_PLUGIN_NAME} PUBLIC ${MICO_CORE_COMPILE_DEFS})
else(UNIX)
    set(EXPORTED_PLUGIN_NAME ${PLUGIN_NAME} ${PLUGIN_NAME})
endif()

add_custom_target(flow_install_${PLUGIN_NAME} ALL
                COMMAND ${CMAKE_COMMAND} -E copy 	$<TARGET_FILE:${EXPORTED_PLUGIN_NAME}>
                ${CMAKE_BINARY_DIR}/plugins
)
add_custom_target(flow_install_${PLUGIN_NAME}_resources ALL
                COMMAND ${CMAKE_COMMAND} -E copy_directory 	${CMAKE_CURRENT_SOURCE_DIR}/resources 
                ${CMAKE_BINARY_DIR}/plugins/resources/math
)

add_dependencies(flow_install_${PLUGIN_NAME} ${PLUGIN_NAME})
add_dependencies(flow_install_${PLUGIN_NAME}_resources ${PLUGIN_NAME})
