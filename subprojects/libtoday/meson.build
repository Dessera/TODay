project(
  'today',
  'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=gnu++26'],
)

qt_lib = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Widgets'])

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_TODAY']

inc = include_directories('include')
src = files('src/todotask/model.cpp', 'src/todotask/todotask.cpp')
moc = qt_lib.compile_moc(
  headers: files('include/today/todotask/model.h'),
  dependencies: [qt6_dep],
  include_directories: inc,
)

shlib = shared_library(
  'today',
  src + moc,
  include_directories: inc,
  dependencies: [qt6_dep],
  install: true,
  cpp_args: lib_args,
  gnu_symbol_visibility: 'hidden',
)

# Make this library usable as a Meson subproject.
today_dep = declare_dependency(include_directories: inc, link_with: shlib)

# Make this library usable from the system's
# package manager.
install_subdir('include', install_dir: 'include', strip_directory: true)

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name: 'today',
  filebase: 'today',
  description: 'Today todo base library',
  subdirs: 'today',
  libraries: shlib,
  version: '0.1',
)