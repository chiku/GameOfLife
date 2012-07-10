require 'gtk2'
require_relative 'game'
require_relative 'window'

module GameOfLife
  class GTK
    def run
      Gtk.init
      game = Gol::Game.new
                      .add_cell_at(0, 0)
                      .add_cell_at(1, -1)
                      .add_cell_at(2, -1)
                      .add_cell_at(3, -1)
                      .add_cell_at(-3, -1)
                      .add_cell_at(-2, -1)
                      .add_cell_at(-2, 1)
      Window.new(game)
      Gtk.main
    end
  end
end