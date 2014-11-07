project (GameOfLife C CXX)
cmake_minimum_required (VERSION 2.8.7)

include (CheckCSourceCompiles)
include (CheckCXXSourceCompiles)
include (CheckIncludeFiles)
include (CheckIncludeFileCXX)

check_include_files	(check.h HAVE_CHECK_H)

set(CMAKE_C_FLAGS "-Wall -Werror -fPIC")
set(CMAKE_CXX_FLAGS "-Wall -Werror")

include_directories ("${CMAKE_SOURCE_DIR}/src/lib/include")
add_library (gol src/lib/coordinates.c src/lib/cell.c src/lib/rules.c src/lib/world.c src/lib/game.c)

include_directories ("${CMAKE_SOURCE_DIR}/src/ports/C/include")
add_library (gol-loop src/ports/C/main_loop/handle_signals.c src/ports/C/main_loop/process_arguments.c src/ports/C/main_loop/main_loop.c src/ports/C/main_loop/main.c) 

add_executable (gol-test-c test/lib/test_suite.c)
target_link_libraries(gol-test-c gol check)

add_executable (gol-c-curses src/ports/C/interfaces/curses.c)
target_link_libraries(gol-c-curses gol-loop gol curses)

add_executable (gol-c-xlib src/ports/C/interfaces/Xlib.c)
target_link_libraries(gol-c-xlib gol-loop gol X11)

add_executable (gol-c-xcb src/ports/C/interfaces/xcb.c)
target_link_libraries(gol-c-xcb gol-loop gol xcb)

include_directories ("${CMAKE_SOURCE_DIR}/src/ports/C++/include")
add_executable (gol-test-cxx src/ports/C++/game.cxx test/ports/C++/game_test.cxx)
target_link_libraries(gol-test-cxx gol boost_unit_test_framework)

add_executable (gol-cxx-fltk src/ports/C++/game.cxx src/ports/C++/interfaces/fltk/mark_cell.cxx src/ports/C++/interfaces/fltk/canvas.cxx src/ports/C++/interfaces/fltk/runner.cxx src/ports/C++/interfaces/fltk/window.cxx src/ports/C++/interfaces/fltk/main.cxx)
target_link_libraries(gol-cxx-fltk gol fltk)
