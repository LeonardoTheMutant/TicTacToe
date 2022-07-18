/*
  TicTacToe
  by LeonardoTheMutant

  Basic TicTacToe game on C++
*/


#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

//text
const char welcomeText[]="Welcome to Tic-Tac-Toe!\nHold CTRL+C anytime to leave\n\nNumbers of cells:\n\n1|2|3\n-+-+-\n4|5|6\n-+-+-\n7|8|9";
const char selectPlayerText[]="Select type of new game:";
const char playerText[]="Player ";
const char cellPrompt[]=" which cell number to make turn?";
const char CMDpause[]="PAUSE";
const char CMDclear[]="CLS";
const char CMDsetresolution[]="MODE CON COLS=50 LINES=20";
const char NoNumberText[]="Type only 1-9 numbers!";
const char NoFreeCellText[]="Type only numbers of free cells!";
const char winText[]=" win!";
const char tieText[]="Tie!";
const char computerText[]="Computer";
const char vsText[]=" vs. ";
const char humanText[]="Human";
char board[9]={32,32,32, 32,32,32, 32,32,32}; //the clear board (by spaces)

//symbols
const char X=88;
const char O=79;
const char space=32;
const char bvborder=186;
const char bhborder=205;
const char tvborder=179;
const char thborder=196;
const char trcorner=187;
const char brcorner=188;
const char blcorner=200;
const char tlcorner=201;
const char tcross=209;
const char bcross=207;
const char lcross=182;
const char rcross=199;
const char cross=197;

bool turn=1; //0 - O, 1 - X
unsigned short cell=1;
unsigned short filled=0;

int parseInt(char symbol){
	return symbol - '0';
}
void RESET(char theboard[9]){ //reset the game
	theboard[0]=space;
	theboard[1]=space;
	theboard[2]=space;
	theboard[3]=space;
	theboard[4]=space;
	theboard[5]=space;
	theboard[6]=space;
	theboard[7]=space;
	theboard[8]=space;
	cell=0;
	turn=1;
}

void game(short gametype);

