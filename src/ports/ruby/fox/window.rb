require 'fox16'
require_relative 'mark_cell'

module GameOfLife
  module Fox
    class Window < ::Fox::FXMainWindow
      class << self
        def init &block
          ::Fox::FXApp.new do |app|
            @app = app
            instance_eval &block
          end
        end

        def start game
          Window.new @app, game
          @app.create
          @app.run
        end
      end

      def initialize app, game
        @app = app
        @game = game
        @time_interval = 100

        super @app, "Conway's Game of Life", width: width, height: height
        init_ui
      end

      def create
        super
        show ::Fox::PLACEMENT_SCREEN
      end

      def width
        1280
      end

      def height
        800
      end

      def init_ui
        init_canvas
        hook_events
      end

      def init_canvas
        @canvas = ::Fox::FXCanvas.new self, opts: ::Fox::LAYOUT_FILL_X | ::Fox::LAYOUT_FILL_Y
      end

      def mark_cell context
        MarkCell.new context: context, width: width, height: height
      end

      def hook_events
        @app.addTimeout 200 do
          ::Fox::FXDCWindow.new @canvas do |context|
            context.setForeground ::Fox::FXRGB(172, 172, 172)
            context.fillRectangle 0, 0, width, height
          end
        end

        @app.addTimeout @time_interval, repeat: true do
          ::Fox::FXDCWindow.new @canvas do |context|
            @game.render_generation_with mark_cell(context)
          end
        end
      end
    end
  end
end
