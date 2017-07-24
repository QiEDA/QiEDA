cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(roeda)

set( CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake )

#Require C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if( CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
    set( CMAKE_C_FLAGS   "-Wall ${CMAKE_C_FLAGS}" )
    set( CMAKE_CXX_FLAGS "-Wall ${CMAKE_CXX_FLAGS}" )
    
    set( CMAKE_C_FLAGS_DEBUG   "-g3 -ggdb3 -DDEBUG" )
    set( CMAKE_CXX_FLAGS_DEBUG "-g3 -ggdb3 -DDEBUG" )
endif()

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

# dump generated files into the build bin...makes it easier to debug
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(deps)

include_directories(
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_BINARY_DIR}/include
  )


if( NOT APPLE )
    set( QIEDA_BIN ${CMAKE_INSTALL_PREFIX}/bin CACHE PATH "Location of binaries" )
    
    if( WIN32 )
        set( QIEDA_LIB ${QIEDA_BIN} CACHE PATH "Location of librarys(.dll,.so)" )
    else()
        set( QIEDA_LIB ${CMAKE_INSTALL_PREFIX}/lib CACHE PATH "Location of librarys(.dll,.so)" )
    endif()
endif()

mark_as_advanced( QIEDA_BIN
    QIEDA_LIB )

add_subdirectory(src)

# Borrowed from https://github.com/wisk/medusa/blob/dev/src/tools/qt/CMakeLists.txt
# QT5 is a PITA to package
if (WIN32)

  set(QT5_BIN_PATH ${QT5_CMAKE_PATH}/../../bin)
  file(TO_CMAKE_PATH ${QT5_BIN_PATH} QT5_BIN_PATH)
  if(MSYS)
  set(QT5_PPF_PATH ${QT5_CMAKE_PATH}/../../share/qt5/plugins/platforms)
  else()
  set(QT5_PPF_PATH ${QT5_CMAKE_PATH}/../../plugins/platforms)
  endif()
  file(TO_CMAKE_PATH ${QT5_PPF_PATH} QT5_PPF_PATH)

  list(APPEND QT5_NEEDED_DLL ${QT5_BIN_PATH}/Qt5Gui.dll)
  list(APPEND QT5_NEEDED_DLL ${QT5_BIN_PATH}/Qt5Core.dll)
  list(APPEND QT5_NEEDED_DLL ${QT5_BIN_PATH}/Qt5Widgets.dll)
  if (EXISTS "${QT5_BIN_PATH}/libGLESv2.dll")
    list(APPEND QT5_NEEDED_DLL ${QT5_BIN_PATH}/libGLESv2.dll)
  endif()
  if (EXISTS "${QT5_BIN_PATH}/libEGL.dll")
    list(APPEND QT5_NEEDED_DLL ${QT5_BIN_PATH}/libEGL.dll)
  endif()

  file(GLOB icuin_dll ${QT5_BIN_PATH}/icuin*.dll)
  list(APPEND QT5_NEEDED_DLL ${icuin_dll})
  file(GLOB icuuc_dll ${QT5_BIN_PATH}/icuuc*.dll)
  list(APPEND QT5_NEEDED_DLL ${icuuc_dll})
  file(GLOB icudt_dll ${QT5_BIN_PATH}/icudt*.dll)
  list(APPEND QT5_NEEDED_DLL ${icudt_dll})
  file(GLOB d3dcompiler_dll ${QT5_BIN_PATH}/d3dcompiler_*.dll)
  list(APPEND QT5_NEEDED_DLL ${d3dcompiler_dll})

  foreach (lib ${QT5_NEEDED_DLL})
    install(FILES ${lib} DESTINATION .)
  endforeach ()

  install(FILES ${QT5_PPF_PATH}/qwindows.dll DESTINATION platforms)

endif ()

add_subdirectory(test)