void menu(){ //main menu
	system(CMDsetresolution);
	cout << welcomeText << endl;
	cout << endl;
	cout << selectPlayerText << endl;
	cout << 1 << space << humanText << vsText << computerText << endl;
	cout << 2 << space << computerText << vsText << humanText << endl;
	cout << 3 << space << computerText << vsText << computerText << endl;
	cout << 4 << space << humanText << vsText << humanText << endl;
	int menuSelect=0;
	cin >> menuSelect;
	switch(menuSelect){ //game select
		case 1:
		    game(1); //human vs com
			break;
		case 2:
		    game(2); //com vs human
			break;
		case 3:
		    game(3); //com vs com, perfect coin flip simulator
			break;
		case 4:
		    game(4); // human vs human
			break;
		default:
		    menu();
			break;
	}
}
void drawboard(const char theboard[9]){ //draw the board
	system(CMDclear);
	cout << tlcorner << bhborder << tcross << bhborder << tcross << bhborder << trcorner << endl;              //top border
	cout << bvborder << theboard[0] << tvborder << theboard[1] << tvborder << theboard[2] << bvborder << endl; //1st line
	cout << rcross << thborder << cross << thborder << cross << thborder << lcross << endl;                    //border between 1st and 2nd lines
	cout << bvborder << theboard[3] << tvborder << theboard[4] << tvborder << theboard[5] << bvborder << endl; //2nd line
	cout << rcross << thborder << cross << thborder << cross << thborder << lcross << endl;                    //border between 2nd and 3rd lines
	cout << bvborder << theboard[6] << tvborder << theboard[7] << tvborder << theboard[8] << bvborder << endl; //3rd line
	cout << blcorner << bhborder << bcross << bhborder << bcross << bhborder << brcorner << endl;              //bottom border
	cout << endl;
}
void prompt(bool player){ //ask for cell to fill from HUMAN
	cell=0;
	if(player){ cout << playerText << X << cellPrompt << endl; }
	else{ cout << playerText << O << cellPrompt << endl; }
	cin >> cell;
	if(cell>=1 and cell<=9 and board[cell-1]==32){
		if(player){board[cell-1]=X;}
		else{board[cell-1]=O;}
		turn=!turn;
	}else{
		cout << NoFreeCellText << endl;
		system(CMDpause);
		drawboard(board);
		prompt(player);
	}
}
void prompt2(bool player){ //ask for cell to fill from COMPUTER
    do{
		cell=rand()%9; //get random cell
	}while(board[cell]!=32);
	if(player){board[cell]=X;}
	else{board[cell]=O;}
	turn=!turn;
}
short checkBoard(char theboard[9]){ //check if board is filled or someone won
    drawboard(theboard);
    filled=0;
    for(int cellnum=0; cellnum<9; cellnum++){ //count how many filled cells
		if (theboard[cellnum]!=space) filled++;
	}
	//check if board is filled
	if (filled==9){
		cout << tieText << endl;
		system(CMDpause);
		RESET(theboard);
		return 3;
	}
	//check for O
	if (theboard[0]==O && theboard[1]==O && theboard[2]==O){
		cout << playerText << O << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 1;
	}
	if (theboard[3]==O && theboard[4]==O && theboard[5]==O){
		cout << playerText << O << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 1;
	}
	if (theboard[6]==O && theboard[7]==O && theboard[8]==O){
		cout << playerText << O << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 1;
	}
	if (theboard[0]==O && theboard[3]==O && theboard[6]==O){
		cout << playerText << O << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 1;
	}
	if (theboard[1]==O && theboard[4]==O && theboard[7]==O){
		cout << playerText << O << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 1;
	}
	if (theboard[2]==O && theboard[5]==O && theboard[8]==O){
		cout << playerText << O << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 1;
	}
	if (theboard[0]==O && theboard[4]==O && theboard[8]==O){
		cout << playerText << O << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 1;
	}
	if (theboard[2]==O && theboard[4]==O && theboard[6]==O){
		cout << playerText << O << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 1;
	}
	//check for X
	if (theboard[0]==X && theboard[1]==X && theboard[2]==X){
		cout << playerText << X << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 2;
	}
	if (theboard[3]==X && theboard[4]==X && theboard[5]==X){
		cout << playerText << X << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 2;
	}
	if (theboard[6]==X && theboard[7]==X && theboard[8]==X){
		cout << playerText << X << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 2;
	}
	if (theboard[0]==X && theboard[3]==X && theboard[6]==X){
		cout << playerText << X << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 2;
	}
	if (theboard[1]==X && theboard[4]==X && theboard[7]==X){
		cout << playerText << X << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 2;
	}
	if (theboard[2]==X && theboard[5]==X && theboard[8]==X){
		cout << playerText << X << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 2;
	}
	if (theboard[0]==X && theboard[4]==X && theboard[8]==X){
		cout << playerText << X << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 2;
	}
	if (theboard[2]==X && theboard[4]==X && theboard[6]==X){
		cout << playerText << X << winText << endl << endl;;
		system(CMDpause);
		RESET(theboard);
		return 2;
	}
	return 0;
}
void game(short gametype){
	while(1){
		drawboard(board);
		switch(gametype){
			case 1:
			    prompt(turn);
				checkBoard(board);
				drawboard(board);
				prompt2(turn);
			    break;
			case 2:
			    prompt2(turn);
				checkBoard(board);
				drawboard(board);
				prompt(turn);
			case 3:
			    prompt2(turn);
				break;
			case 4:
			    prompt(turn);
				break;
			default: //if unknown gametype is given, just exit
			    exit(-1);
				break;
		}
		checkBoard(board);
	}
	
}

//driver code, empty though, I guess you should go check menu();
int main(){
	srand(time(0)); //init the random seed
	menu();
	return 0;
}