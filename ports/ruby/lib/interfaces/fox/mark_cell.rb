require 'fox16'

module GameOfLife
  module Interfaces
    module Fox
      class MarkCell
        SIZE = 4
        ALIVE_COLOUR = ::Fox::FXRGB(204, 51, 102)
        DEAD_COLOUR = ::Fox::FXRGB(172, 200, 172)

        attr_reader :context, :width, :height

        def initialize options
          @context = options[:context]
          @width = options[:width]
          @height = options[:height]
        end

        def alive_at x, y, generation
          draw_at x, y, ALIVE_COLOUR
        end

        def dead_at x, y, generation
          draw_at x, y, DEAD_COLOUR
        end

        def draw_at x, y, colour
          x1 = x * SIZE + width / 2 - SIZE / 2
          y1 = y * SIZE + height / 2 - SIZE / 2

          context.setForeground colour
          context.fillRectangle x1, y1, SIZE - 1, SIZE - 1
        end
      end
    end
  end
end
