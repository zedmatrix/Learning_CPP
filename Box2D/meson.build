project('Box2D_Demo', 'cpp', version: '0.2.0',
    default_options: ['cpp_std=c++23'],
    meson_version: '>=1.6.0')

box2d_dep = dependency('box2d', required: true)
sdl2_dep = dependency('sdl2', required: true)
glew_dep = dependency('glew', required: true)

incdir = include_directories('bengine/')
srcdir = files(
    'main.cpp',
    'App.cpp',
    'IMainGame.cpp',
    'IMainWindow.cpp',
    'IScreenList.cpp',
    'bengine/ResourceManager.cpp',
    'bengine/GLSLProgram.cpp',
    'bengine/SpriteBatch.cpp',
    'bengine/TextureCache.cpp',
    'bengine/Camera.cpp',
    'bengine/Input.cpp',
    'bengine/Timing.cpp',
    'bengine/Error.cpp',
    'bengine/picopng.cpp',
    'bengine/IOManager.cpp',
    'Box2d.cpp')

executable('box2d_demo', srcdir,
    include_directories: incdir,
    dependencies: [box2d_dep, sdl2_dep, glew_dep],
    install: false,
)
