project('iphito', 'cpp',
  default_options: ['cpp_std=c++20']
  )

dependencies = []
compile_args = []
link_args = ['-framework', 'OpenGL']

dependencies += dependency('spdlog')
dependencies += dependency('catch2-with-main')
dependencies += dependency('docopt')
dependencies += dependency('glfw3')
dependencies += dependency('glew')
dependencies += dependency('eigen3')

main_sources = [
  'src/main/cli/ASTNode.cpp',
  'src/main/cli/ASTNode.h',
  'src/main/cli/Parser.cpp',
  'src/main/cli/Parser.h',
  'src/main/math/Bezier.cpp',
  'src/main/math/Bezier.h',
  'src/main/math/Curve.h',
  'src/main/math/Hermite3.cpp',
  'src/main/math/Hermite3.h',
  'src/main/math/Hermite5.cpp',
  'src/main/math/Hermite5.h',
  'src/main/math/Line.cpp',
  'src/main/math/Line.h',
  'src/main/renderer/AABB.cpp',
  'src/main/renderer/AABB.h',
  'src/main/renderer/Arrow2D.cpp',
  'src/main/renderer/Arrow2D.h',
  'src/main/renderer/Axes2D.cpp',
  'src/main/renderer/Axes2D.h',
  'src/main/renderer/Bezier2D.cpp',
  'src/main/renderer/Bezier2D.h',
  'src/main/renderer/Camera.cpp',
  'src/main/renderer/Camera.h',
  'src/main/renderer/Canvas.cpp',
  'src/main/renderer/Canvas.h',
  'src/main/renderer/Curve2D.cpp',
  'src/main/renderer/Curve2D.h',
  'src/main/renderer/Curve2DFactory.cpp',
  'src/main/renderer/Curve2DFactory.h',
  'src/main/renderer/Grid.cpp',
  'src/main/renderer/Grid.h',
  'src/main/renderer/Hermite32D.cpp',
  'src/main/renderer/Hermite32D.h',
  'src/main/renderer/Hermite52D.cpp',
  'src/main/renderer/Hermite52D.h',
  'src/main/renderer/Layer.cpp',
  'src/main/renderer/Layer.h',
  'src/main/renderer/Line2D.cpp',
  'src/main/renderer/Line2D.h',
  'src/main/renderer/Point2D.cpp',
  'src/main/renderer/Point2D.h',
  'src/main/renderer/Shader.cpp',
  'src/main/renderer/Shader.h',
  'src/main/renderer/Window.cpp',
  'src/main/renderer/Window.h',
  'src/main/utils/Logger.cpp',
  'src/main/utils/Logger.h',
  'src/main/utils/Utils.cpp',
  'src/main/utils/Utils.h',
]


executable('iphito',
  [main_sources, 'src/main/main.cpp'],
  cpp_args: compile_args,
  link_args: link_args,
  dependencies : dependencies,
)

test_sources = [
  'tests/BezierTest.cpp',
  'tests/CanvasTest.cpp',
  'tests/Hermite3Test.cpp',
  'tests/Hermite5Test.cpp',
  'tests/LayerTest.cpp',
  'tests/ParserTest.cpp',
]

executable('tests',
  [test_sources, main_sources],
  cpp_args: compile_args,
  link_args: link_args,
  dependencies : dependencies,
)

