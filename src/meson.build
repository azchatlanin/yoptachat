inc += include_directories('.')

headers = [ 
  'api/inspector/funcs/htc.hpp',
  'api/executor/funcs/htc.hpp'
]

sources = [ ]

lib = library(
  meson.project_name(), 
  include_directories : inc,
  sources: [headers, sources],
  dependencies : deps,
  cpp_args: args
)

deps += declare_dependency(
  include_directories: inc, 
  link_with: lib, 
)
