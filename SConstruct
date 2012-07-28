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
gol_curses = core.Program('build/bin/gol-curses', ['src/interfaces/curses.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['ncurses'])
gol_xlib = core.Program('build/bin/gol-xlib', ['src/interfaces/Xlib.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['X11'])
gol_xcb = core.Program('build/bin/gol-xcb', ['src/interfaces/xcb.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['xcb'])

source_header = './src/include/game_of_life.h'
target_header = install_prefix + '/include/game_of_life.h'
include_header = core.Command(target_header, source_header,
	[
	Copy("$TARGET", "$SOURCE"),
	Chmod("$TARGET", 0664),
	])

core.Alias('install', core.Install(install_prefix_bin, test_gol))
core.Alias('install', core.Install(install_prefix_bin, gol_curses))
core.Alias('install', core.Install(install_prefix_bin, gol_xlib))
core.Alias('install', core.Install(install_prefix_bin, gol_xcb))
core.Alias('install', core.Install(install_prefix_lib, gol_lib_static))
core.Alias('install', core.Install(install_prefix_lib, gol_lib_dynamic))
core.Alias('install', core.Install(include_header))


# C++ port and interfaces
port_cxx = Environment(CPPPATH = Split([install_prefix_include, 'ports/C++/src/include']))

port_cxx_test_files = [port_cxx.Object('ports/C++/src/game.cxx'), 'ports/C++/tests/game_test.cxx', 'ports/C++/tests/igloo_extensions.cxx']
port_cxx_fltk_files = [port_cxx.Object('ports/C++/src/game.cxx'), 'ports/C++/src/interfaces/fltk/mark_cell.cxx', 'ports/C++/src/interfaces/fltk/canvas.cxx', 'ports/C++/src/interfaces/fltk/window.cxx', 'ports/C++/src/interfaces/fltk/runner.cxx', 'ports/C++/src/interfaces/fltk/main.cxx']

if 'CXX' in os.environ:
  port_cxx.Replace(CXX = os.environ['CXX'])

port_cxx.Append(CXXFLAGS = '--std=c++11 -O3 -Wall')

port_cxx_test_gol = port_cxx.Program('build/bin/test-gol-cxx', Split(port_cxx_test_files), LIBS=[gol_lib_static])
gol_fltk = port_cxx.Program('build/bin/gol-fltk', Split(port_cxx_fltk_files), LIBS=[gol_lib_static, 'fltk'])

port_cxx.Alias('install', port_cxx.Install(install_prefix_bin, port_cxx_test_gol))
port_cxx.Alias('install', port_cxx.Install(install_prefix_bin, gol_fltk))


# Ruby port and interfaces
port_ruby = Environment(ENV = {'PATH' : os.environ['PATH']})
ruby_build = port_ruby.Command('ports', [], './extconf.rb --with-gol-dir=/opt/gol && make', chdir='ports/ruby/lib/ext')
