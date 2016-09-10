
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(
  ${PROJECT_SOURCE_DIR}/nanovg/src
  )
  
set(SRC
	ui/GLScrollArea.cpp
	ui/GLWidget.cpp
		graphics/Color.cpp
		graphics/GraphicLine.cpp
		graphics/GraphicRectangle.cpp)



add_library(qicore SHARED ${SRC})
set_target_properties(qicore PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(
    qicore
    nanovg )

qt5_use_modules(qicore Widgets OpenGL)

install(TARGETS qicore DESTINATION ${QIEDA_LIB} COMPONENT binary)