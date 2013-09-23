require_relative 'crake'

options = {
  cc:       ENV['CC']       || 'gcc',
  cxx:      ENV['CXX']      || 'g++',
  cflags:   ENV['CFLAGS']   || '-O3 -Wall -Wextra',
  cxxflags: ENV['CXXFLAGS'] || '--std=c++11 -O3 -Wall -Wextra',
  ar:       ENV['AR']       || 'ar'
}

source_dir = "src"
tests_dir = "tests"
build_dir = "build"
include_directories = "src/include"

c_source_files = Dir.glob("#{source_dir}/**/*").select {|file| file.end_with? ".c"}
c_test_files = Dir.glob("#{tests_dir}/**/*").select {|file| file.end_with? "_suite.c"}

(c_source_files + c_test_files).each do |source_file|
  build_file = File.join(build_dir, source_file).sub(".c", ".o")

  task build_file => source_file do
    Crake::Track.new(include_directories, ENV).compile(source_file, build_file)
  end

  task "clean:#{build_file}" do
    puts build_file
    FileUtils.rm_f build_file
  end
end

c_core_files = ['src/coordinates.c', 'src/cell.c', 'src/world.c', 'src/rules.c', 'src/game.c']
c_main_files = ['src/main_loop/main_loop.c', 'src/main_loop/process_arguments.c', 'src/main_loop/handle_signals.c', 'src/main_loop/main.c']

c_gol_dependencies = c_core_files.map {|file| File.join build_dir, file.sub(".c", ".o") }
c_gol_shared_dependencies = c_core_files.map {|file| File.join build_dir, file.sub(".c", ".so") }
c_main_dependencies = c_main_files.map {|file| File.join build_dir, file.sub(".c", ".o") }

c_core_files.each do |source_file|
  build_file = File.join(build_dir, source_file).sub(".c", ".so")

  task build_file => source_file do
    Crake::Track.new(include_directories, ENV).and(cflags: "-fPIC").compile(source_file, build_file)
  end

  task "clean:#{build_file}" do
    puts build_file
    FileUtils.rm_f build_file
  end
end

libgol_static_file = "build/lib/libgol.a"
desc "Build #{libgol_static_file}"
task libgol_static_file => c_gol_dependencies do
  FileUtils.mkdir_p File.dirname libgol_static_file
  command = "#{options[:ar]} rc #{libgol_static_file} #{c_gol_dependencies.join(' ')}"
  Crake::Command.new.execute(command)
end

task "clean:#{libgol_static_file}" do
  puts libgol_static_file
  FileUtils.rm_f libgol_static_file
end

libgol_m_static_file = "build/lib/libgol_m.a"
desc "Build #{libgol_m_static_file}"
task libgol_m_static_file => c_main_dependencies do
  FileUtils.mkdir_p File.dirname libgol_m_static_file
  command = "#{options[:ar]} rc #{libgol_m_static_file} #{c_main_dependencies.join(' ')}"
  Crake::Command.new.execute(command)
end

task "clean:#{libgol_m_static_file}" do
  puts libgol_m_static_file
  FileUtils.rm_f libgol_m_static_file
end

libgol_dynamic_file = "build/lib/libgol.so"
desc "Build #{libgol_dynamic_file}"
task libgol_dynamic_file => c_gol_shared_dependencies do
  FileUtils.mkdir_p File.dirname libgol_dynamic_file
  command = "#{options[:cc]} -o #{libgol_dynamic_file} -shared #{c_gol_shared_dependencies.join(' ')}"
  Crake::Command.new.execute(command)
end

task "clean:#{libgol_dynamic_file}" do
  puts libgol_dynamic_file
  FileUtils.rm_f libgol_dynamic_file
end

gol_test_binary = "build/bin/test-gol"
test_suite = "build/tests/test_suite.o"
task gol_test_binary => [test_suite, libgol_static_file] do
  FileUtils.mkdir_p File.dirname gol_test_binary
  command = "#{options[:cc]} -o #{gol_test_binary} #{test_suite} #{libgol_static_file} -lcheck"
  Crake::Command.new.execute(command)
end

task "clean:#{gol_test_binary}" do
  puts gol_test_binary
  FileUtils.rm_f gol_test_binary
end

gol_curses_binary = "build/bin/gol-curses"
curses_interface = "build/src/interfaces/curses.o"
task gol_curses_binary => [curses_interface, libgol_m_static_file, libgol_static_file] do
  FileUtils.mkdir_p File.dirname gol_curses_binary
  command = "#{options[:cc]} -o #{gol_curses_binary} #{curses_interface} #{libgol_m_static_file} #{libgol_static_file} -lncurses"
  Crake::Command.new.execute(command)
end

task "clean:#{gol_curses_binary}" do
  puts gol_curses_binary
  FileUtils.rm_f gol_curses_binary
end

gol_xlib_binary = "build/bin/gol-xlib"
xlib_interface = "build/src/interfaces/Xlib.o"
task gol_xlib_binary => [xlib_interface, libgol_m_static_file, libgol_static_file] do
  FileUtils.mkdir_p File.dirname gol_xlib_binary
  command = "#{options[:cc]} -o #{gol_xlib_binary} #{xlib_interface} #{libgol_m_static_file} #{libgol_static_file} -lX11"
  Crake::Command.new.execute(command)
