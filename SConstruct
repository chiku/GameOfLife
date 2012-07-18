import os

# Core C library and interfaces
core_files = ['src/coordinates.c', 'src/cell.c', 'src/world.c', 'src/rules.c', 'src/game.c']
main_files = ['src/main_loop/main_loop.c', 'src/main_loop/validate_arguments.c', 'src/main_loop/handle_signals.c', 'src/main_loop/main.c']

core = Environment(CPPPATH = ['src/include'])

if 'CC' in os.environ:
  core.Replace(CC = os.environ['CC'])

core.Append(CCFLAGS = '-O3 -Wall')

gol_lib_static = core.StaticLibrary('build/lib/gol', Split(core_files))
gol_lib_dynamic = core.SharedLibrary('build/lib/gol', Split(core_files))
core.StaticLibrary('build/lib/gol_m', Split(main_files))

test_gol = core.Program('build/bin/test_gol', Split(['tests/test_suite.c', 'build/lib/libgol.a']), LIBS=['check'])
golc = core.Program('build/bin/golc', ['src/interfaces/curses.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['ncurses'])
golX = core.Program('build/bin/golX', ['src/interfaces/Xlib.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['X11'])

source_header = "./src/include/game_of_life.h"
target_header = "/opt/local/include/game_of_life.h"
core.Command(target_header, source_header,
	[
	Copy("$TARGET", "$SOURCE"),
	Chmod("$TARGET", 0664),
	])

core.Alias("install", core.Install("/opt/local/bin", test_gol))
core.Alias("install", core.Install("/opt/local/bin", golc))
core.Alias("install", core.Install("/opt/local/bin", golX))
core.Alias("install", core.Install("/opt/local/lib", gol_lib_static))
core.Alias("install", core.Install("/opt/local/lib", gol_lib_dynamic))
core.Alias("install", target_header)

# C++ port and interfaces
port_cpp_files = ['src/ports/C++/ext/game.cpp', 'tests/ports/C++/game_test.cpp', 'tests/ports/C++/igloo_extensions.cpp']

port_cpp = Environment(CPPPATH = Split(['/opt/local/include', 'src/ports/C++/ext/include']))

if 'CXX' in os.environ:
  port_cpp.Replace(CXX = os.environ['CXX'])

port_cpp.Append(CXXFLAGS = '-O3 -Wall')

port_cpp_test_gol = port_cpp.Program('build/ports/C++/bin/test_gol', Split(port_cpp_files), LIBS=gol_lib_static)

port_cpp.Alias("ports", port_cpp_test_gol)


# Ruby port and interfaces
port_ruby = Environment(ENV = {'PATH' : os.environ['PATH']})
ruby_build = port_ruby.Command("ports", [], "./extconf.rb --with-gol-dir=/opt/local && make", chdir="src/ports/ruby/ext")
