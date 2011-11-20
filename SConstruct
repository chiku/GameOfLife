env = Environment(CPPPATH = ['src'])
env.Append(CCFLAGS = '-O3 -Wall')

env.StaticLibrary('lib/gol', Split(['src/cell.c', 'src/world.c', 'src/utils.c']))
env.Program('bin/test_gol', Split(['tests/test_suite.c', 'lib/libgol.a']), LIBS=['check'])

env.Program('bin/golc', ['src/interfaces/curses/curses.c', 'lib/libgol.a'], LIBS=['ncurses'])
env.Program('bin/golX', ['src/interfaces/Xlib/graphics.c', 'src/interfaces/Xlib/Xlib.c', 'lib/libgol.a'], LIBS=['X11'])
env.Program('bin/golFLTK', ['src/interfaces/fltk/graphics.cxx', 'src/interfaces/fltk/fltk.cxx', 'lib/libgol.a'], LIBS=['fltk'])

