require_relative '../ext/game_of_life'

module GameOfLife
  class Game
    def render_generation_with mark_cell
      each_previous_cell { |x, y| mark_cell.dead_at x, y }
      each_cell { |x, y| mark_cell.alive_at x, y }
      tick!
    end
  end
end
