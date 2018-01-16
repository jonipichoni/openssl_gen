file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testlib ${SRCS})

TARGET_LINK_LIBRARIES(testlib
    libgtest
    libgmock
)

if (WIN32 OR CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")

	#gtest and gmock requires MT they way is done here
	target_compile_options(testlib PRIVATE "/MT$<$<CONFIG:Debug>:d>")


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

add_test(NAME testlib
         COMMAND testlib)
