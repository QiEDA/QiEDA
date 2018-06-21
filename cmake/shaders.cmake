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

    string(CONCAT source "static const char *${name}_${extension}_shader = {\n"
            "${source}"
            "};\n")

    string(SHA256 sourceHash "${source}")

    set(destHashFileName "${name}_${extension}.hash")


    set(existingDestHash "")
    file (STRINGS ${DESTINATION_DIR}/${destHashFileName} existingDestHash)
    if(NOT sourceHash STREQUAL existingDestHash)
        file(
                WRITE ${DESTINATION_DIR}/${destHashFileName}
                "${sourceHash}"
        )


        set(destFileName "${name}_${extension}.h")
        file(
                WRITE ${DESTINATION_DIR}/${destFileName}
                "${source}"
        )

        message(STATUS "Shader ${srcfile} converted to ${DESTINATION_DIR}/${destFileName}, hash: ${sourceHash}")
    else()
        message(STATUS "Shader changed not detected for ${srcfile}, hash: ${sourceHash}")
    endif()

endforeach()