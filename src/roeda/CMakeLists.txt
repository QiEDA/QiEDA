
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


set (INC
  About.hpp
        MainWindow.hpp
  )
  
set (SRC
  main.cpp
  MainWindow.cpp
  About.cpp
  GerberOpenGlProcessor.cpp
        )

set(UI
  About.ui
  )
  
# Qt resource files
set(RSRC roeda.qrc)

qt5_wrap_ui(UI_INC ${UI})
qt5_add_resources(RSRC_SRC ${RSRC})
source_group("Forms"               FILES ${UI})
source_group("Resources"           FILES ${RSRC})
source_group("Generated Files\\ui" FILES ${UI_INC})


add_executable(roeda WIN32
  ${INC}
  ${SRC}
  ${MOC}
  ${UI_INC}
  ${RSRC_SRC}
  ${QM}
)

include_directories(${PROJECT_SOURCE_DIR}/deps/rapidjson/include)
target_link_libraries(roeda rocore rogerber)

qt5_use_modules(roeda Widgets)

install(TARGETS roeda RUNTIME DESTINATION ${QIEDA_BIN})