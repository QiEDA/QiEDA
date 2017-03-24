set(SRC
		Gerber.cpp
		GerberCommands.cpp)

include_directories(fmt)

add_library(rogerber SHARED ${SRC})
target_link_libraries(rogerber fmt)
