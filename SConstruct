env = Environment(CPPPATH = ['src'])
env.Append(CCFLAGS = '-O3')

env.SharedLibrary('lib/game_of_life', Split(['src/cell.c', 'src/world.c']))
env.Program('bin/game_of_life_tests', Split(['src/cell.c', 'src/world.c', 'tests/test_suite.c']), LIBS=['check'])

