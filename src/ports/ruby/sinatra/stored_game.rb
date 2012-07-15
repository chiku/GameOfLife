module GameOfLife
  module Sinatra
    class StoredGame
      class << self
        attr_reader :response

        def put game
          @game = game
        end

        def tick!
          @game.tick!
        end

        def response
          @game.to_json
        end
      end
    end
  end
end
