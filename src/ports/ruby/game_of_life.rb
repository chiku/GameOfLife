require_relative 'gtk/runner'

runner = Hash.new(GameOfLife::Gtk::Runner)
runner['gtk'] = GameOfLife::Gtk::Runner

runner[ARGV.first].start
