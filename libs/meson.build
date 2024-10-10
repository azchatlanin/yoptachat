inc += include_directories('.')

headers = [ 
  'https/https.hpp',
  'https/helpers/inspector.hpp',

  'hack/concepts/concepts.hpp',
  'hack/logger/logger.hpp',
  'hack/utils/color.hpp',
  'hack/iterators/associative_ostream_iterator.hpp',
  'hack/iterators/sequence_ostream_iterator.hpp',
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
