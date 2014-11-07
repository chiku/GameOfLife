require_relative '../ext/game_of_life'

module GameOfLife
  class Parser
    def initialize pattern
      @pattern = pattern
    end

    def parse
      return parse_as_life_1_06 @pattern.lines if @pattern.start_with? '#LIFE 1.06'
      return parse_as_life_1_05 @pattern.lines if @pattern.start_with? '#LIFE 1.05'
      []
    end

    private

    def parse_as_life_1_06 lines
      integer = /^[-+]?[0-9]+$/

      lines.
        reject {|line| line.start_with? '#'}.
        map {|line| line.split(" ")}.
        select {|x, y| x =~ integer && y =~ integer }.
        map {|x, y| [x.to_i, y.to_i]}
    end

    def parse_as_life_1_05 lines
      result = []
      x_max = 0

      lines.
        reject {|line| line.start_with? '#'}.
        each_with_index do |line, yi|
          line.chars.
            each_with_index do |char, xi|
              result << [xi, yi] if char == "*"
              x_max = xi if xi > x_max
          end
        end

      x_correction = x_max / 2
      y_correction = lines.count / 2 - 1
      result.map {|x, y| [(x - x_correction), - (y - y_correction)]}
    end
  end
end
