inc += include_directories('.', '../../libs')

headers = [ 
  # API
  'api/inspector/funcs/htc.hpp',
  'api/inspector/inspector.hpp',

  'api/executor/funcs/htc.hpp',
  'api/executor/executor.hpp',

  'api/utils/tracer.hpp',
  
  # LOGS_INGESTER
  'logs_ingester/inspector/funcs/htc.hpp',
  'logs_ingester/inspector/inspector.hpp',

  'logs_ingester/executor/funcs/htc.hpp',
  'logs_ingester/executor/executor.hpp',

  'logs_ingester/utils/tracer.hpp',

  'run.hpp'
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
