
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
		-DFILES="shader.vert;shader.frag"
		-DDESTINATION_DIR="${PROJECT_SOURCE_DIR}/include/rocore/shaders/"
		-P ${CMAKE_MODULE_PATH}/shaders.cmake
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    
#AUTOMOC needs us to add the header to library for it to work on the class
set(INC
		${PROJECT_SOURCE_DIR}/include/rocore/ui/GLWidget.hpp
		${PROJECT_SOURCE_DIR}/include/rocore/ui/QiMainWindow.hpp
		${PROJECT_SOURCE_DIR}/include/rocore/ui/DocumentView.hpp
		${PROJECT_SOURCE_DIR}/include/rocore/ui/GerberDocumentView.hpp
		${PROJECT_SOURCE_DIR}/include/rocore/ui/ProjectView.hpp
        ${PROJECT_SOURCE_DIR}/include/rocore/ui/LayerView.hpp
		${PROJECT_SOURCE_DIR}/include/rocore/ui/LayerViewItem.hpp
		${PROJECT_SOURCE_DIR}/include/rocore/ui/LayerViewItemModel.hpp
		${PROJECT_SOURCE_DIR}/include/rocore/projects/Project.hpp
		${PROJECT_SOURCE_DIR}/include/rocore/projects/ProjectViewItemModel.hpp
	)


set(SRC
		ui/GLScrollArea.cpp
		ui/GLWidget.cpp
		ui/DocumentView.cpp
		ui/GerberDocumentView.cpp
        ui/QiMainWindow.cpp
		ui/ProjectView.cpp
		ui/LayerView.cpp
		ui/LayerViewItem.cpp
		ui/LayerViewItemModel.cpp
		graphics/Color.cpp
		graphics/GraphicArc.cpp
		graphics/GraphicCircle.cpp
		graphics/GraphicLine.cpp
		graphics/GraphicRawLine.cpp
		graphics/GraphicRectangle.cpp
		graphics/GraphicText.cpp
		graphics/GLPainter.cpp
		graphics/GLShader.cpp
		graphics/GraphicLayer.cpp
		graphics/GridLayer.cpp
		graphics/TestLayer.cpp
		graphics/GraphicPoly.cpp
		projects/Project.cpp
		projects/Viewer.cpp
		projects/ProjectViewItem.cpp
		projects/ProjectViewItemModel.cpp
)


include_directories(${PROJECT_SOURCE_DIR}/deps/rapidjson/include)
add_library(rocore SHARED ${SRC} ${INC})

target_link_libraries(
    rocore ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARY} )
add_dependencies(rocore shaders)


qt5_use_modules(rocore Widgets OpenGL)

install(TARGETS rocore DESTINATION ${QIEDA_LIB} COMPONENT binary)