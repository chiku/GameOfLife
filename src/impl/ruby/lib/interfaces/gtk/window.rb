require 'gtk3'
require_relative 'mark_cell'

module GameOfLife
  module Interfaces
    module Gtk
      class Window < ::Gtk::Window
        class << self
          def init
          end

          def main
            ::Gtk.main
          end
        end

        def initialize game
          super()

          @game = game
          @time_interval = 250

          set_title "Conway's Game of Life"
          signal_connect 'destroy' do
            ::Gtk.main_quit
          end

          init_ui
          set_default_size width, height
          maximize

          show_all
        end

        def height
          ::Gdk::Screen.default.height
        end

        def width
          ::Gdk::Screen.default.width
        end

        def container
          @container ||= ::Gtk::DrawingArea.new
        end

        def context
          container.window.create_cairo_context
        end

        def mark_cell context
          MarkCell.new context: context, width: width, height: height
        end

        def init_ui
          container.signal_connect 'draw' do |_, ctx|
            on_draw ctx
          end

          add container

          ::GLib::Timeout.add @time_interval do
            queue_draw
            true
          end
        end

        def on_draw context
          @game.render_generation_with mark_cell(context)
        end
      end
    end
  end
end
