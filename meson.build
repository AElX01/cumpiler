project('cumpiler', 'c',
  default_options : ['warning_level=2', 'c_std=gnu11']
)

# Compiler and linker flags
cflags = [
  '-O3',
  '-flto',
  '-DNDEBUG',
  '-w',
  '-Wpedantic',
  '-Wconversion',
  '-Wshadow',
  '-Wformat=2',
  '-fstack-protector-strong',
  '-D_FORTIFY_SOURCE=3',
  '-pie',
  '-static'
]

# Linker flags (some are passed via link_args)
link_args = [
  '-Wl,-z,relro,-z,now',
  '-Wl,--strip-all',
]

# Source files
src = [
  'thirdparty/tiny-regex-c/re.c',
  'utils.c',
  'parser.c',
  'lexer.c',
  'cumpiler.c',
]

executable('cumpiler', src,
  c_args: cflags,
  link_args: link_args,
  install: false,
)
