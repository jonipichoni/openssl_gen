# cmake -G "Visual Studio 12 2013" .
# cmake --build . --target ALL_BUILD --config Release


set(MODULE_NAME "CertCeg_Server")
set(MODULE_PREFIX "PRE_${MODULE_NAME}")

#set(${MODULE_PREFIX}_SRCS
#	main.cpp
#)

file(GLOB ${MODULE_PREFIX}_SRCS
    "*.h"
    "*.cpp"
)

# Always include the source and build directories in the include path.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Always include the source and build directories in the include path.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# create the shared library
add_executable(${MODULE_NAME} ${${MODULE_PREFIX}_SRCS})

# To include public dll includes
include_directories(${CMAKE_SOURCE_DIR}/src/lib)
# To include exported headers
include_directories(${PROJECT_BINARY_DIR}/src/lib)

# link our executable "main" with the shared library "shared"
#target_link_libraries(${MODULE_NAME} PUBLIC "CertCeg_Lib")
target_link_libraries(${MODULE_NAME} PUBLIC "CertCeg_Lib" libspdlog ${CMAKE_THREAD_LIBS_INIT})
