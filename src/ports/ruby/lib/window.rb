require 'gtk2'
require_relative 'mark_cell'

module GameOfLife
  class Window < Gtk::Window
    def initialize game
      super()

      @game = game
      @time_interval = 250

      set_title "Conway's Game of Life"
      signal_connect 'destroy' do
        Gtk.main_quit
      end

      init_ui
      set_default_size width, height
      fullscreen

      show_all
    end

    def height
      Gdk::Screen.default.height
    end

    def width
      Gdk::Screen.default.width
    end

    def container
      @container ||= Gtk::DrawingArea.new
    end

    def mark_cell
      @context ||= container.window.create_cairo_context
      @mark_cell ||= MarkCell.new context: @context, width: width, height: height
    end

    def init_ui
      container.signal_connect 'expose_event' do
        on_expose_draw
      end

      add container
    end

    def on_expose_draw
      Gtk.timeout_add @time_interval do
        render
      end
    end

    def render
      @game.each_previous_cell { |x, y| mark_cell.dead_at x, y }
      @game.each_cell { |x, y| mark_cell.alive_at x, y }
      @game.tick!
    end
  end
end
