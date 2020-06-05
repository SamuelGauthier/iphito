include(main.cmake)

# BISON_TARGET(iphitoParser
#     ./cli/Parser.yy
#     ${CMAKE_CURRENT_BINARY_DIR}/Parser.tab.cc
#     )

# FLEX_TARGET(iphitoLexer
#     ./cli/Lexer.l
#     ${CMAKE_CURRENT_BINARY_DIR}/Lexer.yy.cc
#     )
# ADD_FLEX_BISON_DEPENDENCY(iphitoLexer iphitoParser)

add_executable(${PROJECT_NAME}
    main.cpp
    ${TARGET_SRC}
    ${TARGET_H}
    # ${FLEX_iphitoLexer_OUTPUTS}
    # ${BISON_iphitoParser_OUTPUTS}
)

target_link_libraries(${PROJECT_NAME}
    OpenGL::GL
    GLEW::GLEW
    glfw
    spdlog::spdlog
)

target_include_directories(${PROJECT_NAME} PRIVATE
    .
    ${UTILS_DIR}
    ${MATH_DIR}
    ${RENDERER_DIR}
    ${CLI_DIR}
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)
