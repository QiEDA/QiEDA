
include_directories(
	${PROJECT_SOURCE_DIR}/nanovg/src
)
  
set(SRC
	${PROJECT_SOURCE_DIR}/nanovg/src/nanovg.c
)


add_library(nanovg SHARED ${SRC})
target_link_libraries( nanovg
    ${OPENGL_gl_LIBRARY}
    ${OPENGL_glu_LIBRARY}
	${GLEW_LIBRARIES})

install(TARGETS nanovg DESTINATION ${QIEDA_LIB} COMPONENT binary)