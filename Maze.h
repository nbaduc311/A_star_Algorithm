#ifndef Astar_H_
#define A star_H_

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define MAZE_SIZE 16	//the size of one dimension of Map
#define ROW MAZE_SIZE
#define COL MAZE_SIZE

//define directions
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

// Solver Constants used on mouse
#define LARGE_F MAZE_SIZE * MAZE_SIZE
#define START_X 0
#define START_Y 15


typedef struct Node {
	/* data fields */
	short row;
	short column;
	float f,g,h;

	struct Node* parent;
} Node;

void logmess(char* text);
void lognum(short i);

#endif /* A star_H_ */