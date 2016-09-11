
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(
  ${PROJECT_SOURCE_DIR}/nanovg/src
  )

#AUTOMOC needs us to add the header to library for it to work on the class
set(INC
		${PROJECT_SOURCE_DIR}/include/qicore/ui/GLWidget.hpp
		${PROJECT_SOURCE_DIR}/include/qicore/ui/QiMainWindow.hpp
	)


set(SRC
		ui/GLScrollArea.cpp
		ui/GLWidget.cpp
		graphics/Color.cpp
		graphics/GraphicArc.cpp
		graphics/GraphicCircle.cpp
		graphics/GraphicLine.cpp
		graphics/GraphicRectangle.cpp
		graphics/GraphicText.cpp
		ui/QiMainWindow.cpp
	)


add_library(qicore SHARED ${SRC} ${INC})
target_link_libraries(
    qicore
    nanovg )

qt5_use_modules(qicore Widgets OpenGL)

install(TARGETS qicore DESTINATION ${QIEDA_LIB} COMPONENT binary)