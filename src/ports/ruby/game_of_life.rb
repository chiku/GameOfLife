require_relative 'lib/game'
require_relative 'gtk/runner'
require_relative 'fox/runner'

game = GameOfLife::Game.new
                       .add_cell_at(0, 0)
                       .add_cell_at(1, -1)
                       .add_cell_at(2, -1)
                       .add_cell_at(3, -1)
                       .add_cell_at(-3, -1)
                       .add_cell_at(-2, -1)
                       .add_cell_at(-2, 1)

gtk = GameOfLife::Gtk::Runner

runner = Hash.new gtk
runner['gtk'] = gtk

runner[ARGV.first].start game
