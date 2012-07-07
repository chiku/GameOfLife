import os

core_files = ['src/coordinates.c', 'src/cell.c', 'src/world.c', 'src/rules.c', 'src/game.c']
main_files = ['src/main_loop/main_loop.c', 'src/main_loop/validate_arguments.c', 'src/main_loop/handle_signals.c', 'src/main_loop/main.c']

env = Environment(CPPPATH = ['src/include'])

if 'CC' in os.environ:
  env.Replace(CC = os.environ['CC'])

env.Append(CCFLAGS = '-O3 -Wall')

gol_lib_static = env.StaticLibrary('build/lib/gol', Split(core_files))
gol_lib_dynamic = env.SharedLibrary('build/lib/gol', Split(core_files))
env.StaticLibrary('build/lib/gol_m', Split(main_files))

test_gol = env.Program('build/bin/test_gol', Split(['tests/test_suite.c', 'build/lib/libgol.a']), LIBS=['check'])
golc = env.Program('build/bin/golc', ['src/interfaces/curses.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['ncurses'])
golX = env.Program('build/bin/golX', ['src/interfaces/Xlib.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['X11'])

source_header = "./src/include/game_of_life.h"
target_header = "/opt/local/include/game_of_life.h"
env.Command(target_header, source_header, [Copy("$TARGET", "$SOURCE")])

env.Alias("install", env.Install("/opt/local/bin", test_gol))
env.Alias("install", env.Install("/opt/local/bin", golc))
env.Alias("install", env.Install("/opt/local/bin", golX))
env.Alias("install", env.Install("/opt/local/lib", gol_lib_static))
env.Alias("install", env.Install("/opt/local/lib", gol_lib_dynamic))
env.Alias("install", target_header)
