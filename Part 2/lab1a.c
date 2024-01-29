/*
 * lab1a.c
 *
 *  Created on: 28 Jan 2024
 *      Author: Vikas Prajapati
 */

/* include helper functions for game */
#include "lifegame.h"
#include <stdio.h>
/* add whatever other includes here */

/* number of generations to evolve the world */
#define NUM_GENERATIONS 50

/* functions to implement */

/* this function should set the state of all
   the cells in the next generation and call
   finalize_evolution() to update the current
   state of the world to the next generation */
void next_generation(void);

/* this function should return the state of the cell
   at (x,y) in the next generation, according to the
   rules of Conway's Game of Life (see handout) */
int get_next_state(int x, int y);

/* this function should calculate the number of alive
   neighbors of the cell at (x,y) */
int num_neighbors(int x, int y);

int main(void)
{
	int n;

	/* TODO: initialize the world */
	initialize_world();
	for (n = 0; n < NUM_GENERATIONS; n++)
		next_generation();
	// /* TODO: output final world state */

	output_world();
	return 0;
}

void next_generation(void)
{
	/* TODO: for every cell, set the state in the next
	   generation according to the Game of Life rules

	   Hint: use get_next_state(x,y) */
	int height = get_world_height();
	int width = get_world_width();
	int i, j;
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			set_cell_state(i, j, get_next_state(i, j));
		}
	}

	finalize_evolution(); /* called at end to finalize */
}

int get_next_state(int x, int y)
{
	/* TODO: for the specified cell, compute the state in
	   the next generation using the rules

	   Use num_neighbors(x,y) to compute the number of live
	   neighbors */
	int a = num_neighbors(x, y);
	//	int
	if (get_cell_state(x, y) == 1)
	{
		if (a == 2 || a == 3)
			return 1;
	}
	else
	{
		if (a == 3)
			return 1;
	}

	return 0;
}

int num_neighbors(int x, int y)
{
	/* TODO: for the specified cell, return the number of
	   neighbors that are ALIVE

	   Use get_cell_state(x,y) */
	int to = 0;
	if (get_cell_state(x - 1, y - 1) != 0)
		to = to + 1;
	if (get_cell_state(x - 1, y) != 0)
		to = to + 1;
	if (get_cell_state(x - 1, y + 1) != 0)
		to = to + 1;
	if (get_cell_state(x, y - 1) != 0)
		to = to + 1;
	if (get_cell_state(x, y + 1) != 0)
		to = to + 1;
	if (get_cell_state(x + 1, y - 1) != 0)
		to = to + 1;
	if (get_cell_state(x + 1, y) != 0)
		to = to + 1;
	if (get_cell_state(x + 1, y + 1) != 0)
		to = to + 1;

	return to;
}
