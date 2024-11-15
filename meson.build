project(
  'today',
  'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=gnu++26'],
)

qt_lib = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Widgets'])

libtoday = subproject('libtoday')
today_dep = libtoday.get_variable('today_dep')

inc = include_directories('include')
src = files('src/main.cpp', 'src/mainwindow.cpp')
ui = qt_lib.compile_ui(sources: files('ui/mainwindow.ui'))
moc = qt_lib.compile_moc(
  headers: files('include/mainwindow.h'),
  dependencies: [qt6_dep, today_dep],
  include_directories: inc,
)

exe = executable(
  'today',
  src + moc + ui,
  include_directories: inc,
  dependencies: [qt6_dep, today_dep],
  install: true,
)

test('basic', exe)