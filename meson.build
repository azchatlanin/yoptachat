project(
  meson.current_source_dir().split('/').get(-1), 
  'cpp', 
  version : run_command('git', 'rev-parse',  '--short', 'HEAD', check: false).stdout().strip(),
  default_options : [
    'warning_level=1',
    'optimization=3',
    'cpp_std=c++20',
])

add_project_arguments (
  '-Wpedantic',
  '-Wno-shadow', 
  '-Wno-unused-but-set-variable',
  '-Wno-comment',
  '-Wno-unused-parameter',
  '-Wno-unused-value',
  '-Wno-missing-field-initializers',
  '-Wno-narrowing',
  '-Wno-deprecated-enum-enum-conversion',
  '-Wno-volatile',
  '-Wno-format-security',
  '-Wno-switch',
  '-Wno-ignored-attributes',
  '-Wno-unused-variable',
  '-Wno-deprecated-enum-enum-conversion',
  language: 'cpp'
)

args = []
inc = []
deps = [
  dependency('uuid'),
  dependency('libpqxx'),
  subproject('nlohmann_json').get_variable('nlohmann_json_dep'),
  subproject('jwt-cpp').get_variable('jwt_dep'),
  subproject('httplib').get_variable('cpp_httplib_dep'),
]

subdir('libs')
subdir('src')
subdir('bin')
