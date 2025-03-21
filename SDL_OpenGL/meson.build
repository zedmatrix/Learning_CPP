project('SDL2/OpenGL', 'cpp', version: '0.2.0',
    default_options: ['cpp_std=c++23'],
    meson_version: '>=1.6.0')

# Dependencies
sdldep = dependency('sdl2', version: '>=2.30.7')
glewdep = dependency('glew', version: '>=2.2.0')

# Option to choose library type: static or shared
lib_type = get_option('default_library')

incdir = include_directories('zengine/header/')

# Define Bengine source files
zengine_src = files(
    'zengine/source/Camera.cpp',
    'zengine/source/GLSLProgram.cpp',
    'zengine/source/Manager.cpp',
    'zengine/source/picopng.cpp',
    'zengine/source/Sprite.cpp',
    'zengine/source/Window.cpp')

# Build Zengine as a static library
zengine_lib = library('zengine', zengine_src,
    include_directories: incdir,
    dependencies: [sdldep, glewdep])

# Define main source files
main_src = files(
    'main.cpp',
    'MainGame.cpp')

# Build the executable and link it with Bengine
executable('opengl-test', main_src,
    include_directories: incdir,
    dependencies: [sdldep, glewdep],
    link_with: zengine_lib
)

# Install textures
install_data('Textures/block_grid.png', install_dir: meson.project_build_root() / 'Textures')
install_data('Textures/CharacterRight_Standing.png', install_dir: meson.project_build_root() / 'Textures')
install_data('Textures/myCharacter_standing.png', install_dir: meson.project_build_root() / 'Textures')

# Install shaders
install_data('Shaders/FragmentShader', install_dir: meson.project_build_root() / 'Shaders')
install_data('Shaders/VertexShader', install_dir: meson.project_build_root() / 'Shaders')

# Create directories for runtime assets
run_command(['mkdir', '-p', meson.project_build_root() / 'Textures'], check: true)
run_command(['cp', 'Textures/block_grid.png', meson.project_build_root() / 'Textures/block_grid.png'], check: true)
run_command(['cp', 'Textures/CharacterRight_Standing.png', meson.project_build_root() / 'Textures/CharacterRight_Standing.png'], check: true)
run_command(['cp', 'Textures/myCharacter_standing.png', meson.project_build_root() / 'Textures/myCharacter_standing.png'], check: true)

run_command(['mkdir', '-p', meson.project_build_root() / 'Shaders'], check: true)
run_command(['cp', 'Shaders/FragmentShader', meson.project_build_root() / 'Shaders/FragmentShader'], check: true)
run_command(['cp', 'Shaders/VertexShader', meson.project_build_root() / 'Shaders/VertexShader'], check: true)
