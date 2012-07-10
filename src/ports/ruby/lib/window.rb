require 'gtk2'

module GameOfLife
  class Window < Gtk::Window
    attr_reader :cell_size
    attr_reader :time_interval
    attr_reader :game

    def initialize(game)
      super()

      @game = game
      @cell_size = 5
      @time_interval = 250

      set_title("Conway's Game of Life")
      signal_connect('destroy') do
        Gtk.main_quit
      end

      init_ui
      set_default_size(width, height)
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

    def context
      @context ||= container.window.create_cairo_context
    end

    def init_ui
      container.signal_connect('expose_event') do
        on_expose_draw
      end

      add(container)
    end

    def on_expose_draw
      Gtk.timeout_add(time_interval) do
        render
      end
    end

    def mark_cell_alive_at(x, y)
      context.set_source_rgb(0.8, 0.2, 0.4)
      cell_draw(x, y)
    end

    def mark_cell_dead_at(x, y)
      context.set_source_rgb(0.9, 1, 0.8)
      cell_draw(x, y)
    end

    def cell_draw(x, y)
      x1 = x * cell_size + width / 2 - cell_size / 2
      y1 = y * cell_size + height / 2 - cell_size / 2
      context.rectangle(x1, y1, cell_size, cell_size)
      context.fill
    end

    def render
      game.each_previous_cell { |x, y| mark_cell_dead_at(x, y) }
      game.each_cell { |x, y| mark_cell_alive_at(x, y) }
      game.tick!
    end
  end
end
