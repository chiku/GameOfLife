require 'minitest/autorun'
require 'minitest/spec'

require File.expand_path(File.join('..', '..', '..', 'src', 'ports', 'ruby', 'lib', 'game'))

module GameOfLife
  describe Game do
    describe "when empty" do
      let :empty_game do
        Game.new
      end

      it "is a game" do
        empty_game.instance_of?(Game).must_equal true
      end

      it "has a cell count of zero" do
        empty_game.cell_count.must_equal 0
      end
    end

    describe "after adding one cell" do
      let :game do
        Game.new.tap do |game|
          game.add_cell_at(1, 0)
        end
      end

      it "has cell count of one" do
        game.cell_count.must_equal 1
      end

      it "knows where the cell is present" do
        game.has_cell_at?(1, 0).must_equal true
        game.has_cell_at?(1, 1).must_equal false
      end
    end

    describe "after adding two cells" do
      let :game do
        Game.new.tap do |game|
          game.add_cell_at(1, 0).add_cell_at(0, 1)
        end
      end

      it "has cell count of two" do
        game.cell_count.must_equal 2
      end
    end

    describe "blinker" do
      let :blinker do
        Game.new.add_cell_at(-1, 0).add_cell_at(0, 0).add_cell_at(1, 0)
      end

      describe "after a tick" do
        before do
          blinker.tick!
        end

        it "has three cells" do
          blinker.cell_count.must_equal 3
        end

        [[0, -1], [0, 0], [0, 1]].each do |position|
          x, y = position.first, position.last
          it "has a cell at (#{x}, #{y})" do
            blinker.has_cell_at?(x, y).must_equal true
          end
        end
      end
    end

    it "is stressed" do
      blinker = Game.new.add_cell_at(-1, 0).add_cell_at(0, 0).add_cell_at(1, 0)
      1.upto(100) do |i|
        blinker.tick!
      end
    end

    it "can be visited at each cell of current generation" do
      pattern = Game.new.add_cell_at(-1, 0).add_cell_at(0, -1).add_cell_at(1, 0).add_cell_at(5, 5)
      xs, ys = [], []
      pattern.each_cell do |x, y|
        xs << x
        ys << y
      end
      xs.must_equal [-1, 0, 1, 5]
      ys.must_equal [ 0,-1, 0, 5]
    end

    it "can be visited at each cell of older generation" do
      pattern = Game.new.add_cell_at(-1, 0).add_cell_at(0, -1).add_cell_at(1, 0).add_cell_at(5, 5).tick!
      xs, ys = [], []
      pattern.each_previous_cell do |x, y|
        xs << x
        ys << y
      end
      xs.must_equal [-1, 0, 1, 5]
      ys.must_equal [ 0,-1, 0, 5]
    end
  end
end
