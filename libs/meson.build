inc += include_directories('.')

headers = [ 
  'https/https.hpp',
  'https/helpers/execute.hpp',
  'https/helpers/function_manager.hpp',
  'https/helpers/inspector.hpp',
  'https/helpers/verification.hpp',

  'hack/concepts/concepts.hpp',
  'hack/exception/exception.hpp',
  'hack/iterators/associative_ostream_iterator.hpp',
  'hack/iterators/sequence_ostream_iterator.hpp',
  'hack/logger/logger.hpp',
  'hack/security/uuid.hpp',
  'hack/string/string_concat_helper.hpp',
  'hack/transaction/transaction.hpp',
  'hack/tracer/tracer.hpp',

  'hack/utils/color.hpp',
  'hack/utils/json_compare.hpp',
  'hack/utils/json_converter.hpp',
  'hack/utils/using.hpp'
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
