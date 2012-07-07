#include <ruby.h>
#include <game_of_life.h>

static VALUE rb_gol;
static VALUE rb_game;

static VALUE
c_game_allocate(VALUE klass)
{
	Game *game = Game_New();
	return Data_Wrap_Struct(klass, 0, 0, game);
}

static VALUE
c_game_cell_count(VALUE self)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	return LONG2FIX(Game_Cell_Count(game));
}

static VALUE
c_game_has_cell_at(VALUE self, VALUE x, VALUE y)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	return Game_Has_Cell_At(game, FIX2LONG(x), FIX2LONG(y)) ? Qtrue : Qfalse;
}

static VALUE
c_game_add_cell_at(VALUE self, VALUE x, VALUE y)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	Game_Add_Cell_At(game, FIX2LONG(x), FIX2LONG(y));
	return self;
}

static VALUE
c_game_tick(VALUE self)
{
	Game *game;
	Data_Get_Struct(self, Game, game);
	Game_Tick(game);
	self = Data_Wrap_Struct(rb_game, 0, 0, game);
	return self;
}

void Init_game_of_life()
{
	rb_gol = rb_define_module("Gol");
	rb_game = rb_define_class_under(rb_gol, "Game", rb_cObject);

	rb_define_alloc_func(rb_game, c_game_allocate);
	rb_define_method(rb_game, "cell_count", c_game_cell_count, 0);
	rb_define_method(rb_game, "has_cell_at?", c_game_has_cell_at, 2);
	rb_define_method(rb_game, "add_cell_at", c_game_add_cell_at, 2);
	rb_define_method(rb_game, "tick!", c_game_tick, 0);
}
