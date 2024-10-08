inc += include_directories('.', 'api', 'libs')

headers = [ 
  'libs/https/https.hpp',
  'libs/https/helpers/inspector.hpp',

  'libs/hack/concepts/concepts.hpp',
  'libs/hack/logger/logger.hpp',
  'libs/hack/utils/color.hpp',
  'libs/hack/iterators/associative_ostream_iterator.hpp',
  'libs/hack/iterators/sequence_ostream_iterator.hpp',

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
