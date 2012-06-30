#ifndef GOL_GAME_OF_LIFE_H
#define GOL_GAME_OF_LIFE_H

typedef struct Coordinates Coordinates;
typedef struct Game Game;
extern struct World World;

struct Coordinates
{
	long int x;
	long int y;
};

struct Game
{
	struct Coordinates *neighbour_locations;
	struct World *world;
};

extern void Game_Destroy(Game *self);

extern Game* Game_Create_From_File(const char file_name[]);

extern Game* Game_Tick(Game *self);
extern void Game_At_Each_Cell(const Game *self, void (*visitor)(struct Coordinates coordinates, void*), void *data);

#endif
