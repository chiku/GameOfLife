core_files = ['src/coordinates.c', 'src/cell.c', 'src/cell_collection.c', 'src/rules.c', 'src/game.c']
main_files = ['src/main_loop/main_loop.c', 'src/main_loop/validate_arguments.c', 'src/main_loop/handle_signals.c', 'src/main_loop/main.c']

env = Environment(CPPPATH = ['src'])
env.Replace(CC= 'clang')
env.Append(CCFLAGS = '-O3 -Wall')

env.StaticLibrary('lib/gol', Split(core_files))
env.SharedLibrary('lib/gol', Split(core_files))
env.StaticLibrary('lib/gol_ev', Split(main_files))

env.Program('bin/test_gol', Split(['tests/test_suite.c', 'lib/libgol.a']), LIBS=['check'])

env.Program('bin/golc', ['src/interfaces/curses/graphics.c', 'lib/libgol_ev.a', 'lib/libgol.a'], LIBS=['ncurses'])
env.Program('bin/golX', ['src/interfaces/Xlib/graphics.c', 'lib/libgol_ev.a', 'lib/libgol.a'], LIBS=['X11'])
