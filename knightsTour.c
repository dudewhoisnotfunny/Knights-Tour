#include <stdlib.h>
#include <stdio.h>

/* 	Point struct 
	models a point with an tag to identify it
*/
typedef struct{
	int x;
	int y;
	int moveid;
}point;

/*	validMoveSet struct
	a structure that holds all availble moves in an array 
	with a counter variable to tell how many there are
*/
typedef struct {
	point moves[8];
	int numOfMoves;

}validMoveSet;

int **createPond(int pondSize);
void commandLineErrorCheck(int numArgs, char *args[]);
void setMoveList(point moveList[]);
void findPath(int **pond, int pondSize, point moveList[], int numMoves, int x, int y, int i, int prevMove);
void printPond(int **pond, int pondSize);
validMoveSet *findValidMoves(point moveList[], int numMoves, int x, int y, int prevMove, int pondSize, int **pond);






int main (int argc, char *argv[] ){

	commandLineErrorCheck(argc, argv);//Error checking
	
	int **pond;
	
	int pondSize =  atoi(argv[1]);
	int startX = atoi(argv[2]);
	int startY = atoi(argv[3]);
	
	int numMoves = 8;//knight can have no more than 8 possible moves at a time
	point moveList[numMoves];
	
	setMoveList(moveList);//fill in array with all possible knight moves
	
	pond = createPond(pondSize);
	
	findPath(pond, pondSize, moveList, numMoves, startX, startY, 1, -1);
	//send in 1 to since first step, send in -1 since there was no prevMove
	
	printf("No Possible path");
	
	

}

/*	Find Path

	int **pond, the board the frog will hop on
	int pondSize, side length of the square pond
	point moveList[], array of all possible frog hops
	int numMoves, the number of hops in moveList[]
	int x, current x coordinate of the frog
	int y, current y coordinate of the frog
	int i, the number of pads landed on
	int prevMove the corresponding moveid of the previous move
	
	Prints a possible path for the frog to hop to each lily pad only hitting each lily pad once
	and never making the same move twice in a row
*/
	
void findPath(int **pond, int pondSize, point moveList[], int numMoves, int x, int y, int i, int prevMove){
	
	int j;
	pond[x][y] = i;
	
	validMoveSet *validMoves;

	
	if(i == pondSize*pondSize){
		printPond(pond, pondSize);
		exit(0);
		
	}else{

	
	validMoves = findValidMoves(moveList, numMoves, x, y, prevMove, pondSize, pond);
		
	for(j = 0; j < validMoves->numOfMoves; j++){
		
		findPath(pond, pondSize, moveList, numMoves, validMoves->moves[j].x, validMoves->moves[j].y, i+1, validMoves->moves[j].moveid);
	}
	free(validMoves);
	pond[x][y] = 0;
	}
	
	

}

/*	find valid moves

	point moveList[], array of all possible frog hops
	int numMoves, the number of hops in moveList[]
	int x, current x coordinate of the frog
	int y, current y coordinate of the frog
	int prevMove the corresponding moveid of the previous move
	int pondSize, side length of the square pond
	int **pond, the board the frog will hop on
	
	Checks to see out of all possible moves which are legal
	legal being
	A hop that doesnt land you outside the board
	A hop that doesnt land on a pad previously landed on
	A hop that is not the same as the previous hop
	
	returns a validMoveSet struct with all possible moves
	that could be made by the frog
*/
	
validMoveSet *findValidMoves(point moveList[], int numMoves, int x, int y, int prevMove, int pondSize, int **pond){

	int i;
	
	validMoveSet *validMoves = malloc(sizeof(validMoveSet));
	validMoves->numOfMoves = 0;
	
	for(i = 0; i < numMoves; i++){
	
		if(i != prevMove){
		
			if(x + moveList[i].x >= 0 && x + moveList[i].x < pondSize){
			
				if(y + moveList[i].y >= 0 && y + moveList[i].y < pondSize){
					
					if(pond[x + moveList[i].x][y + moveList[i].y] == 0){
						
						
						validMoves->moves[validMoves->numOfMoves].x = x + moveList[i].x;
						validMoves->moves[validMoves->numOfMoves].y = y + moveList[i].y;
						validMoves->moves[validMoves->numOfMoves].moveid = moveList[i].moveid;
						validMoves->numOfMoves++;
					}
				
				}
			}
			
		}
	
	}
	
	return validMoves;

}

/*	create pond
	
	int pondSize, side length of the pond
	
	Dynamically allocates a 2d square array with side length pondSize
	and sets all cells to 0
*/
int **createPond(int pondSize){

	int **pond = calloc(pondSize, sizeof(int *));
	int i;
	for(i = 0; i < pondSize; i++){
		pond[i] = calloc(pondSize, sizeof(int));
	}
	return pond;
}

/*	print pond

	int **pond, pond to be printed
	int pondSize, size of pond being printed
	
	Prints the pond so that all numbers are right justified
	ex:
	 1  2  3
	34 56 99
	 8 78 90
*/
void printPond(int **pond, int pondSize){
	
	int i, j;
	for(i = 0; i < pondSize; i++){
		for(j = 0; j < pondSize; j++){
			printf("%2d ", pond[i][j]);
		}
		printf("\n");
	}
}

/*	Command line error check

	checks if apropiate comand line arguments were entered
	if wrong argument was entered program exits and prints error
*/
void commandLineErrorCheck(int numArgs, char *args[]){

	if(numArgs != 4){
		fprintf(stderr,"Wrong Number of Command Line arguments");
		exit(1);
	}

	int pondSize = atoi(args[1]);
	
	if(pondSize <= 0 || pondSize > 9){
		fprintf(stderr,"Invalid Board size; must be between 1 - 9 (inclusive)");
		exit(2);
	}
	
	int x = atoi(args[2]), y = atoi(args[3]);
	
	if(x < 0 || x >= pondSize){
		fprintf(stderr,"X coordinate out of range");
		exit(3);
	}
	
	if(y < 0 || y >= pondSize){
		fprintf(stderr,"Y coordinate out of range");
		exit(4);
	}

}

/*	set move list

	an array containing all possible hops for the frog
	stored in the form of dx, dy
*/
void setMoveList(point moveList[]){
	
	moveList[0].x = 2;
	moveList[0].y = 1;
	moveList[0].moveid = 0;
	
	moveList[1].x = 2;
	moveList[1].y = -1;
	moveList[1].moveid = 1;
	
	moveList[2].x = -2;
	moveList[2].y = 1;
	moveList[2].moveid = 2;
	
	moveList[3].x = -2;
	moveList[3].y = -1;
	moveList[3].moveid = 3;
	
	moveList[4].x = 1;
	moveList[4].y = 2;
	moveList[4].moveid = 4;
	
	moveList[5].x = 1;
	moveList[5].y = -2;
	moveList[5].moveid = 5;
	
	moveList[6].x = -1;
	moveList[6].y = 2;
	moveList[6].moveid = 6;
	
	moveList[7].x = -1;
	moveList[7].y = -2;
	moveList[7].moveid = 7;


}