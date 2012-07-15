require_relative 'server'

module GameOfLife
  module Sinatra
    class Runner
      class << self
        def start game
          Server.run! game
        end
      end
    end
  end
end
