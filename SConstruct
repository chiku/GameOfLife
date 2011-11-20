env = Environment(CPPPATH = ['src'])
env.Append(CCFLAGS = '-O3 -Wall')

env.StaticLibrary('lib/gol', Split(['src/cell.c', 'src/world.c']))
env.StaticLibrary('lib/gol_ev', Split(['src/event_loop/event_loop.c', 'src/event_loop/validate_arguments.c', 'src/event_loop/handle_signals.c']))

env.Program('bin/test_gol', Split(['tests/test_suite.c', 'lib/libgol.a']), LIBS=['check'])

env.Program('bin/golc', ['src/interfaces/curses/graphics.c', 'src/interfaces/curses/curses.c', 'src/event_loop/main.c', 'lib/libgol.a', 'lib/libgol_ev.a'], LIBS=['ncurses'])
env.Program('bin/golX', ['src/interfaces/Xlib/graphics.c', 'src/interfaces/Xlib/Xlib.c', 'src/event_loop/main.c', 'lib/libgol.a', 'lib/libgol_ev.a'], LIBS=['X11'])
env.Program('bin/golFLTK', ['src/interfaces/fltk/graphics.cxx', 'src/interfaces/fltk/fltk.cxx', 'lib/libgol.a', 'lib/libgol_ev.a'], LIBS=['fltk'])

