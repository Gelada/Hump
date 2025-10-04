cmake_minimum_required(VERSION 3.20)
project(NativeWrapper LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Windows: use vcpkg toolchain for dependency resolution
# cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
# macOS: normal brew prefixes should be auto-found

find_package(OpenCV CONFIG REQUIRED COMPONENTS core imgproc imgcodecs)
find_package(CGAL   CONFIG REQUIRED)

add_library(hump SHARED
    src/hump.cpp
    src/hump.h
)

target_link_libraries(hump
    PRIVATE
        opencv_core
        opencv_imgproc
        opencv_imgcodecs
        CGAL::CGAL
)

# Consistent base name across platforms
set_target_properties(hump PROPERTIES
    OUTPUT_NAME "hump"
)

# Optional: control MSVC runtime to match vcpkg default
if (MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

# Install for packaging or local consumption
include(GNUInstallDirs)
install(TARGETS hump
    RUNTIME DESTINATION bin        # .dll
    LIBRARY DESTINATION lib        # .dylib/.so
    ARCHIVE DESTINATION lib        # .lib (import)
)
