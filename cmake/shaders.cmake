separate_arguments(FILES)

foreach (file ${FILES})
    set(srcfile ${SOURCE_DIR}/${file})
    get_filename_component(name ${srcfile} NAME_WE)
    get_filename_component(extension ${srcfile} EXT)
    
    #strip the leading . in extension
    string(SUBSTRING  ${extension} 1 -1 extension)
    if(NOT ${extension} MATCHES "frag")
        if(NOT ${extension} MATCHES "vert")
            message(FATAL_ERROR "Unsupported file type '${extension}' for '${srcfile}'")
        endif()
    endif()
    
    set(source "")
    
    file(STRINGS ${srcfile} lines)
    foreach (line ${lines})
        set(source "${source}    \"${line}\\n\"\n")
    endforeach()
    
    
    set(destfilename "${name}_${extension}.h")
    file(
        WRITE ${DESTINATION_DIR}/${destfilename}
        "static const GLchar *${name}_${extension}_shader[] = {\n"
        "${source}"
        "};\n"
    )
    
    message(STATUS "Shader converted: ${srcfile} to ${DESTINATION_DIR}/${destfilename}")
endforeach()