cmake_minimum_required(VERSION 3.5)
project(sominsula VERSION 0.1 LANGUAGES C CXX)

# set(CMAKE_SYSTEM_NAME Windows)
# set(TOOLCHAIN_PREFIX x86_64-w64-mingw32)

# # cross compilers to use for C, C++ and Fortran
# set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}-gcc)
# set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}-g++)
# set(CMAKE_Fortran_COMPILER ${TOOLCHAIN_PREFIX}-gfortran)
# set(CMAKE_RC_COMPILER ${TOOLCHAIN_PREFIX}-windres)

# # target environment on the build host system
# set(CMAKE_FIND_ROOT_PATH /usr/${TOOLCHAIN_PREFIX})

# # modify default behavior of FIND_XXX() commands
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)
ExternalProject_Add(SFML 
		GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1 
		#SOURCE_DIR  ${CMAKE_SOURCE_DIR}/ext/SFML 
    		CMAKE_ARGS 
			-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
			-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
ExternalProject_Get_Property(SFML INSTALL_DIR)
set(SFML_LIB ${INSTALL_DIR})

add_compile_options(-g -static -O2 -pedantic -Wextra)

# file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/**.cpp)

set(SRC_FILES
	${CMAKE_SOURCE_DIR}/src/main.cpp
	${CMAKE_SOURCE_DIR}/src/sominsula.cpp
	${CMAKE_SOURCE_DIR}/src/realm/realm.cpp
	${CMAKE_SOURCE_DIR}/src/component/entity.cpp
	${CMAKE_SOURCE_DIR}/src/component/animation.cpp
	${CMAKE_SOURCE_DIR}/src/component/io/entity_controller.cpp
	${CMAKE_SOURCE_DIR}/src/component/displayed_tilemap.cpp
	${CMAKE_SOURCE_DIR}/src/scene/game_scene.cpp
	${CMAKE_SOURCE_DIR}/src/component/ui/inventory_ui.cpp
)

include_directories(${SFML_LIB}/include)
link_directories(${SFML_LIB}/lib)

add_executable(sominsula ${SRC_FILES})

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT sominsula)
	set_target_properties( sominsula PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Build")
	set_target_properties( sominsula PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Build")
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif(MSVC)

add_dependencies(sominsula SFML)

TARGET_LINK_LIBRARIES(sominsula
					optimized sfml-system		debug sfml-system-d 
					optimized sfml-window		debug sfml-window-d 
					optimized sfml-graphics		debug sfml-graphics-d 
					optimized sfml-audio		debug sfml-audio-d
          optimized sfml-network  debug sfml-network-d)




