import os

core_files = ['src/coordinates.c', 'src/cell.c', 'src/world.c', 'src/rules.c', 'src/game.c']
main_files = ['src/main_loop/main_loop.c', 'src/main_loop/validate_arguments.c', 'src/main_loop/handle_signals.c', 'src/main_loop/main.c']

env = Environment(CPPPATH = ['src/include'])

if 'CC' in os.environ:
  env.Replace(CC = os.environ['CC'])

env.Append(CCFLAGS = '-O3 -Wall')

env.StaticLibrary('build/lib/gol', Split(core_files))
env.SharedLibrary('build/lib/gol', Split(core_files))
env.StaticLibrary('build/lib/gol_m', Split(main_files))

env.Program('build/bin/test_gol', Split(['tests/test_suite.c', 'build/lib/libgol.a']), LIBS=['check'])

env.Program('build/bin/golc', ['src/interfaces/curses.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['ncurses'])
env.Program('build/bin/golX', ['src/interfaces/Xlib.c', 'build/lib/libgol_m.a', 'build/lib/libgol.a'], LIBS=['X11'])
