#!/usr/bin/env ruby

require_relative 'lib/interfaces/interfaces'
require_relative 'lib/game'

file_name = ARGV[0]

unless file_name
  puts "Please give a file name as the first argument"
  exit 20
end

begin
  raw_lines = File.read(file_name)
rescue => ex
  puts "Error when opening '#{file_name}': #{ex.message}"
  exit 21
end

lines = GameOfLife::Parser.new(raw_lines).parse
game = GameOfLife::Game.new(lines)

gtk = GameOfLife::Interfaces::Gtk::Runner
fox = GameOfLife::Interfaces::Fox::Runner
sinatra = GameOfLife::Interfaces::Sinatra::Runner

runner = Hash.new gtk
runner['gtk'] = gtk
runner['fox'] = fox
runner['sinatra'] = sinatra

runner[ARGV[1]].start game
