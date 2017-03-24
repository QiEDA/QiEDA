add_executable(gerbertest
        GerberTest.cpp)

target_link_libraries(gerbertest rogerber)


install(TARGETS gerbertest RUNTIME DESTINATION ${QIEDA_BIN})