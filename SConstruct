env = Environment(CPPPATH = ['src'])
env.Append(CCFLAGS = '-O3 -Wall')

env.SharedLibrary('lib/gol', Split(['src/cell.c', 'src/world.c', 'src/utils.c']))
env.Program('bin/game_of_life_tests', Split(['lib/libgol.so', 'tests/test_suite.c']), LIBS=['check'])

env.Program('bin/golc', ['src/interfaces/curses/curses.c', 'lib/libgol.so'], LIBS=['ncurses'])
env.Program('bin/golX', ['src/interfaces/Xlib/graphics.c', 'src/interfaces/Xlib/Xlib.c', 'lib/libgol.so'], LIBS=['X11'])

