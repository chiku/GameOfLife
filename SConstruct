env = Environment(CPPPATH = ['src'])
env.Append(CCFLAGS = '-O3')

env.SharedLibrary('lib/gol', Split(['src/cell.c', 'src/world.c']))
env.Program('bin/game_of_life_tests', Split(['lib/libgol.so', 'tests/test_suite.c']), LIBS=['check'])

env.Program('bin/golc', ['src/curses.c', 'lib/libgol.so'], LIBS=['ncurses'])

