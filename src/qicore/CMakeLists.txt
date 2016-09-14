
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

include_directories(
  ${PROJECT_SOURCE_DIR}/nanovg/src
  )

#add shader precompile as a custom target + "post-build" of the target
add_custom_target(
    shaders ALL
)

add_custom_command(
    TARGET shaders
    POST_BUILD
	COMMAND ${CMAKE_COMMAND}
        -DSOURCE_DIR="${PROJECT_SOURCE_DIR}/src/qicore/shaders/"
		-DFILES="circle.vert;circle.frag"
        -DDESTINATION_DIR="${PROJECT_SOURCE_DIR}/include/qicore/shaders/"
		-P ${CMAKE_MODULE_PATH}/shaders.cmake
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  

    
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
		../../include/qicore/Units.hpp graphics/GLPainter.cpp ../../include/qicore/graphics/GLPainter.hpp)


add_library(qicore SHARED ${SRC} ${INC})
target_link_libraries(
    qicore ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARY} )
add_dependencies(qicore shaders)


qt5_use_modules(qicore Widgets OpenGL)

install(TARGETS qicore DESTINATION ${QIEDA_LIB} COMPONENT binary)