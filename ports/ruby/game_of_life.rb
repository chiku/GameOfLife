#!/usr/bin/env ruby

require_relative 'lib/interfaces/interfaces'
require_relative 'lib/game'

game = GameOfLife::Game.new
                       .add_cell_at(0, 0)
                       .add_cell_at(1, -1)
                       .add_cell_at(2, -1)
                       .add_cell_at(3, -1)
                       .add_cell_at(-3, -1)
                       .add_cell_at(-2, -1)
                       .add_cell_at(-2, 1)

gtk = GameOfLife::Interfaces::Gtk::Runner
fox = GameOfLife::Interfaces::Fox::Runner
sinatra = GameOfLife::Interfaces::Sinatra::Runner

runner = Hash.new gtk
runner['gtk'] = gtk
runner['fox'] = fox
runner['sinatra'] = sinatra

runner[ARGV.first].start game
