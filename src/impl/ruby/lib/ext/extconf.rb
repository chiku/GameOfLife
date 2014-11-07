#!/usr/bin/env ruby

require 'rbconfig'
require 'mkmf'

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

path_to_library = File.expand_path("../../../../../build")
path_to_headers = File.expand_path("../../../../lib/include")

extension_name = 'game_of_life'
gol_lib = 'gol'
gol_header = 'game_of_life.h'

dir_config('gol', path_to_headers, path_to_library)
have_header(gol_header) or raise "#{gol_header} not found!"
have_library(gol_lib, 'Game_Allocate') or raise "#{gol_lib} not found!"

create_header
create_makefile(extension_name)
