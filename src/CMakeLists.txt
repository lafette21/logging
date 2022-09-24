set(EXEC_NAME example)

include_directories(${CMAKE_HOME_DIRECTORY}/include)

add_executable(${EXEC_NAME}
    main.cc
)

target_link_libraries(${EXEC_NAME}
    project_warnings
    ${CONAN_LIBS}
)
