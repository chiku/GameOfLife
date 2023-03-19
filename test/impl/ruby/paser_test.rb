require 'minitest/autorun'
require 'minitest/spec'

require File.expand_path(File.join('..', '..', '..', 'src', 'impl', 'ruby', 'lib', 'game', 'parser'))

module GameOfLife
  describe Parser do
    describe "when reading a LIFE 1.06 format" do
      it "reads in x and y coordinates" do
        pattern = <<-PATTERN
#LIFE 1.06
1 0
-1 1
1 -2
        PATTERN
        expect(Parser.new(pattern).parse).must_equal [[1, 0], [-1, 1], [1, -2]]
      end

      it "ignores spaces at the extremes" do
        pattern = <<-PATTERN
#LIFE 1.06
  4 3 
  -1 -2
3 4 
PATTERN
        expect(Parser.new(pattern).parse).must_equal [[4, 3], [-1,-2], [3, 4]]
      end

      it "ignores separations made using double spaces" do
        pattern = <<-PATTERN
#LIFE 1.06
2 3
 -4  4
1 2
PATTERN
        expect(Parser.new(pattern).parse).must_equal [[2, 3], [-4,4], [1, 2]]
      end

      it "ignores malformed lines" do
        pattern = <<-PATTERN
#LIFE 1.06
2 
4 bat
man 2
PATTERN
        expect(Parser.new(pattern).parse).must_equal []
      end
    end

    describe "when reading a LIFE 1.05 format" do
      it "captures *'s as live cells with centering" do
        pattern = <<-PATTERN
#LIFE 1.05
***
*..
.*.
PATTERN
        expect(Parser.new(pattern).parse).must_equal [[-1, 1], [0, 1], [1, 1], [-1, 0], [0, -1]]
      end

      it "centers x's using maximum width" do
        pattern = <<-PATTERN
#LIFE 1.05
**...
**.
..*
PATTERN
        expect(Parser.new(pattern).parse).must_equal [[-2, 1], [-1, 1], [-2, 0], [-1, 0], [0, -1]]
      end
    end

    it "is an empty array when invalid file format" do
      expect(Parser.new("").parse).must_equal []
    end
  end
end
