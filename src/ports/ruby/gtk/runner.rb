require_relative '../lib/game'
require_relative 'window'

module GameOfLife
  module Gtk
    class Runner
      class << self
        def start
          game = Game.new
                     .add_cell_at(0, 0)
                     .add_cell_at(1, -1)
                     .add_cell_at(2, -1)
                     .add_cell_at(3, -1)
                     .add_cell_at(-3, -1)
                     .add_cell_at(-2, -1)
                     .add_cell_at(-2, 1)
          Window.init
          Window.new game
          Window.main
        end
      end
    end
  end
end
