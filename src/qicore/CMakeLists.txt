set(SRC
  )
  
add_library(qicore SHARED ${SRC})
set_target_properties(qicore PROPERTIES LINKER_LANGUAGE CXX)
