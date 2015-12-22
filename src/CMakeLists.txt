set(SOURCE_FILES
        main.c)

add_executable(v2r-irsend ${SOURCE_FILES})

install(TARGETS v2r-irsend
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        )