require 'json'

require_relative '../ext/game_of_life'
require_relative 'cell'

module GameOfLife
  class Game
    alias_method :old_tick!, :tick!
    private :old_tick!

    def initialize(pattern = [])
      @cache_current = false
      @cache_previous = false
      pattern.each {|x, y| add_cell_at(x, y)}
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
      cells_to_remove.each { |cell| mark_cell.dead_at(cell.x, cell.y, cell.generation) }
      cells_to_add.each { |cell| mark_cell.alive_at(cell.x, cell.y, cell.generation) }
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
