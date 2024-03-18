//
//TicTacToe
//by LeonardoTheMutant
//
//Basic TicTacToe game in C
//
//Version 2
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

//text
const char welcomeText[] = "Welcome to Tic-Tac-Toe!\nHold CTRL+C anytime to leave\n\nNumbers of cells:\n\n1|2|3\n-+-+-\n4|5|6\n-+-+-\n7|8|9";
const char selectPlayerText[] = "Select a number of the game type:";
const char playerText[] = "Player";
const char cellPrompt[] = "which cell number to make turn?";
const char quitText[] = "Press CTRL+C to quit";
const char pauseText[] = "Press SPACE+ENTER to continue...";
#ifdef _WIN32
const char CMDclear[] = "cls";
#else
const char CMDclear[] = "clear";
#endif
const char NoNumberText[] = "Type only numbers from 1 to 9!";
const char NoFreeCellText[] = "Type only numbers of free cells!";
const char winText[] = "won!";
const char tieText[] = "Tie!";
const char humanText[] = "Human";
const char vsText[] = "vs.";
const char computerText[] = "Computer";
char board[9] = {32,32,32, 32,32,32, 32,32,32}; //the clear board (by spaces)

//symbols
const char X = 88;
const char O = 79;
const char space = 32;
#ifdef _WIN32
const char bvborder = 186;
const char bhborder = 205;
const char tvborder = 179;
const char thborder = 196;
const char trcorner = 187;
const char brcorner = 188;
const char blcorner = 200;
const char tlcorner = 201;
const char tcross = 203;
const char bcross = 202;
const char lcross = 185;
const char rcross = 204;
const char cross = 197;
#else
const char bvborder = 124;
const char bhborder = 45;
const char tvborder = 124;
const char thborder = 45;
const char trcorner = 43;
const char brcorner = 43;
const char blcorner = 43;
const char tlcorner = 43;
const char tcross = 43;
const char bcross = 43;
const char lcross = 43;
const char rcross = 43;
const char cross = 43;
#endif

uint8_t turn = 1; //boolean, 0 - O, 1 - X
uint8_t cell;

void PAUSE() //pause and wait for user to press ENTER
{
	printf("%s\n", pauseText);
	char dummy;
	while (dummy != 32) dummy = getchar(); //system("pause") is not a solution
}
void RESET(char board[9]) //reset the game
{
	for (uint8_t i = 0; i < 9; i++) board[i] = space;
	cell=0;
	turn=1;
}

void game(char gametype);

void menu() //menu main
{
	system(CMDclear);
	printf("%s\n\n", welcomeText);
	printf("%s\n", selectPlayerText);
	printf("1 %s %s %s\n", humanText, vsText, computerText);
	printf("2 %s %s %s\n", computerText, vsText, humanText);
	printf("3 %s %s %s\n", computerText, vsText, computerText);
	printf("4 %s %s %s\n\n", humanText, vsText, humanText);
	uint8_t menuSelect;
	scanf("%hhu", &menuSelect);
	switch(menuSelect){ //game select
		case 1:
			game(1); //human vs com
			break;
		case 2:
			game(2); //com vs human
			break;
		case 3:
			game(3); //com vs com (3-value randomizer)
			break;
		case 4:
			game(4); // human vs human
			break;
		default:
			menu();
			break;
	}
}

