add_subdirectory(fmt)
add_subdirectory(googletest)
add_subdirectory(clipper)
add_subdirectory(poly2tri)

set(RAPIDJSON_HAS_STDSTRING ON)
add_subdirectory(rapidjson)