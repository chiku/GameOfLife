require_relative '../ext/game_of_life'

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
      "(#{x}, #{y}) <#{generation}>"
    end

    def to_json(options = {})
      "{\"x\": #{x}, \"y\": #{y}, \"generation\": #{generation}}"
    end
  end
end
