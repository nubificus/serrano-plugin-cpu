cmake_minimum_required(VERSION 3.10)

project(vaccelrt-plugin-serrano-cpu
	VERSION 0.1
	DESCRIPTION "vAccelRT plugin for SERRANO project"
	LANGUAGES C)

# Export json with compile commands
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
	EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
		${CMAKE_SOURCE_DIR}/compile_commands.json
	)
ENDIF()

set(VACCELRT_INCLUDE
	${CMAKE_SOURCE_DIR}/vaccelrt/src/include
	${CMAKE_SOURCE_DIR}/vaccelrt/third-party/slog/src
	CACHE STRING "Path to vAccel runtime headers")

set(SOURCES
    src/vaccel.c
    src/gemm.c
    src/gemm.h
    src/minmax.c
    src/minmax.h
)

# export rpath for libraries when installing
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_subdirectory(version)
add_library(vaccel-serrano-cpu SHARED ${SOURCES})
add_dependencies(vaccel-serrano-cpu version)
target_compile_features(vaccel-serrano-cpu PUBLIC)
target_include_directories(vaccel-serrano-cpu PRIVATE ${VACCELRT_INCLUDE} ${CMAKE_BINARY_DIR}/version)
target_link_libraries(vaccel-serrano-cpu m)

# Setup `make install`
include(GNUInstallDirs)
install(TARGETS vaccel-serrano-cpu DESTINATION "${CMAKE_INSTALL_LIBDIR}")

set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT "Anastassios Nanos <ananos@nubificus.co.uk>")
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

include(CPack)

