require_relative 'server'

module GameOfLife
  module Interfaces
    module Sinatra
      class Runner
        class << self
          def start game
            StoredGame.put game
            Server.run!
          end
        end
      end
    end
  end
end
