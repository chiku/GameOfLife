#ifndef GOL_GAME_OF_LIFE_H
#define GOL_GAME_OF_LIFE_H

typedef struct Coordinates Coordinates;
typedef struct Cell Cell;
typedef struct World World;
typedef struct Game Game;


struct Coordinates
{
	long int x;
	long int y;
};

struct Cell
{
	Coordinates coordinates;
};

struct World
{
	long int cell_count;
	Cell *cells;
};

struct Game
{
	Coordinates *neighbour_locations;
	World *world;
};

static const int MAX_NEIGHBOURS = 8;


/* Coordinates Methods */
Coordinates Coordinates_New(long int x, long int y);

Coordinates Coordinates_Get(Coordinates coordinates);
int Coordinates_Match(Coordinates c1, Coordinates c2);
Coordinates Coordinates_Shifted_By(Coordinates self, Coordinates displacement);

void Coordinates_Dump(Coordinates self);
/* Coordinates Methods */


/* Cell Methods */
Cell Cell_New(long int x, long int y);
Cell Cell_New_From_Coordinates(Coordinates coordinates);

Coordinates Cell_Coordinates(Cell self);

int Cell_Is_At(Cell self, Coordinates coordinates);

void Cell_Dump(Cell self);
/* Cell Methods */


/* Rules Methods */
int Rule_Carry_Forward_Cell(int cell_alive, int neighbours);
/* Rules Methods */


/* World Methods */
World* World_Allocate();
World* World_Initialize(World *allocated_world);

World* World_New();
void World_Destroy(World *self);

long int World_Cell_Count(const World *self);

void World_Add_Cell(World *self, Cell cell);
int World_Has_Cell_At(const World *self, Coordinates coordinates);
int World_Cell_Count_Around(const World *self, Coordinates coordinates, Coordinates *neighbour_locations, int location_size);
World* World_All_Neighbours_For_Set(const World *self, Coordinates *neighbour_locations, int location_size);

void World_At_Each_Cell(const World *self, void (*visitor)(Coordinates coordinates, void *), void *data);

void World_Dump(const World *self);
/* World Methods */


/* Game Methods */
Game* Game_Allocate();
Game* Game_Initialize(Game *allocated_game);

Game* Game_New();
void Game_Destroy(Game *self);

Game* Game_Create_From_File(const char file_name[]);

void Game_Add_Cell(Game *self, Cell cell);
int Game_Cell_Count_Around(const Game *self, Coordinates coordinates);
World* Game_Active_Zone(const Game *self);

Game* Game_Tick(Game *self);
void Game_At_Each_Cell(const Game *self, void (*visitor)(Coordinates coordinates, void*), void *data);

void Game_Dump(const Game *self);
/* Game Methods */


#endif /* GAME_OF_LIFE_H */
