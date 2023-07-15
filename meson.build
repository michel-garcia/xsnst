project('xsnst', 'cpp', default_options: ['cpp_std=c++20'])
dependencies = [
  dependency('x11', required: true),
  dependency('xrandr', required: true),
]
sources = [
  'src/main.cpp',
  'src/Sunset.cpp'
]
executable('xsnst', sources, dependencies: dependencies, install: true)
