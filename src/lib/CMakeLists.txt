# cmake -G "Visual Studio 12 2013" .
# cmake --build . --target ALL_BUILD --config Release


set(MODULE_NAME "CertCeg_Lib")
set(MODULE_PREFIX "PRE_${MODULE_NAME}")

set(${MODULE_PREFIX}_SRCS
	shared.cpp
	shared.h
	openssl_w.cpp
	openssl_w.h
)

# Export no symbols by default (if the compiler supports it).
# This makes e.g. GCC's "visibility behavior" consistent with MSVC's. 
# On Windows/MSVC this is a noop.
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Always include the source and build directories in the include path.
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Add Openssl
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

# create the shared library
# If Static not specified  type of the library will be determined by value of BUILD_SHARED_LIBS variable
add_library(${MODULE_NAME} SHARED ${${MODULE_PREFIX}_SRCS})


# generate export header automatically
include (GenerateExportHeader)
GENERATE_EXPORT_HEADER(${MODULE_NAME}
             BASE_NAME ${MODULE_NAME}
             EXPORT_MACRO_NAME ${MODULE_NAME}_EXPORT
             EXPORT_FILE_NAME ${MODULE_NAME}_Export.h
             STATIC_DEFINE ${MODULE_NAME}_BUILT_AS_STATIC)

target_link_libraries(${MODULE_NAME} OpenSSL::SSL libspdlog ${CMAKE_THREAD_LIBS_INIT})