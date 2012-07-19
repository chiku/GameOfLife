import os

install_prefix = '/opt/gol'
install_prefix_bin = install_prefix + '/bin'
install_prefix_lib = install_prefix + '/lib'
install_prefix_include = install_prefix + '/include'

# Core C library and interfaces
core = Environment(CPPPATH = ['src/include'])

core_files = ['src/coordinates.c', 'src/cell.c', 'src/world.c', 'src/rules.c', 'src/game.c']
main_files = ['src/main_loop/main_loop.c', 'src/main_loop/validate_arguments.c', 'src/main_loop/handle_signals.c', 'src/main_loop/main.c']

if 'CC' in os.environ:
  core.Replace(CC = os.environ['CC'])

core.Append(CCFLAGS = '-O3 -Wall')

gol_lib_static = core.StaticLibrary('build/lib/gol', Split(core_files))
gol_lib_dynamic = core.SharedLibrary('build/lib/gol', Split(core_files))
core.StaticLibrary('build/lib/gol_m', Split(main_files))

test_gol = core.Program('build/bin/test-gol', Split(['tests/test_suite.c', 'build/lib/libgol.a']), LIBS=['check'])
golc = core.Program('build/bin/golc', ['src/interfaces/curses.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['ncurses'])
golX = core.Program('build/bin/golX', ['src/interfaces/Xlib.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['X11'])

source_header = './src/include/game_of_life.h'
target_header = install_prefix + '/include/game_of_life.h'
include_header = core.Command(target_header, source_header,
	[
	Copy("$TARGET", "$SOURCE"),
	Chmod("$TARGET", 0664),
	])

core.Alias('install', core.Install(install_prefix_bin, test_gol))
core.Alias('install', core.Install(install_prefix_bin, golc))
core.Alias('install', core.Install(install_prefix_bin, golX))
core.Alias('install', core.Install(install_prefix_lib, gol_lib_static))
core.Alias('install', core.Install(install_prefix_lib, gol_lib_dynamic))
core.Alias('install', core.Install(include_header))


# C++ port and interfaces
port_cpp = Environment(CPPPATH = Split([install_prefix_include, 'src/ports/C++/include']))

port_cpp_test_files = [port_cpp.Object('src/ports/C++/game.cpp'), 'tests/ports/C++/game_test.cpp', 'tests/ports/C++/igloo_extensions.cpp']
port_cpp_fltk_files = [port_cpp.Object('src/ports/C++/game.cpp'), 'src/ports/C++/interfaces/fltk/runner.cpp', 'src/ports/C++/interfaces/fltk/main.cpp']

if 'CXX' in os.environ:
  port_cpp.Replace(CXX = os.environ['CXX'])

port_cpp.Append(CXXFLAGS = '--std=c++11 -O3 -Wall')

port_cpp_test_gol = port_cpp.Program('build/bin/test-gol-cxx', Split(port_cpp_test_files), LIBS=[gol_lib_static, 'fltk'])
golFLTK = port_cpp.Program('build/bin/golFLTK', Split(port_cpp_fltk_files), LIBS=[gol_lib_static, 'fltk'])

port_cpp.Alias('install', port_cpp.Install(install_prefix_bin, port_cpp_test_gol))
port_cpp.Alias('install', port_cpp.Install(install_prefix_bin, golFLTK))


# Ruby port and interfaces
port_ruby = Environment(ENV = {'PATH' : os.environ['PATH']})
ruby_build = port_ruby.Command('ports', [], './extconf.rb --with-gol-dir=/opt/gol && make', chdir='src/ports/ruby/ext')
