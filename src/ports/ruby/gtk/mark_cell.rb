module GameOfLife
  module Gtk
    class MarkCell
      SIZE = 4
      ALIVE_COLOUR = [0.8, 0.2, 0.4]
      DEAD_COLOUR = [0.9, 1, 0.8]

      attr_reader :context, :width, :height

      def initialize options
        @context = options[:context]
        @width = options[:width]
        @height = options[:height]
      end

      def alive_at x, y
        draw_at x, y, ALIVE_COLOUR
      end

      def dead_at x, y
        draw_at x, y, DEAD_COLOUR
      end

      def draw_at x, y, colour
        x1 = x * SIZE + width / 2 - SIZE / 2
        y1 = y * SIZE + height / 2 - SIZE / 2

        context.set_source_rgb *colour
        context.rectangle x1, y1, SIZE - 1, SIZE - 1
        context.fill
      end
    end
  end
end
