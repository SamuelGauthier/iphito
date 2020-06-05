set(UTILS_DIR ./utils/)

set(UTILS_SRC
    Logger.cpp
    Utils.cpp
    )

set(UTILS_H
    Logger.h
    Utils.h
    )

set(MATH_DIR ./math/)

set(MATH_SRC
    Hermite3.cpp
    Hermite5.cpp
    Bezier.cpp
    )

set(MATH_H
    Curve.h
    Hermite3.h
    Hermite5.h
    Bezier.h
    )

set(RENDERER_DIR ./renderer/)

set(RENDERER_SRC
    Camera.cpp
    Canvas.cpp
    Window.cpp
    Shader.cpp
    Layer.cpp
    Curve2D.cpp
    Hermite32D.cpp
    Hermite52D.cpp
    Bezier2D.cpp
    Arrow2D.cpp
    Point2D.cpp
    Line2D.cpp
    Axes2D.cpp
    )

set(RENDERER_H
    Camera.h
    Canvas.h
    Window.h
    Shader.h
    Layer.h
    Curve2D.h
    Hermite32D.h
    Hermite52D.h
    Bezier2D.h
    Arrow2D.h
    Point2D.h
    Line2D.h
    Axes2D.h
    )

set(CLI_DIR ./cli/)

set(CLI_SRC
    Parser.cpp
    ASTNode.cpp
    )

set(CLI_H
    Parser.h
    ASTNode.h
    )

list(TRANSFORM UTILS_SRC PREPEND ${UTILS_DIR})
list(TRANSFORM UTILS_H PREPEND ${UTILS_DIR})
list(TRANSFORM MATH_SRC PREPEND ${MATH_DIR})
list(TRANSFORM MATH_H PREPEND ${MATH_DIR})
list(TRANSFORM RENDERER_SRC PREPEND ${RENDERER_DIR})
list(TRANSFORM RENDERER_H PREPEND ${RENDERER_DIR})
list(TRANSFORM CLI_SRC PREPEND ${CLI_DIR})
list(TRANSFORM CLI_H PREPEND ${CLI_DIR})

set(TARGET_H
    ${UTILS_H}
    ${MATH_H}
    ${RENDERER_H}
    ${CLI_H}
    )

set(TARGET_SRC
    ${UTILS_SRC}
    ${MATH_SRC}
    ${RENDERER_SRC}
    ${CLI_SRC}
    )
