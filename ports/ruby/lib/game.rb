require 'json'

require_relative 'ext/game_of_life'

module GameOfLife
  class Cell
    attr_reader :x, :y, :generation

    def == other
      return true if self.equal? other
      return false unless other.is_a? Cell
      self.x == other.x && self.y == other.y
    end

    def eql? other
      self == other
    end

    def hash
      (x * x) + (y * y)
    end

    def to_s
      "{x: #{x}, y: #{y}}"
    end

    def to_json(options = {})
      "{\"x\": #{x}, \"y\": #{y}}"
    end
  end

  class Game
    alias_method :old_tick!, :tick!
    private :old_tick!

    def initialize
      @cache_current = false
      @cache_previous = false
    end

    def tick!
      @cache_current = false
      @cache_previous = false
      old_tick!
    end

    def current_generation
      return @current_generation if @cache_current

      @cache_current = true
      @current_generation = []
      each_cell { |cell| @current_generation << cell }
      @current_generation
    end

    def previous_generation
      return @previous_generation if @cache_previous

      @cache_previous = true
      @previous_generation = []
      each_previous_cell { |cell| @previous_generation << cell }
      @previous_generation
    end

    def cells_to_remove
      previous_generation - current_generation
    end

    def cells_to_add
      current_generation - previous_generation
    end

    def render_generation_with mark_cell
      cells_to_remove.each { |cell| mark_cell.dead_at(cell.x, cell.y) }
      cells_to_add.each { |cell| mark_cell.alive_at(cell.x, cell.y) }
      tick!
    end

    def to_json(options = {})
      {
        world:
        {
          current: current_generation,
          previous: previous_generation
        }
      }.to_json
    end
  end
end
