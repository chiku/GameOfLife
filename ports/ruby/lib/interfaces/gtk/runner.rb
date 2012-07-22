require_relative 'window'

module GameOfLife
  module Interfaces
    module Gtk
      class Runner
        class << self
          def start game
            Window.init
            Window.new game
            Window.main
          end
        end
      end
    end
  end
end
