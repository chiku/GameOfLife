module GameOfLife
  module Interfaces
    module Sinatra
      class StoredGame
        class << self
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
end
