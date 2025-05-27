cmake_minimum_required (VERSION 3.10.0)
project (GameOfLife C CXX)

include (CheckCSourceCompiles)
include (CheckCXXSourceCompiles)
include (CheckIncludeFiles)
include (CheckIncludeFileCXX)

set(CMAKE_C_FLAGS "-Wall -Werror -fPIC")
set(CMAKE_CXX_FLAGS "-Wall -Werror")

include_directories ("${CMAKE_SOURCE_DIR}/src/lib/include")
add_library (gol src/lib/coordinates.c src/lib/cell.c src/lib/rules.c src/lib/world.c src/lib/game.c)

include_directories ("${CMAKE_SOURCE_DIR}/src/impl/C/include")
add_library (gol-loop src/impl/C/main_loop/handle_signals.c src/impl/C/main_loop/process_arguments.c src/impl/C/main_loop/main_loop.c src/impl/C/main_loop/main.c) 

add_executable (gol-test-c test/lib/test_suite.c)
target_link_libraries(gol-test-c gol)

add_executable (gol-c-curses src/impl/C/interfaces/curses.c)
target_link_libraries(gol-c-curses gol-loop gol curses)

add_executable (gol-c-xlib src/impl/C/interfaces/Xlib.c)
target_link_libraries(gol-c-xlib gol-loop gol X11)

add_executable (gol-c-xcb src/impl/C/interfaces/xcb.c)
target_link_libraries(gol-c-xcb gol-loop gol xcb)

include_directories ("${CMAKE_SOURCE_DIR}/src/impl/C++/include")
add_executable (gol-test-cxx src/impl/C++/game.cxx test/impl/C++/game_test.cxx)
target_link_libraries(gol-test-cxx gol)

add_executable (gol-cxx-fltk src/impl/C++/game.cxx src/impl/C++/interfaces/fltk/mark_cell.cxx src/impl/C++/interfaces/fltk/canvas.cxx src/impl/C++/interfaces/fltk/runner.cxx src/impl/C++/interfaces/fltk/window.cxx src/impl/C++/interfaces/fltk/main.cxx)
target_link_libraries(gol-cxx-fltk gol fltk)
