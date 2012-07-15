require 'minitest/autorun'
require 'minitest/spec'

require 'json'

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

    describe "current generation cells" do
      it "can be visited" do
        pattern = Game.new.add_cell_at(-1, 0).add_cell_at(0, -1).add_cell_at(1, 0).add_cell_at(5, 5)
        xs, ys = [], []
        pattern.each_cell do |x, y|
          xs << x
          ys << y
        end
        xs.must_equal [-1, 0, 1, 5]
        ys.must_equal [ 0,-1, 0, 5]
      end

      it "can be collected" do
        pattern = Game.new.add_cell_at(-1, 0).add_cell_at(0, -1).add_cell_at(1, 0)
        pattern.current_generation.must_equal [[-1, 0], [0, -1], [1, 0]]
      end

      it "is not cached" do
        pattern = Game.new.add_cell_at(-1, 0).add_cell_at(-2, 0).add_cell_at(-3, 0).tick!
        pattern.current_generation.must_equal [[-2, -1], [-2, 0], [-2, 1]]
      end
    end

    describe "previous generation cells" do
      it "can be visited" do
        pattern = Game.new.add_cell_at(-1, 0).add_cell_at(0, -1).add_cell_at(1, 0).add_cell_at(5, 5).tick!
        xs, ys = [], []
        pattern.each_previous_cell do |x, y|
          xs << x
          ys << y
        end
        xs.must_equal [-1, 0, 1, 5]
        ys.must_equal [ 0,-1, 0, 5]
      end

      it "can be collected" do
        pattern = Game.new.add_cell_at(-1, 0).add_cell_at(0, -1).add_cell_at(1, 0).add_cell_at(5, 5).tick!
        pattern.previous_generation.must_equal [[-1, 0], [0, -1], [1, 0], [5, 5]]
      end

      it "is not cached" do
        pattern = Game.new.add_cell_at(-1, 0).add_cell_at(-2, 0).add_cell_at(-3, 0).tick!.tick!
        pattern.previous_generation.must_equal [[-2, -1], [-2, 0], [-2, 1]]
      end
    end

    describe "cells to remove" do
      it "are the cells that exist in previous generation but not in current" do
        game = Game.new.add_cell_at(-1, 0).add_cell_at(0, 0).add_cell_at(1, 0)
        game.tick!
        game.cells_to_remove.must_equal [[-1, 0], [1, 0]]
      end
    end

    describe "cells to add" do
      it "are the cells that exist in current generation but not in previous" do
        game = Game.new.add_cell_at(-1, 0).add_cell_at(0, 0).add_cell_at(1, 0)
        game.tick!
        game.cells_to_add.must_equal [[0, -1], [0, 1]]
      end
    end

    describe "on serialization to JSON" do
      it "produces a JSON string representation of the current generation" do
        pattern = Game.new.add_cell_at(-1, 0).add_cell_at(-2, 0).add_cell_at(-3, 0)
        json = pattern.to_json

        deserialized = JSON.parse(json)['world']
        deserialized.count.must_equal 3
        deserialized.include?([-1, 0]).must_equal true
        deserialized.include?([-2, 0]).must_equal true
        deserialized.include?([-3, 0]).must_equal true
      end
    end
  end
end
