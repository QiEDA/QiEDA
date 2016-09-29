add_executable(gerbertest
        GerberTest.cpp)

target_link_libraries(gerbertest qigerber)


install(TARGETS gerbertest RUNTIME DESTINATION ${QIEDA_BIN})