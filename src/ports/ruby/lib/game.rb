require_relative '../ext/game_of_life'

module GameOfLife
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
      each_cell { |x, y| @current_generation << [x, y] }
      @current_generation
    end

    def previous_generation
      return @previous_generation if @cache_previous

      @cache_previous = true
      @previous_generation = []
      each_previous_cell { |x, y| @previous_generation << [x, y] }
      @previous_generation
    end

    def cells_to_erase
      previous_generation - current_generation
    end

    def cells_to_keep
      current_generation - previous_generation
    end

    def render_generation_with mark_cell
      cells_to_erase.each { |x, y| mark_cell.dead_at x, y }
      cells_to_keep.each { |x, y| mark_cell.alive_at x, y }
      tick!
    end
  end
end
