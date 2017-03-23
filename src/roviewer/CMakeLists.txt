
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


set (INC
  About.hpp
  MainWindow.h
  )
  
set (SRC
  main.cpp
  MainWindow.cpp
  About.cpp
  )

set(UI
  About.ui
  )
  
# Qt resource files
set(RSRC roviewer.qrc)

qt5_wrap_ui(UI_INC ${UI})
qt5_add_resources(RSRC_SRC ${RSRC})
source_group("Forms"               FILES ${UI})
source_group("Resources"           FILES ${RSRC})
source_group("Generated Files\\ui" FILES ${UI_INC})


add_executable(roviewer WIN32
  ${INC}
  ${SRC}
  ${MOC}
  ${UI_INC}
  ${RSRC_SRC}
  ${QM}
)

target_link_libraries(roviewer rocore rogerber)

qt5_use_modules(roviewer Widgets)

install(TARGETS roviewer RUNTIME DESTINATION ${QIEDA_BIN})