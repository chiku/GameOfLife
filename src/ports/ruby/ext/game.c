#include <ruby.h>
#include <game_of_life.h>

static VALUE gol_gol;
static VALUE gol_game;

static VALUE
gol_game_allocate(VALUE klass)
{
	Game *game = Game_New();
	return Data_Wrap_Struct(klass, 0, 0, game);
}

static VALUE
gol_game_cell_count(VALUE self)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	return LONG2FIX(Game_Cell_Count(game));
}

static VALUE
gol_game_has_cell_at(VALUE self, VALUE x, VALUE y)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	return Game_Has_Cell_At(game, FIX2LONG(x), FIX2LONG(y)) ? Qtrue : Qfalse;
}

static VALUE
gol_game_add_cell_at(VALUE self, VALUE x, VALUE y)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	Game_Add_Cell_At(game, FIX2LONG(x), FIX2LONG(y));
	return self;
}

static VALUE
gol_game_tick(VALUE self)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	Game_Tick(game);
	self = Data_Wrap_Struct(gol_game, 0, 0, game);
	return self;
}

static void
yield_visitor(Coordinates coordinates, void *data)
{
	VALUE ary = rb_ary_new();
	rb_ary_push(ary, LONG2FIX(coordinates.x));
	rb_ary_push(ary, LONG2FIX(coordinates.y));
	rb_yield(ary);
}

static VALUE
gol_game_yield_at_each_cell(VALUE self)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	Game_At_Each_Cell(game, yield_visitor, NULL);
	return self;
}

static VALUE
gol_game_yield_at_each_previous_cell(VALUE self)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	Game_At_Each_Old_Cell(game, yield_visitor, NULL);
	return self;
}

void Init_game_of_life()
{
	gol_gol = rb_define_module("GameOfLife");
	gol_game = rb_define_class_under(gol_gol, "Game", rb_cObject);

	rb_define_alloc_func(gol_game, gol_game_allocate);
	rb_define_method(gol_game, "cell_count", gol_game_cell_count, 0);
	rb_define_method(gol_game, "has_cell_at?", gol_game_has_cell_at, 2);
	rb_define_method(gol_game, "add_cell_at", gol_game_add_cell_at, 2);
	rb_define_method(gol_game, "tick!", gol_game_tick, 0);
	rb_define_method(gol_game, "each_cell", gol_game_yield_at_each_cell, 0);
	rb_define_method(gol_game, "each_previous_cell", gol_game_yield_at_each_previous_cell, 0);
}
