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
    )

set(RENDERER_H
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
    )

list(TRANSFORM UTILS_SRC PREPEND ${UTILS_DIR})
list(TRANSFORM UTILS_H PREPEND ${UTILS_DIR})
list(TRANSFORM MATH_SRC PREPEND ${MATH_DIR})
list(TRANSFORM MATH_H PREPEND ${MATH_DIR})
list(TRANSFORM RENDERER_SRC PREPEND ${RENDERER_DIR})
list(TRANSFORM RENDERER_H PREPEND ${RENDERER_DIR})

set(TARGET_H
    ${UTILS_H}
    ${MATH_H}
    ${RENDERER_H}
    )

set(TARGET_SRC
    ${UTILS_SRC}
    ${MATH_SRC}
    ${RENDERER_SRC}
    )
