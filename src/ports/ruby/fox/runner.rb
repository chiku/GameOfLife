require 'fox16'
require_relative 'window'

module GameOfLife
  module Fox
    class Runner
      class << self
        def start game
          Window.init do
            start game
          end
        end
      end
    end
  end
end
