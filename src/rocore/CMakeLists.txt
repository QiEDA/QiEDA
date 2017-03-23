
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

#add shader precompile as a custom target + "post-build" of the target
add_custom_target(
    shaders ALL
)

add_custom_command(
    TARGET shaders
    POST_BUILD
	COMMAND ${CMAKE_COMMAND}
        -DSOURCE_DIR="${PROJECT_SOURCE_DIR}/src/rocore/shaders/"
		-DFILES="circle.vert;circle.frag"
        -DDESTINATION_DIR="${PROJECT_SOURCE_DIR}/include/rocore/shaders/"
		-P ${CMAKE_MODULE_PATH}/shaders.cmake
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})



add_custom_command(
		TARGET shaders
		POST_BUILD
		COMMAND ${CMAKE_COMMAND}
		-DSOURCE_DIR="${PROJECT_SOURCE_DIR}/src/rocore/shaders/"
		-DFILES="shader.vert;shader.frag"
		-DDESTINATION_DIR="${PROJECT_SOURCE_DIR}/include/rocore/shaders/"
		-P ${CMAKE_MODULE_PATH}/shaders.cmake
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    
#AUTOMOC needs us to add the header to library for it to work on the class
set(INC
		${PROJECT_SOURCE_DIR}/include/rocore/ui/GLWidget.hpp
		${PROJECT_SOURCE_DIR}/include/rocore/ui/QiMainWindow.hpp
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
		graphics/GLPainter.cpp
		graphics/GLShader.cpp
		graphics/GraphicLayer.cpp
        graphics/GridLayer.cpp )


add_library(rocore SHARED ${SRC} ${INC})
target_link_libraries(
    rocore ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARY} )
add_dependencies(rocore shaders)


qt5_use_modules(rocore Widgets OpenGL)

install(TARGETS rocore DESTINATION ${QIEDA_LIB} COMPONENT binary)