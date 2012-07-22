#!/usr/bin/env ruby

require 'rbconfig'
require 'mkmf'

RbConfig::MAKEFILE_CONFIG['CC'] = ENV['CC'] if ENV['CC']

extension_name = 'game_of_life'
gol_lib = 'gol'
gol_header = 'game_of_life.h'

dir_config('gol', '/opt/local', '/opt/local')
raise "#{gol_header} not found!" unless have_header(gol_header)
raise "#{gol_lib} not found!" unless have_library(gol_lib, 'Game_Allocate')

create_header
create_makefile(extension_name)
