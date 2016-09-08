
include_directories(
  ../../../nanovg/src
  )
  
set(SRC
	../../../nanovg/src/nanovg.c
  )


add_library(nanovg SHARED ${SRC})
target_link_libraries( nanovg
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
	${GLEW_LIBRARIES})