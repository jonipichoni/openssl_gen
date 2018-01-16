
# mkdir build
# cd build 
# cmake .. && cmake --build . --target Example --config Release
# Warning:
# On windows the openssl lib installed must be compiled with the same visual studio chain used
# eg:
#   cmake .. -DOPENSSL_ROOT_DIR=C:/OpenSSL-Win32  -DOPENSSL_INCLUDE_DIR=C:/OpenSSL-Win32/include
#
# Shared Libraries
#  - By default is linked statically
#  - Use cmake .. -DBUILD_SHARED_LIBS=ON Otherwise
#
# Toolchain
#  - On MSVC make sure openssl has been built with the same MSVC version
#  - cmake .. -G "Visual Studio 14 2015"
#
#

cmake_minimum_required (VERSION 3.0)

project (CertGen)

enable_testing()

if(MSVC)
  # RuntimeLibrary
  # 0 (MultiThreaded) == /MT
  # 1 (MultiThreadedDebug) == /MTd
  # 2 (MultiThreadedDLL) == /MD
  # 3 (MultiThreadedDebugDLL) == /MDd
  # set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
  # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")

  # TreatWChar_tAsBuiltInType: true == /Zc:wchar_t  false == /Zc:wchar_t-
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t")

  # WarningLevel: /W<level 0 to 4> or /Wall
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")

  # Optimization level
  # set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} /O1")

endif()

if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")
    endif ()
else ()
    set (CMAKE_CXX_STANDARD 11)
endif ()


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include_3rd_party)
find_package(Threads)

add_subdirectory(src)

MESSAGE( STATUS "Compiler Info:")
# the compiler used for C++ files 
MESSAGE( STATUS "     CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} )
# the compiler flags for compiling C++ sources 
MESSAGE( STATUS "     CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )
MESSAGE( STATUS "     CMAKE_CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE} )
MESSAGE( STATUS "     CMAKE_CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG} )

MESSAGE( STATUS "Directory Info:")
MESSAGE( STATUS "     CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR} )
MESSAGE( STATUS "     PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )
MESSAGE( STATUS "     CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
MESSAGE( STATUS "     CMAKE_ARCHIVE_OUTPUT_DIRECTORY: " ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
MESSAGE( STATUS "     CMAKE_LIBRARY_OUTPUT_DIRECTORY: " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
MESSAGE( STATUS "     CMAKE_RUNTIME_OUTPUT_DIRECTORY: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )


