require 'minitest/autorun'
require 'minitest/spec'

require File.expand_path(File.join('..', '..', '..', 'src', 'impl', 'ruby', 'lib', 'game', 'cell'))

module GameOfLife
  describe Cell do
    describe "when created with two arguments" do
      let :cell do
        Cell.new 10, 20
      end

      it "has an x-coordinate" do
        expect(cell.x).must_equal 10
      end

      it "has a y-coordinate" do
        expect(cell.y).must_equal 20
      end

      it "has a default generation" do
        expect(cell.generation).must_equal 1
      end
    end

    describe "when created with three arguments" do
      let :cell do
        Cell.new 10, 20, 30
      end

      it "has an x-coordinate" do
        expect(cell.x).must_equal 10
      end

      it "has a y-coordinate" do
        expect(cell.y).must_equal 20
      end

      it "has a generation" do
        expect(cell.generation).must_equal 30
      end
    end

    it "equals another cell with same x, y and generation" do
      expect(Cell.new(10, 20, 30)).must_equal Cell.new(10, 20, 30)
    end

    it "equals another cell with same x and y but different generation" do
      expect(Cell.new(10, 20, 30)).must_equal Cell.new(10, 20, 3)
    end

    it "doesn't equal another cell with different x" do
      expect(Cell.new(10, 20, 30)).wont_equal Cell.new(-10, 20, 30)
    end

    it "doesn't equal another cell with different y" do
      expect(Cell.new(10, 20, 30)).wont_equal Cell.new(-10, -20, 30)
    end

    it "equals itself" do
      cell = Cell.new(10, 20, 30)
      expect(cell).must_equal cell
    end

    it "doesn't equals nil" do
      expect(Cell.new(10, 20, 30)).wont_equal nil
    end

    it "doesn't equals a struct" do
      expect(Cell.new(10, 20, 30)).wont_equal Struct.new(:x, :y, :generation).new(10, 20, 30)
    end

    it "has same hash code when equal" do
      expect(Cell.new(10, 20, 30).hash).must_equal Cell.new(10, 20, 3).hash
    end
  end
end
