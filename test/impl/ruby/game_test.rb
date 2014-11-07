require 'minitest/autorun'
require 'minitest/spec'

require 'json'

require File.expand_path(File.join('..', '..', '..', 'src', 'impl', 'ruby', 'lib', 'game', 'game'))

module GameOfLife
  describe Game do
    describe "when created with a pattern" do
      it "adds the passed contents as its cells" do
        game = Game.new([[1, 1], [-1, 2]])
        game.has_cell_at?(1, 1).must_equal true
        game.has_cell_at?(-1, 2).must_equal true
      end
    end

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
        game = Game.new.add_cell_at(-1, 0).add_cell_at(0, -1).add_cell_at(1, 0).add_cell_at(5, 5)
        xs, ys = [], []
        game.each_cell do |cell|
          xs << cell.x
          ys << cell.y
        end
        xs.must_equal [-1, 0, 1, 5]
        ys.must_equal [ 0,-1, 0, 5]
      end

      it "can be collected" do
        game = Game.new.add_cell_at(-1, 0).add_cell_at(0, -1).add_cell_at(1, 0)
        game.current_generation.must_equal [Cell.new(-1, 0), Cell.new(0, -1), Cell.new(1, 0)]
      end

      it "is not cached" do
        game = Game.new.add_cell_at(-1, 0).add_cell_at(-2, 0).add_cell_at(-3, 0).tick!
        game.current_generation.must_equal [Cell.new(-2, -1), Cell.new(-2, 0), Cell.new(-2, 1)]
      end
    end

    describe "previous generation cells" do
      it "can be visited" do
        game = Game.new.add_cell_at(-1, 0).add_cell_at(0, -1).add_cell_at(1, 0).add_cell_at(5, 5).tick!
        xs, ys = [], []
        game.each_previous_cell do |cell|
          xs << cell.x
          ys << cell.y
        end
        xs.must_equal [-1, 0, 1, 5]
        ys.must_equal [ 0,-1, 0, 5]
      end

      it "can be collected" do
        game = Game.new.add_cell_at(-1, 0).add_cell_at(0, -1).add_cell_at(1, 0).add_cell_at(5, 5).tick!
        game.previous_generation.must_equal [Cell.new(-1, 0), Cell.new(0, -1), Cell.new(1, 0), Cell.new(5, 5)]
      end

      it "is not cached" do
        game = Game.new.add_cell_at(-1, 0).add_cell_at(-2, 0).add_cell_at(-3, 0).tick!.tick!
        game.previous_generation.must_equal [Cell.new(-2, -1), Cell.new(-2, 0), Cell.new(-2, 1)]
      end
    end

    describe "cells to remove" do
      it "are the cells that exist in previous generation but not in current" do
        game = Game.new.add_cell_at(-1, 0).add_cell_at(0, 0).add_cell_at(1, 0)
        game.tick!
        game.cells_to_remove.must_equal [Cell.new(-1, 0), Cell.new(1, 0)]
      end

      it "don't include unchanged cell" do
        game = Game.new.add_cell_at(0, 0).add_cell_at(1, 0).add_cell_at(0, 1).add_cell_at(1, 1)
        game.tick!
        game.cells_to_remove.must_equal []
      end
    end

    describe "cells to add" do
      it "are the cells that exist in current generation but not in previous" do
        game = Game.new.add_cell_at(-1, 0).add_cell_at(0, 0).add_cell_at(1, 0)
        game.tick!
        game.cells_to_add.must_equal [Cell.new(0, -1), Cell.new(0, 1)]
      end

      it "don't include unchanged cell" do
        game = Game.new.add_cell_at(0, 0).add_cell_at(1, 0).add_cell_at(0, 1).add_cell_at(1, 1)
        game.tick!
        game.cells_to_add.must_equal []
      end
    end

    describe "on serialization to JSON" do
      let :deserialized do
        game = Game.new.add_cell_at(-1, 0).add_cell_at(0, 0).add_cell_at(1, 0)
        game.tick!
        json = game.to_json

        JSON.parse(json)['world']
      end

      it "produces a JSON string representation of the current generation" do
        current = deserialized['current']
        current.count.must_equal 3
        current.include?({"x" => 0, "y" => -1, "generation" => 1}).must_equal true
        current.include?({"x" => 0, "y" =>  0, "generation" => 2}).must_equal true
        current.include?({"x" => 0, "y" =>  1, "generation" => 1}).must_equal true
      end

      it "produces a JSON string representation of the previous generation" do
        previous = deserialized['previous']

        previous.count.must_equal 3
        previous.include?({"x" => -1, "y" => 0, "generation" => 1}).must_equal true
        previous.include?({"x" =>  0, "y" => 0, "generation" => 1}).must_equal true
        previous.include?({"x" =>  1, "y" => 0, "generation" => 1}).must_equal true
      end
    end
  end
end
