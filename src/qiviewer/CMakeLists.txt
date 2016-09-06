
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#commented out for now
#set(CMAKE_AUTOMOC ON)


set (INC
  About.hpp
  )
  
set (SRC
  main.cpp
  About.cpp
  )

set(UI
  About.ui
  )
  
# Qt resource files
set(RSRC qiviewer.qrc)

qt5_wrap_ui(UI_INC ${UI})
qt5_add_resources(RSRC_SRC ${RSRC})
source_group("Forms"               FILES ${UI})
source_group("Resources"           FILES ${RSRC})
source_group("Generated Files\\ui" FILES ${UI_INC})


add_executable(qiviewer WIN32
  ${INC}
  ${SRC}
  ${MOC}
  ${UI_INC}
  ${RSRC_SRC}
  ${QM}
)

target_link_libraries(qiviewer qicore)

qt5_use_modules(qiviewer Widgets)