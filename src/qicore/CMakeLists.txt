
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_AUTOMOC ON)

set(SRC
	ui/GLWidget.cpp
  )

  
add_library(qicore SHARED ${SRC})
target_link_libraries(
    qicore
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY} )

qt5_use_modules(qicore Widgets OpenGL)