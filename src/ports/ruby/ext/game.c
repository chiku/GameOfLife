#include <ruby.h>
#include <game_of_life.h>

static VALUE rb_gol;
static VALUE rb_game;

static VALUE
rb_game_allocate(VALUE klass)
{
	Game *game = Game_New();
	return Data_Wrap_Struct(klass, 0, 0, game);
}

static VALUE
rb_game_cell_count(VALUE self)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	return LONG2FIX(Game_Cell_Count(game));
}

static VALUE
rb_game_has_cell_at(VALUE self, VALUE x, VALUE y)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	return Game_Has_Cell_At(game, FIX2LONG(x), FIX2LONG(y)) ? Qtrue : Qfalse;
}

static VALUE
rb_game_add_cell_at(VALUE self, VALUE x, VALUE y)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	Game_Add_Cell_At(game, FIX2LONG(x), FIX2LONG(y));
	return self;
}

static VALUE
rb_game_tick(VALUE self)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	Game_Tick(game);
	self = Data_Wrap_Struct(rb_game, 0, 0, game);
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
rb_game_yield_at_each_cell(VALUE self)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	Game_At_Each_Cell(game, yield_visitor, NULL);
	return self;
}

static VALUE
rb_game_yield_at_each_previous_cell(VALUE self)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	Game_At_Each_Old_Cell(game, yield_visitor, NULL);
	return self;
}

void Init_game_of_life()
{
	rb_gol = rb_define_module("Gol");
	rb_game = rb_define_class_under(rb_gol, "Game", rb_cObject);

	rb_define_alloc_func(rb_game, rb_game_allocate);
	rb_define_method(rb_game, "cell_count", rb_game_cell_count, 0);
	rb_define_method(rb_game, "has_cell_at?", rb_game_has_cell_at, 2);
	rb_define_method(rb_game, "add_cell_at", rb_game_add_cell_at, 2);
	rb_define_method(rb_game, "tick!", rb_game_tick, 0);
	rb_define_method(rb_game, "each_cell", rb_game_yield_at_each_cell, 0);
	rb_define_method(rb_game, "each_previous_cell", rb_game_yield_at_each_previous_cell, 0);
}
