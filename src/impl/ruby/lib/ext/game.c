#include <ruby.h>
#include <game_of_life.h>

static VALUE gol_gol;
static VALUE gol_game;
static VALUE gol_cell;

static void gol_game_free(void *ptr) {
	Game_Destroy(ptr);
}

static const rb_data_type_t gol_game_data_type = {
	"GameOfLife::Game",
	{0, gol_game_free, 0,},
	0, 0, RUBY_TYPED_FREE_IMMEDIATELY,
};

static VALUE
gol_cell_initialize(int argc, VALUE* argv, VALUE self)
{
	VALUE generation;

	if (argc < 2 || argc > 3) {
		rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 2..3)", argc);
	}

	generation = (argc == 3) ? argv[2] : INT2NUM(1);

	rb_iv_set(self, "@x", argv[0]);
	rb_iv_set(self, "@y", argv[1]);
	rb_iv_set(self, "@generation", generation);

	return self;
}

static VALUE
gol_game_allocate(VALUE klass)
{
	Game *game = Game_New();
	return TypedData_Wrap_Struct(klass, &gol_game_data_type, game);
}

static VALUE
gol_game_cell_count(VALUE self)
{
	Game *game;
	TypedData_Get_Struct(self, Game, &gol_game_data_type, game);
	return LONG2FIX(Game_Cell_Count(game));
}

static VALUE
gol_game_has_cell_at(VALUE self, VALUE x, VALUE y)
{
	Game *game;
	TypedData_Get_Struct(self, Game, &gol_game_data_type, game);
	return Game_Has_Cell_At(game, FIX2LONG(x), FIX2LONG(y)) ? Qtrue : Qfalse;
}

static VALUE
gol_game_add_cell_at(VALUE self, VALUE x, VALUE y)
{
	Game *game;
	TypedData_Get_Struct(self, Game, &gol_game_data_type, game);
	Game_Add_Cell_At(game, FIX2LONG(x), FIX2LONG(y));
	return self;
}

static VALUE
gol_game_tick(VALUE self)
{
	Game *game;
	TypedData_Get_Struct(self, Game, &gol_game_data_type, game);
	Game_Tick(game);
	return self;
}

static void
yield_visitor(Cell cell, void *data)
{
	VALUE args[3];

	args[0] = LONG2FIX(cell.coordinates.x);
	args[1] = LONG2FIX(cell.coordinates.y);
	args[2] = LONG2FIX(cell.generation);

	rb_yield(rb_class_new_instance(3, args, gol_cell));
}

static VALUE
gol_game_yield_at_each_cell(VALUE self)
{
	Game *game;
	TypedData_Get_Struct(self, Game, &gol_game_data_type, game);
	Game_At_Each_Cell(game, yield_visitor, NULL);
	return self;
}

static VALUE
gol_game_yield_at_each_previous_cell(VALUE self)
{
	Game *game;
	TypedData_Get_Struct(self, Game, &gol_game_data_type, game);
	Game_At_Each_Old_Cell(game, yield_visitor, NULL);
	return self;
}

static VALUE
gol_game_dump(VALUE self)
{
	Game *game;
	TypedData_Get_Struct(self, Game, &gol_game_data_type, game);
	Game_Dump(game);
	return self;
}

void Init_game_of_life(void)
{
	gol_gol = rb_define_module("GameOfLife");
	gol_game = rb_define_class_under(gol_gol, "Game", rb_cObject);
	gol_cell = rb_define_class_under(gol_gol, "Cell", rb_cObject);
	rb_define_method(gol_cell, "initialize", gol_cell_initialize, -1);

	rb_define_alloc_func(gol_game, gol_game_allocate);
	rb_define_method(gol_game, "cell_count", gol_game_cell_count, 0);
	rb_define_method(gol_game, "has_cell_at?", gol_game_has_cell_at, 2);
	rb_define_method(gol_game, "add_cell_at", gol_game_add_cell_at, 2);
	rb_define_method(gol_game, "tick!", gol_game_tick, 0);
	rb_define_method(gol_game, "each_cell", gol_game_yield_at_each_cell, 0);
	rb_define_method(gol_game, "each_previous_cell", gol_game_yield_at_each_previous_cell, 0);
	rb_define_method(gol_game, "dump", gol_game_dump, 0);
}