end

task "clean:#{gol_xlib_binary}" do
  puts gol_xlib_binary
  FileUtils.rm_f gol_xlib_binary
end

gol_xcb_binary = "build/bin/gol-xcb"
xcb_interface = "build/src/interfaces/xcb.o"
task gol_xcb_binary => [xcb_interface, libgol_m_static_file, libgol_static_file] do
  FileUtils.mkdir_p File.dirname gol_xcb_binary
  command = "#{options[:cc]} -o #{gol_xcb_binary} #{xcb_interface} #{libgol_m_static_file} #{libgol_static_file} -lxcb"
  Crake::Command.new.execute(command)
end

task "clean:#{gol_xcb_binary}" do
  puts gol_xcb_binary
  FileUtils.rm_f gol_xcb_binary
end

desc "Build all C libraries"
task "c:libraries" => [libgol_static_file, libgol_m_static_file, libgol_dynamic_file]

desc "Build all C binaries"
task "c:binaries" => [gol_test_binary, gol_curses_binary, gol_xlib_binary, gol_xcb_binary]


cpp_source_dir = "ports/C++/src"
cpp_tests_dir = "ports/C++/tests"
cpp_build_dir = "build"
cpp_include_directories = "-Iports/C++/src/include -I/opt/gol/include"

cpp_source_files = Dir.glob("#{cpp_source_dir}/**/*").select {|file| file.end_with? ".cxx"}
cpp_test_files = Dir.glob("#{cpp_tests_dir}/**/*").select {|file| file.end_with? ".cxx"}

(cpp_source_files + cpp_test_files).each do |source_file|
  build_file = File.join(build_dir, source_file).sub(".cxx", ".o")

  desc "a"
  task build_file => source_file do
    FileUtils.mkdir_p File.dirname build_file
    command = "#{options[:cxx]} -o #{build_file} -c #{options[:cxxflags]} #{cpp_include_directories} #{source_file}"
    Crake::Command.new.execute(command)
  end

  task "clean:#{build_file}" do
    puts build_file
    FileUtils.rm_f build_file
  end
end

gol_test_cpp_binary = "build/bin/test-gol-cxx"
gol_test_cpp_binary_deps = ["build/ports/C++/src/game.o", "build/ports/C++/tests/game_test.o", "build/ports/C++/tests/igloo_extensions.o", libgol_static_file]
task gol_test_cpp_binary => gol_test_cpp_binary_deps do
  FileUtils.mkdir_p File.dirname gol_test_cpp_binary
  command = "#{options[:cxx]} -o #{gol_test_cpp_binary} #{gol_test_cpp_binary_deps.join(" ")}"
  Crake::Command.new.execute(command)
end

task "clean:#{gol_test_cpp_binary}" do
  puts gol_test_cpp_binary
  FileUtils.rm_f gol_test_cpp_binary
end

gol_fltk_binary = "build/bin/gol-fltk"
gol_fltk_binary_deps = ['build/ports/C++/src/game.o', 'build/ports/C++/src/interfaces/fltk/mark_cell.o', 'build/ports/C++/src/interfaces/fltk/canvas.o', 'build/ports/C++/src/interfaces/fltk/window.o', 'build/ports/C++/src/interfaces/fltk/runner.o', 'build/ports/C++/src/interfaces/fltk/main.o', libgol_static_file]
task gol_fltk_binary => gol_fltk_binary_deps do
  FileUtils.mkdir_p File.dirname gol_fltk_binary
  command = "#{options[:cxx]} -o #{gol_fltk_binary} #{gol_fltk_binary_deps.join(" ")} -lfltk"
  Crake::Command.new.execute(command)
end

task "clean:#{gol_fltk_binary}" do
  puts gol_fltk_binary
  FileUtils.rm_f gol_fltk_binary
end

desc "Build all C++ binaries"
task "c++:binaries" => [gol_test_cpp_binary, gol_fltk_binary]

desc "Build all Ruby binaries"
task "ruby:binaries" => [libgol_static_file] do
  Dir.chdir "ports/ruby/lib/ext"
  sh "./extconf.rb --with-gol-dir=/opt/gol"
  sh "make"
end

desc "Compile everything"
task :compile => ["c:libraries", "c:binaries", "c++:binaries", "ruby:binaries"]

desc "Install"
task :install => [:compile]

desc "Run all tests without compile"
task "tests:without:compile" do
  sh "#{gol_test_binary}"
  sh "#{gol_test_cpp_binary}"
  Dir.chdir "ports/ruby/tests" do
    sh "rake test"
  end
end

desc "Run all tests"
task "tests" => [:compile, gol_test_binary, gol_test_cpp_binary, "ruby:binaries", "tests:without:compile"]

desc "Install without compile"
task "install:without:compile" do
  puts "Copying over files to /opt/gol"
  FileUtils.mkdir_p "/opt/gol/include"
  FileUtils.cp_r "build/lib", "/opt/gol"
  FileUtils.cp_r "build/bin", "/opt/gol"
  FileUtils.cp_r "src/include/game_of_life.h", "/opt/gol/include"
end

desc "Install"
task :install => [:compile, "install:without:compile"]

desc "Compile, install and run tests"
task :default => [:compile, :install, :tests]
