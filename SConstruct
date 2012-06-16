env = Environment(CPPPATH = ['src'])
env.Append(CCFLAGS = '-O3 -Wall')

env.StaticLibrary('lib/gol', Split(['src/cell.c', 'src/rules.c', 'src/world.c']))
env.SharedLibrary('lib/gol', Split(['src/cell.c', 'src/rules.c', 'src/world.c']))
env.StaticLibrary('lib/gol_ev', Split(['src/main_loop/main_loop.c', 'src/main_loop/validate_arguments.c', 'src/main_loop/handle_signals.c', 'src/main_loop/main.c']))

env.Program('bin/test_gol', Split(['tests/test_suite.c', 'lib/libgol.a']), LIBS=['check'])

env.Program('bin/golc', ['src/interfaces/curses/graphics.c', 'lib/libgol_ev.a', 'lib/libgol.a'], LIBS=['ncurses'])
env.Program('bin/golX', ['src/interfaces/Xlib/graphics.c', 'lib/libgol_ev.a', 'lib/libgol.a'], LIBS=['X11'])
