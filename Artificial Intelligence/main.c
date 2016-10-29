#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


/*  Macros  */
#define BUFFERSIZE (1000)

#define MAZE_ENTRANCE 'I'
#define MAZE_EXIT     'O'
#define MAZE_WALL     'T'
#define MAZE_PATH     ' '
#define MAZE_TRAIL    'X'

#define MOVE_LEFT  (0)
#define MOVE_UP    (1)
#define MOVE_RIGHT (2)
#define MOVE_DOWN  (3)

#define MAZE_NOWAY      (0)
#define MAZE_FOUNDEXIT  (1)
#define MAZE_NOEXIT    (-1)




struct maze {
	char ** map;
	int startx, starty;
	int numrows;
	int initdir;
};

struct pos {
	int x, y, dir;
};






int look(struct maze * maze, struct pos pos) {
	int i, n;

	switch ( pos.dir ) {
		case MOVE_UP:
			pos.y -= 1;
			break;

		case MOVE_DOWN:
			pos.y += 1;
			break;

		case MOVE_LEFT:
			pos.x -= 1;
			break;

		case MOVE_RIGHT:
			pos.x += 1;
			break;

		default:
			break;
	}




	if ( pos.y < 0 || pos.y >= maze->numrows )
		return MAZE_NOWAY;
	else if ( pos.x < 0 || pos.x >= strlen(maze->map[pos.y]) )
		return MAZE_NOWAY;
	else if ( maze->map[pos.y][pos.x] == MAZE_WALL )
		return MAZE_NOWAY;
	else if ( maze->map[pos.y][pos.x] == MAZE_EXIT )
		return MAZE_FOUNDEXIT;
	else if ( maze->map[pos.y][pos.x] == MAZE_ENTRANCE )
		return MAZE_NOEXIT;




	pos.dir -= 1;
	if ( pos.dir < 0 )
		pos.dir += 4;

	for ( i = 0; i < 3; ++i ) {
		maze->map[pos.y][pos.x] = MAZE_TRAIL;          

		n = look(maze, pos);
		if ( n ) {
			if ( n == MAZE_NOEXIT )
				maze->map[pos.y][pos.x] = MAZE_PATH;   
			return n;
		}

		pos.dir += 1;
		if ( pos.dir > 3 )
			pos.dir -= 4;
	}




	maze->map[pos.y][pos.x] = MAZE_PATH;

	return 0;
}




int solve(struct maze * maze) {
	struct pos pos;

	pos.x = maze->startx;
	pos.y = maze->starty;
	pos.dir = maze->initdir;

	return look(maze, pos);
}    


/*  Frees memory used by a maze  */

void FreeMaze(struct maze * maze) {
	int n;

	for ( n = 0; n < maze->numrows; ++n )
		free(maze->map[n]);

	free(maze->map);
}


void GetMazeFromFile(char * filename, struct maze * maze) {
	char buffer[BUFFERSIZE];
	FILE * fp;
	char ** map;
	int n = 0, foundentrance = 0, foundexit = 0;


	/*  Open file  */

	if ( !(fp = fopen(filename, "r")) ) {
		sprintf(buffer, "Couldn't open file %s", filename);
		perror(buffer);
		exit(EXIT_FAILURE);
	}


	/*  Determine number of rows in maze  */

	while ( fgets(buffer, BUFFERSIZE, fp) )
		++n;


	/*  Allocate correct number of rows  */

	if ( !(map = malloc(n * sizeof *map)) ) {
		fputs("Couldn't allocate memory for map\n", stderr);
		exit(EXIT_FAILURE);
	}


	/*  Reset file  */

	rewind(fp);
	n = 0;


	/*  Store each row  */

	while ( fgets(buffer, BUFFERSIZE, fp) ) {
		int i;

		if ( !(map[n] = malloc((strlen(buffer)+1) * sizeof map[n])) ) {
			fputs("Couldn't allocate memory for map\n", stderr);

			for ( i = 0; i < n; ++i )
				free(map[i]);

			free(map);

			exit(EXIT_FAILURE);
		}

		strcpy(map[n], buffer);


		/*  Remove trailing whitespace  */

		for ( i = strlen(map[n]) - 1; isspace(map[n][i]); --i )
			map[n][i] = 0;


		/*  Check for entrance and store position if found  */

		if ( !foundentrance ) {
			i = 0;
			while ( map[n][i] != 'I' && map[n][i++] );
			if ( map[n][i] == MAZE_ENTRANCE ) {
				maze->startx = i;
				maze->starty = n;
				foundentrance = 1;
			}
		}

		/*  Check for exit  */

		if ( !foundexit ) {
			if ( strchr(map[n], MAZE_EXIT) )
				foundexit = 1;
		}
		++n;
	}


	/*  Fill in maze structure  */

	maze->map = map;
	maze->numrows = n;


	/*  Exit if there is no entrance or no exit */

	if ( !foundentrance ) {
		fputs("Maze has no entrance!\n", stderr);
		FreeMaze(maze);
		exit(EXIT_FAILURE);
	}

	if ( !foundexit ) {
		fputs("Maze has no exit!\n", stderr);
		FreeMaze(maze);
		exit(EXIT_FAILURE);
	}


	/*  Check for initial direction into the maze  */

	if ( maze->startx < strlen(maze->map[maze->starty]) - 1 &&
			maze->map[maze->starty][maze->startx+1] == MAZE_PATH )
		maze->initdir = MOVE_RIGHT;
	else if ( maze->startx > 0 &&
			maze->map[maze->starty][maze->startx-1] == MAZE_PATH )
		maze->initdir = MOVE_LEFT;
	else if ( maze->starty > 0 &&
			maze->map[maze->starty-1][maze->startx] == MAZE_PATH )
		maze->initdir = MOVE_UP;
	else if ( maze->starty < (maze->numrows-1) &&
			maze->map[maze->starty+1][maze->startx] == MAZE_PATH )
		maze->initdir = MOVE_DOWN;


	/*  Close file and return  */

	if ( fclose(fp) ) {
		perror("Couldn't close file");
		FreeMaze(maze);
		exit(EXIT_FAILURE);
	}
}




/*  Outputs a maze  */

void PrintMaze(struct maze * maze) {
	int n;

	for ( n = 0; n < maze->numrows; ++n )
		puts(maze->map[n]);
}


int main(int argc, char *argv[]) {
	struct maze maze;

	if ( argc < 2 ) {
		puts("You must specify the filename of your maze");
		return EXIT_FAILURE;
	}
	else if ( argc > 2 ) {
		puts("Too many command line arguments");
		return EXIT_FAILURE;
	}

	GetMazeFromFile(argv[1], &maze);

	if ( solve(&maze) == MAZE_FOUNDEXIT )
		puts("Found exit!");
	else
		puts("Can't reach exit!");

	PrintMaze(&maze);
	FreeMaze(&maze);

	return EXIT_SUCCESS;
	getch();
}
