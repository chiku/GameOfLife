#!/usr/bin/env ruby

file_name, runner_kind = ARGV[0], ARGV[1]

unless file_name
  puts "Please give a file name as the first argument"
  exit 2
end

begin
  raw_lines = File.read(file_name)
rescue => ex
  puts "Error when opening '#{file_name}': #{ex.message}"
  exit 1
end

require_relative 'lib/interfaces/interfaces'
require_relative 'lib/game'

lines = GameOfLife::Parser.new(raw_lines).parse
game = GameOfLife::Game.new(lines)

gtk = GameOfLife::Interfaces::Gtk::Runner
fox = GameOfLife::Interfaces::Fox::Runner
sinatra = GameOfLife::Interfaces::Sinatra::Runner

runner = Hash.new gtk
runner['gtk'] = gtk
runner['fox'] = fox
runner['sinatra'] = sinatra

runner[runner_kind].start game