void drawBoard() //draw the board
{
	system(CMDclear);
	printf("%c%c%c%c%c%c%c\n", tlcorner, bhborder, tcross, bhborder, tcross, bhborder, trcorner);     //top border
	printf("%c%c%c%c%c%c%c\n", bvborder, board[0], tvborder, board[1], tvborder, board[2], bvborder); //1st line
	printf("%c%c%c%c%c%c%c\n", rcross, thborder, cross, thborder, cross, thborder, lcross);           //border between 1st and 2nd lines
	printf("%c%c%c%c%c%c%c\n", bvborder, board[3], tvborder, board[4], tvborder, board[5], bvborder); //2nd line
	printf("%c%c%c%c%c%c%c\n", rcross, thborder, cross, thborder, cross, thborder, lcross);           //border between 2nd and 3rd lines
	printf("%c%c%c%c%c%c%c\n", bvborder, board[6], tvborder, board[7], tvborder, board[8], bvborder); //3rd line
	printf("%c%c%c%c%c%c%c\n\n", blcorner, bhborder, bcross, bhborder, bcross, bhborder, brcorner);   //bottom border
}
void prompt(uint8_t player) //ask for the cell to fill from HUMAN
{
	if (player) printf("%s %c %s\n", playerText, X, cellPrompt);
	else printf("%s %c %s\n", playerText, O, cellPrompt);
	cell = 0;
	scanf("%hhu", &cell);
	if((cell >= 1) && (cell <= 9) && (board[cell - 1] == 32))
	{
		if(player) board[cell-1]=X;
		else board[cell-1]=O;
		turn=!turn;
		return;
	}
	else if ((cell < 1) || (cell > 9)) printf("%s\n", NoNumberText);
	else if (board[cell - 1] != 32) printf("%s\n", NoFreeCellText);
	PAUSE();
	drawBoard();
	prompt(player);
}
void prompt2(uint8_t player) //let COMPUTER try to fill a cell
{
	do cell = rand() % 9; while(board[cell] != 32); //get random cell and fill it
	if (player) board[cell] = X;
	else board[cell] = O;
	turn = !turn;
}
void win(uint8_t winner)
{
	switch(winner)
	{
		case 1:
			printf("%s %c %s\n", playerText, O, winText);
			break;
		case 2:
			printf("%s %c %s\n", playerText, X, winText);
			break;
		case 0:
			printf("%s\n", tieText);
			break;
	}
	printf("%s\n", quitText);
	PAUSE();
	RESET(board);
}
void checkBoard() //check if board is filled or someone won
{
	drawBoard();
	uint8_t filled = 0;
	//count how many filled cells
	for(uint8_t cellnum = 0; cellnum < 9; cellnum++) if (board[cellnum] != space) filled++;
	//check for O
	if ((board[0] == O) && (board[1] == O) && (board[2] == O)) win(1);
	else if ((board[3] == O) && (board[4] == O) && (board[5] == O)) win(1);
	else if ((board[6] == O) && (board[7] == O) && (board[8] == O)) win(1);
	else if ((board[0] == O) && (board[3] == O) && (board[6] == O)) win(1);
	else if ((board[1] == O) && (board[4] == O) && (board[7] == O)) win(1);
	else if ((board[2] == O) && (board[5] == O) && (board[8] == O)) win(1);
	else if ((board[0] == O) && (board[4] == O) && (board[8] == O)) win(1);
	else if ((board[2] == O) && (board[4] == O) && (board[6] == O)) win(1);
	//check for X
	else if ((board[0] == X) && (board[1] == X) && (board[2] ==X)) win(2);
	else if ((board[3] == X) && (board[4] == X) && (board[5] ==X)) win(2);
	else if ((board[6] == X) && (board[7] == X) && (board[8] ==X)) win(2);
	else if ((board[0] == X) && (board[3] == X) && (board[6] ==X)) win(2);
	else if ((board[1] == X) && (board[4] == X) && (board[7] ==X)) win(2);
	else if ((board[2] == X) && (board[5] == X) && (board[8] ==X)) win(2);
	else if ((board[0] == X) && (board[4] == X) && (board[8] ==X)) win(2);
	else if ((board[2] == X) && (board[4] == X) && (board[6] ==X)) win(2);
	//check if board is filled
	else if (filled == 9) win(0);
}
void game(char gametype)
{
	while(1)
	{
		drawBoard();
		switch(gametype)
		{
			case 1: //human vs. com
				prompt(turn);
				checkBoard();
				prompt2(turn);
				break;
			case 2: //com vs. human
				prompt2(turn);
				checkBoard();
				prompt(turn);
				break;
			case 3: //com vs. com
				prompt2(turn);
				break;
			case 4: //human vs. human
				prompt(turn);
				break;
			case 10: //debug, print ASCII symbols (128-255)
				for (uint8_t i = 128; i <= 255; i++) printf("%d %c\n", i, i);
				exit(0);
			default: //if unknown gametype is given, just exit
				exit(-1);
				break;
		}
		checkBoard();
	}
}
int main(int argc, char *argv[])
{
	srand(time(0)); //init the random seed
	if (argc >= 2) game(strtol(argv[1], NULL, 0));
	else menu();
}
